#include <time.h>
#include <math.h>
#include <chrono>
#include <stdbool.h>
#include <Jugador.h>

#include <iostream>
#include <exception>
#include <vector>

#define NUM_PLAYERS_MAX 20
#define BOARD_SIZE_FILA 200
#define BOARD_SIZE_COLUMNA 10
#define NUM_COLU_PRINT 4

int getRandomStep()
{
    return rand() % 6;
}

int getRandomExponent()
{
    return rand() % 80;
}

//Imprimimos el tablero.
void printBoard(int board[BOARD_SIZE_FILA][BOARD_SIZE_COLUMNA])
{
    printf("Tablero:\n");
    for (int i = 0; i < BOARD_SIZE_FILA; i++)
    {
        printf("|");
        for (int j = 0; j < NUM_COLU_PRINT; j++)
        {
            if (board[i][j] == -1)
            {
                printf(" |");
            }
            else
            {
                printf("%d|", board[i][j]);
            }
        }
        printf("\n");
    }
}

//Si hay una colisión entre dos jugadores, esta función decide el ganado.
int resuelveColision(int jugador1, int jugador2, int exponent)
{
    int perdedor;
    long double valor1;
    long double valor2;
    auto start1 = std::chrono::high_resolution_clock::now(); // Momento de inicio
    for (int i = 0; i < 1000000; i++)
        valor1 = pow(50.0, exponent);
    auto stop1 = std::chrono::high_resolution_clock::now();                                 // Momento de finalización
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1); // cambiar a miliseconds si no llega a durar 1 segundo

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
        valor2 = pow(50.0, exponent);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);

    printf("Jugador %d tarda %lld milisegundos en resolver 50^%d un millón de veces.\n", jugador1, duration1.count(), exponent);
    printf("Jugador %d tarda %lld milisegundos en resolver 50^%d un millón de veces.\n", jugador2, duration2.count(), exponent);
    if (valor1 != valor2)
        printf("Algún jugador ha dado un valor erróneo.\n");

    if (duration1 < duration2)
    {
        printf("Jugador %d ha sido eliminado.\n", jugador2);
        perdedor = jugador2;
    }
    else if (duration2 < duration1)
    {
        printf("Jugador %d ha sido eliminado.\n", jugador1);
        perdedor = jugador1;
    }
    else
    {
        printf("Han empatado, por lo cual se eleminará uno aleatoriamente.\n");
        if (rand() % 2)
        {
            printf("Jugador %d ha sido eliminado.\n", jugador1);
            perdedor = jugador1;
        }
        else
        {
            printf("Jugador %d ha sido eliminado.\n", jugador2);
            perdedor = jugador2;
        }
    }
    return perdedor;
}

//Movemos los jugadores
void moverJugador(int posX, int posY, int exponent, int steps, bool bajar, bool meta, int board[BOARD_SIZE_FILA][BOARD_SIZE_COLUMNA], int numJugador, std::vector<Jugador *> vector)
{
    int tope;
    bool colision = false;
    bool mover = false;

    // Colocamos el punto final hacia donde el jugador se moverá
    if (meta && bajar)
        tope = BOARD_SIZE_FILA - posX - 1;
    else if (meta)
        tope = posX;
    else
        tope = steps;
    long double valor;
    for (int i = 0; i < 1000000; i++)
        valor = pow(50.0, exponent);
    // En el siguiente bucle movemos al jugador y si hay alguna colisión luchan, si no, el jugador se mueve
    for (int j = 1; j <= tope; j++)
    {
        if (bajar)
        {
            if (board[posX + j][posY] != -1)
            {
                int perdedor;
                colision = true;
                printf("¡Colisión entre Jugador %d y Jugador %d!\n", numJugador, board[posX + j][posY]);
                perdedor = resuelveColision(numJugador, board[posX + j][posY], exponent);
                vector[perdedor]->setEstado(-1);
                // Si gana el jugador que se está moviendo quitamos al otro jugador del tablero
                if (perdedor != numJugador)
                {
                    board[posX + j][posY] = -1;
                    if (j == tope - 1)
                        mover = true;
                }
                else
                {
                    board[posX][posY] = -1;
                    break;
                }
            }
        }
        else
        {
            if (board[posX - j][posY] != -1)
            {
                int perdedor;
                colision = true;
                printf("¡Colisión entre Jugador %d y Jugador %d!\n", numJugador, board[posX - j][posY]);
                perdedor = resuelveColision(numJugador, board[posX - j][posY], exponent);
                vector[perdedor]->setEstado(-1);
                if (perdedor != numJugador)
                {
                    board[posX - j][posY] = -1;
                    if (j == tope - 1)
                        mover = true;
                }
                else
                {
                    board[posX][posY] = -1;
                    break;
                }
            }
        }
    }
    //Si está bajando y se mueve o no ha colisionado, movemos al jugador
    if (bajar)
    {
        if (!colision || mover)
        {
            vector[numJugador]->setX(posX + tope);
            board[posX][posY] = -1;
            board[posX + tope][posY] = numJugador;
        }
    }
    else if ((!colision || mover))
    {
        vector[numJugador]->setX(posX - tope);
        board[posX][posY] = -1;
        board[posX - tope][posY] = numJugador;
    }
}

