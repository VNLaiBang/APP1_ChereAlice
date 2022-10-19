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
    envoyer_recevoir("login 12116356 \"NGUYEN\"", reponse);
    envoyer_recevoir("load crypteSeq", reponse);  

    char decryp[MAXMSG];
    BayOfPigs_2(reponse, decryp);
    envoyer_recevoir(decryp, reponse);

    envoyer_recevoir("start",reponse);
    
    char decrypStart[MAXMSG];
    BayOfPigs_2(reponse, decrypStart);
    
    printf("\nLe message decrypté:\n%s",decrypStart);

    char crypteParCSeq[MAXMSG];
    crypteSeq(decrypStart, crypteParCSeq);
    envoyer_recevoir(crypteParCSeq,reponse);
    
    char decrypteParSeq[MAXREP];
    decrypteSeq(reponse + 83, decrypteParSeq);
    envoyer_recevoir(decrypteParSeq, reponse);

    
    return 0;
}