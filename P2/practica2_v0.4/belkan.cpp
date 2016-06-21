///RAFA LEYVA RUIZ

#include "belkan.h"
#include "conexion.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;


int ESTORBO = 10000000;
int CICLO = 0;
int giros = 0;
bool atasco = false;


//nota mental: Comentar all the codigo

void PasarVectoraMapaSolucion(int fila, int columna, char m[100][100], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	  case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
    break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

    break;
    }

}

// -----------------------------------------------------------
void PasarVectoraMapaCaracteres(int fila, int columna, char m[200][200], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	  case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
    break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

    break;
    }

}


// -----------------------------------------------------------
void Agent::Perceive(Environment &env)
{
	env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, false);

}


bool Agent::Perceive_Remote(conexion_client &Cliente, Environment &env)
{
	bool actualizado=false;


	actualizado = env.Perceive_Remote(Cliente);
	if (actualizado)
		env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, true);

    return actualizado;
}


// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	case Agent::actPICKUP: return "PICK UP";
	case Agent::actPUTDOWN: return "PUT DOWN";
	case Agent::actPUSH: return "PUSH";
	case Agent::actPOP: return "POP";
	case Agent::actGIVE: return "GIVE";
	case Agent::actTHROW: return "THROW";
	default: return "????";
	}
}

