
//Distance vector client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8888

typedef struct DistanceVector {
    int node;
    int cost;
} DistanceVector;

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    DistanceVector dv;
    dv.node = 1;
    dv.cost = 0;

    while (1) {
        printf("Sending distance vector to server...\n");
        sendto(client_socket, &dv, sizeof(dv), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        sleep(5); // Send the distance vector periodically
    }

    close(client_socket);
    return 0;
