#include <stdio.h>
#include <stdlib.h>

void gravarEmCSV(const unsigned char * hist, char *const fileName){
    FILE *arquivoCVS;

    // adcionar um arquivo no fim de curso
    arquivoCVS = fopen("teste2.csv", "ab");
    
    for(int i = 0; i < 256; i++){
        // printf("%d, ", *(hist+i));
        fprintf(arquivoCVS, "%d,", *(hist+i));
    }

    fprintf(arquivoCVS, "%c\n", fileName[1]);

    fclose(arquivoCVS);

}