// -----------------------------------------------------------
void Agent::ActualizarInformacion(Environment *env){
	// Actualizar mi informacion interna
	if (REINICIADO_){
    for (int i=0;i<200;i++)
        for(int j=0;j<200;j++){
          mapa_entorno_[i][j]='?';
          mapa_objetos_[i][j]='?';
        }

      for(int i=0; i<100; i++)
        for(int j=0; j<100;j++)
          veces_pasadas[i][j] = 0;

      baliza1 = false;
      baliza2 = false;
      ubicado = false;
	}

	switch(last_accion_){
	  case 0: //avanzar
	  switch(orientacion_){
	    case 0: // norte
		    y_--;
		    break;
	    case 1: // este
		    x_++;
		    break;
	    case 2: // sur
		    y_++;
		    break;
	    case 3: // este
		    x_--;
		    break;
	  }
	  break;
	  case 1: // girar izq
		  orientacion_=(orientacion_+3)%4;
		  break;
	  case 2: // girar dch
		  orientacion_=(orientacion_+1)%4;
		  break;
	}
  CICLO++;
  veces_pasadas[y_][x_] = CICLO;
  cout << "en la casilla " << y_ << " " << x_ << " he estado en el paso: " << CICLO << endl;
  cout << "la matriz veces pasadas en " << y_ << " " << x_ << " vale: " << veces_pasadas[y_][x_] << endl;

  mapa_entorno_[x_][y_] = VISTA_[0];
  //Switch para almacenar en la variable mapa_entorno la vista del agente..
  switch (orientacion_) {
    case 0:
      //siguiente casilla, justo la que hay delante de el AGENTE
      mapa_entorno_[x_][y_-1] = VISTA_[1];

      //segunda fila de lo que ve el AGENTE
      for (size_t i = 0; i < 3; i++) {
        for (size_t j = x_-1; j <= x_+1; j++) {
          mapa_entorno_[j][y_-2] = VISTA_[2+i];
        }
      }

      //tercera fila de lo que ve el AGENTE
      for (size_t i = 0; i < 5; i++) {
        for (size_t j = x_-2; j <= x_+2; j++) {
          mapa_entorno_[j][y_-3] = VISTA_[5+i];
        }
      }

    break;

    //este
    case 1:
    //siguiente casilla, justo la que hay delante de el AGENTE
    mapa_entorno_[x_+1][y_] = VISTA_[1];

    //segunda fila de lo que ve el AGENTE
    for (size_t i = 0; i < 3; i++) {
      for (size_t j = y_-1; j <= y_+1; j++) {
        mapa_entorno_[x_+1][j] = VISTA_[2+i];
      }
    }

    //tercera fila de lo que ve el AGENTE
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = y_-2; j <= y_+2; j++) {
        mapa_entorno_[x_+2][j] = VISTA_[5+i];
      }
    }

    break;

    //sur
    case 2:
    //siguiente casilla, justo la que hay delante de el AGENTE
    mapa_entorno_[x_][y_+1] = VISTA_[1];

    //segunda fila de lo que ve el AGENTE
    for (size_t i = 0; i < 3; i++) {
      for (size_t j = x_-1; j <= x_+1; j++) {
        mapa_entorno_[j][y_+2] = VISTA_[2+i];
      }
    }

    //tercera fila de lo que ve el AGENTE
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = x_-2; j <= x_+2; j++) {
        mapa_entorno_[j][y_+3] = VISTA_[5+i];
      }
    }
    break;

    //Oeste
    case 3:
    //siguiente casilla, justo la que hay delante de el AGENTE
    mapa_entorno_[x_-1][y_] = VISTA_[1];

    //segunda fila de lo que ve el AGENTE
    for (size_t i = 4; i >= 2 ; i--) {
      for (int j = y_-1; j <= y_+1; j++) {
        mapa_entorno_[x_-2][j] = VISTA_[i];
      }
    }

    //tercera fila de lo que ve el AGENTE
    for (size_t i = 9; i >= 5; i--) {
      for (int j = y_-2; j <= y_+2; j++) {
        mapa_entorno_[x_-3][j] = VISTA_[i];
      }
    }
    break;
  }

  /*Actualizacion del mapa de objetos y personajes moviles, otra vez lo mismo que la vista.*/
  if(SURFACE_[0] != '?')
    mapa_objetos_[y_][x_] == SURFACE_[0];

  switch (orientacion_) {
    case 0:
      if(SURFACE_[0] != '?')
        mapa_objetos_[y_-1][x_] = SURFACE_[1];

      for (size_t i = 0; i < 3; i++) {
        for (size_t j = x_-1; j <= x_+1; j++) {
          if (SURFACE_[2+i] !=  '?') {
            mapa_objetos_[y_-2][j] == SURFACE_[2+i];
          }
        }
      }

      for (size_t i = 0; i < 5; i++) {
        for (size_t j = x_-2; j <= x_+2; j++) {
          if (SURFACE_[5+i] !=  '?') {
            mapa_objetos_[y_-3][j] == SURFACE_[5+i];
          }
        }
      }
      break;
      case 1:
      if(SURFACE_[0] != '?')
        mapa_objetos_[y_][x_+1];

      for (size_t i = 0; i < 3; i++) {
        for (size_t j = y_-1; j <= y_+1; j++) {
            if (SURFACE_[2+i] !=  '?') {
              mapa_objetos_[j][x_+2] == SURFACE_[2+i];
            }
          }
      }

      for (size_t i = 0; i < 5; i++) {
        for (size_t j = y_-2; j <= y_+2; j++) {
          if (SURFACE_[5+i] !=  '?') {
            mapa_objetos_[j][x_+3] == SURFACE_[5+i];
          }
        }
      }
      break;
        mapa_objetos_[x_][y_+1] = SURFACE_[1];

      for (size_t i = 0; i < 3; i++) {
        for (size_t j = x_-1; j <= x_+1; j++) {
          if (SURFACE_[2+i] !=  '?') {
            mapa_objetos_[y_+2][j] == SURFACE_[2+i];
          }
        }
      }

      for (size_t i = 0; i < 5; i++) {
        for (size_t j = x_-2; j <= x_+2; j++) {
          if (SURFACE_[5+i] !=  '?') {
            mapa_objetos_[y_+3][j] == SURFACE_[5+i];
          }
        }
      }
      break;
      case 3:

        //siguiente casilla, justo la que hay delante de el AGENTE
        mapa_entorno_[x_-1][y_] = VISTA_[1];

        //segunda fila de lo que ve el AGENTE
        for (size_t i = 4; i >= 2 ; i--) {
          for (int j = y_-1; j <= y_+1; j++) {
            if(SURFACE_[i] != '?')
              mapa_entorno_[x_-2][j] = SURFACE_[i];
          }
        }

        //tercera fila de lo que ve el AGENTE
        for (size_t i = 9; i >= 5; i--) {
          for (int j = y_-2; j <= y_+2; j++) {
            if(SURFACE_[i] != '?')
              mapa_entorno_[x_-3][j] = SURFACE_[i];
          }
        }
      break;
  }

	// Comprobacion para no salirme del rango del mapa
	bool algo_va_mal=false;
	if (y_<0){
		y_=0;
		algo_va_mal=true;
	}
	else if (y_>199){
		y_=199;
		algo_va_mal=true;
	}
	if (x_<0){
		x_=0;
		algo_va_mal=true;
	}
	else if (x_>199){
		x_=199;
		algo_va_mal=true;
	}

	if (algo_va_mal){
		cout << "CUIDADO: NO ESTAS CONTROLANDO BIEN LA UBICACION DE TU AGENTE\n";
	}


	PasarVectoraMapaCaracteres(y_,x_,mapa_entorno_,VISTA_,orientacion_);
	PasarVectoraMapaCaracteres(y_,x_,mapa_objetos_,SURFACE_,orientacion_);
  PasarVectoraMapaSolucion(y_%100, x_%100, mapa_solucion_, VISTA_, orientacion_);

	env->ActualizarMatrizUsuario(mapa_entorno_);

}

