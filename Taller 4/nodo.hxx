#include "nodo.h"

template <class T>
Nodo<T>::Nodo()
{
    this->min_max = NULL;
    this->posicionesTablero[3][3] = NULL;
    this->valorJugada = NULL;
}
template <class T>
Nodo<T>::Nodo(T min_maxVal, T tableroVal, T valorJugadaVal)
{
    this->min_max = min_maxVal;
    this->posicionesTablero[3][3] = tableroVal;
    this->valorJugada = valorJugadaVal;
}
/* funcion que se encarga de crear los hijos de un nodo
la funcion recorre todas las posiciones del tablero y dependiendo
de el turno actual del juego y de los valores que ya esten dentro del tablero
escribe en una posiciion de la matriz el siguiente movimiento y se lo asigna a un hijo,
se escribe 1 si es el jugador 2 si es la maquina o 0 si la casilla esta vacia
*/
template <class T>
void Nodo<T>::crearHijos()
{   
    int hijosNivelUnoMin_max = 0;
    int hijosValorJugada = 0;
    if (this->min_max == 1)
    {
        hijosNivelUnoMin_max = 2;
    }
    else
    {
        hijosNivelUnoMin_max = 1;
    }
    for(int j = 0; j < 3;j++)
    {
        for(int k = 0; k < 3; k++)
        {
            if(this->posicionesTablero[j][k] == 0)
            {
                Nodo<int> nuevoHijo;
                nuevoHijo.min_max = hijosNivelUnoMin_max;
                nuevoHijo.valorJugada = hijosValorJugada;
                for (int x = 0; x < 3; x++)
                {
                    for(int y = 0; y < 3; y++) 
                    {
                        nuevoHijo.posicionesTablero[x][y] =  this->posicionesTablero[x][y];
                    }
                }
                nuevoHijo.posicionesTablero[j][k] = hijosNivelUnoMin_max;
                this->hijos.push_back(nuevoHijo);
            }
        }
    }
}
/* funcion que se encarga de imprimir los hijos que tiene un nodo
la impresion es el tablero que esta almacenando acada uno de los hijos
*/
template <class T>
void Nodo<T>::imprimirHijos()
{
    for(int i = 0; i < this->hijos.size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0;k<3;k++)
            {
                std::cout << this->hijos[i].posicionesTablero[j][k];
            }
        std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << this->hijos[i].valorJugada << std::endl;
        }
    

}

/*
funcion que se encarga de calcular el valor de la jugada para los hijos de
primer nivel, la funcion evalua si se tiene que buscar el valor de 2 maquina o 1 jugador 
para asi calcular el numero de probabilidades que tiene de ganar, una vez obtenido la posicion
contrincante lo que se hace es ver si este esta en una esquina, en una de las mitades o en el centro
del tablero, para asi poder dar un valor a la variable max, de mismo modo de hace con el jugador actual
para poder guardar la variable min, seguido a esto se hace la respectiva resta y se guarda el valor 
en la variable de puntaje que guarda cada nodo
*/
template <class T>
void Nodo<T>::calcularValorJugada()
{
    int valorABuscar = 0, valorABuscar2 = 0, min = 0, max = 0;
    if(this->min_max == 1)
    {
        valorABuscar = 2;
        valorABuscar2 = 1;
    }
    else
    {
        valorABuscar = 1;
        valorABuscar2 = 2;
    }

    int posicionX = -1;
    int posicionY = -1;
    for(int i = 0; i< 3;i++)
    {
        for(int j = 0; j<3;j++)
        {
            if(this->posicionesTablero[i][j] == valorABuscar)
            {
                posicionX = i;
                posicionY = j;
            }
        }
    }

    if((posicionX == 0 && posicionY == 0)||(posicionX == 0 && posicionY == 2)||(posicionX == 2 && posicionY == 0)||(posicionX == 2 && posicionY == 2))
    {
        max = 5;
    }
    if((posicionX == 0 && posicionY == 1)||(posicionX == 1 && posicionY == 0)||(posicionX == 2 && posicionY == 1)||(posicionX == 1 && posicionY == 2))
    {
        max = 6;
    }
    if(posicionX == 1 && posicionY == 1)
    {
        max = 4;
    }

    int posicionX2 = -1;
    int posicionY2 = -1;
    for(int i = 0; i< 3;i++)
    {
        for(int j = 0; j<3;j++)
        {
            if(this->posicionesTablero[i][j] == valorABuscar2)
            {
                posicionX2 = i;
                posicionY2 = j;
            }
        }
    }

    if((posicionX2 == 0 && posicionY2 == 0)||(posicionX2 == 0 && posicionY2 == 2)||(posicionX2 == 2 && posicionY2 == 0)||(posicionX2 == 2 && posicionY2 == 2))
    {
       min = 5; 
    }
    if((posicionX2 == 0 && posicionY2 == 1)||(posicionX2 == 1 && posicionY2 == 0)||(posicionX2 == 2 && posicionY2 == 1)||(posicionX2 == 1 && posicionY2 == 2))
    {
        min = 6;
    }
    if(posicionX2 == 1 && posicionY2 == 1)
    {
        min = 4;
    }

    int resultado = max - min;
    this->valorJugada = resultado;
}

