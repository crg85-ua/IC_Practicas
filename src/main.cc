#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include "dummy.h"

#define NUM_PLAYERS_MAX 20
#define BOARD_SIZE_FILA 50
#define BOARD_SIZE_COLUMNA 10

int getRandomStep() {
    return rand() % 6;
}

void printBoard(int positions[], int numPlayers) {
    printf("Tablero:\n");
    for (int i = 0; i < BOARD_SIZE_FILA; i++) {
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

int pedirNumero(){
    int numPlayers,result,c;
    bool valid = false;
    while (valid == false){
        // Pedir al usuario el número de jugadores y si desea usar números random o fijos
        printf("Ingrese el número de jugadores (hasta %d): \n", NUM_PLAYERS_MAX);
        result = scanf("%d", &numPlayers);

        if (result != 1){
            printf("Debe de introducir un número, inténtelo de nuevo\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
        } else if (numPlayers < 2 || numPlayers > NUM_PLAYERS_MAX) {
            printf("Número de jugadores no válido. Debe ser entre 2 y %d, inténtelo de nuevo.\n", NUM_PLAYERS_MAX);
        } else{
            valid = true;
        }
    }
    return numPlayers;
}

int pedirAvanzar(){
    int choise, steps,c,result;
    bool valid = false;
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
            valid = true;
            steps = 0;
        } else {
            printf("Opción no válida. Debe ser 0 o 1, inténtelo de nuevo\n");
        }
    }
    return steps;
}

int pedirExponente(){
    int choise, exponent,c,result;
    bool valid = false;
    while (valid == false){
        printf("¿Desea usar números aleatorios para el exponente? (1 para Sí, 0 para No): \n");
        result = scanf("%d", &choise);
        printf("aaa");
        if (result != 1){
            printf("Debe de introducir un número, inténtelo de nuevo\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
        } else if(choise == 0){
            while (valid == false){
                printf("Elija un número para el exponent\n");
                result = scanf("%d", &exponent);

                if (result != 1){
                    printf("Debe de introducir un número, inténtelo de nuevo\n");
                    while ((c = getchar()) != '\n' && c != EOF) {}
                } else if (exponent < 0){
                    printf("Nuḿero erróneo, tiene que ser mayor que 0\n");
                } else{
                    valid = true;
                }
            }
        } else if (choise == 1){
            valid = true;
            exponent = 0;
        } else {
            printf("Opción no válida. Debe ser 0 o 1, inténtelo de nuevo\n");
        }
    }
    return exponent;
}

int main() {
    int numPlayers, steps ,exponent;
    bool valid = false;
    bool validAux = false;
    numPlayers = pedirNumero();
    steps = pedirAvanzar();
    exponent = pedirExponente();
    

    srand(time(NULL)); // Inicializamos la semilla para números aleatorios
    
    int positions[NUM_PLAYERS_MAX] = {(0,0)};
    int board[BOARD_SIZE_FILA][BOARD_SIZE_COLUMNA] = {0};
    for(int i = 0; i < numPlayers; i+2){
        board[0][i] = i;
        board[BOARD_SIZE_FILA - 1][i] = i+1; 
    }
    
    while (1) {
        for (int i = 0; i < numPlayers; i++) {
            // Movemos jugador
            if (steps == 0) {
                positions[i] += getRandomStep();
            } else {
                positions[i] += steps;
            }
            
            // Verificamos si el jugador llegó al final del tablero
            if (positions[i] >= BOARD_SIZE_FILA) {
                printf("Jugador %d ha llegado al final del tablero.\n", i + 1);
                positions[i] = -1; // Marcamos al jugador como que ha terminado
            }
            
            // Verificamos colisiones
            for (int j = 0; j < numPlayers; j++) {
                if (i != j && positions[i] == positions[j]) {
                    int exponentAux;
                    if(exponent == 0){
                        steps = rand() % 6;
                    }
                    int time1 = (int)pow(3, exponentAux);
                    int time2 = (int)pow(3, exponentAux);
                    
                    printf("¡Colisión entre Jugador %d y Jugador %d!\n", i + 1, j + 1);
                    printf("Jugador %d tarda %d segundos en resolver 3^%d.\n", i + 1, time1, exponentAux);
                    printf("Jugador %d tarda %d segundos en resolver 3^%d.\n", j + 1, time2, exponentAux);
                    
                    if (time1 < time2) {
                        printf("Jugador %d ha sido eliminado.\n", j + 1);
                        positions[j] = -1; // Marcamos al jugador como eliminado
                    } else if (time2 < time1) {
                        printf("Jugador %d ha sido eliminado.\n", i + 1);
                        positions[i] = -1; // Marcamos al jugador como eliminado
                    } else {
                        printf("Empate. Ambos jugadores continúan.\n");
                    }
                }
            }
            
            // Imprimir el tablero
            printBoard(positions, numPlayers);
        }
        
        // Verificar si todos los jugadores han llegado al final del tablero
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
