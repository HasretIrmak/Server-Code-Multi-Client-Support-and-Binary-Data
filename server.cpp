#include <iostream>
#include <winsock2.h>
#include <thread> // For multithreading
#include <vector>

#pragma comment(lib, "ws2_32.lib") // Linking the Winsock library

using namespace std;

void handleClient(SOCKET clientSocket) {
    char buffer[1024];

    // Receive data from the client (binary data)
    int recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (recvSize == SOCKET_ERROR) {
        cout << "Recv failed" << endl;
        return;
    }

    // Process the incoming data
    cout << "Received binary data of size: " << recvSize << " bytes" << endl;

    // Send a response as binary data
    const char response[] = { 0x01, 0x02, 0x03, 0x04 };
    send(clientSocket, response, sizeof(response), 0);

    // Send a simple HTTP response
    const char *httpResponse =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Hello from server!";
    send(clientSocket, httpResponse, strlen(httpResponse), 0);

    // Cleanup
    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed" << endl;
        return 1;
    }

    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed" << endl;
        return 1;
    }

    // Set up the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on all network interfaces
    serverAddr.sin_port = htons(8080); // Use port 8080

    // Bind the socket to the address
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Bind failed" << endl;
        return 1;
    }

    // Start listening for incoming connections
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        cout << "Listen failed" << endl;
        return 1;
    }

    cout << "Waiting for connections..." << endl;

    // Accept client connections in an infinite loop
    while (true) {
        // Accept a client connection
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            cout << "Accept failed" << endl;
            continue;
        }

        cout << "Connection established!" << endl;

        // Handle each client in a separate thread
        thread(handleClient, clientSocket).detach();
    }

    // Cleanup
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
