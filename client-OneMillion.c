#include "client.h"
#include "client_rendu.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAXMSG MAXREP

int main()
{
    // char concat[50];

    char ret[MAXREP];
    char reponse[MAXMSG];
    char *mil = (char *)malloc(8000000);
    char *enc = (char *)malloc(8000000);

    mode_debug(true);
    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    
    // LOGIN
    envoyer_recevoir("login 12116356 \"NGUYEN\"", reponse);
    envoyer_recevoir("load OneMillion", reponse);

    BayOfPigs_2(reponse, ret);
    printf("\nLe message decypté:\n%s\n", ret);

    envoyer_recevoir("help", reponse);
    // création des 9999 copies
    for (int i = 0; i < 9999; i++)
    {
        strcat(mil, reponse);
    }

    envoyer_recevoir("start", reponse);
    strcat(mil, reponse);
    BayOfPigs_2(mil, enc);
    // 100 premiers caractères
    enc[100] = '\0';
    envoyer_recevoir(enc, reponse);

    BayOfPigs_2(reponse, enc);

    envoyer_recevoir(enc, reponse);
    free(enc);
    free(mil);
    return 0;
}