#include "client_rendu.h"
#include <string.h>
#include "client.h"
#define MAXMSG MAXREP

/* -----------------Decoder dans projectX------------------*/
void decodeCesar(char *enc, char *txt, int decale)
{ /*La fonction qui permet de decoder le code Cesar */
    for (unsigned long i = 0; i < strlen(enc); i++)
    {
        char carac = enc[i];

        if (carac <= 'z' && carac >= 'a')
        { // Cas minuscule
            txt[i] = (carac + (26 - decale) - 'a') % 26 + 'a';
        }
        else if (carac <= 'Z' && carac >= 'A')
        { // Cas Majuscule
            txt[i] = (carac + (26 - decale) - 'A') % 26 + 'A';
        }
        else
        {
            txt[i] = enc[i];
        }
    }
}
/* -------------------------------------------------------- */

/* ---------------- Fonction crypteMove -------------------*/
void XcharALaFin(char *txt, unsigned long x, char *stock)
{
    unsigned long len = strlen(txt);
    if (len > x)
    {
        unsigned long l = 0;
        while (l < len - x)
        {
            txt[l] = txt[l + x];
            l++;
        }
        while (l < len)
        {
            txt[l] = stock[l - (len - x)];
            l++;
        }
    }
}

void decalerTxt(char *txt, unsigned long len)
{
    unsigned long j = 1;
    while (j < len)
    {
        txt[j - 1] = txt[j]; // Remplacer le caractere par la suite
        j++;
    }
    txt[j - 1] = '\0'; // Fermer txt par remplacer le dernier caractere par '\0'
}

void crypteMove(char *txt, char *enc)
{
    unsigned long i = 0;
    while (txt[0] != '\0')
    {
        char carac; // Pour stocker le premier caractere de txt

        carac = txt[0]; // Prendre le 1er caractere et le mettre dans carac
        enc[i] = carac; // Mettre a la fin du enc

        unsigned long len = strlen(txt); // La longueur de txt
        if (len > 0)
        {
            decalerTxt(txt, len);
        }

        unsigned long x;
        x = carac % 8; // Prendre modulos 8 de carac

        char stock[8];
        // Lưu X chữ cái đầu tiên của txt vào trong stock
        for (unsigned long k = 0; k < x; k++)
        {
            stock[k] = txt[k];
        }
        stock[x] = '\0'; // Fermer le stock

        XcharALaFin(txt, x, stock); // Envoyer X caracter a la fin du txt
        i++;
    }
}
/* --------------------------------------------------------- */

/* --------------------Fonction BayOfPigs - version originale ------------------- */
void XcharAuDebut(char *txt, unsigned long x, char *stock)
{
    unsigned long len_txt = strlen(txt);
    for (unsigned long j = 1; j <= len_txt; j++)
    {
        txt[len_txt + x - j] = txt[len_txt - j]; // Decaler X fois vers la fin
    }

    for (unsigned long k = 0; k < x; k++)
    {
        txt[k] = stock[k]; // Mettre stock au debut du texte
    }
    txt[len_txt] = '\0';
}

void BayOfPigs(char *enc, char *txt)
{
    char carac;
    while (enc[0] != '\0')
    {
        carac = enc[strlen(enc) - 1]; // Prendre le dernier caractere
        enc[strlen(enc) - 1] = '\0';  // Enlever ce caractere

        unsigned long x;
        x = carac % 8; // Prendre modulos 8 de carac

        unsigned long len_txt = strlen(txt);
        char stock[8]; // Stocker temporairement X caractere
        if (len_txt > x)
        {
            for (unsigned long i = 0; i < x; i++)
            {
                stock[i] = txt[len_txt - x + i]; // Prendre X dernier caracter de txt
            }
            XcharAuDebut(txt, x, stock); // Mettre au debut
        }
        for (unsigned long l = 1; l <= len_txt; l++)
        {
            txt[len_txt + 1 - l] = txt[len_txt - l]; // Decaler 1 fois vers la fin
        }
        txt[0] = carac; // mettre le caractere au debut
        txt[len_txt + 1] = '\0';
        stock[x] = '\0';
    }
}
/* -------------------- Version for OneMillion (pour aller plus vite)----------------------- */
void BayOfPigs_2(char *enc, char *txt)
{
    int i, x, skip, len = 0;
    char *head = txt; // pointer head vers txt


    /* Cet etape equivalent a la fonction strlen(enc) */
    while (enc[len] != '\0') // Tant que enc n'est pas fini
    {
        ++len; // Prendre la longueur du sequence
    }

    for (i = 0; i < len; ++i)
    {
        txt[i] = '*'; // Marquer aux place vide des etoiles
    }

    for (i = 0; i < len - 1; ++i)
    {
        *txt = *enc; // Mettre le premiere de enc a txt
        x = *(enc++) % 8; // (tinh ki tu tiep theo)

        if (len - i > x) 
            ++x;
        else
            x = 1;

        for (skip = 0; skip < x; ++skip) // decplacer le pointeur
            do
            {
                txt++; // Pour la position suivante dans txt
                if (head + len == txt) // Comparaisons l'address
                    txt = head;
            } while (*txt != '*');
    }
    *txt = *enc; // Evite une infinite de boucle en deplacant pointer
    head[len] = '\0';
}