/*
de mismo modo que ne la funcion anterior esta calcula el valor de la jugada para los hijos que se encuentran
en el segundo nivel del arbol, aqui las condiciones son mas extensas ya que se tiene que verificar cuantas fichas 
del contrincante ya se encuentran en el tablero y las posicines de esta para calcular de manera optima
las posibles jugadas que nos den la victoria,hay distintas variable booleanas que nos ayudan a saber si el contrincante
se encuentra en una esquina, en los centros, en las mitades y si son fichas que son vecinas o si estan paralelas unas a otras
con esto calculamos en valor de las jugadas que venefician al jugador actual y luego se calcula las posibilidades que tiene el 
contrincante de poder ganar para hacer el respectivo calculo. finalmente el valor es almacenado en la variable de valor de jugada
de cada uno de los nodos
*/
template <class T>
void Nodo<T>::calcularValor2()
{
    int valorABuscar = 0,valorABuscar2 = 0, min = 0, max = 0;
    if(this->min_max == 1)
    {
        valorABuscar = 1;
        valorABuscar2 = 2;
    }
    else
    {
        valorABuscar = 2;
        valorABuscar2 = 1;
    }

    int posicionX1 = -1;
    int posicionY1 = -1;
    int posicionX2 = -1;
    int posicionY2 = -1;
    bool encontradoPrimero = false;
    bool valorUnoEsEsquina = false;
    bool valorDosEsEsquina = false;
    bool valorUnoEsCentro = false;
    bool valorDosEsCentro = false;
    bool valorUnoEsMitad = false;
    bool valorDosEsMitad = false;
    bool sonVecinos = false;
    bool sonParalelos = false;
    int puntaje = 0;
    for(int i = 0; i< 3;i++)
    {
        for(int j = 0; j<3;j++)
        {
            if(this->posicionesTablero[i][j] == valorABuscar && encontradoPrimero == false)
            {
                posicionX1 = i;
                posicionY1 = j;
                encontradoPrimero = true;
                if((posicionX1 == 0 && posicionY1 == 0)||(posicionX1 == 0 && posicionY1 == 2)||(posicionX1 == 2 && posicionY1 == 0)||(posicionX1 == 2 && posicionY1 == 2))
                {
                    valorUnoEsEsquina = true;
                }
                if((posicionX1 == 0 && posicionY1 == 1)||(posicionX1 == 1 && posicionY1 == 0)||(posicionX1 == 2 && posicionY1 == 1)||(posicionX1 == 1 && posicionY1 == 2))
                {
                    valorUnoEsMitad = true;
                }
                if(posicionX1 == 1 && posicionY1 == 1)
                {
                    valorUnoEsCentro = true;
                }
            }
        
            if(this->posicionesTablero[i][j] == valorABuscar && encontradoPrimero == true)
            {
                posicionX2 = i;
                posicionY2 = j;
                if((posicionX2 == 0 && posicionY2 == 0)||(posicionX2 == 0 && posicionY2 == 2)||(posicionX2 == 2 && posicionY2 == 0)||(posicionX2 == 2 && posicionY2 == 2))
                {
                    valorDosEsEsquina = true;
                }
                if((posicionX2 == 0 && posicionY2 == 1)||(posicionX2 == 1 && posicionY2 == 0)||(posicionX2 == 2 && posicionY2 == 1)||(posicionX2 == 1 && posicionY2 == 2))
                {
                    valorDosEsMitad = true;
                }
                if(posicionX2 == 1 && posicionY2 == 1)
                {
                    valorDosEsCentro = true;
                }
                if((posicionX2 == posicionX1 && posicionY2 - 1 == posicionY1) || (posicionX2 +1 == posicionX1 && posicionY2 == posicionY1) || (posicionX2 == posicionX1 && posicionY2 + 1 == posicionY1) || (posicionX2 -1 == posicionX1 && posicionY2  == posicionY1))
                {
                    sonVecinos = true;
                }
                if((posicionX2 == posicionX1 && posicionY2 - 2 == posicionY1) || (posicionX2 +2 == posicionX1 && posicionY2 == posicionY1) || (posicionX2 == posicionX1 && posicionY2 + 2 == posicionY1) || (posicionX2 -2 == posicionX1 && posicionY2  == posicionY1))
                {
                    sonParalelos = true;
                }
            }
        }
    }

    if(valorUnoEsEsquina || valorDosEsEsquina)
    {
        if(valorUnoEsEsquina && valorDosEsEsquina)
        {
            puntaje = 3;
        }
        if((valorUnoEsEsquina && valorDosEsMitad && sonVecinos == false) || (valorDosEsEsquina && valorUnoEsMitad && sonVecinos == false))
        {
            puntaje = 3;
        }
        if((valorUnoEsEsquina && valorDosEsMitad && sonVecinos == true) || (valorDosEsEsquina && valorUnoEsMitad && sonVecinos == true))
        {
            puntaje = 4;
        }
        if((valorUnoEsEsquina && valorDosEsCentro) || (valorDosEsEsquina && valorUnoEsCentro))
        {
            puntaje = 2;
        }
    }
    else
    {
        if(sonVecinos)
        {
            puntaje = 3;
        }
        if(sonParalelos)
        {
            puntaje = 5;
        }
        else
        {
            puntaje = 4;
        }
    }

    int puntaje2 = 0;

    for(int i = 0; i< 3;i++)
    {
        for(int j = 0; j<3;j++)
        {
            if(this->posicionesTablero[i][j] == valorABuscar2)
            {
                posicionX2 = i;
                posicionY2 = j;
            }
        }
    }

    if((posicionX2 == 0 && posicionY2 == 0)||(posicionX2 == 0 && posicionY2 == 2)||(posicionX2 == 2 && posicionY2 == 0)||(posicionX2 == 2 && posicionY2 == 2))
    {
        puntaje2 = 5; 
    }
    if((posicionX2 == 0 && posicionY2 == 1)||(posicionX2 == 1 && posicionY2 == 0)||(posicionX2 == 2 && posicionY2 == 1)||(posicionX2 == 1 && posicionY2 == 2))
    {
        puntaje2 = 6;
    }
    if(posicionX2 == 1 && posicionY2 == 1)
    {
        puntaje2 = 4;
    }

    int resultado = puntaje - puntaje2;
    this->valorJugada = resultado;

}