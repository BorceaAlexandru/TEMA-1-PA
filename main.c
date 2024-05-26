#include "librariamea.h"

int main(int argc, char** argv){

    FILE* fisier_input=fopen(argv[2], "r");
    FILE* fisier_output=fopen(argv[3], "w");
    FILE* verificare_task=fopen(argv[1], "r");

    if(fisier_input==NULL)
    {puts("Eroare!");
    exit(1);}

    if(verificare_task==NULL)
    {puts("Eroare!");
    exit(1);}

    int numarEchipe;
    fscanf(fisier_input, "%d", &numarEchipe);\
    struct Team* teamList=NULL;

    int *vectorTask=(int*)malloc(5*sizeof(int));
    for(int i=0; i<5; i++)
        fscanf(verificare_task, "%d", &vectorTask[i]);


    if(vectorTask[0]==1) task1(fisier_input, fisier_output, &teamList, numarEchipe, vectorTask);
    if(vectorTask[1]==1) task2(fisier_output, numarEchipe, &teamList);
    if(vectorTask[2]==1) task3(fisier_output, &teamList); 

    fclose(fisier_input);
    fclose(fisier_output);
    fclose(verificare_task);
    return 0;
}