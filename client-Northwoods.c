#include "client_rendu.h"
#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

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
    envoyer_recevoir("login 12116356 \"NGUYEN\"", reponse);
    envoyer_recevoir("load Northwoods", reponse);
    envoyer_recevoir("start", reponse);
    envoyer_recevoir("hasta la victoria siempre",reponse);

    char decrypt1[MAXMSG];
    decrypteSeq(reponse, decrypt1);
    printf("\nLe message decrypté: %s\n", decrypt1);
    
    // L'etape de prise le password
    char passAuto1[100];
    for (int m = 0; m < 20; m++) {
        passAuto1[m] = decrypt1[strlen(decrypt1) - 29 + m];
    }
    envoyer_recevoir(passAuto1,reponse);

    char decrypt2[MAXMSG];
    decrypteSeq(reponse, decrypt2);
    printf("\nLe message decrypté: %s", decrypt2); 

    char message[MAXREP] = "There will be no Nineteen Eighty-Four";
    char passCrypteSeq[100];
    crypteSeq(message, passCrypteSeq);
    envoyer_recevoir(passCrypteSeq, reponse);
    
    char decrypte3[MAXMSG];
    decrypteSeq(reponse + 24, decrypte3);
    envoyer_recevoir(decrypte3, reponse);

    printf("Fin de la connection au serveur\n");

    return 0;
}