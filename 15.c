//GO back Server
// GO_BACK SERVER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define WINDOW_SIZE 5

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int window_start = 0;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8080...\n");

    // Accept incoming connections and handle data
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        int packet;
        while (recv(new_socket, &packet, sizeof(packet), 0) > 0) {
            if (packet == -1) {
                // End of transmission signal received
                break;
            }

            // Process the received packet (e.g., store it, respond to it)
            printf("Received packet: %d\n", packet);

            // Send ACK for the received packet
            send(new_socket, &packet, sizeof(packet), 0);

            // Update the window start position
            window_start = packet + 1;
        }

        close(new_socket);
    }

    return 0;
}
