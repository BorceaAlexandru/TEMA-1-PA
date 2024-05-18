#include <stdio.h>
#include <stdlib.h>
#include "librariamea.h"

int main(int argc, char** argv){

    //afisare();

    FILE* fisier_input=fopen(argv[2], "r");
    FILE* fisier_output=fopen(argv[3], "w");
    FILE* verificare_task=fopen(argv[1], "r");

    if(fisier_input==NULL)
    {
        puts("Eroare!");
        exit(1);
    }

    if(verificare_task==NULL)
    {
        puts("Eroare!");
        exit(1);
    }

    int task=determinTask(verificare_task);
    if(task==-1)
    {
        puts("Nu s-a gasit taskul");
        exit(1);
    }
    else{
        printf("Se rezolva cazul:%d ", task);
        switch(task){
            case 1:
                int nrEchipe, nrPlayeri;
    fscanf(fisier_input, "%d", &nrEchipe);

    struct Team* teamList=NULL;
    int i, j;
    for(i=0; i<nrEchipe; i++)
    {
        fscanf(fisier_input, "%d", &nrPlayeri);
        char* numeEchipa=citireNumeEchipa(fisier_input);

        teamList=creazaEchipa(numeEchipa, teamList);

        for(j=0; j<nrPlayeri; j++)
        {
            char* firstName=citireSir(fisier_input);
            char* secondName=citireSir(fisier_input);
            int points;
            fscanf(fisier_input, "%d", &points);

            //eliberare
            free(firstName);
            free(secondName);
        }
    }

    struct Team* curent=teamList;
    while(curent!=NULL)
    {
        fprintf(fisier_output, "%s\n", curent->name);
        curent=curent->next;
    }

    fclose(fisier_input);
    fclose(fisier_output);
    fclose(verificare_task);

        break;

            case 2:
            printf("2");
            break;

            case 3:
            printf("3");
            break;

            case 4:
            printf("4");
            break;

            case 5:
            printf("5");
            break;

            default:
            printf("error");
        }
    }

    //printf("%d", task);


    /*
    int nrEchipe, nrPlayeri;
    fscanf(fisier_input, "%d", &nrEchipe);

    struct Team* teamList=NULL;
    int i, j;
    for(i=0; i<nrEchipe; i++)
    {
        fscanf(fisier_input, "%d", &nrPlayeri);
        char* numeEchipa=citireNumeEchipa(fisier_input);

        teamList=creazaEchipa(numeEchipa, teamList);

        for(j=0; j<nrPlayeri; j++)
        {
            char* firstName=citireSir(fisier_input);
            char* secondName=citireSir(fisier_input);
            int points;
            fscanf(fisier_input, "%d", &points);

            //eliberare
            free(firstName);
            free(secondName);
        }
    }

    struct Team* curent=teamList;
    while(curent!=NULL)
    {
        fprintf(fisier_output, "%s\n", curent->name);
        curent=curent->next;
    }

    fclose(fisier_input);
    fclose(fisier_output);
    fclose(verificare_task);
    */
    return 0;
}
