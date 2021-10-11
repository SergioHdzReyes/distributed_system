//
// Created by sergio on 10/10/21.
//

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int tcp_sock, r;
    struct sockaddr_in server_addr;
    int SERVER_PORT = 50000;
    int bytes;
    int MAX = 256;
    char line[MAX], ans[MAX];

    // Se crea descriptor de archivo para socket
    if ((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ocurrio un error al crear el socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    // Se intenta conectar a servidor
    if (connect(tcp_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Ocurrio un error al conectar");
        return 1;
    }
    printf("Conectado al servidor\n");

    while (1) {
        bzero(line, MAX);

        printf("Enviar mensaje: ");
        fgets(line, MAX, stdin);
        line[strlen(line)-1] = 0; // kill \n at end

        if (line[0]==0) // exit if NULL line
            exit(0);

        // Se manda mensaje a servidor
        bytes = write(tcp_sock, line, MAX);
        printf("cliente: escrito n=%d; line=%s\n", bytes, line);

        // Se recibe respuesta de servidor
        bytes = read(tcp_sock, ans, MAX);
        printf("cliente: leido n=%d; dato=%s\n", bytes, ans);
    }

    return 0;
}