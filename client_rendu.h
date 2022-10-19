#ifndef __CLIENT_RENDU_H__
#define __CLIENT_RENDU_H__


/* ProjectX */
void decodeCesar(char *enc, char *txt, int decale); 
    /*Permettre de decoder le code cesar*/ 

/* crypteMove */
void crypteMove(char *txt, char *enc);

/* BayOfPigs */
void BayOfPigs(char *enc, char *txt);

/* BayOfPigs_2 */
void BayOfPigs_2(char *source, char *dest);

/* crypteSeq */
void crypteSeq(char *txt, char *output);

/* decrypteSeq */
void decrypteSeq(char *enc, char *output);

/* crypteAssoc*/
void crypteAssoc(char *txt, char *enc);

/* decrypteAssoc*/
void decrypteAssoc(char *txt, char *enc);

#endif 