/* --------------------Fonction CrypteSeq--------------------*/
void crypteSeq(char *txt, char *output)
{
    char seq[MAXMSG] = "\0";
    char lettre;

    // strcpy(txt,reponse);
    for (unsigned long i = 0; i < strlen(txt); i++)
    {
        char c;
        c = txt[i]; // Predre caractere a chaque fois
        unsigned long indice = 0;

        unsigned long len_seq = strlen(seq);
        unsigned long len_output = strlen(output);
        unsigned long j = 0;

        char c_confirm = 'n'; // Confirmer si carac est dans la sequence
        while (j < len_seq)
        {
            if (c == seq[j])
            {
                c_confirm = 'c'; // Si il existe -> confirme
                indice = j;
            }
            j++;
        }

        if (c_confirm == 'c') // Si le caractere est dans la sequence
        {
            if (indice != 0)
            {
                // Gerer la sequence
                lettre = seq[indice - 1];
            }
            else
            {
                lettre = seq[len_seq - 1];
            }

            // L'etape de decalage
            for (unsigned long k = indice; k < len_seq; k++)
            {
                seq[k] = seq[k + 1];
            }

            seq[len_seq - 1] = c;
            seq[len_seq] = '\0';

            // Ajoute la lettre devant dans output
            output[len_output] = lettre;
            output[len_output + 1] = '\0';
        }
        else
        {
            output[len_output] = c;
            seq[len_seq] = c;
            output[len_output + 1] = '\0';
            seq[len_seq + 1] = '\0';
        }
    }
}

/* --------------------------------------------------------- */

/* -------------------------decrypteSeq--------------------- */
void decrypteSeq(char enc[MAXMSG], char decrypt[MAXREP])
{
    char carac; // Pour stocker caracter encypte dans enc
    char seq[MAXMSG] = "\0";
    unsigned long len = strlen(enc);
    for (unsigned long i = 0; i < len; i++)
    {
        carac = enc[i];           // Stocker le caractere en cara
        unsigned long indice = 0; // L'indice de carac dans la sequence

        unsigned long len_seq = strlen(seq);
        unsigned long len_decrypt = strlen(decrypt);

        char carac_confirm = 'n';
        // Verifier si carac est dans la sequence
        unsigned long j = 0;
        while (j < len_seq)
        {
            if (carac == seq[j])
            {
                carac_confirm = 'c'; // Si carac existe dans seq
                indice = j;
            }
            j++;
        }

        // Si carac n'est pas dans la sequence
        if (carac_confirm == 'n')
        {
            decrypt[len_decrypt] = carac;    // Ajouter le carac a la fin du decrypt
            decrypt[len_decrypt + 1] = '\0'; // Fermer le message decrypte
            seq[len_seq] = carac;            // Mettre carac a la fin du sequence
            seq[len_seq + 1] = '\0';         // Fermer la sequence
        }
        else
        {
            unsigned long indice_decrypt;
            char lettre_decrypt;
            if (indice != len_seq - 1) // Si le caractere n'est pas la dernier lettre
            {
                indice_decrypt = indice + 1; // Prendre la lettre suivante
                lettre_decrypt = seq[indice_decrypt];
            }
            else // Sinon
            {
                indice_decrypt = 0; // Prendre la premiere lettre dans la sequence
                lettre_decrypt = seq[indice_decrypt];
            }

            for (unsigned long k = indice_decrypt; k < len_seq; k++)
            {
                seq[k] = seq[k + 1]; // On envoie la lettre suivant la fin, alors il faut decaler les lettres dans la sequence
            }

            seq[len_seq - 1] = lettre_decrypt;
            seq[len_seq] = '\0';

            decrypt[len_decrypt] = lettre_decrypt;
            decrypt[len_decrypt + 1] = '\0';
        }
    }
}
/* --------------------------------------------------------- */

