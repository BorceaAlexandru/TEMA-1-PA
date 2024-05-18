#include "librariamea.h"

//aici scriu functiile

/*void afisare(){
    printf("ceva");
}*/

//functie care determina numarul taskului
int determinTask(FILE* fisier)
{
    if(fisier==NULL)
    {
        puts("Eroare!");
        exit(1);
    }
    int tasks[5], i;
    for(i=0 ;i<5; i++)
    {
        if(fscanf(fisier,"%d", &tasks[i])!=1) return -1;
    }

    for(i=0; i<5; i++)
        if(tasks[i]==1)
            return i+1;

    return -1;
}

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

//functie care creeaza echipa si o adauga la inceputul listei
struct Team* creazaEchipa(char* name, struct Team* head)
{
    struct Team* newTeam=(struct Team*)malloc(sizeof (struct Team));
    newTeam->name=name;
    newTeam->next=head;
    return newTeam;
}

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
