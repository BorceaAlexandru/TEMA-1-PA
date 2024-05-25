#include "librariamea.h"


//functie care citeste din d.in (cate un cuvant)
char* citireSir(FILE* fisier)
{
    if(fisier==NULL)
    {
        puts("Eroare!");
        exit(1);
    }
    char buffer[100];
    fscanf(fisier, "%s", buffer);
    char* cuv=(char*)malloc(strlen(buffer)+1);
    strcpy(cuv, buffer);
    return cuv;
}

//functie pentru a citit numele exhipei (citeste intreaga linie)
char* citireNumeEchipa(FILE* fisier)
{
    if(fisier==NULL)
    {
        puts("Eroare!");
        exit(1);
    }
    char buffer[100];
    fgetc(fisier); //sterge spatiul ramas de la nr de jucatori
    fgets(buffer, sizeof(buffer), fisier);
    buffer[strcspn(buffer, "\n")]='\0';
    char* name=(char*)malloc(strlen(buffer)+1);
    strcpy(name, buffer);
    return name;
}

//functie pentru eliberare de memorie
void freeMem(struct Team* head)
{
    while(head!=NULL)
    {
        struct Team* aux=head;
        head=head->next;
        free(aux->name); //eliberez mem pt numele echipei
        free(aux); //eliberez mem pt struct echipei
    }
}

//creeazaEchipa modificat + cu punctaj
struct Team* creazaEchipa(char* name, int punctajTotal, struct Team* head)
{
    struct Team* newTeam=(struct Team*)malloc(sizeof (struct Team));
    newTeam->name=name;
    newTeam->punctajTotal=punctajTotal;
    newTeam->next=head;
    return newTeam;
}

//putere 2
int putereDoi(int n)
{
    if(n<1) return 0;
    return (n&(n-1))==0;
}


//elimina echipa
void eliminaEchipa(struct Team** head, int numarEchipe)
{
    while((numarEchipe & (numarEchipe-1))!=0) //verific daca n e putere a lui 2
    {
        struct Team* cur=*head;
        struct Team* prev=NULL;
        struct Team* minPrev=NULL;
        struct Team* minTeam=cur;

        while(cur!=NULL)
        {
            if(cur->punctajTotal < minTeam->punctajTotal)
            {
                minPrev=prev;
                minTeam=cur;
            }
            prev=cur;
            cur=cur->next;
        }

        if(minPrev==NULL)
            *head=(*head)->next;
        else
            minPrev->next=minTeam->next;

        free(minTeam->name);
        free(minTeam);
        numarEchipe--;
    }
}



//FUNCTII TASK

void task1(FILE* fisier_input, FILE* fisier_output, struct Team** teamList, int numarEchipe, int* vectorTask)
{
    int nrPlayeri;

    int i, j;
    for(i=0; i<numarEchipe; i++)
    {
        fscanf(fisier_input, "%d", &nrPlayeri);
        int punctajTotal=0;
        char* numeEchipa=citireNumeEchipa(fisier_input);

        

        for(j=0; j<nrPlayeri; j++)
        {
            char* firstName=citireSir(fisier_input);
            char* secondName=citireSir(fisier_input);
            int points;
            fscanf(fisier_input, "%d", &points);
            punctajTotal+=points;

            //eliberare
            free(firstName);
            free(secondName);
        }

        (*teamList)=creazaEchipa(numeEchipa, punctajTotal, *teamList);
    }

    if(vectorTask[0]==1 && (vectorTask[1]==0 && vectorTask[2]==0 && vectorTask[3]==0 && vectorTask[4]==0))
    {
    struct Team* curent=(*teamList);
    while(curent!=NULL)
    {
        fprintf(fisier_output, "%s\n", curent->name);
        curent=curent->next;
    }
    }
}


void task2(FILE* fisier_output, int numarEchipe, struct Team** teamList)
{
    eliminaEchipa(teamList, numarEchipe);

    struct Team* curent=(*teamList);
        while(curent!=NULL)
            {
                fprintf(fisier_output, "%s\n", curent->name);
                curent=curent->next;
            }
}
