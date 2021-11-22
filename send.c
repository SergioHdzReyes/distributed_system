//
// Created by sergio on 09/10/21.
//

#include "gui_tools.h"
#include "send.h"

void send_conexions(int MAX, int CUR_PORT_REC, int BASE_PORT) {
    int tcp_sock, r;
    struct sockaddr_in server_addr;
    int bytes, port;
    char line[MAX], ans[MAX];

    // Se crea descriptor de archivo para socket
    if ((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ocurrio un error al crear el socket");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (CUR_PORT_REC > BASE_PORT) { // Se esta ejecutando segunda aplicacion
        port = BASE_PORT;
    } else { // Se esta ejecutando la primera aplicacion
        port = CUR_PORT_REC+1;
    }
    server_addr.sin_port = htons(port);
    printw("[send_conexions] PUERTO: %d\n", port);

    // Se intenta conectar a servidor
    if (connect(tcp_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        //perror("Ocurrio un error al conectar");
        printw("Ocurrio un error al conectar");
        exit(0);
    }
    printw("Conectado al servidor\n");

    while (1) {
        bzero(line, MAX);

        printw("2-Enviar mensaje: ");
        fgets(line, MAX, stdin);
        line[strlen(line)-1] = 0; // kill \n at end

        /*if (line[0]==0) // exit if NULL line
            exit(0);*/

        // Se manda mensaje a servidor
        bytes = write(tcp_sock, line, MAX);
        //printf("cliente: escrito n=%d; line=%s\n", bytes, line);

        // Se recibe respuesta de servidor
        //bytes = read(tcp_sock, ans, MAX);
        //printf("cliente: leido n=%d; dato=%s\n", bytes, ans);
    }
}