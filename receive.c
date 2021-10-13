//
// Created by sergio on 10/10/21.
//

#include "receive.h"

void receive_conexions(int MAX_CHAR, int CUR_PORT_REC) {
    int tcp_sock;
    char *buffer = "Respuesta desde servidor";
    char line[MAX_CHAR];
    struct sockaddr_in server_addr, client_addr;

    // Se crea descriptor de archivo para socket
    if ((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ocurrio un error al crear socket");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(CUR_PORT_REC);

    // Se enlaza socket con direccion y puerto
    if (bind(tcp_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Ocurrio un eror en bind( )");
        exit(0);
    }

    // Se prepara para escuchar conexiones
    listen(tcp_sock, 5);

    int con_sock;
    socklen_t len;
    ssize_t len_buffer = (ssize_t)strlen(buffer);
    ssize_t n;

    while (1) {
        len = sizeof(client_addr);
        // Se acepta nueva conexion
        con_sock = accept(tcp_sock, (struct sockaddr*) &client_addr, &len);

        if (con_sock < 0) {
            perror("Ocurrio un error al aceptar comunicacion");
            exit(0);
        }

        while (1) {
            // Se recibe informacion desde socket, limitado a MAX_CHAR bytes
            n = read(con_sock, line, MAX_CHAR);

            if (n == 0){
                printf("servidor: cliente termino de enviar\n");
                close(con_sock);
                break;
            }

            printf("servidor: n=%ld bytes leidos; line=%s\n", n, line);
            //printf("Recibido: %s\n", line);

            // Se manda respuesta de servidor
            n = write(con_sock, buffer, len_buffer);
            if (n < 0) {
                perror("Ocurrio un error al escribir al socket");
                break;
            }
        }
    }
}