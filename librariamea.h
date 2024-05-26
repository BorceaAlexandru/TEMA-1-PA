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
struct Team
{
    char* name;
    float punctajTotal;
    struct Team* next;
};

//structuri pentru coada si stiva

//struct pentru un nod al cozii cu 2 campuri Team, adica echipele care participa la meci
struct Coada_Nod
{
    struct Team* team1;
    struct Team* team2;
    struct Coada_Nod* next;
};

//struct pt coada, fata-primul nod al cozii, spate-ultimul nod. Se foloseste pt gestiune
struct Coada
{
    struct Coada_Nod* fata;
    struct Coada_Nod* spate;
};

//struct pentru un nod al stivei cu un camp team, adica echipa stocata in acel nod
struct Stiva_Nod
{
    struct Team* team;
    struct Stiva_Nod* next;
};

//struct pt stiva cu un pointer catre varf
struct Stiva
{
    struct Stiva_Nod* varf;
};

//functii
char* citireSir(FILE* fisier);
char* citireNumeEchipa(FILE* fisier);
struct Team* creazaEchipa(char* name, float punctaj, struct Team* head);
void freeMem(struct Team* head);
void eliminaEchipa(struct Team** head, int n);
struct Coada* createQueue();
void enqueue(struct Coada *coada, struct Team* team1, struct Team* team2);
void dequeue(struct Coada* coada);
int coadaGoala(struct Coada* coada);
struct Coada_Nod* fata(struct Coada* coada);
struct Stiva* createStack();
void push(struct Stiva *stiva, struct Team* team);
void pop(struct Stiva* stiva);
int stivaGoala(struct Stiva* stiva);
struct Stiva_Nod varf(struct Stiva *stiva);


//APELARE FUNCTII TASK
void task1(FILE* fisier_in, FILE* fisier_out, struct Team** teamList, int numarEchipe, int* vectorTask);
void task2(FILE* fisier_output, int numarEchipe, struct Team** teamList);
void task3(FILE* fisier_output, struct Team** teamList);