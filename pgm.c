// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// //#include "pgm.h"

// void readPGMImage(struct pgm *pio, char *filename){

// 	FILE *fp;
// 	char ch;
// 	// printf("%s", filename);

// 	if (!(fp = fopen(filename,"r"))){
// 		perror("Erro.");
// 		exit(1);
// 	}

// 	if ( (ch = getc(fp))!='P'){
// 		puts("A imagem fornecida não está no formato pgm");
// 		exit(2);
// 	}
	
// 	pio->tipo = getc(fp)-48;
	
// 	fseek(fp,1, SEEK_CUR);

// 	// pra vê se tem comentarios
// 	while((ch=getc(fp))=='#'){
// 		while( (ch=getc(fp))!='\n');
// 	}

// 	fseek(fp,-1, SEEK_CUR);

// 	fscanf(fp, "%d %d",&pio->c,&pio->r);
// 	if (ferror(fp)){ 
// 		perror(NULL);
// 		exit(3);
// 	}	
// 	fscanf(fp, "%d",&pio->mv);
// 	fseek(fp,1, SEEK_CUR);

// 	// dados da imagem
// 	pio->pData = (unsigned char*) malloc(pio->r * pio->c * sizeof(unsigned char));

// 	switch(pio->tipo){
// 		case 2:
// 			puts("Lendo imagem PGM (dados em texto)");
// 			for (int k=0; k < (pio->r * pio->c); k++){
// 				fscanf(fp, "%hhu", pio->pData+k);
// 			}
// 		break;	
// 		case 5:
// 			puts("Lendo imagem PGM (dados em binário)");
// 			fread(pio->pData,sizeof(unsigned char),pio->r * pio->c, fp);
// 		break;
// 		default:
// 			puts("Não está implementado");
// 	}
	
// 	fclose(fp);

// }

// void writePGMImage(struct pgm *pio, char *filename){
// 	FILE *fp;
// 	char ch;

// 	if (!(fp = fopen(filename,"wb"))){
// 		perror("Erro.");
// 		exit(1);
// 	}

// 	fprintf(fp, "%s\n","P5");
// 	fprintf(fp, "%d %d\n",pio->c, pio->r);
// 	fprintf(fp, "%d\n", 255);

// 	fwrite(pio->pData, sizeof(unsigned char),pio->c * pio->r, fp);

// 	fclose(fp);

// }

// void viewPGMImage(struct pgm *pio){
// 	printf("Tipo: %d\n",pio->tipo);
// 	printf("Dimensões: [%d %d]\n",pio->c, pio->r);
// 	printf("Max: %d\n",pio->mv);

// 	for (int k=0; k < (pio->r * pio->c); k++){
// 		if (!( k % pio->c)) printf("\n");
// 		printf("%d ",*(pio->pData+k));
// 	}	
// 	printf("\n");
// }