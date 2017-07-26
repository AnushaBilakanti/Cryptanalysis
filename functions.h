//will contain all the declarations
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <openssl/md5.h> 

# define CODES "abcdefghijklmnopqrstuvwxyz"

void keygen(char *pphrase,int period);  
void crypt(FILE *fp,FILE *fp_key1,FILE *fp_key2);
void inverse_key(FILE *keyfile1,FILE *keyfile2);
void histogram(FILE *fp, int period, int position);
void solve(FILE *fp1,FILE *fp2, FILE *fp3,int max_length);

char * RandomInteger(char *pphrase,int length);
char * MD5_gen(char *pphrase,int length);


int getPosition_crypt(char ch);

int get_position_histo(char ch);

int getPosition_inv(char ch);
int get_char(int i);

int get_position_coinci(char ch);
void solve_coincidence(FILE *fp2,int max_length);
void auto_correlation(FILE *fp3,int max_length);









