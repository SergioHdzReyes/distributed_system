//
// Created by sergio on 09/10/21.
//

#include <unistd.h>
#include "receive.h"
#include "send.h"

#define BASE_PORT 3000
#define MAX_PORTS 10
#define MAX_CHAR 256


int CUR_PORT_REC = 3000;

int search_app();

int main() {

    if (search_app()) { // Ya hay aplicaciones corriendo
        if ( fork()==0 ) {
            send_conexions(MAX_CHAR, CUR_PORT_REC, BASE_PORT);
        }
        /*if ( fork()==0 ) {
            receive_conexions(MAX_CHAR, CUR_PORT_REC);
            //printf("Termina procesar peticion\n");
            //exit(0);
        }*/
    } else {
        if ( fork()==0 ) {
            receive_conexions(MAX_CHAR, CUR_PORT_REC);
        }
    }

    while (1) {

    }

    return 0;
}

// 1 -> aplicacion corriendo
// 0 -> no hay aplicaciones
int search_app() {
    printf("Se comienza a buscar chat disponible...\n");

    int tcp_sock;
    struct sockaddr_in server_addr;
    int aux = 1, exists = 0;

    // Se crea descriptor de archivo para socket
    if ((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ocurrio un error al crear el socket");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    while (aux < MAX_PORTS) {
        server_addr.sin_port = htons(CUR_PORT_REC);

        // Se intenta conectar a servidor
        if (connect(tcp_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
            // Se cierra Socket
            shutdown (tcp_sock, SHUT_RDWR);
            close(tcp_sock);
            return exists;
        } else {
            exists = 1;
        }

        CUR_PORT_REC += 1;
        aux += 1; // Mantiene cantidad de aplicaciones escaneadas
    }

    printf("Se ha excedido el numero de conexiones disponibles(10)\nSaliendo...\n");
    exit(0);
}