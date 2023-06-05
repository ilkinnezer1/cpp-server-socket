#include <iostream>
#include <WinSock2.h>
#include <string>
#include <unistd.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSAData wsaData;
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "Failed to init winsocket" << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == INVALID_SOCKET){
        std::cerr << "Failed to create a socket" << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind the socket to an address and port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    // Define the port to send a request
    serverAddress.sin_port = htons(8080);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR){
        std::cerr << "Failed to bind a socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if(listen(serverSocket, SOMAXCONN) ==SOCKET_ERROR ){
        std::cerr << "Failed to listen on socket" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port: " << 8080 << std::endl;

    // Accept and handle incoming connection

    while(true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if(clientSocket == INVALID_SOCKET){
            std::cerr << "Failed to accept client connection" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }


        // Data receiving and handling
        char buffer [4096];
        ZeroMemory(buffer, sizeof(buffer));
        int byteRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if(byteRead  == SOCKET_ERROR){
            std::cerr << "Failed to receive a data from client" << std::endl;
            closesocket(clientSocket);
            continue;
        }

        // Initializing GET request
        std::string request(buffer);
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";

        // Send the response back to the client
        if(send(clientSocket, response.c_str(), response.size(), 0) == SOCKET_ERROR){
            std::cerr << "Failed to send response to the client" << std::endl;
        }

        // close the client socket
        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
