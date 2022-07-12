void readPGMImage(struct pgm *pio, char *filename)
{

    FILE *fp;
    char ch;

    if (!(fp = fopen(filename, "r")))
    {
        perror("Erro.");
        exit(1);
    }

    if ((ch = getc(fp)) != 'P')
    {
        puts("A imagem fornecida não está no formato pgm");
        exit(2);
    }

    pio->tipo = getc(fp) - 48;

    fseek(fp, 1, SEEK_CUR);

    // pra vê se tem comentarios
    while ((ch = getc(fp)) == '#')
    {
        while ((ch = getc(fp)) != '\n')
            ;
    }

    fseek(fp, -1, SEEK_CUR);

    fscanf(fp, "%d %d", &pio->c, &pio->r);
    if (ferror(fp))
    {
        perror(NULL);
        exit(3);
    }
    fscanf(fp, "%d", &pio->mv);
    fseek(fp, 1, SEEK_CUR);

    // dados da imagem
    pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char));

    switch (pio->tipo)
    {
    case 2:
        puts("Lendo imagem PGM (dados em texto)");
        for (int k = 0; k < (pio->r * pio->c); k++)
        {
            fscanf(fp, "%hhu", pio->pData + k);
        }
        break;
    case 5:
        puts("Lendo imagem PGM (dados em binário)");
        fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
        break;
    default:
        puts("Não está implementado");
    }

    fclose(fp);
}

void writePGMImage(struct pgm *pio, char *filename)
{
    FILE *fp;
    char ch;

    if (!(fp = fopen(filename, "wb")))
    {
        perror("Erro.");
        exit(1);
    }

    fprintf(fp, "%s\n", "P5");
    fprintf(fp, "%d %d\n", pio->c, pio->r);
    fprintf(fp, "%d\n", 255);

    fwrite(pio->pData, sizeof(unsigned char), pio->c * pio->r, fp);

    fclose(fp);
}

void viewPGMImage(struct pgm *pio)
{
    printf("Tipo: %d\n", pio->tipo);
    printf("Dimensões: [%d %d]\n", pio->c, pio->r);
    printf("Max: %d\n", pio->mv);

    for (int k = 0; k < (pio->r * pio->c); k++)
    {
        if (!(k % pio->c))
            printf("\n");
        printf("%d ", *(pio->pData + k));
    }
    printf("\n");
}

void histogramaCSV(const unsigned char *hist, char *const nomeArquivo, char * identificador)
{
    FILE *arquivoCVS;

    // adcionar um arquivo no fim de curso
    arquivoCVS = fopen("outputHistogram.csv", "ab");

    for (int i = 0; i < 256; i++)
    {
        fprintf(arquivoCVS, "%d,", *(hist + i));
    }
    
    fprintf(arquivoCVS, "%c\n", identificador);

    fclose(arquivoCVS);
}

void filtrolbp(struct pgm *img, struct pgm *imgFiltro)
{
    // Filtro LBP. Janela de 8 bits. Método Comparativo
    // Prenchimento da estrutura
    imgFiltro->tipo = 5;
    imgFiltro->r = img->r;
    imgFiltro->c = img->c;
    imgFiltro->mv = 255;
    imgFiltro->pData = (unsigned char *)calloc(imgFiltro->r * imgFiltro->c, sizeof(unsigned char));

    // Execução do filtro LBP
    int l = imgFiltro->r, c = imgFiltro->c;  // linhas e colunas
    unsigned char soma, pixelMatriz; // soma dos bits das janelas e bit da janela
    int j, k, s, pos;    // j = posição linha, k = posição coluna, s = sentido
    // de rotação, pos = posição do bit na janela

    for (int i = 0; i < l * c; i++)
    { // i = posição ponteiro inicial
        soma = 0, j = -1, k = -1, s = 1, pos = 0;//mantido
               
        for (int p = 0; p < T; p++)        
        {
            pixelMatriz = ((i < c && j == -1) || (!(i % c) && k == -1) || (i > (l * c) - c && j == 1) || (!((i + 1) % c) && k == 1)) ? 0 : *(img->pData + i + k + j * c);
            //no primeiro caso, verifica se esta nas quinas da matriz, pois n tera um valor prévio inserido na janela do filtro, caso sim o pixel atual é preenchido com 0, se não é inserido o valor referente a coordenada do pixel
            if (pixelMatriz >= *(img->pData + i)) soma += pow(2, pos);//caso em que se tem a comparação do pixel da janela com o pixel central, que pertence a imagem original        
         
            pos++;

            switch (s)
            { // J e K desloca a janela, s Muda o sido da janela
            case 1:
                k++;
                if (k == 1)
                    s++;
                break;
            case 2:
                j++;
                if (j == 1)
                    s++;
                break;
            case 3:
                k--;
                if (k == -1)
                    s++;
                break;
            case 4:
                j--;
                if (j == -1)
                    s++;
                break;
            }
        }
       
        *(imgFiltro->pData + i) = soma; // Recebe a soma dos bits no ponteiro de saída
    }
    
}

void histograma(unsigned char *m, int l, int c, unsigned char *hist)
{
    for (int i = 0; i < l * c; i++)
    {
        *(hist + *(m + i)) += 1;
    }  

}