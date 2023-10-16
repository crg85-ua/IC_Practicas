#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <Jugador.h>

#include <iostream>
#include <exception>

#define NUM_PLAYERS_MAX 20
#define BOARD_SIZE_FILA 50
#define BOARD_SIZE_COLUMNA 10

int getRandomStep()
{
    return rand() % 6;
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

void temp_main()
{
    int numPlayers, steps, exponent;
    bool valid = false;
    bool validAux = false;
    // numPlayers =
    // steps =
    // exponent =

    srand(time(NULL)); // Inicializamos la semilla para números aleatorios

    int positions[NUM_PLAYERS_MAX] = {(0, 0)};
    int board[BOARD_SIZE_FILA][BOARD_SIZE_COLUMNA] = {0};
    for (int i = 0; i < numPlayers; i + 2)
    {
        board[0][i] = i;
        board[BOARD_SIZE_FILA - 1][i] = i + 1;
    }

    while (1)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            int posAnterior = positions[i];
            // Movemos jugador
            if (steps == 0)
            {
                positions[i] += getRandomStep();
            }
            else
            {
                positions[i] += steps;
            }

            // Verificamos si el jugador llegó al final del tablero
            if (positions[i] >= BOARD_SIZE_FILA)
            {
                printf("Jugador %d ha llegado al final del tablero.\n", i + 1);
                positions[i] = -1; // Marcamos al jugador como que ha terminado
            }

            // while (board[]){

            // }

            // Verificamos colisiones
            for (int j = 0; j < numPlayers; j++)
            {
                if (i != j && positions[i] == positions[j])
                {
                    int exponentAux;
                    if (exponent == 0)
                    {
                        steps = rand() % 6;
                    }
                    int time1 = (int)pow(3, exponentAux);
                    int time2 = (int)pow(3, exponentAux);

                    printf("¡Colisión entre Jugador %d y Jugador %d!\n", i + 1, j + 1);
                    printf("Jugador %d tarda %d segundos en resolver 3^%d.\n", i + 1, time1, exponentAux);
                    printf("Jugador %d tarda %d segundos en resolver 3^%d.\n", j + 1, time2, exponentAux);

                    if (time1 < time2)
                    {
                        printf("Jugador %d ha sido eliminado.\n", j + 1);
                        positions[j] = -1; // Marcamos al jugador como eliminado
                    }
                    else if (time2 < time1)
                    {
                        printf("Jugador %d ha sido eliminado.\n", i + 1);
                        positions[i] = -1; // Marcamos al jugador como eliminado
                    }
                    else
                    {
                        printf("Empate. Ambos jugadores continúan.\n");
                    }
                }
            }

            // Imprimir el tablero
            printBoard(positions, numPlayers);
        }

        // Verificar si todos los jugadores han llegado al final del tablero
        int finishedPlayers = 0;
        for (int i = 0; i < numPlayers; i++)
        {
            if (positions[i] == -1)
            {
                finishedPlayers++;
            }
        }

        if (finishedPlayers == numPlayers)
        {
            printf("¡Todos los jugadores han llegado al final del tablero! Juego terminado.\n");
            break;
        }
    }
}

int main(int argc, char **argv)
{
    try
    {
        if (argc != 4)
        {
            throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <num_players> <steps> <exponent>");
        }

        int numPlayer = std::atoi(argv[1]);
        int steps = std::atoi(argv[2]);
        int exponent = std::atoi(argv[3]);

        if (numPlayer < 1 || numPlayer > NUM_PLAYERS_MAX)
        {
            throw std::invalid_argument("Number of players must be between 1 and 20");
        }

        if (steps > 5 )
        {
            throw std::invalid_argument("Number of steps must be between 1 and 5");
        }

        temp_main();

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