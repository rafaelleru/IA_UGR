/*
Devuelve la accion a realizar para un tablero e
Se ignoran todas las acciones de los nodos hijos, solo se tienen en cuenta las acciondes
del padre.


Para controlar el tipo de jugador (Min, Max), en vez de player se ponen dos parametros mas
prof que si es par indica nodo max e impar nodoi Min
lim el limite de la poda, que nos da la condicion de parada.
*/
double practicar(const Environment &e, int Player, int prof, int acc){
  double maximo = MENOSINF;
  if(prof == 0){ //ampliar con condicion para nodos terminales.
    //Evalua nodos con heurisitca
    return ValoracionTest(e, Player);
    //Sustituir por mi heurisitca
  }else{
    int ultacc = -1;
    int KK;
    Environment hijo = T.generateNextMov(ultacc); //ult acc cambia cada vez quese genera el tablero
    //si ultacc = 8 no hay mas movimientos

    while (ultacc > 8) {
      valor = practicar(hijo, Player, prof-1, KK);

      if(valor > maximo){
        maximo = valor;
        acc = ultacc;
      }
      //genero siguiente hijo
      hijo = T.generateNextMov(ultacc)
    }
    return maximo;
  }
}