int minimo(int izda, int frente, int dcha){
  cout << "Paso nº: " << CICLO << endl;
  cout << "a la izquierda hay: " << izda <<
  "en frente hay: " << frente << "y a la derecha: " << dcha << endl;

/*  if( frente == izda && izda == dcha && frente == ESTORBO){
    return 2;
  }*/

  if(frente <= izda && frente <= dcha){
    if(frente != ESTORBO)
      return 0;
    else{ return 1; atasco = true;}
  }else if( izda <= dcha)
    return 1;
  else return 2;
}


void Agent::CuadraMatriz(){
  int f1,f2,c1,c2;
  f1=baliza_1.y_real-baliza_2.y_real;
  f2=baliza_1.y - baliza_2.y;
  c1=baliza_1.x_real-baliza_2.x_real;
  c2=baliza_1.x - baliza_2.x;
  char m[200][200];
  if (f1==f2){
    cout << "estoy bien orientada "<<endl;
  for (int f=0; f<200;f++){
      for(int c=0; c<200;c++)
        m [f][c]=mapa_entorno_[f][c];
    }
  }else if (f1== -f2){
    cout << "estoy boca abajo"<<endl;
    for (int f=0; f<200;f++){
      for(int c=0; c<200;c++)
        m [f][c]=mapa_entorno_[199-f][199-c];
    }

    baliza_2.y=199-baliza_2.y;
    baliza_2.x=199-baliza_2.x;
    orientacion_=(orientacion_+2)%4;

  }else if (f1==c2){
    cout << "debo rotar 90 grados a la izquierda"<<endl;
    for (int f=0; f<200;f++){
      for(int c=0; c<200;c++)
        m [f][c]=mapa_entorno_[c][199-f];
    }
    // fila auxiliar para no perder el valor de mypk2f
    int fil_aux = baliza_2.y;

    baliza_2.y=199-baliza_2.x;
    baliza_2.x=fil_aux;
    orientacion_=(orientacion_+3)%4;

  }else if (f1==-c2){
    cout <<"debo rotar 90 grados a la derecha"<<endl;
    for (int f=0; f<200;f++){
      for(int c=0; c<200;c++)
        m [f][c]=mapa_entorno_[199-c][f];
    }

    int fil_aux = baliza_2.y;
    baliza_2.y=baliza_2.x;
    baliza_2.x=199-fil_aux;
    orientacion_=(orientacion_+1)%4;
  }
  //borro la matriz mapa entorno
  for (int f=0; f<200;f++){
      for(int c=0; c<200;c++)
        mapa_entorno_ [f][c]='?';

  }
  //desplazo la matriz a las primeras 100 filas y 100 columnas de mapa_entorno
  for (int f=0; f<100;f++){
      for(int c=0; c<100;c++){
        cout << "Poniendo crema la matriz" << endl;
        mapa_entorno_ [f][c]=m[f+baliza_2.y-baliza_2.y_real][c+baliza_2.x-baliza_2.x_real];
  }
}
  x_=baliza_2.x;
  y_=baliza_2.y;

  //poner la matriz en su lugar correcto.
  /*cout << "ya he corregido la orieentacion" << endl;
  for (size_t i = 0; i < 200; i++) {
    for (size_t j = 0; j < 200; j++) {
      cout << "estoy poniendo las cosas en su sitio" << endl;
     mapa_entorno_[i][j] = aux[i + baliza_2.y - baliza_2.y_real][j + baliza_2.x - baliza_2.x_real];
    }
  }

  x_ = baliza_2.x_real;
  y_ = baliza_2.y_real;

  cout << "y = " << y_ << " & x = " << x_ << endl;*/
};

bool Agent::HayObstaculo(int fila, int col){
  if(mapa_entorno_[fila][col] == 'A' || mapa_entorno_[fila][col] == 'B'
   || mapa_entorno_[fila][col] == 'P' || mapa_entorno_[fila][col] == 'M')
    return true;
  else return false;
}

