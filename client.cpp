#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed" << endl;
        return 1;
    }

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Socket creation failed" << endl;
        return 1;
    }

    // Set up the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Server port
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Connect to localhost

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Connection failed" << endl;
        return 1;
    }

    // Send binary data (e.g., 4 bytes)
    const char message[] = { 0x10, 0x20, 0x30, 0x40 };
    send(clientSocket, message, sizeof(message), 0);

    // Receive a response from the server
    int recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (recvSize == SOCKET_ERROR) {
        cout << "Recv failed" << endl;
        return 1;
    }

    cout << "Received binary data of size: " << recvSize << " bytes" << endl;

    // Cleanup
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
