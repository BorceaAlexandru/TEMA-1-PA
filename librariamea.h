#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//de aici se fac apelarile


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
    struct Team* next;
};

//void afisare();

int determinTask(FILE* fisier);
char* citireSir(FILE* fisier);
char* citireNumeEchipa(FILE* fisier);
struct Team* creazaEchipa(char* name, struct Team* head);
void freeMem(struct Team* head);

//adaugate pt task2 inca nu s finalizate
struct Team{
    char* name;
    int punctajTotal;
    struct Team* next;
};

void eliminaEchipa(struct Team** head, int n);
int putereDoi(int n);


