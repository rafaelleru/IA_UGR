
#ifndef AGENT__
#define AGENT__

#include <string>
#include <vector> //para los regalos
#include <iostream>
#include <cstdlib>
#include "conexion.h"
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;


struct baliza{
	int x;
	int y;
	int x_real;
	int y_real; //y son las filas
};

/*class RegaloPersona{
private:
	char personaje;
	int regalo;
public:
	RegaloPersona(char p, int r);
	RegaloPersona& operator=(const RegaloPersona p);
};*/

struct RegaloPersona{
	char personaje;
	int objeto;
};


class Agent
{
public:
	Agent(){
		x_= 99;
		y_= 99;
		orientacion_=3;
		role_="PlYR";
		last_accion_=3;
		REINICIADO_=false;
		size_=200;
		for (int i=0;i<200;i++)
		    for(int j=0;j<200;j++){
		      mapa_entorno_[i][j]='?';
		      mapa_objetos_[i][j]='?';
					veces_pasadas[i][j] = 0;
		    }

		for (int i=0;i<100;i++)
		    for(int j=0;j<100;j++){
		      mapa_solucion_[i][j]='?';
				}
		baliza1 = baliza2 = false;
		ubicado = false;
		gire_derecha = false;
		media_vuelta = false;

		setRegalos();

	}

	enum ActionType
	{
	    actFORWARD, // avanzar
	    actTURN_L,  // Girar Izquierda
	    actTURN_R,  // Girar Derecha
	    actIDLE,    // No hacer nada
	    actPICKUP,  // Recoger un objeto
	    actPUTDOWN, // Soltar un objeto
	    actPUSH,    // Meter en la mochila
	    actPOP,     // Sacar de la mochila
	    actGIVE,	// Dar un objeto a un personaje
	    actTHROW	// Lanzar un objeto

	};



	void Perceive(Environment &env);
	bool Perceive_Remote(conexion_client &Cliente, Environment &env);
	void ActualizarInformacion(Environment *env);
	ActionType Think();
	void FixLastAction(Agent::ActionType x){last_accion_=x;};
	bool HayObstaculo(int fila, int col);
	bool HayObjeto(int fila, int col);
	bool RegaloApropiado();
	int getRegaloParaPersonaje(char personaje);
	bool HayPersonaje(int fila, int col);
	void setRegalos();
	void CuadraMatriz();

	char mapa_entorno_[200][200]; // mapa que muestra el tipo de terreno
	char mapa_objetos_[200][200]; // mapa que muestra los objetos que estan encima del terreno
	char mapa_solucion_[100][100]; // Mapa que almacena la solucion que el alumno propone
	int veces_pasadas[200][200];
	bool fin_muro_d, fin_muro_i;
	bool ubicado;
	bool gire_derecha;
	bool media_vuelta;
	RegaloPersona regalos[6];

	// Funciones de acceso a los datos
	void GetCoord(int &fila, int &columna, int &brujula){fila=y_;columna=x_;brujula=orientacion_;};

	void CapturaFilaColumnaPK (string mensaje, int &fila, int &columna);


private:
	//Variables de interaccion con el entorno grafico
	int size_;

	//SENSORES
	char VISTA_[10];
	char SURFACE_[10];
	bool REINICIADO_;
	string MENSAJE_;
	char EN_USO_;
	char MOCHILLA_[5];
	char PUNTUACION_[9];
	bool FIN_JUEGO_;
	char SALUD_;

	bool recorrerObst;
	bool baliza1, baliza2;
	baliza baliza_1, baliza_2;

	//Variables de estado
	int x_,y_, orientacion_;
	int last_accion_;
	string role_;

};

string ActionStr(Agent::ActionType);



#endif
