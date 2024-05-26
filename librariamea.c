#include "librariamea.h"


//functie pt eliminare spatii dupa numele echipei
void stergCaractere(char* nume)
{
    int i=strlen(nume)-1;
    while(strchr(" \r\n\t\v\f", nume[i]))
        i--;

    nume[i+1]=0;
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
    stergCaractere(buffer);
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
struct Team* creazaEchipa(char* name, float punctajTotal, struct Team* head)
{
    struct Team* newTeam=(struct Team*)malloc(sizeof (struct Team));
    newTeam->name=name;
    newTeam->punctajTotal=punctajTotal;
    newTeam->next=head;
    return newTeam;
}

//elimina echipa
void eliminaEchipa(struct Team** head, int numarEchipe)
{
    while((numarEchipe & (numarEchipe-1))!=0) //verific daca numarEchipe e putere a lui 2
    {
        struct Team* cur=*head;
        struct Team* prev=NULL;
        struct Team* minPrev=NULL;
        struct Team* minTeam=cur;

        while(cur!=NULL)
        {
            if(cur->punctajTotal<minTeam->punctajTotal)
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

//functii pt coada

//functie createQueue
struct Coada* createQueue()
{
    struct Coada *q=(struct Coada*)malloc(sizeof(struct Coada));
    q->fata=q->spate=NULL;
    return q;
}

//functie pentru a baga in coada
void enqueue(struct Coada* coada, struct Team* team1, struct Team* team2)
{
    if (coada->fata==NULL)
        coada->spate=NULL;
    struct Coada_Nod *newNode=(struct Coada_Nod*)malloc(sizeof(struct Coada_Nod));
    newNode->team1=team1;
    newNode->team2=team2;
    newNode->next=NULL;
    if(coada->spate==NULL)
    {
        coada->fata=coada->spate=newNode;
        return; //sar peste ultimele 2 linii ca sa ies din functie
    }

    coada->spate->next=newNode;
    coada->spate=newNode;
}

//functie pentru a scoate din coada
void dequeue(struct Coada *coada)
{
    if(coada->fata==NULL) return;
    struct Coada_Nod *nod=coada->fata;
    coada->fata=coada->fata->next;
    if(coada->fata==NULL)
        coada->spate=NULL;
    free(nod);
}

//functie verific coada goala
int coadaGoala(struct Coada* coada)
{
    return coada->fata==NULL;
}

//functie pentru acces la primul element din coada
struct Coada_Nod* front(struct Coada* coada)
{
    return coada->fata;
}

//functii pentru stiva

//functie createStack
struct Stiva* createStack()
{
    struct Stiva* s=(struct Stiva*)malloc(sizeof(struct Stiva));
    s->varf=NULL;
    return s;
}

//functie pt a baga in stiva
void push(struct Stiva* stiva, struct Team* team)
{
    struct Stiva_Nod *newNode=(struct Stiva_Nod*)malloc(sizeof(struct Stiva_Nod));
    newNode->team=team;
    newNode->next=stiva->varf;
    stiva->varf=newNode;
}

//functie pt a scoate din stiva
void pop(struct Stiva* stiva)
{
    if(stiva->varf==NULL) return;
    struct Stiva_Nod *newNode=stiva->varf;
    stiva->varf=stiva->varf->next;
    //free(newNode);
}

//functie verific stiva goala
int stivaGoala(struct Stiva *stiva)
{
    return stiva->varf==NULL;
}

//functie pt acces la elementul din varful stivei
struct Stiva_Nod* top(struct Stiva *stiva)
{
    return stiva->varf;
}


//FUNCTII TASK

void task1(FILE* fisier_input, FILE* fisier_output, struct Team** teamList, int numarEchipe, int* vectorTask)
{
    int nrPlayeri;

    int i, j;
    for(i=0; i<numarEchipe; i++)
    {
        fscanf(fisier_input, "%d", &nrPlayeri);
        float punctajTotal=0;
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

        punctajTotal/=(float)nrPlayeri;
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


void task3(FILE* fisier_output, struct Team** teamList)
{
    struct Coada* meciuri=createQueue();
    struct Stiva* castigatori=createStack();
    struct Stiva* pierzatori=createStack();

    struct Team* curent=(*teamList);

    

    //adaug echipe in struct meciuri
    while(curent!=NULL && curent->next!=NULL)
    {   
        enqueue(meciuri, curent, curent->next);
        curent=curent->next->next;
    }

    int round=1;

    while(!coadaGoala(meciuri))
    {
       int k=0;    
       fprintf(fisier_output, "\n--- ROUND NO:%d\n", round);    
       while(!coadaGoala(meciuri))
       {
        
        struct Coada_Nod* meci=front(meciuri);
        struct Team* team1=meciuri->fata->team1;
        struct Team* team2=meciuri->fata->team2;
    
        k++;

        dequeue(meciuri);

        if(team2==NULL) break;

        fprintf(fisier_output, "%-33s-%33s\n", team1->name, team2->name);

        if(team1->punctajTotal>team2->punctajTotal)
        {
            team1->punctajTotal+=1;
            push(castigatori, team1);
            push(pierzatori, team2);
        }
        else 
        {

            team2->punctajTotal+=1;
            push(castigatori, team2);
            push(pierzatori, team1);
        }

       } 

        //eliberare memorie echipe pierzatoare
        while(!stivaGoala(pierzatori))
        {
            struct Team* PIERZATORII=top(pierzatori)->team;
            pop(pierzatori);
            free(PIERZATORII->name);
            free(PIERZATORII);
        }

        fprintf(fisier_output, "\nWINNERS OF ROUND NO:%d\n", round);

        //bag castigatorii inapoi in coada de meciuri
        while(!stivaGoala(castigatori))
        {
            struct Team* team1=castigatori->varf->team;
            pop(castigatori);
            fprintf(fisier_output, "%-34s-  %.2f\n", team1->name, team1->punctajTotal);
            if(k==1) break;

            struct Team* team2=castigatori->varf->team;
            pop(castigatori);
            fprintf(fisier_output, "%-34s-  %.2f\n", team2->name, team2->punctajTotal);
            enqueue(meciuri, team1, team2);
        }
        round++;
    }

    //return;

    // printf("inaitne\n");

    // curent=(*teamList);
    // struct Team* top8=NULL;
    // int cnt=0;
    // while(curent!=NULL && cnt<8)
    // {
    //     struct Team* next=curent->next;
    //     curent->next=top8;
    //     top8=curent;
    //     curent=next;
    //     cnt++;
    // }

    // (*teamList)=top8;

    // printf("dipa\n");

    // //se continua meciurile pana se afla echipa castigatoare
    // while(!coadaGoala(meciuri))
    // {
    //     struct Coada_Nod* meci=front(meciuri);
    //     struct Team* team1=meciuri->fata->team1;
    //     struct Team* team2=meciuri->fata->team2;
    //     dequeue(meciuri);

    //     //struct Team* team1=meci->team1;
    //     //struct Team* team2=meci->team2;

    //     if (team1->punctajTotal>=team2->punctajTotal) 
    //     {
    //         team1->punctajTotal+=1;
    //         push(castigatori, team1);
    //     } 
    //     else 
    //     {
    //         team2->punctajTotal+=1;
    //         push(castigatori, team2);
    //     }

    //     free(meci);
    // }

    // struct Team* castigatori_smecheri=top(castigatori)->team;
    // fprintf(fisier_output, "%-34s-%.2f\n", castigatori_smecheri->name, castigatori_smecheri->punctajTotal);

    // //freemem
    // while(!stivaGoala(castigatori)) 
    //     pop(castigatori);

    // while (!stivaGoala(pierzatori))
    //     pop(pierzatori);
    
    // free(castigatori);
    // free(pierzatori);
    // free(meciuri);

}
