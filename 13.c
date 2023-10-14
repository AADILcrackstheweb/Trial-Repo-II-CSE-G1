//distance vector server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8888
#define MAX_NODES 10
#define INFINITY 9999

typedef struct DistanceVector {
    int node;
    int cost;
} DistanceVector;

typedef struct RoutingTable {
    int nodes[MAX_NODES];
    int costs[MAX_NODES];
    int num_nodes;
} RoutingTable;

void initializeRoutingTable(RoutingTable *rt, int self_node) {
    rt->num_nodes = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        rt->nodes[i] = -1;
        rt->costs[i] = INFINITY;
    }
    rt->nodes[0] = self_node;
    rt->costs[0] = 0;
    rt->num_nodes = 1;
}

void updateRoutingTable(RoutingTable *rt, DistanceVector *dv) {
    int updated = 0;
    for (int i = 0; i < rt->num_nodes; i++) {
        if (rt->nodes[i] == dv->node) {
            if (rt->costs[i] > dv->cost + rt->costs[0]) {
                rt->costs[i] = dv->cost + rt->costs[0];
                updated = 1;
            }
        }
    }
    if (!updated) {
        rt->nodes[rt->num_nodes] = dv->node;
        rt->costs[rt->num_nodes] = dv->cost + rt->costs[0];
        rt->num_nodes++;
    }
}

void printRoutingTable(RoutingTable *rt) {
    printf("Routing Table:\n");
    for (int i = 0; i < rt->num_nodes; i++) {
        printf("Node %d -> Cost %d\n", rt->nodes[i], rt->costs[i]);
    }
}

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[1024];

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in binding");
        exit(1);
    }

    printf("Server is listening on port %d\n", PORT);

    RoutingTable rt;
    int self_node = 1;
    initializeRoutingTable(&rt, self_node);

    while (1) {
        DistanceVector dv;
        addr_size = sizeof(new_addr);

        int bytes_received = recvfrom(server_socket, &dv, sizeof(dv), 0, (struct sockaddr *)&new_addr, &addr_size);
        if (bytes_received < 0) {
            perror("Error in receiving data");
            exit(1);
        }

        // Update the routing table with the received distance vector
        updateRoutingTable(&rt, &dv);

        // Print the updated routing table
        printRoutingTable(&rt);
    }

    close(server_socket);
    return 0;
}
