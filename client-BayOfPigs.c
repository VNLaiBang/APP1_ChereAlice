#include "client.h"
#include "client_rendu.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main()
{
    char reponse[MAXREP];    // pour stocker la réponse du serveur
    char repDecrypt[MAXREP]; // Pour stocker le message decrypte dans help
    char txt[MAXMSG];        // Pour decrypter le message dans start
    char enc[MAXREP];        // Pour stocker le pass "Patria o muerte" encrypte par crypteMove

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12116356 NGUYEN", reponse);
    envoyer_recevoir("load BayOfPigs", reponse);
    int decale = 5;
    char decryptCesar[MAXREP];
    decodeCesar(reponse, decryptCesar, decale);
    printf("\nLe message decrypte apres load BayOfPigs:\n%s", decryptCesar);
    envoyer_recevoir("help", reponse);

    decodeCesar(reponse, repDecrypt, decale); /* Decoder le message dans help */
    printf("\nLe message decrypte dans help:\n%s", repDecrypt);
    envoyer_recevoir("start", reponse);

    BayOfPigs_2(reponse, txt);
    printf("\n%s", txt);

    char pass[MAXMSG] = "Patria o muerte";
    crypteMove(pass, enc); // Encrypter le pass avec crypteMove
    envoyer_recevoir(enc, reponse);

    char enc_2[MAXREP]; // Pour stocker la reponse
    BayOfPigs_2(reponse, enc_2);

    envoyer_recevoir(enc_2, reponse);

    printf("\nFin de la connection au serveur\n");
    return 0;
}