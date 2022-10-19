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
    envoyer_recevoir("load planB", reponse);
    envoyer_recevoir("start", reponse);
    envoyer_recevoir("help", reponse);

    int decaleinit = reponse[0] - 'C'; /* Chaque fois on lance cet exercice, le message va etre codé en un autre decalage.
                                            Et comme Bob est poli, donc il faut que le premier mot soit Chere...*/
    char decrypt[MAXREP];
    decodeCesar(reponse, decrypt, decaleinit);
    printf("\nLe message decrypte dans help:\n%s", decrypt);

    char pass[100] = "hasta la revolucion";
    char passDecrypt[100];
    decodeCesar(pass, passDecrypt, decaleinit);

    envoyer_recevoir(passDecrypt, reponse);
    char decrypt2[MAXREP];
    decodeCesar(reponse, decrypt2, decaleinit);
    printf("\nLe message decrypte\n%s", decrypt2);
    envoyer_recevoir("end", reponse);

    printf("Fin de la connection au serveur\n");
    return 0;
}