void temp_main(int numPlayers, int steps, int exponent)
{
    srand(time(NULL)); // Inicializamos la semilla para números aleatorios
    int mitad;
    bool impar = false;

    std::vector<Jugador *> vector;

    int board[BOARD_SIZE_FILA][BOARD_SIZE_COLUMNA];
    for (int i = 0; i < BOARD_SIZE_FILA; i++)
    {
        for (int j = 0; j < BOARD_SIZE_COLUMNA; j++)
        {
            board[i][j] = -1;
        }
    }
    if (numPlayers % 2 == 0)
    {
        mitad = numPlayers / 2;
    }
    else
    {
        mitad = numPlayers / 2 + 1;
        impar = true;
    }
    int cont = 0;
    for (int i = 0; i < BOARD_SIZE_FILA; i += (BOARD_SIZE_FILA - 1))
    {
        for (int j = 0; j < mitad; j++)
        {
            if(cont < numPlayers)
            {
                if (i != 0 && !impar && j != mitad - 1)
                {
                    board[i][j] = cont;
                    vector.push_back(new Jugador(cont, i, j, 0));
                    cont++;
                }
                else
                {
                    board[i][j] = cont;
                    vector.push_back(new Jugador(cont, i, j, 0));
                    cont++;
                }
            }
        }
    }

    // Sacamos los pasos a mover
    if (steps == 0)
    {
        steps = getRandomStep();
    }

    // Sacamos el exponente
    if (exponent == 0)
    {
        exponent = getRandomExponent();
    }

    int llegadaMeta = 0;
    while (1)
    {
        //Nos vamos posicionando en cada uno de los jugadores para moverlos si siguen vivos.
        for (int i = 0; i < numPlayers; i++)
        {
            //Si el jugador sigue vivo lo movemos.
            if (vector[i]->getEstado() == 0)
            {
                int posX, posY;
                bool bajar = false;
                bool colision = false;
                bool meta = false;

                posX = vector[i]->getX();
                posY = vector[i]->getY();
                if (i < mitad)
                    bajar = true;

                //Si su posición es la misma que la meta lo marcamos como que ha llegado a la meta.
                if ((posX == (BOARD_SIZE_FILA - 1) && bajar) || (posX == 0 && !bajar))
                {
                    llegadaMeta++;
                    vector[i]->setEstado(1);
                }
                else 
                {
                    if ((posX + steps >= (BOARD_SIZE_FILA - 1) && bajar) || (posX - steps <= 0 && !bajar)) // Verificamos si al mover el jugador saldríamos del tablero
                    {
                    meta = true;
                    }
                    moverJugador(posX, posY, exponent, steps, bajar, meta, board, i, vector);
                }
                
                //Imprimimos el tablero por pantalla
                //printBoard(board);
            }
        }

        // Verificar si todos los jugadores han llegado al final del tablero
        if (llegadaMeta == mitad)
        {
            printf("¡Los jugadores han llegado al final del tablero! Juego terminado.\n");
            break;
        }
    }

    // Free vector of players memory
    for (auto jugador : vector)
    {
        delete jugador;
        jugador = nullptr;
    }

    vector.clear();
}

int main(int argc, char **argv)
{
    int numPlayers = 20;
    int steps = 4;
    int exponent = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    temp_main(numPlayers, steps, exponent);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("El programa ha tardado %lld milisegundos terminar.\n", duration.count());

    return EXIT_SUCCESS;
}
