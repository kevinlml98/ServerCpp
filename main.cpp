/**
 * @file floydwarshall.h
 * @version 1.0
 * @date 28/09/2020
 * @author kevinlml
 * @title ServidorCpp
 * @brief Recibe unos caracteres por medio de un socket.
*/


#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include "floydwarshall.h"
#define PORT 8080

using namespace std;

int main(){

    /// Creación del socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }


    /// Escuchar por la dirección ip y el puerto
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons( PORT );
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);

    ///Esperando una conexión del cliente
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    while(true) {

        ///Se acepta a concexión del cliente
        int clientSocket = accept(listening, (sockaddr *) &client, &clientSize);

        char host[NI_MAXHOST];      /// Nombre del cliente remoto
        char service[NI_MAXSERV];   /// Servicio (i.e. port) el cliente está encendido


        if (getnameinfo((sockaddr *) &client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
            cout << host << " connected on port " << service << endl;
        } else {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            cout << host << " connected on port " << ntohs(client.sin_port) << endl;
        }

        /// Acepta el mensaje
        char buf[4096]; /// char buf; Almacena los datos qe introdujo el cliente
        char *buffer; /// pointer buffer; Señala el recorrido de los nodos
        int *ruta; /// pointer ruta; Señala el valor de la ruta mas corta


        /// Instanciar la clase de FloydWarshall
        FloydWarshall fw;

        while (true) {


            int bytesReceived = recv(clientSocket, buf, 4096, 0);

            if (bytesReceived == -1) {
                cerr << "Error in recv(). Quitting" << endl;
                break;
            }

            if (bytesReceived == 0) {
                cout << "Client disconnected " << endl;
                break;
            }else {
                ///Llamar a la funcion sendShortDistance()
                buffer = fw.sendShortDistance(buf[0], buf[1]);
                /// Llamar a la funcion shortDistance()
                ruta = fw.shortDistance(buf[0],buf[1]);
                /// Eviar por el socket la ruta mas corta y el valor de la ruta;
                send(clientSocket, buffer, bytesReceived, 0);
                send(clientSocket, ruta, bytesReceived, 0);
            }

        }


        // Close the socket
        close(clientSocket);
    }
    return 0;
}
