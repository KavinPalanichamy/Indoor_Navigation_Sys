#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        return 1;
    }
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(4568);  
    serverAddress.sin_addr.s_addr = inet_addr("10.2.1.223");  

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to the server");
        close(clientSocket);
        return 1;
    }

    std::cout<<"Hello";
    
    const char* message = "Hello, Server!";
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        perror("Error sending data to the server");
        close(clientSocket);
        return 1;
    }
  
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("Error receiving data from the server");
        close(clientSocket);
        return 1;
    }
    buffer[bytesRead] = '\0';

    std::cout << "Received from server: " << buffer << std::endl;
   
    close(clientSocket);

    return 0;
}