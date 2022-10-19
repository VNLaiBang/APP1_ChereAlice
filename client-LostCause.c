#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "client_rendu.h"

#define MAXMSG MAXREP

int main()
{
    char reponse[MAXREP]; // pour stocker la réponse du serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12116356 NGUYEN", reponse);
    envoyer_recevoir("load LostCause", reponse);  

    char decrypt[MAXMSG];
    decrypteSeq(reponse, decrypt);
    printf("\nLe message dcrypte: %s\n",decrypt);

    char decrypt2[MAXMSG];
    envoyer_recevoir("help", reponse);
    decrypteSeq(reponse, decrypt2);
    printf("\nLe message decrypte: %s", decrypt2);

    // char decrypt3[MAXMSG];
    // char txt[MAXMSG] = "abcbcca";
    // crypteAssoc(txt, decrypt3);
    // printf("\nLe message decrypte: %s", decrypt3);

    char decrypte3[MAXMSG];
    // char txt_2[MAXMSG] = "abcabaa";
    envoyer_recevoir("start", reponse);
    decrypteAssoc(reponse, decrypte3);
    printf("\nLe message decrypte %s\n",decrypte3);

    envoyer_recevoir("tout va bien",reponse);
    envoyer_recevoir("end", reponse);

    return 0;
}