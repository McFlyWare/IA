
#ifndef __NODO_H__
#define __NODO_H__

#include <iostream>
#include <string>
#include <list>
#include <vector>

/*
esta es la estructura de cada uno de los nodos que se va a guardar 
en el arbol, se tiene la posicion del tablero la cual se guarda en una matriz 
de 3x3, el valor min max que nos dice de quien es el turno actual en la partida 
1 si es jugador o 2 si el la maquina, valor jugada que es la variable encargada
de almacenar el valor de la jugada con la formula vista en clase y un vector
que almacena nodos los cuales van a ser los hijos de este nodo con todas
las posibles jugadas restantes.
*/
template< class T >
class Nodo {
  public:
    T posicionesTablero[3][3];
    T min_max;
    T valorJugada;
    std::vector<Nodo<T>> hijos;
  public:
    Nodo(); // constructor del nodo
    Nodo(T min_maxVal, T tableroVal, T valorJugadaVal); //contructor del nodo con valores que se pasan por paramtro
    void crearHijos(); // funcion para creal los hijos de un nodo dependiendo de las jugadas posibles
    void imprimirHijos(); // funcion que imprime los hijos
    void calcularValorJugada(); // funcion que calcula el valor de la jugada para los hijos del primer nivel
    void calcularValor2(); // funcion que calcula el valor de la jugada para los hijos del segundo nivel
};


#include "nodo.hxx"


#endif // __NODO_H__