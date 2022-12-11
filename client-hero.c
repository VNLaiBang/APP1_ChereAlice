#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celulle {
	char *valeur;
	struct celulle *suivant;
} cellule;

typedef struct liste {
	cellule *tete;
	cellule *queue;
} liste;

void
ajouter_queue(liste *li, char *n)
{
	char *str;
	cellule *tmp;

	str = malloc(20);
	strcpy(str, n);
	tmp = malloc(sizeof(cellule));
	tmp->valeur = str;
	tmp->suivant = NULL;

	if (li->tete == NULL) {
		li->tete = li->queue = tmp;
		return;
	}

	li->queue = li->queue->suivant = tmp;
}

// if 0 then gotta check if we are done
int
getpages(liste *li, char *str, int *n)
{
	char tmp[20] = "";
	int x;

	*n = 0;

	if (strstr(str, "empoisonné") != NULL)
		return 0;

	if (strstr(str, "gagné") != NULL)
		return 0;

	if (strstr(str, "Ha bah non") != NULL)
		return 0;

	if (strstr(str, "aussi vite") != NULL)
		str = strstr(str, "vite");

	while ((str = strstr(str, " page")) != NULL) {
		*n += sscanf(str, "%*s %s", tmp);
		x = strlen(tmp);
		if (tmp[x - 1] == '.' || tmp[x - 1] == ',')
			tmp[x - 1] = '\0';
		ajouter_queue(li, tmp);
		++str;
	}

	if (*n == 0)
		return 0;
	return 1;
}

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP];
	liste pages;
	cellule *cel;
    int n;
	/* représente le chemin (trouvé avec un parcours en profondeur qui dure une heure...)
	 * on compte à partir de zero de gauche a droite;
	 */
	int chemin[100] = { 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 2, 1, 0, 0, 2, 2, 2, 0, 2, 1, 3, 0, 1, 1, 3, 2, 0, 0, 2, 0, 17, 0, 20, 0, 21, 0, 8, 0, 5, 0, 3, 0, 9, 0, 13, 0, 3, 0, 3, 0, 5, 0, 4, 0, 1, 1, 2, 0, 0, 0, 1, 0, 3, 2, 1, 0, 114, 49 };
	int y = 0;

	pages.queue = NULL;
	pages.tete = NULL;
    connexion("im2ag-appolab.u-ga.fr", 9999);
	mode_debug(1);


    envoyer_recevoir("login 12116356 NGUYEN", reponse);

	envoyer_recevoir("load hero", reponse);
	envoyer_recevoir("start", reponse);
	envoyer_recevoir("NGUYEN", reponse);

	for (int ti = 0; ti < 81; ++ti) {
		getpages(&pages, reponse, &n);
		cel = pages.tete;
		for (int pzk = 0; pzk < chemin[y]; ++pzk)
			cel = cel->suivant;
		envoyer_recevoir(cel->valeur, reponse);
		++y;
		pages.queue = NULL;
		pages.tete = NULL;
	}
	// envoyer_recevoir("gro naz", reponse);
	// envoyer_recevoir("perlimpimpin", reponse);
	// envoyer_recevoir("fin", reponse);

	return 0;
}
