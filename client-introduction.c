#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP];
    char message[MAXMSG];

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    puts("Bienvenue dans cette introduction à AppoLab !\n"
            "AppoLab est un serveur d'exercices algorithmiques que vous allez devoir \n"
            "utiliser pour vos APPs. Je vais vous guider pas à pas pour que vous \n"
            "puissiez vous débrouiller tout·e seul·e.");

    attendre();

    puts("Le client va maintenant tenter de se connecter automatiquement au serveur \n"
          	"AppoLab. Il vous faut bien entendu pour cela une connection internet.\n"
          	"(En cas de problème, modifiez le fichier client-introduction.c pour \n"
                "utiliser le port 443 au lieu de 9999 sur la ligne 'connexion'.)" );

    attendre();

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    puts("Si tout va bien, vous devez avoir reçu le message de bienvenue d'AppoLab.\n"
            "Si non, arrêtez ce programme (avec Ctrl-C) et demandez de l'aide à un·e enseignant·e.\n"
            "(Si vous avez des difficultés à lire certains messages, modifiez les couleurs dans client.h et recompilez.)"
            );

    attendre();

    puts("Comme indiqué, commencez par vous loguer avec l'identifiant et le mot de \n"
            "passe qui vous ont été fournis. Pour les étudiants d'INF301, le login est\n"
            "votre numéro d'étudiant·e, et le mot de passe votre nom en majuscule.\n"
            "Entrez les au clavier ainsi :\n"
            "login 12345678 \"MOT DE PASSE\"");

    while (true) {
        lire_clavier (message);

        envoyer_recevoir(message, reponse);

        if (strstr(reponse, "Veuillez d'abord") != NULL) {
            puts("Vous devez utiliser la commande 'login'");
        } else if (strstr(reponse, "incorrect") != NULL) {
            puts("Vu avez du vous tromper dans vos identifiants, réessayez...");
        } else if (strstr(reponse, "Bienvenue") != NULL) {
            break;
        } else {
            puts("Message inconnu, réessayez de vous loguer...");
        }
    }

    puts("Bravo, vous venez de vous identifier auprès du serveur !\n"
            "Comme vous pouvez le voir ce programme trace tout ce que vous envoyez au \n"
            "serveur sur les lignes commençant par <<<envoi<<<, et tout ce que répond le \n"
            "serveur sur des lignes commençant par >>>recu >>>.");

    attendre();

    puts("Vous êtes maintenant prêt·e à lancer le premier exercice qui se nomme 'tutoriel'.\n"
            "Lancez le grâce à la commande 'load' ainsi :\n"
            "load tutoriel");

    while (true) {
        lire_clavier(message);
        envoyer_recevoir(message, reponse);

        if (strstr(reponse, "Commande inconnue") != NULL) {
            puts("Vous devez utiliser la commande 'load'");
        } else if (strstr(reponse, "n'existe pas") != NULL) {
            puts("Vu avez du vous tromper dans le nom de l'exercice, réessayez...");
        } else if (strstr(reponse, "Bienvenue") != NULL) {
            break;
        } else {
            puts("Message inconnu, réessayez de vous loguer...");
        }
    }

    puts("Voilà, vous venez de lancer votre premier exercice...\n"
            "Suivez les consignes de l'exercice maintenant.");

    while (true) {
        lire_clavier(message);
        envoyer_recevoir(message, reponse);

        if (strstr(reponse, "trop lent") != NULL) {
            break;
        }
    }

    attendre();

    if (strstr(reponse, "beaucoup trop lent") != NULL) {

        puts("Bon, finalement vous avez échoué à cet exercice, mais c'était\n"
                "fait exprès :-)");
        attendre();
        puts("Relancez ce programme et essayez d'être plus rapide cette fois !");
    }
    else {
        puts("Bravo vous êtes plutôt rapide.\n"
             "Vous pourriez relancer ce programme pour tenter à nouveau votre\n"
             "chance, mais vous allez vite vous rendre compte que c'est fastidieux\n"
             "de retaper votre login et mot de passe à chaque fois...");

        attendre();

        puts("Changez donc de programme et utilisez à la place 'client-tutoriel.c'\n"
                "Par contre, vous devez tout d'abord éditer le fichier, et y trouver où \n"
                "rentrer votre identifiant et mot de passe.");

        attendre();

        puts("Au revoir.");
    }

    deconnexion();

    return 0;
}
