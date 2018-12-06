#include <stdio.h>
#include <stdlib.h>

struct zaznam {
    char kategoria[51];
    char znacka[51];
    char predajca[101];
    char cena[10];
    char rok_vyroby[10];
    char stav_vozidla[201];
    struct zaznam *next;
};

//---------------------------------------------------------------------

void n(struct zaznam **zaznam_zac, struct zaznam **zaznam_act, int *poc_zaznamov){

    FILE *f;
    char pole[201];
    int poc_zaznam=0;

    if ((f = fopen("auta.txt", "r")) == NULL) {           //otvorí súbor a skontroluje či sa správne otovoril
        printf("something is wrong\n");
        return;
    }

    while ((fgets(pole, sizeof(pole), f)) != NULL) {            //spočíta počet záznamov v súbore

        if (pole[0] == '$'){
            poc_zaznam++;}
    }
    *poc_zaznamov = poc_zaznam;

    rewind(f);

    *zaznam_zac = NULL;

    *zaznam_zac = malloc(sizeof(struct zaznam));
    if (*zaznam_zac == NULL)
        printf("something is wrong\n");
    *zaznam_act = *zaznam_zac;

    while (!feof(f)){

        if (((*zaznam_act)->next = malloc(sizeof(struct zaznam))) == NULL) {
            printf("Malo pamate.\n");
            return;
        }

        fscanf(f, "%*c");
        fscanf(f, "%*c");
        fscanf(f, "%51[^\n]", (*zaznam_act)->kategoria);
        fscanf(f, "%*c");
        fscanf(f, "%51[^\n]", (*zaznam_act)->znacka);
        fscanf(f, "%*c");
        fscanf(f, "%101[^\n]", (*zaznam_act)->predajca);
        fscanf(f, "%*c");
        fscanf(f, "%10[^\n]", (*zaznam_act)->cena);
        fscanf(f, "%*c");
        fscanf(f, "%10[^\n]", (*zaznam_act)->rok_vyroby);
        fscanf(f, "%*c");
        fscanf(f, "%201[^\n]", (*zaznam_act)->stav_vozidla);
        fscanf(f, "%*c");


        *zaznam_act = (*zaznam_act)->next;
    }
    (*zaznam_act)->next = NULL;

    if (*poc_zaznamov == 0)
        printf("Zaznamy neboli nacitane\n");
    else
        printf("Nacitalo sa %d zaznamov\n", *poc_zaznamov);

    fclose(f);

}

//---------------------------------------------------------------------

void v(struct zaznam **zaznam_zac, struct zaznam **zaznam_act, int *poc_zaznamov){

    int counter = 1;

    *zaznam_act = *zaznam_zac;

    while (*zaznam_act != NULL){
        if (counter == *poc_zaznamov+1)
            break;
        printf("%d.\n", counter);
        printf("kategoria: %s\n", (*zaznam_act)->kategoria);
        printf("znacka: %s\n", (*zaznam_act)->znacka);
        printf("predajca: %s\n", (*zaznam_act)->predajca);
        printf("cena: %s\n", (*zaznam_act)->cena);
        printf("rok_vyroby: %s\n", (*zaznam_act)->rok_vyroby);
        printf("stav_vozidla: %s\n", (*zaznam_act)->stav_vozidla);
        *zaznam_act = (*zaznam_act)->next;
        counter++;
    }

}

//---------------------------------------------------------------------

int main() {

    char c=0;
    int *poc_zaznamov=0;

    struct zaznam *zaznam_zac, *zaznam_act;

    while (1){
        scanf("%c", &c);

        switch (c){
            case ('n'): n(&zaznam_zac, &zaznam_act, &poc_zaznamov);break;
            case ('v'): v(&zaznam_zac, &zaznam_act, &poc_zaznamov);break;
        }
    }

}