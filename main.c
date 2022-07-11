#include "lib.h"

int main(int argc, char *argv[])
{
    filterImg = malloc(sizeof(struct pgm));  

    dir = opendir("./imgs/");  
   
    while ((pImgArq = readdir(dir)) != NULL){

        strcpy(nomeArquivo[iArquivo], "./imgs/");
        identificador[iArquivo] = pImgArq->d_name[0];
        strcat(nomeArquivo[iArquivo], pImgArq->d_name);
        iArquivo++;

    }

    for (int i = 2; i < iArquivo; i++){

        readPGMImage(&img, nomeArquivo[i]);
        filtrolbp(&img, filterImg);
        hist = malloc(TAMCHAR * sizeof(unsigned int));
        histograma(filterImg->pData, filterImg->r, filterImg->c, hist);
        histogramaCSV(hist, nomeArquivo[i], identificador[i]);

    }

    closedir(dir);

    return 0;
}