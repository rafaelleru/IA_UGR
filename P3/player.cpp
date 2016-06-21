#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;
const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

double Alfa_Beta(Environment &tablero, int player, int prof, int limite, int &acc,
  double alfa, double beta);

// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar
//MISCOSAS
/**
*
*
*
*
*
**/


  int cuenta3Hor(const Environment &tablero, int player){
    //cout << "Cuento 3 Horizontal: ";
    char cPlayer;
    int coincidencias = 0;
    if (player == 1) {
      cPlayer = '1';
    }else cPlayer = '0';

    for (size_t i = 0; i < 7; i++) {
      for (size_t j = 0; j < 5; j++) {
        if (  tablero.See_Casilla(i, j) == cPlayer && tablero.See_Casilla(i, j+1) == cPlayer
          && tablero.See_Casilla(i, j+2) == cPlayer) {
        coincidencias++;
        }
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }

  int cuenta2Hor(const Environment &tablero, int player){
    //cout << "Cuento 2 Horizontal: ";
    char cPlayer;
    int coincidencias = 0;
    if (player == 1) {
      cPlayer = '1';
    }else cPlayer = '0';

    for (size_t i = 0; i < 7; i++) {
      for (size_t j = 0; j < 6; j++) {
        if (  tablero.See_Casilla(i, j) == cPlayer && tablero.See_Casilla(i, j+1) == cPlayer) {
        coincidencias++;
        }
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }


  int cuenta3Vert(const Environment &tablero, int player){
    //cout << "Cuento 3 Vertical: ";
    char cPlayer;
    int coincidencias = 0;
    if (player == 1) {
      cPlayer = '1';
    }else cPlayer = '0';

    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 7; j++) {
        if (  tablero.See_Casilla(i, j) == cPlayer && tablero.See_Casilla(i+1, j) == cPlayer
          && tablero.See_Casilla(i+2, j) == cPlayer) {
        coincidencias++;
        }
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }

  int cuenta2Vert(const Environment &tablero, int player){
    //cout << "Cuento 2 Vertical: ";
    char cPlayer;
    int coincidencias = 0;
    if (player == 1) {
      cPlayer = '1';
    }else cPlayer = '0';

    for (size_t i = 0; i < 6; i++) {
      for (size_t j = 0; j < 7; j++) {
        if (  tablero.See_Casilla(i, j) == cPlayer && tablero.See_Casilla(i+1, j) == cPlayer) {
        coincidencias++;
        }
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }


  //Las diagonales, la movida.


  int cuenta3Diag(const Environment &tablero, int player){
    //cout << "Cuento 3 Diagonal: ";
    char cPlayer;
    int coincidencias = 0;
    if (player == 1) {
      cPlayer = '1';
    }else cPlayer = '0';

    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        if(tablero.See_Casilla(i, j) == cPlayer && tablero.See_Casilla(i+1, j+1) == cPlayer &&
          tablero.See_Casilla(i+2, j+2) == cPlayer)
          coincidencias++;
      }
    }

    //coincidencias pal otro lao
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 7; j > 2; j--) {
        if(tablero.See_Casilla(i, j) == cPlayer && tablero.See_Casilla(i+1, j-1) == cPlayer &&
          tablero.See_Casilla(i+2, j-2) == cPlayer)
          coincidencias++;
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }

  //cuento los cuadrados de 3 x 3 que hay en el tablero
  //Buscamos los casos en los que el tablero contiene posiciones de fichas 
  //que contengan cosas del tipo:
  //* * * * * * *
  //* * * * * * *
  //* * * * * * *
  //1 1 1 * * * 2
  //1 1 1 * * * 1
  //1 1 1 2 2 * 1
  int cuentaCuadrados3(const Environment &tablero, int player){
  	//cout << "Cuento los cuadrados de 3 fichas que hay";
  	char cPlayer;
    int coincidencias = 0;
    if (player == 1) {
      cPlayer = '1';
    }else cPlayer = '0';

    for (size_t i = 0; i < 4; i++){
    	for (int j = 0; j < 4; j++){
    		for (int k = 0; k < 2; k++){
    			for (int l = 0; l < 2; l++){
    				if(tablero.See_Casilla(i,j) == tablero.See_Casilla(k, l))
    					coincidencias++;
    			}
    		}
    	}
    }

    return coincidencias;
  }

  int cuenta2Diag(const Environment &tablero, int player){
    cout << "Cuento 2 Diagonal: ";
    char cPlayer;
    int coincidencias = 0;
    if (player == 1) {
      cPlayer = '1';
    }else cPlayer = '0';

    for (size_t i = 0; i < 6; i++) {
      for (size_t j = 0; j < 6; j++) {
        if(tablero.See_Casilla(i, j) == cPlayer && tablero.See_Casilla(i+1, j+1) == cPlayer)
          coincidencias++;
      }
    }

    //coincidencias pal otro lao
    for (size_t i = 0; i < 7 ; i++) {
      for (int j = 0; j > 1; j++){
        if(tablero.See_Casilla(i, j) == cPlayer && tablero.See_Casilla(i+1, j-1) == cPlayer)
          coincidencias++;
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }



// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){

  int ganador = estado.RevisarTablero();

  if (ganador==jugador)
     return 99999999.0; // Gana el jugador que pide la valoracion
  else if (ganador!=0)
          return -99999999.0; // Pierde el jugador que pide la valoracion
  else if (estado.Get_Casillas_Libres()==0)
          return 0;  // Hay un empate global y se ha rellenado completamente el tablero
  else{
    double valoracion4, valoracion3, valoracion2,valoracion4o, valoracion3o, valoracion2o,  valoracion_total,
            valoracion_bomba, valoracion_bomba_o, valoracionCuad_o, valoracionCuad;

    //valoracion4 = (cuenta4Vert(estado, jugador) + cuenta4Hor(estado, jugador) + cuenta4Diag(estado, jugador))*1000;
    cout << "Cuento 3 mias" << endl;
    valoracion3 = (cuenta3Vert(estado, jugador) + cuenta3Hor(estado, jugador) + cuenta3Diag(estado, jugador))*100;
    cout << "Cuento 2 mias" << endl;
    valoracion2 = (cuenta2Vert(estado, jugador) + cuenta2Hor(estado, jugador) + cuenta2Diag(estado, jugador))*10;
    valoracionCuad = cuentaCuadrados3(estado, jugador)*100;
    if(estado.Have_BOOM(jugador)){
      valoracion_bomba = 500;
    }

    //jugadas que me "penalizan"
    //valoracion4o = (cuenta4Vert(estado, (jugador+1)%2) + cuenta4Hor(estado, (jugador+1)%2) + cuenta4Diag(estado, (jugador+1)%2))*1000;
    cout << "Cuento 3 de el" << endl;
    valoracion3o = (cuenta3Vert(estado, (jugador+1)%2) + cuenta3Hor(estado, (jugador+1)%2) + cuenta3Diag(estado, (jugador+1)%2))*1000;
    cout << "Cuento 2 de el" << endl;
    valoracion2o = (cuenta2Vert(estado, (jugador+1)%2) + cuenta2Hor(estado, (jugador+1)%2) + cuenta2Diag(estado, (jugador+1)%2))*100;
    //Cuento sus cuadrados de 3x3, son muy potenciales de que provoquen un 4 en raya.
    valoracionCuad_o = cuentaCuadrados3(estado, (jugador+1)%2);
    if(estado.Have_BOOM((jugador+1)%2))
      valoracion_bomba_o = 100;
    //Pongo la valoracion del contrario?¿

    valoracion_total = valoracion3o + valoracion2o + valoracion_bomba_o + valoracionCuad_o -
                      - valoracion3 - valoracion2 - valoracion_bomba - valoracionCuad;
    cout << "valoracion: " << valoracion_total;
    return valoracion_total;
  }
}





// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}






// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){


    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    //--------------------- COMENTAR Desde aqui
    /*cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }
        */
    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    // valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
    valor = Alfa_Beta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, n_act, alpha, beta);
    //if (accion == Environment::ActionType::BOOM) {
      //accion = Environment::ActionType::PUT7;

    //}

    accion = static_cast <Environment::ActionType> (n_act);
    cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
    return accion;
}

double Alfa_Beta(Environment &tablero, int player, int prof, int limite, int &acc,
  double alfa, double beta){
    //cout << "\nPODANDO VOY";
    double valoracion;
    Environment hijo;
    Environment::ActionType accion;
    int contador, kk;
    bool noparo = true;
    int ultacc = -1;

    //priifundidad maxima => valoracion tablero
    if(prof == limite || tablero.JuegoTerminado()){
      return Valoracion(tablero, player);
    }else{

      hijo = tablero.GenerateNextMove(ultacc);
      if(prof%2 == 0){
        //cout << "Nodou MAX, busco mi maximo beneficio" << endl << flush;

        while (ultacc<8 and beta>alfa) {
          valoracion = Alfa_Beta(hijo, player, prof+1, limite, kk, alfa, beta);

          //cambios en los parametros alfa beta
          if(valoracion > alfa){
            alfa = valoracion;
            acc = ultacc;
            //almaceno la accion mejor
            //accion = static_cast <Environment::ActionType> (ultacc);
          }

          hijo = tablero.GenerateNextMove(ultacc);
        }
        return alfa;
      }else{
        //cout << "Nodo MIN, busco el minimo beneficio para el rival" << endl << flush;

        while (ultacc<8 and beta>alfa) {
          valoracion = Alfa_Beta(hijo, player, prof+1, limite, kk, alfa, beta);

          //cambios en los parametros alfa beta
          if(valoracion < beta){
            beta = valoracion;
            acc = ultacc;
            //almaceno la accion mejor
            //accion = static_cast <Environment::ActionType> (ultacc);
          }

          hijo = tablero.GenerateNextMove(ultacc);
        }
        return beta;
      }
    }

  }

  /*int detonaBOOM(Environment &estado, int player){
    if(player = 0)
      char bomba = '4';
    else char bomba = '5';

    int casillafil, casillacol;

    for (size_t i = 0; i < 7; i++) {
      for (size_t j = 0; j < 7; j++) {
        if(estado.See_Casilla(i, j) == bomba){
          casillafil = i;
          casillacol = j;
        }
      }
    }

    Environment aux = estado;

  }*/
