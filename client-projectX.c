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
    char texteDecrypte[MAXMSG]; // Pour stocker le message decrypte par decodeCesar
    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12116356 \"NGUYEN\"", reponse);
    envoyer_recevoir("load projetX", reponse);

    envoyer_recevoir("help", reponse); /*Je decode le message recu par serveur*/

    int decale = 5;
    decodeCesar(reponse, texteDecrypte, decale);

    texteDecrypte[strlen(texteDecrypte) - 55] = '\0'; // Cette ligne sert a eviter le cas il decale aussi la phrase "Envoyer 'stat' ..."

    printf("\nLe texte decypté:\n%s",texteDecrypte);

    // Getting started
    envoyer_recevoir("start", reponse);
    envoyer_recevoir("veni vidi vici", reponse);

    envoyer_recevoir("end",reponse);
    printf("Fin de la connection au serveur\n");
    return 0;
}