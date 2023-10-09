#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define NUM_PLAYERS_MAX 10
#define BOARD_SIZE 20

int getRandomStep() {
    return rand() % 6;
}

void printBoard(int positions[], int numPlayers) {
    printf("Tablero:\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        int playerIndex = -1;
        for (int j = 0; j < numPlayers; j++) {
            if (positions[j] == i) {
                playerIndex = j;
                break;
            }
        }
        if (playerIndex == -1) {
            printf("| ");
        } else {
            printf("|%d", playerIndex + 1);
        }
    }
    printf("|\n");
}

int main() {
    int numPlayers, choise, steps, result, c;
    bool valid = false;
    while (valid == false){
        // Pedimos al usuario el número de jugadores y si desea usar números random o fijos
        printf("Ingrese el número de jugadores (hasta %d): \n", NUM_PLAYERS_MAX);
        result = scanf("%d", &numPlayers);

        if (result != 1){
            printf("Debe de introducir un número, inténtelo de nuevo\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
        } else if (numPlayers < 2 || numPlayers > NUM_PLAYERS_MAX) {
            printf("Número de jugadores no válido. Debe ser entre 2 y %d.\n, inténtelo de nuevo.\n", NUM_PLAYERS_MAX);
            return 1;
        } else{
            valid = true;
        }
    }
    
    valid = false;

    while (valid == false){
        printf("¿Desea usar números aleatorios para avanzar? (1 para Sí, 0 para No): \n");
        result = scanf("%d", &choise);
        
        if (result != 1){
            printf("Debe de introducir un número, inténtelo de nuevo\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
        } else if(choise == 0){
            while (valid == false){
                printf("Elija un número del 1 al 5\n");
                result = scanf("%d", &steps);

                if (result != 1){
                printf("Debe de introducir un número, inténtelo de nuevo\n");
                while ((c = getchar()) != '\n' && c != EOF) {}
                } else if (steps < 1 || steps > 5){
                    printf("Nuḿero erróneo, seleccione otro número\n");
                } else{
                    valid = true;
                }
            }
        } else if (choise == 1){
            valid == true;
            steps = 0;
        } else {
            printf("Opción no válida. Debe ser 0 o 1.\n, inténtelo de nuevo");
            return 1;
        }
    }
    
    srand(time(NULL)); // Inicializamos la semilla para números aleatorios
    
    int board[BOARD_SIZE] = {0};
    int positions[NUM_PLAYERS_MAX] = {0};
    
    while (1) {
        for (int i = 0; i < numPlayers; i++) {
            // Mover jugadorFALSE
            if (choise) {
                positions[i] += getRandomStep();
            } else {
                positions[i] += steps;
            }
            
            // Verificamos si el jugador ha llegado al final del tablero
            if (positions[i] >= BOARD_SIZE) {
                printf("Jugador %d ha llegado al final del tablero.\n", i + 1);
                positions[i] = -1; // Marcar al jugador como terminado
            }
            
            // Verificamos colisiones
            for (int j = 0; j < numPlayers; j++) {
                if (i != j && positions[i] == positions[j]) {
                    int exponent = choise ? (rand() % 6) : steps;
                    int time1 = (int)pow(3, exponent);
                    int time2 = (int)pow(3, exponent);
                    
                    printf("¡Colisión entre Jugador %d y Jugador %d!\n", i + 1, j + 1);
                    printf("Jugador %d tarda %d segundos en resolver 3^%d.\n", i + 1, time1, exponent);
                    printf("Jugador %d tarda %d segundos en resolver 3^%d.\n", j + 1, time2, exponent);
                    
                    if (time1 < time2) {
                        printf("Jugador %d ha sido eliminado.\n", j + 1);
                        positions[j] = -1; // Marcar al jugador como eliminado
                    } else if (time2 < time1) {
                        printf("Jugador %d ha sido eliminado.\n", i + 1);
                        positions[i] = -1; // Marcar al jugador como eliminado
                    } else {
                        printf("Empate. Ambos jugadores continúan.\n");
                    }
                }
            }
            
            // Imprimimos el tablero
            printBoard(positions, numPlayers);
        }
        
        // Verificamos si todos los jugadores han llegado al final del tablero
        int finishedPlayers = 0;
        for (int i = 0; i < numPlayers; i++) {
            if (positions[i] == -1) {
                finishedPlayers++;
            }
        }
        
        if (finishedPlayers == numPlayers) {
            printf("¡Todos los jugadores han llegado al final del tablero! Juego terminado.\n");
            break;
        }
    }
    
    return 0;
}
