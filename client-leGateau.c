// Exercice "leGateau" sur AppoLab

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "client.h"

#define MAXMSG MAXREP

void dernierNombre(char *s, char *res) {
    int i = strlen(s) - 1;
    char tab[100];
    while (s[i] != '\0') {
        i++;
    }
    while (i >= 0 && !isdigit(s[i])) {
        i--;
    }
    int j = i;
    while (j >= 0 && isdigit(s[j])) {
        j--;
    }
    j++;
    int k = 0;
    while (j <= i) {
        tab[k] = s[j];
        j++;
        k++;
    }
    tab[k] = '\0';
    strcpy(res, tab);
}

void dernierMot(char *s, char *res) {
    int i = strlen(s) - 1;
    char tab[100];
    while (s[i] != '\0') {
        i++;
    }
    while (i >= 0 && s[i] != ' ') {
        i--;
    }
    i++;
    int j = 0;
    while (s[i] != ' ' && s[i] != '\0' && s[i] != '.' && s[i] != ',' && s[i] != '!' && s[i] != '?' && s[i] != '"') {
        tab[j] = s[i];
        i++;
        j++;
    }
    tab[j] = '\0';
    strcpy(res, tab);
}

void page(char *s, char *res) {
    int i = 0;
    char tab[100];
    while (s[i] != ' ') {
        i++;
    }
    i++;
    int j = 0;
    while (s[i] != '\0' && s[i] != ' ' && s[i] != '?' && s[i] != '!' && s[i] != '.' && s[i] != ',') {
        tab[j] = s[i];
        i++;
        j++;
    }
    tab[j] = '\0';
    strcpy(res, tab);
}

void premierMot(char *s, char *res) {
    int i = 0;
    char tab[100];
    while (s[i] != ' ') {
        tab[i] = s[i];
        i++;
    }
    tab[i] = '\0';
    strcpy(res, tab);
}

int main()
{
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12116356 NGUYEN", reponse);
    envoyer_recevoir("load leGateau", reponse);

    envoyer_recevoir("start", reponse);

    int nbMessages = 0;
    char *premierNombre;
    int tours = 0;
    while (nbMessages < 10000) {
        
        if (strstr(reponse, "see you page") != NULL)	
            page(reponse+16, message);
        else if (strstr(reponse, "A very small page") != NULL)
            page(reponse + 17, message);
        else if (strstr(reponse, "Looking carefully, you read") != NULL)
            dernierMot(reponse+27, message);
        else if (strstr(reponse, "You are a courageous zealot searching a cake page") != NULL)
            page(reponse + 49, message);
        else if (strstr(reponse, "Page ") != NULL)
            page(reponse+4, message);
        else if (strstr(reponse, "See you on page ") != NULL)
            page(reponse+15, message);
        else if (strstr(reponse, "Go to page") != NULL)
            dernierMot(reponse, message);
        else if (strstr(reponse, "You arrive somewhere... You don't know where, but the only way out is through page"))
            page(reponse+81, message);
        else if (strstr(reponse, "It's not there. Maybe the next pages will help? Next page is"))
            page(reponse+59, message);
        else if (strstr(reponse, "Check page ") != NULL)
            dernierMot(reponse, message);
        else if (strlen(reponse) < 15)
            dernierMot(reponse, message);
        else if (strstr(reponse, "... message ") || nbMessages % 50 == 0 || strstr(reponse, "Try page ") || strstr(reponse, "game") || strstr(reponse, "go") || strstr(reponse, "mind") || strstr(reponse, "deserve some cake") || strstr(reponse, "satisfied with it?") || strstr(reponse, "happens next")
                || strstr(reponse, "Another lie?") || strstr(reponse, "Another life?") || strstr(reponse, "half-life?") || strstr(reponse, "this journey?") || strstr(reponse, "on the table"))
            dernierMot(reponse, message);
        else if (strstr(reponse, "Do you understand"))
            premierMot(reponse, message);
        else 
            dernierNombre(reponse, message);

        if (tours == 0 && nbMessages == 48) {
            envoyer_recevoir(message, reponse);
            envoyer_recevoir(premierNombre, reponse);
            nbMessages = 0;
            dernierNombre(reponse, message);
            tours = 1;
            nbMessages++;
        }
        if (nbMessages == 0 && tours == 0) {
            premierNombre = malloc(strlen(message) + 1);
            strcpy(premierNombre, message);
        }

        if (nbMessages == 100) {
            dernierMot(reponse, message);
            envoyer_recevoir(message, reponse);
            nbMessages++;
        }
        else {
            envoyer_recevoir(message, reponse);
            nbMessages++;
        }
    }
    
    envoyer_recevoir("GlaDOS", reponse);

    printf("Fin de la connection au serveur\n");
    return 0;
}
