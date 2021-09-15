//
// Created by matan on 15/09/2021.
//

#ifndef SUDUKUSOLVER_SUDUKU_H
#define SIZE 3
#include <stdio.h>
void createBoard(char board[][SIZE*SIZE],char str[]);
void printBoard(char board[][SIZE*SIZE]);
int isSameBoard(char board[][SIZE*SIZE],char board1[][SIZE*SIZE]);
void makeMove(char board[][SIZE*SIZE], char move[]);
void completeBoard(char board[][SIZE*SIZE]);
int testBoard(char board[][SIZE*SIZE]);
int onlyOneEmpty(char board[][SIZE * SIZE]);

#define SUDUKUSOLVER_SUDUKU_H

#endif //SUDUKUSOLVER_SUDUKU_H
