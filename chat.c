//
// Created by sergio on 09/10/21.
//

#include <ncurses.h>
#include <unistd.h>
#include <sys/shm.h>

#include "gui_tools.h"
#include "receive.h"
#include "send.h"

#define BASE_PORT 3000
#define MAX_PORTS 10
#define MAX_CHAR 256


int CUR_PORT_REC = 3000;

int search_app();

int main() {
    int *data_received = 0;
    int client_running = 0;

    // ftok to generate unique key
    key_t key = ftok("shrchat",1990);
    // shmget returns an identifier in shmid
    int shmid = shmget(key,sizeof(int),0666|IPC_CREAT);
    // shmat to attach to shared memory
    int *con_rec = shmat(shmid,(int*)0,0);
    *con_rec = 0;

    //draw_windows();
    //getch();
    initscr();

    if (search_app()) { // Ya hay aplicaciones corriendo
        if ( fork()==0 ) {
            printw("Nuevo fork, [receive_conexions]\n");
            receive_conexions(MAX_CHAR, CUR_PORT_REC, &data_received); // Servidor
        }
        if ( fork()==0 ) {
            printw("Nuevo fork, [send_conexions]\n");
            send_conexions(MAX_CHAR, CUR_PORT_REC, BASE_PORT); // Cliente
        }
        client_running = 1;
    } else {
        if ( fork()==0 ) {
            printw("Nuevo fork, [receive_conexions]\n");
            receive_conexions(MAX_CHAR, CUR_PORT_REC, &data_received); // Servidor
        }
        //wait_conexions();
    }
    refresh();

    while (1) {
        //printf("VALOR: %d", *con_rec);
        if (!client_running && (*con_rec == 1)) {
            if ( fork()==0 ) {
                printw("Nuevo fork, [send_conexions]\n");
                send_conexions(MAX_CHAR, CUR_PORT_REC, BASE_PORT); // Cliente
            }
            client_running = 1;
            draw_windows();
        }
    }

    endwin();
    return 0;
}

// 1 -> aplicacion corriendo
// 0 -> no hay aplicaciones
int search_app() {
    printw("Se comienza a buscar chat disponible...\n");

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
            printw("[search_app] Puerto disponible: %d\n", CUR_PORT_REC);
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

    printw("Se ha excedido el numero de conexiones disponibles(10)\nSaliendo...\n");
    exit(0);
}

void signal_data_received() {

}