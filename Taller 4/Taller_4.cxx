#include <iostream>
#include <string>
#include "nodo.h"

int main()
{

    // inicializacion de los valores de la raiz del arbol en el cual se le pide a el jugador que ingrese las coordenadas de la primera jugada
    Nodo<int> raiz;
    raiz.min_max = 1;
    raiz.valorJugada = 0;
    int posicionX;
    int posicionY;
    std::cout << "ingrese la posicion x: " << std::endl;
    std::cin >> posicionX;
    std::cout << "ingrese la posicion y: " << std::endl;
    std::cin >> posicionY;
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            raiz.posicionesTablero[i][j] = 0;
        }
    }
    raiz.posicionesTablero[posicionX][posicionY] = 1; 

    // llamado a la funcion que crea los hijos de la raiz
    raiz.crearHijos();

    // for encargado de crear los hijos de los hijos y calcular el valor de la jugada de cada uno
    for(int i = 0; i < raiz.hijos.size(); i++)
    {
        raiz.hijos[i].crearHijos();
        raiz.hijos[i].calcularValorJugada();
        // por cada hijo que se creo ahora se van a crear sus hijos de segundo nivel
        for(int j = 0; j< raiz.hijos[i].hijos.size();j++ )
        {
            //calculo de la jugada de cada uno de los hijos de los hijos
            raiz.hijos[i].hijos[j].calcularValor2();
        }
    }

    // parte del codigo que recorre los hijos y nos ayuda a decir cual es el mejor camino a tomar
    // en una variable se guarda que camino nos da el mayor puntaje y esta se compara con todos los hijo  de nivel 1 y sus respectivos hijos de nivel 2
    int mayor = 0, auxMayor = 0, posicionHijo1 = -1, posicionHijo2 = -1;
    for (int i = 0; i < raiz.hijos.size(); i++)
    {
        auxMayor = auxMayor + raiz.hijos[i].valorJugada;
        for (int j = 0; j < raiz.hijos[i].hijos.size(); j++)
        {
            if(auxMayor + raiz.hijos[i].hijos[j].valorJugada> mayor)
            {
                mayor = auxMayor + raiz.hijos[i].hijos[j].valorJugada;
                posicionHijo1 = i;
                posicionHijo2 = j;
            }
        }
        auxMayor = 0;
    }

    // impresion de los resultados obtenidos
    std::cout << "El camino elegido tiene un puntaje de: " + std::to_string(mayor)<< std::endl;
    std::cout << "hijo 1" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << raiz.hijos[posicionHijo1].posicionesTablero[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "hijo 2" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << raiz.hijos[posicionHijo1].hijos[posicionHijo2].posicionesTablero[i][j];
        }
        std::cout << std::endl;
    }


    
    

}