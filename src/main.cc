#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <stdbool.h>
#include <Jugador.h>

#include <iostream>
#include <exception>
#include <vector>

#define NUM_PLAYERS_MAX 20
#define BOARD_SIZE_FILA 50
#define BOARD_SIZE_COLUMNA 10

int getRandomStep()
{
    return rand() % 6;
}

int getRandomExponent()
{
    return rand() % 50;
}

void printBoard(int positions[], int numPlayers)
{
    printf("Tablero:\n");
    for (int i = 0; i < BOARD_SIZE_FILA; i++)
    {
        int playerIndex = -1;
        for (int j = 0; j < numPlayers; j++)
        {
            if (positions[j] == i)
            {
                playerIndex = j;
                break;
            }
        }
        if (playerIndex == -1)
        {
            printf("| ");
        }
        else
        {
            printf("|%d", playerIndex + 1);
        }
    }
    printf("|\n");
}

int resuelveColision(int jugador1, int jugador2, int exponent)
{
    int perdedor;
    auto start1 = std::chrono::high_resolution_clock::now(); // Momento de inicio
    int valor1 = (int)pow(3, exponent);
    auto stop1 = std::chrono::high_resolution_clock::now();                                 // Momento de finalización
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1); // cambiar a miliseconds si no llega a durar 1 segundo

    auto start2 = std::chrono::high_resolution_clock::now();
    int valor2 = (int)pow(3, exponent);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);

    printf("Jugador %d tarda %lld milisegundos en resolver 3^%d.\n", jugador1, duration1.count(), exponent);
    printf("Jugador %d tarda %lld milisegundos en resolver 3^%d.\n", jugador2, duration2.count(), exponent);

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

void moverJugador(int posX, int posY, int exponent, int steps, bool bajar, bool meta, int board[BOARD_SIZE_FILA][BOARD_SIZE_COLUMNA], int i, std::vector<Jugador *> vector)
{
    int tope;
    bool colision = false;
    if (meta)
        tope = BOARD_SIZE_FILA - posY - 1;
    else
        tope = steps;
    for (int j = 0; j < tope; j++)
    {
        if (bajar)
        {
            if (board[posX][posY + j] != 0)
            {
                int perdedor;
                colision == true;
                printf("¡Colisión entre Jugador %d y Jugador %d!\n", i + 1, board[posX][posY + j]);
                perdedor = resuelveColision(i + 1, board[posX][posY + j], exponent);
                vector[perdedor]->setEstado(-1);
            }
        }
        else
        {
            if (board[posX][posY - j] != 0)
            {
                int perdedor;
                colision == true;
                printf("¡Colisión entre Jugador %d y Jugador %d!\n", i + 1, board[posX][posY - j]);
                perdedor = resuelveColision(i + 1, board[posX][posY + j], exponent);
                vector[perdedor]->setEstado(-1);
            }
        }
    }
}

void temp_main(int numPlayers, int steps, int exponent)
{
    srand(time(NULL)); // Inicializamos la semilla para números aleatorios
    int mitad;
    bool impar = false;

    std::vector<Jugador *> vector;

    int board[BOARD_SIZE_FILA][BOARD_SIZE_COLUMNA] = {0};
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
    for (int i = 0; i <= BOARD_SIZE_FILA; i += BOARD_SIZE_FILA)
    {
        for (int j = 0; j < mitad; j++)
        {
            if (i != 0 && !impar && j != mitad - 1)
            {
                board[i][j] = cont;
                vector.push_back(new Jugador(cont, i, j, 0));
                cont++;
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

    while (1)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (vector[i]->getEstado() == 0)
            {
                int posX, posY;
                bool bajar = false;
                bool colision = false;
                bool meta = false;

                posX = vector[i]->getX();
                posY = vector[i]->getY();
                if (i <= mitad)
                    bajar = true;

                // Verificamos si al mover al jugador saldríamos del tablero
                if (posY + steps >= (BOARD_SIZE_FILA - 1))
                {
                    meta = true;
                    moverJugador(posX, posY, exponent, steps, bajar, meta, board, i, vector);
                    if (vector[i]->getEstado() == 0)
                    {
                        vector[i]->setY(BOARD_SIZE_FILA - 1);
                        vector[i]->setEstado(1);
                    }
                }
                else
                {
                    moverJugador(posX, posY, exponent, steps, bajar, meta, board, i, vector);
                    if (vector[i]->getEstado() == 0)
                        vector[i]->setY(posY + steps);
                }

                // Imprimir el tablero
                // printBoard(positions, numPlayers);
            }
        }

        // Verificar si todos los jugadores han llegado al final del tablero
        int finishedPlayers = 0;
        int livePlayers = 0;
        for (int i = 0; i < numPlayers; i++)
        {
            if (vector[i]->getEstado() == -1)
            {
                finishedPlayers++;
            }
            else if (vector[i]->getEstado() == 0)
            {
                livePlayers++;
            }
        }
        if (livePlayers == 0)
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
    try
    {
        if (argc != 4)
        {
            throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <num_players> <steps> <exponent>");
        }

        int numPlayers = std::atoi(argv[1]);
        int steps = std::atoi(argv[2]);
        int exponent = std::atoi(argv[3]);

        if (numPlayers < 1 || numPlayers > NUM_PLAYERS_MAX)
        {
            throw std::invalid_argument("Number of players must be between 1 and 20");
        }

        if (steps > 5)
        {
            throw std::invalid_argument("Number of steps must be between 1 and 5");
        }
        auto start = std::chrono::high_resolution_clock::now();
        temp_main(numPlayers, steps, exponent);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        printf("El programa ha tardado %lld milisegundos terminar.\n", duration.count());

        return EXIT_SUCCESS;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_FAILURE;
}