#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structura player din tema
struct Player
{
    char* firstName;
    char* secondName;
    int points;
};

//structura pt informatii despre echipa
struct Team{
    char* name;
    int punctajTotal;
    struct Team* next;
};

//functii
char* citireSir(FILE* fisier);
char* citireNumeEchipa(FILE* fisier);
struct Team* creazaEchipa(char* name, int punctaj, struct Team* head);
void freeMem(struct Team* head);
void eliminaEchipa(struct Team** head, int n);
int putereDoi(int n);


//APELARE FUNCTII TASK
void task1(FILE* fisier_in, FILE* fisier_out, struct Team** teamList, int numarEchipe, int* vectorTask);
void task2(FILE* fisier_output, int numarEchipe, struct Team** teamList);