bool Agent::HayObjeto(int fila, int col){
  if (mapa_objetos_[fila][col] != '?') {
    return true;
  }else return false;
}

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	Agent::ActionType accion = actFORWARD; // Por defecto avanza
  /*Si la ultima accion fue tirar un objeto siempre cojemos uno*/
  if (last_accion_ == actPUTDOWN && !MOCHILLA_[0] == '-' && CICLO > 0) {
    last_accion_ = actPOP;
    return accion = actPOP;
  }

  if (last_accion_ == actGIVE) {
    if (gire_derecha) {
      gire_derecha = false;
      last_accion_ = actTURN_L;
      return actTURN_L;
    }else{
      gire_derecha = true;
      last_accion_ = actTURN_R;
      return actTURN_R;
    }
  }

  if(last_accion_ == actPICKUP){
    if (EN_USO_ != '-') {
      last_accion_ = actPUSH;
      return actPUSH;
    }
    last_accion_ = actFORWARD;
    return actFORWARD;
  }
  if(!baliza1 || !baliza2){
    if(VISTA_[0] == 'K'){
      if(!baliza1){
        cout << "capturo la baliza 1" << endl;
        CapturaFilaColumnaPK(MENSAJE_, baliza_1.y_real, baliza_1.x_real);
        baliza_1.x = y_;
        baliza_1.y = x_; // y es filas
        baliza1 = true;

        cout << "baliza.x = " << baliza_1.x << endl;
        std::cout << "baliza.y = " << baliza_1.y << std::endl;
        std::cout << "baliza.x_real = " << baliza_1.x_real << std::endl;
        std::cout << "baliza.y_real = " << baliza_1.y_real << std::endl;
      }else if(!baliza2){
        cout << "capturo la baliza 2" << endl;
        CapturaFilaColumnaPK(MENSAJE_, baliza_2.y_real, baliza_2.x_real);
        baliza_2.x = y_;
        baliza_2.y = x_;
        baliza2 = true;

        cout << "baliza.x = " << baliza_2.x << endl;
        std::cout << "baliza.y = " << baliza_2.y << std::endl;
        std::cout << "baliza.x_real = " << baliza_2.x_real << std::endl;
        std::cout << "baliza.y_real = " << baliza_2.y_real << std::endl;
      }

    }
  }
  if (baliza1 && baliza2 && !ubicado) {
    //ahora lo hago
    //hacer la cuenta para ubicar el mapa en la solucion
    cout << "Me dispongo a poner la matriz en correctamente cuadrada." << endl;
    CuadraMatriz();
    ubicado = true;
  }

  //Para intentar evitar dar vueltas en circulo vamos a comprobar las veces que hemos pasado por una casilla y sus
  //Vecinas de modo que si por una casilla hemos pasado muchas veces y su vecina no nos desviaremos del rumbo logico para
  //ir hacia las casillas menos recorridas, evitando asi dar muchas vueltas en circulos(Nota: Intentar mejorar)
  int izda, frente, dcha;
  switch (orientacion_) {
    case 0://norte
      if(HayObstaculo(y_, x_-1))
        izda = ESTORBO;
      else izda = veces_pasadas[y_][x_-1];

      if(HayObstaculo(y_, x_+1))
        dcha = ESTORBO;
      else dcha = veces_pasadas[y_][x_+1];

      if(HayObstaculo(y_-1, x_))
        frente = ESTORBO;
      else frente = veces_pasadas[y_-1][x_];

    break;

    case 1://Este
      if(HayObstaculo(y_-1, x_))
        izda = ESTORBO;
      else izda = veces_pasadas[y_-1][x_];

      if(HayObstaculo(y_+1, x_))
        dcha = ESTORBO;
      else dcha = veces_pasadas[y_+1][x_];

      if(HayObstaculo(y_, x_+1))
        frente = ESTORBO;
      else frente = veces_pasadas[y_][x_+1];

    break;
    case 2://Sur

      if(HayObstaculo(y_, x_+1))
        izda = ESTORBO;
      else izda = veces_pasadas[y_][x_+1];

      if(HayObstaculo(y_, x_-1))
        dcha = ESTORBO;
      else dcha = veces_pasadas[y_][x_-1];

      if(HayObstaculo(y_+1, x_))
        frente = ESTORBO;
      else frente = veces_pasadas[y_+1][x_];



    break;
    case 3:
      if(HayObstaculo(y_+1, x_))
        izda = ESTORBO;
      else izda = veces_pasadas[y_+1][x_];

      if(HayObstaculo(y_-1, x_))
        dcha = ESTORBO;
      else dcha = veces_pasadas[y_-1][x_];

      if(HayObstaculo(y_, x_-1))
        frente = ESTORBO;
      else frente = veces_pasadas[y_][x_-1];
      }

  int acc = minimo(izda, frente, dcha); //si el minimo es frente hay que girar.

  accion = static_cast < Agent::ActionType > (acc);

  /*Parte para la gestion de la  recogida y entrega de objetos, hay que pensar si lo saco
  afuera como otra funcion*/

  /*if (HayPersonaje(y_, x_)) {
    /*Compruebo si tengo en la mano o en la mochila el regalo apropiado
    Si lo tengo en la mano lo regalo.
    if(EN_USO_ != '-')
      accion = actGIVE;
    else accion = static_cast < Agent::ActionType > (minimo(ESTORBO, izda, dcha));
  }

  if (HayObjeto(y_, x_)) {
    if (EN_USO_ != '-') {
      bool hueco_mochila;
      for (size_t i = 0; i < 5; i++) {
        if(MOCHILLA_[i] == '-')
          hueco_mochila = true;
      }

      if (hueco_mochila) {
        accion = actPUSH;
      } else accion = actPUTDOWN;
    }else accion = actPICKUP;
  }

  if (HayPersonaje(y_, x_) && EN_USO_ == '-') {
    accion = actTURN_R;
  }*/

  if(HayPersonaje(y_, x_)){
        media_vuelta = true; //variable reutilizada, indica que vi un personaje;
        int acc = minimo(izda, ESTORBO, dcha);
        return static_cast < Agent::ActionType > (acc);
  }

  if(media_vuelta){
    accion = actFORWARD;
    media_vuelta = false;

  }

  if(atasco){
    accion = static_cast < Agent::ActionType > (last_accion_);
  }

  cout << "La accion tomada es: " << ActionStr(accion) << endl;

  last_accion_ = accion;
  return accion;
}
bool Agent::RegaloApropiado(){
  char viendo = SURFACE_[1];
  RegaloPersona aux;

  for(int i=0; i < 6; i++){
    if(regalos[i].personaje == viendo)
      aux = regalos[i];
  }

  if(aux.objeto = MOCHILLA_[0])
    return true;
  else return false;
}

