#include "inc.h"
struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};
//criação das váriaveis que serão utilizadas na main
struct pgm img;
struct pgm *filterImg;
unsigned char *hist;
char nomeArquivo[MAXF][MAXN];
DIR *dir;
struct dirent *pImgArq;
int iArquivo = 0;
char identificador[TAMCHAR];