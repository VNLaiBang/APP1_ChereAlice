#include "client.h"
#include "client_rendu.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main()
{
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char enc[MAXMSG];     // pour stocker la reponse crypte

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12116356 \"NGUYEN\"", reponse);
    envoyer_recevoir("load crypteMove", reponse);
    envoyer_recevoir("help", reponse);

    crypteMove(reponse, enc);

    envoyer_recevoir("start", reponse);
    envoyer_recevoir(enc, reponse);

    envoyer_recevoir("end",reponse);

    printf("\nFin de la connection au serveur\n");
    return 0;
}