/* -----------------------crypte Assoc --------------------- */
void echangeavant(char *aso, unsigned long indice)
{
    /*Permettre d'echanger l'association de carac avec celle avant*/
    char tmp;
    unsigned long len_aso = strlen(aso);
    if (indice != 0)
    {
        tmp = aso[indice - 1];
        aso[indice - 1] = aso[indice];
        aso[indice] = tmp;
    }
    else // Si indice == 0, carac est le premiere caractere
    {
        tmp = aso[len_aso - 1];
        aso[len_aso - 1] = aso[0];
        aso[0] = tmp;
    }
}

void ALaFin(char *tab, unsigned long indice)
{
    /*Permettre d'envoyer le carac a la fin du tableau*/
    char carac = tab[indice];
    unsigned long len = strlen(tab);
    for (unsigned long k = indice; k < len; k++)
    {
        tab[k] = tab[k + 1];
    }
    tab[len - 1] = carac;
}

void crypteAssoc(char *txt, char *enc)
{
    char carac;           // Pour stocker le caractere dans la sequence
    unsigned long indice; // L'indice du carac dans la sequence
    char seq[MAXMSG] = "\0";
    char aso[MAXMSG] = "\0";
    unsigned long len_txt = strlen(txt);
    for (unsigned long i = 0; i < len_txt; i++)
    {
        carac = txt[i];

        char c_confirm = 'n'; // Confirmer si carac est dans la sequence
        unsigned long len_seq = strlen(seq);
        unsigned long j = 0;
        while (j < len_seq)
        {
            if (carac == seq[j])
            {
                c_confirm = 'c'; // Si il existe -> confirme
                indice = j;
            }
            j++;
        }

        if (c_confirm == 'n')
        {
            aso[len_seq] = carac;
            seq[len_seq] = carac;
            enc[i] = carac;
            enc[i + 1] = '\0';
        }
        else // Si il existe deja dans la sequence
        {
            echangeavant(aso, indice);
            enc[i] = aso[indice];
            ALaFin(aso, indice);
            ALaFin(seq, indice); // Envoyer le dernier caractere en meme temps
            seq[len_seq + 1] = '\0';
            aso[len_seq + 1] = '\0';
        }
    }
}

/* ---------------------decrypte Assoc --------------------- */
void echangesuivant(char *seq, unsigned long indice)
{
    /*Permettre d'echanger l'association de carac avec celle avant*/
    char tmp;
    unsigned long len_seq = strlen(seq);
    if (indice != len_seq - 1)
    {
        tmp = seq[indice + 1];
        seq[indice + 1] = seq[indice];
        seq[indice] = tmp;
    }
    else // Si indice == 0, carac est le premiere caractere
    {
        tmp = seq[len_seq - 1];
        seq[len_seq - 1] = seq[0];
        seq[0] = tmp;
    }
}

/* ----------------------Decrypter Assoc ---------------------*/
void decrypteAssoc(char *txt, char *enc)
{                         // Ici, on trouve que si on echange le role de seq et aso on aura le decryptage
    char carac;           // Pour stocker le caractere dans la sequence
    unsigned long indice; // L'indice du carac dans la sequence
    char seq[MAXMSG] = "\0";
    char aso[MAXMSG] = "\0";
    unsigned long len_txt = strlen(txt);
    for (unsigned long i = 0; i < len_txt; i++)
    {
        carac = txt[i];

        char c_confirm = 'n'; // Confirmer si carac est dans la sequence
        unsigned long len_aso = strlen(aso);
        unsigned long j = 0;
        while (j < len_aso)
        {
            if (carac == aso[j])
            {
                c_confirm = 'c'; // Si il existe -> confirme
                indice = j;
            }
            j++;
        }

        if (c_confirm == 'n')
        {
            aso[len_aso] = carac;
            seq[len_aso] = carac;
            enc[i] = carac;
            enc[i + 1] = '\0';
        }
        else // Si il existe deja dans la sequence
        {
            echangesuivant(seq, indice);
            enc[i] = seq[indice];
            ALaFin(aso, indice);
            ALaFin(seq, indice);
            seq[len_aso + 1] = '\0';
            aso[len_aso + 1] = '\0';
        }
    }
}