bool Agent::HayPersonaje(int fila, int col){
  return (SURFACE_[1] == 'e' || SURFACE_[1] == 'g' || SURFACE_[1] == 'i' || SURFACE_[1] == 'k' || SURFACE_[1] == 'm' || SURFACE_[1] == 'o');
}

int Agent::getRegaloParaPersonaje(char personaje){
  int regalo = -1;
  for(int i=0; i < 6; i++){
    if(regalos[i].personaje == personaje)
      regalo = regalos[i].objeto;
  }

  return regalo;
}

//funcion para obtener fila y columna del PK
//Realizada por los profesores de la etsiit de la asignatura IA
void Agent::CapturaFilaColumnaPK (string mensaje, int &fila, int &columna){
	if (mensaje.substr(0,8)=="PK fila:"){
		int pos = mensaje.find('c');
		string valor = mensaje.substr(9,pos-8);
		fila = atoi(valor.c_str());

		int pos2 = mensaje.find('.');
		pos = pos+8;
		valor = mensaje.substr(pos,pos2-1);
		columna = atoi(valor.c_str());
	}
}

void Agent::setRegalos(){

  cout << "inicializo los regalos" << endl;

  RegaloPersona aldeano;
  aldeano.personaje = 'e';
  aldeano.objeto = 7;
  regalos[0] = aldeano;

  RegaloPersona princesa;
  princesa.personaje = 'g';
  princesa.objeto = 3;
  regalos[1] = princesa;

  RegaloPersona dicaprio;
  dicaprio.personaje = 'i';
  dicaprio.objeto = 5;
  regalos[2] = dicaprio;

  RegaloPersona princeso;
  princeso.personaje = 'k';
  princeso.objeto = 2;
  regalos[3] = princeso;

  RegaloPersona bruja;
  bruja.personaje = 'm';
  bruja.objeto = 8;
  regalos[4] = bruja;

  RegaloPersona profe;
  profe.personaje = 'o';
  profe.objeto = 9;


}
