#include <iostream>
#include "model/client.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[]) {
    /* Seteo puerto e ip del server*/
    int port = 0;
    string ip = "127.0.0.1";

    /* Creo al cliente */
    Client* cliente1 = new Client();

    /* Para el manejo de errores */
    extern int errno;

    /* Configuracion del puerto
     * atoi() devuelve 0 si el parametro es invalido*/
    if (argc > 1)  port = atoi(argv[1]);
    if (port == 0) port = 1500;

    /* Menu de cliente */

    bool endloop=false, conectado=false;
    char keypressed;

    cout << "\033[2J\033[1;1H"; /* clear screen */
    do{
        cout << "*-----------------------*" << endl;
        cout << "! Bienvenido al cliente !" << endl;
        cout << "*-----------------------*" << endl << endl;
        cout << "\t1 .- Conectar al servidor" << endl;
        if (conectado == true){
            cout << "\t2 .- Enviar Mensaje" << endl;
            cout << "\t3 .- Chequear mensajes" << endl;
            cout << "\t4 .- Desconectar" << endl;
            cout << "\t5 .- Lorem Ipsum" << endl;
        }
        cout << "\t6 .- Salir" << endl << endl;
        cout << "Elije una opcion: ";
 
        cin >> keypressed;
 
        switch(keypressed)
        {

            case '1':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (!conectado) {
                cout << "Estableciendo la conexion con el servidor..." << endl << endl;
                    cliente1->connect_to_server(ip, port);
                    conectado = true;
                    break;
                } 
                cout << " Ud. ya se encuentra conectado al servidor " << endl << endl;
                break;
 


            case '2':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (conectado) {
                    int userSelected;
                    cout << "*-----------------------*" << endl;
                    cout << "!    Envio de mensajes   !" << endl;
                    cout << "*-----------------------*" << endl << endl;
                    cout << "Elija el destinatario" << endl << endl;
                    
                    cliente1->show_users_list();  /* implementar esto */
                    cin >> userSelected;
                    cliente1->send_message_to(userSelected); /* implementar esto */

                    break;
                    }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;
 


            case '3':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (conectado) {    
                    cout << "Solicitando mensajes al servidor..." << endl << endl;
                    cliente1->ask_for_messages(); /* implementar esto */
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;



            case '4':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (conectado) {
                    cliente1->disconnect();
                    cout << "Ud. Se ha desconectado del servidor" << endl << endl;
                    conectado = false;
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;



             case '5':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (conectado) {
                    cout << "*-----------------------*" << endl;
                    cout << "!      Lorem Ipsum      !" << endl;
                    cout << "*-----------------------*" << endl << endl;

                    /* Falta implementar el lorem */
                    
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;



            case '6':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                endloop=true;
                cliente1->disconnect();;
                conectado = false;
                delete cliente1;
                break;



            default:
                cout << "\033[2J\033[1;1H"; /* clear screen */
                cout << "Opcion no valida." << endl << endl;
                break;
        }
    }while(endloop!=true);

    
    return 0;
}
