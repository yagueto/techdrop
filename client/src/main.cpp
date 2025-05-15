// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <cstdio>
#include <iostream>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

char menu()
{
	printf("\n");
	printf("Elige la OPCION que desees: \n");
	printf("1. Sumar (2 + 3 + 5) \n");
	printf("2. Raiz cuadrada (9) \n");
	printf("3. Obtener IP del servidor \n");
	printf("4. Salir \n\n");
	printf("Opcion: ");
	char opcion = getchar();

	char c; while ((c = getchar()) != '\n' && c != EOF); // Vac�a el buffer de entrada

	return opcion;
}


int main(int argc, char *argv[])
{

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	//SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	char c;
	do
	{
		c = menu();
		if (c == '1')
		{
			// SENDING command SUMAR and parameters to the server
			strcpy(sendBuff, "1\\SUMAR\0");
			send(s, sendBuff, strlen(sendBuff), 0);
			strcpy(sendBuff, "2");
			send(s, sendBuff, strlen(sendBuff), 0);
			strcpy(sendBuff, "3");
			send(s, sendBuff, strlen(sendBuff), 0);
			strcpy(sendBuff, "5");
			send(s, sendBuff, strlen(sendBuff), 0);
			strcpy(sendBuff, "SUMAR-END\0");
			send(s, sendBuff, strlen(sendBuff), 0);

			// RECEIVING response to command SUMAR from the server
			int result = recv(s, recvBuff, sizeof(recvBuff), 0);
			if (result > 0) {
				std::cerr << "Suma: " << recvBuff << std::endl;
			} else {
				std::cerr << "edf: " << WSAGetLastError << std::endl;
			}
		}

		if (c == '2')
		{
			// SENDING command RAIZ and parameter to the server
			strcpy(sendBuff, "RAIZ");
			send(s, sendBuff, strlen(sendBuff), 0);
			strcpy(sendBuff, "9");
			send(s, sendBuff, strlen(sendBuff), 0);
			strcpy(sendBuff, "RAIZ-END");
			send(s, sendBuff, strlen(sendBuff), 0);

			// RECEIVING response to command RAIZ from the server
			recv(s, recvBuff, strlen(recvBuff), 0);
			printf("Raiz cuadrada = %s \n", recvBuff);
		}

		if (c == '3')
		{
			// SENDING command IP
			strcpy(sendBuff, "IP");
			send(s, sendBuff, strlen(sendBuff), 0);
			strcpy(sendBuff, "IP-END");
			send(s, sendBuff, strlen(sendBuff), 0);

			// RECEIVING response to command IP from the server
			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("IP del servidor = %s \n", recvBuff);
		}

		if (c == '4')
		{
			// SENDING command EXIT
			strcpy(sendBuff, "EXIT");
			send(s, sendBuff, strlen(sendBuff), 0);
		}
	}while(c != '4');

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
