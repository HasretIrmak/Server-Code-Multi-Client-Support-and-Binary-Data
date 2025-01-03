# Multi-Client Server with Binary Data Transfer

This project demonstrates a simple multi-client server using Winsock in C++ that can handle binary data transfer between clients and the server. The server can accept multiple client connections concurrently by creating a new thread for each client. A simple HTTP response is also simulated in the server.

## Features

- **Multi-Client Support:** The server can handle multiple client connections simultaneously by creating new threads for each connection.
- **Binary Data Transfer:** Both the server and client can send and receive binary data.
- **HTTP Response Simulation:** The server sends a simple HTTP response after receiving the binary data.
- **Cross-Platform:** This project works on Windows systems with Winsock.

## Requirements

- A Windows machine (since the project uses Winsock).
- A C++ compiler (e.g., MSVC or MinGW).
- Visual Studio or any IDE supporting C++ development.

## How to Run

### 1. Server

1. **Compile the Server Code**:
   - Open a terminal (Command Prompt or PowerShell) and navigate to the directory where `server.cpp` is saved.
   - Compile using your C++ compiler:
     ```bash
     g++ server.cpp -o server -lws2_32
     ```

2. **Run the Server**:
   - In the terminal, run the server executable:
     ```bash
     server.exe
     ```
   - The server will start listening for client connections on port 8080.

### 2. Client

1. **Compile the Client Code**:
   - Open a terminal and navigate to the directory where `client.cpp` is saved.
   - Compile using your C++ compiler:
     ```bash
     g++ client.cpp -o client -lws2_32
     ```

2. **Run the Client**:
   - In the terminal, run the client executable:
     ```bash
     client.exe
     ```
   - The client will connect to the server running on `localhost` (127.0.0.1) and send binary data.

### Sample Interaction

1. **Server**: The server waits for client connections on port 8080. Once a client connects, the server processes the data and sends a response.
   
2. **Client**: The client connects to the server, sends 4 bytes of binary data, and waits for the server’s response.

### Example Output

- **Server**:
  ```bash
  Waiting for connections...
  Connection established!
  Received binary data of size: 4 bytes
