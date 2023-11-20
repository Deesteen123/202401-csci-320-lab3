#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab3.h"

extern int** sudoku_board;
int* worker_validation;

int** read_board_from_file(char* filename){
    FILE *fp = NULL;
 if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int** board = (int**)malloc(sizeof(int*) * ROW_SIZE);
    if (board == NULL) {
        perror("Error allocating memory for rows");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROW_SIZE; i++) {
        board[i] = (int*)malloc(sizeof(int) * COL_SIZE);
        if (board[i] == NULL) {
            perror("Error allocating memory for columns");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < COL_SIZE; j++) {
            if (fscanf(fp, "%d,", &board[i][j]) != 1) {
                perror("Error reading from file");
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(fp);
    return board;

	

}


void* validate(void* arg) {
    param_struct* params = (param_struct*)arg;
    int* validation = &worker_validation[params->id];

    for (int i = params->starting_row; i <= params->ending_row; i++) {
        for (int j = params->starting_col; j <= params->ending_col; j++) {
            for (int k = i + 1; k <= params->ending_row; k++) {
                if (params->is_row && sudoku_board[i][j] == sudoku_board[k][j]) {
                    *validation = 0;
                    pthread_exit(NULL);
                } else if (!params->is_row && sudoku_board[j][i] == sudoku_board[j][k]) {
                    *validation = 0;
                    pthread_exit(NULL);
                }
            }
        }
    }

    *validation = 1;
    pthread_exit(NULL);
}



int is_board_valid(){
    pthread_t* tid;  /* the thread identifiers */
    pthread_attr_t attr;
    param_struct* parameter;
    worker_validation = malloc(NUM_OF_THREADS * sizeof(int));

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int index = 0;
    // replace this comment with your code
   //Vaildate by row 
   for (int i = 0; i < ROW_SIZE; i++) {
        param_struct* params = malloc(sizeof(param_struct));
        params->id = index++;
        params->starting_row = i;
        params->ending_row = i;
        params->starting_col = 0;
        params->ending_col = COL_SIZE - 1;
        params->is_row = 1;
        pthread_create(&tid[params->id], &attr, validate, (void*)params);
    }
    // Validate by column
    for (int j = 0; j < COL_SIZE; j++) {
        param_struct* params = malloc(sizeof(param_struct));
        params->id = index++;
        params->starting_row = 0;
        params->ending_row = ROW_SIZE - 1;
        params->starting_col = j;
        params->ending_col = j;
        params->is_row = 0;
        pthread_create(&tid[params->id], &attr, validate, (void*)params);
    }
    //Validate by Subgrid
    for (int i = 0; i < ROW_SIZE; i += 3) {
        for (int j = 0; j < COL_SIZE; j += 3) {
            param_struct* params = malloc(sizeof(param_struct));
            params->id = index++;
            params->starting_row = i;
            params->ending_row = i + 2;
            params->starting_col = j;
            params->ending_col = j + 2;
            params->is_row = 1; 
            pthread_create(&tid[params->id], &attr, validate, (void*)params);
        }
    }

     for (int i = 0; i < NUM_OF_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    int board_valid = 1;
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        if (worker_validation[i] == 0) {
            board_valid = 0;
            break;
        }
    }

    free(worker_validation);
    pthread_attr_destroy(&attr);

    return board_valid;





}
