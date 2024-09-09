#include <stdio.h>
#include <string.h>  // para usar a fun��o strcmp() que compara duas strings
#include <stdlib.h>  // para usar a fun��o exit() que interrompe (aborta) a execu��o do programa.


// ------------------------Estrutura de Pilha Encadeada-----------------------------------
typedef struct TpDADO {
    int L, C;
} TpDADO;

typedef struct TpNODE {  /// estrutura da "caixa" do nodo
            TpDADO dado;
            struct TpNODE *prox; /// permite encadear caixas (*p para Link)
    } TpNODE;

typedef struct TpPILHA {   /// cabecalho (ou descritor) da estrutura de dados
            TpNODE *topo;
          //  int len;    /// campos complementares do descritor
          //  TpNODE *fim; ///
    } TpPILHA;

void displayLL(TpPILHA *p) {
printf("\n Display:\n");
    if(p->topo) // se o ponteiro nao eh NULL
    {
        TpNODE *paux;
        paux = p->topo;
        printf("Os elementos armazenados na Pilha sao:\n");
        do
        {
            printf(" (%d,%d)  ", paux->dado.L, paux->dado.C);
            paux = paux->prox;

        } while(paux);
        printf("\n ......... Fim da PILHA .........\n");
    }
    else {
        printf("\n ......... PILHA Vazia. \n\n");
    }
    return;
}


void InicializaPilha(TpPILHA *p){
printf("\n Inicializa:\n");
//    p = (TpPILHA*) malloc(sizeof(TpPILHA));
//    if (!p) {
//        printf("\n ERRO de alocacao da PILHA:\n");
//        exit(0);
//    }
    p->topo = NULL;
   ///  p->len = 0;   /// outros campos do descritor
   ///  p->fim = NULL;

}


int push(TpDADO x, TpPILHA *p) { /// empilhar x

    TpNODE *paux;
    /// alocar memoria
    paux = (TpNODE*) malloc(sizeof(TpNODE*));
    /// se houve erro na alocacao, entao paux eh NULL (??)
    /// em C, NULL eh o mesmo que ZERO
    if(!paux) {
        printf("\n ERRO na alocacao de um novo NODO na pilha.");
        return -1;
    }

    /// inserir x = 20 na memoria alocada
    paux->dado = x;
    paux->prox = p->topo;
    p->topo = paux;

    return 1;/// sucesso
}

int pop(TpDADO *x, TpPILHA *p) { /// desempilhar x

    if(!p->topo) {
            printf("\n ERRO no desempilhamento. Pilha vazia.");
            return -2;// nao se pode desempilhar em pilha vazia
    }
    /// tem dados empilhados
    TpNODE *paux;
    paux = p->topo;


    /// copiar o valor do dado armazenado no topo da pilha
    *x = paux->dado;
    p->topo = paux->prox;
    paux->prox = NULL; /// desligar do encadeamento a caixa do topo.

    return 2; /// sucesso

}
// ---------------------------------------------------------------------------------------

// --------------------------Estrutura de Imagem PGM--------------------------------------

typedef unsigned char Tpixel; // tipo Tpixel para valores em [0, 255]

typedef struct pgm {
    int w;     // largura da imagem em pixels (TC - Total de pixels em cada coluna da imagem)
    int h;     // altura da imagem em pixel   (TL - Total de pixels em cada linha da imagem )
    int max;   // valor de brilho m�ximo registrado na imagem (use 255 sempre)
    Tpixel* pData; // ponteiro para o reticulado (matriz) da immagem alocada como um vetor.
} pgm;

int WritePGM(const char* arq, const char* tpPGM, pgm* pPgm) {
    FILE *f;

    f = fopen(arq, "w");  /// modo "w" --> abrir para escrita
    if (!f) {
        printf("\n ERRO: Incapaz de abrir arquivo: %s.", arq);
        return -1;  // algum c�digo de erro - Arquivo nao existe.
    }

//      //gravar no arquivo o cabe�alho de imagens PGM cinza

    fprintf(f, "%s\n", tpPGM); ///  assinatura PGM cinza "P2" ou binario "P1"
    fprintf(f,"%d %d\n", pPgm->w, pPgm->h); // largura e altura da imagem em pixel
    fprintf(f,"255\n"); // valor de brilho m�ximo na imagem (use sempre 255

    // gravar no arquivo os valores dos pixels da imagem computada
    for (unsigned int k = 0; k < (pPgm->w * pPgm->h); k++) {
        fprintf(f,"%d ", pPgm->pData[k]);
    }

    fclose(f);
}

int ReadPGMP2(const char* arq, pgm* pPgm) {
    /// ReadPGMP2 --> ler um arquivo de imagem PGM P2 e armazenar os dados da imagem
    ///               no suporte de dados da imagem pPgm.
    ///               O arquivo de imagem PGM P2 tem a seguinte estrutura:
    ///               P2
    ///               # Comentário
    ///               Largura Altura
    ///               Max
    ///               Dados da imagem (pixels)
    ///               O suporte de dados da imagem pPgm é uma matriz de pixels (Tpixel)
    ///               armazenada como um vetor de pixels (Tpixel *pData).
    ///               O suporte de dados da imagem pPgm é alocado dinamicamente.
    ///               O arquivo de imagem PGM P2 é lido e os dados da imagem são armazenados
    ///               no suporte de dados da imagem pPgm.
    ///               O nome do arquivo de imagem é arq.
    ///               O suporte de dados da imagem é pPgm.
    ///               A função retorna 0 se a leitura foi bem sucedida e -1 se houve erro.

    int word;            // inteiro de prop�sito geral
    unsigned int nRead = 0;       // �ndice para o vetor/matriz de dados (pixels) da imagem
    char readChars[256]; // buffer para ler caracteres do arquivo (prop�sito geral)

    FILE* fd;  /// descritor para um arquivo

    //abrir arquivo de entrada arq e checar se teve sucesso
    fd = fopen(arq, "r");  // modo "r" --> abrir somente para leitura
    if (!fd) {
        printf("\n ERRO: Incapaz de abrir arquivo: %s.\n\n", arq);
        exit(1);  // ERRO 1: arquivo inexistente ou n�o encontrado no caminho especificado.
        // encerra a execu��o do programa e fecha todos os arquivos abertos
    }
    printf("\n Arquivo '%s' foi aberto", arq);
    // se o arquivo existe, ele pode ser um PGM. Ent�o,
    fscanf (fd, "%s", readChars); // leia a primeira linha (string) do arquivo fd cujo valor esperado � "P2"

    if ((strcmp(readChars, "P2"))) { //tipo PGM n�o � v�lido? strcmp(s1,s2) compara os caracteres das
        //   strings s1 e s2 e retorna o valor zero se s1 � exatamente igual a s2
        printf ("\n\nErro em PGM: %s. Formato nao suportado em:  ", readChars);
        fclose(fd);
        exit(2);  // c�digo de erro para "Arquivo n�o � um PGM P2"
    }
    printf("\n ... tem assinatura de arquivo de imagem PGM 'P2'");
    // o arquivo arq vinculado ao descritor fd tem assinatura PGM "P2", ent�o
    fscanf (fd, "%s", readChars); // leia a segunda linha

    while (readChars[0] == '#') {   // se no cabe�alho do arquivo existe uma linha de coment�rio,
        fgets (readChars, 255, fd);  // ela come�a com o char "#".

        fscanf (fd, "%s", readChars); // Pular essa linha (ela � irrelevante)
    }
    sscanf (readChars, "%d", &pPgm->w);  // para preencher os campos da struct � importante manter a
    fscanf (fd, "%d", &pPgm->h);        // mesma ordem da defini��o desses campos.
    fscanf (fd, "%d", &pPgm->max);

    unsigned int Totalpixels = (pPgm->w) * (pPgm->h);

    printf("\n ... Total de Pixels = %d", Totalpixels);

    pPgm->pData = (Tpixel*)malloc(sizeof(Tpixel) * (Totalpixels)); // pData � um vetor alocado dinamicamente
    // ler cada o valor de brilho de cada pixel do arquivo da imagem e armazen�-lo corretamente no
    // suporte do reticulado (matriz) da imagem, o qual � um vetor criado dinamicamente.


    for (nRead = 0; nRead < Totalpixels; nRead++) {
        fscanf(fd, "%d" ,&word); // l� o valor de brilho de um pixel do arquivo
        pPgm->pData[nRead] = word; // armazena o valor deste pixel no vetor alocado
    } // for

    fclose(fd); // sempre fechar o arquivo se n�o � o mesmo n�o � mais necess�rio

    return 0; // retorne os dados de imagem no nome da fun��o
} // ReadPGMP2 - fim da fun��o


int MemImgZero(pgm* atual, pgm* zeropgm) {
    /// MemImgZero ---> cria na memoria RAM um reticulado para suporte de dados de imagem (pPgm)
    ///                 com dimensoes (pPgm->h x pPgm->w) = tp bytes. Todos esses  tp pixels do reticulado
    ///                 serao associados com o valor ZERO. O reticulado eh um vetor de Tpixel
    ///                 apontado pelo ponteiro *pData (Tpixel *pData).
    ///
    ///                 os dados sao copyados de pgm* atual
    zeropgm->w = atual->w;
    zeropgm->h = atual->h;
    zeropgm->max = atual->max;

    unsigned int tp, Totalpixels = (zeropgm->w) * (zeropgm->h);

    zeropgm->pData = (Tpixel*)malloc(sizeof(Tpixel) * (Totalpixels)); // pData � um vetor alocado dinamicamente.
        // pData eh o suporte do reticulado (matriz) da imagem, o qual � um vetor criado dinamicamente.
        if (!(zeropgm->pData)) {
            printf("ERRO na alocacao de matriz de zeros.");
            return -1;
        }

        const Tpixel ZERO = 0;
        for (tp = 0; tp < Totalpixels; tp++) {
              zeropgm->pData[tp] = ZERO;
        } // for

printf("\n ... Criada a Matriz %d x %d  com ZEROS (na memoria RAM).", zeropgm->w, zeropgm->h);

       return 1; /// Sucesso
}


Tpixel GetPixel(pgm* img, int L, int C){

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) ||  (C >= img->w) || ( L < 0) || (C < 0)) {
        printf("\n ..... Coordenada de imagem esta fora dos limites da grade da imagem.");
        exit(0);
    }
    Tpixel K;
    K = *((img->pData) + L*img->w + C);

    return (K);
}

int PutPixel(pgm* img, int L, int C, Tpixel v){

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) ||  (C >= img->w) || ( L < 0) || (C < 0)) {
        printf("\n ..... Coordenada de imagem esta fora dos limites da grade da imagem.");
        exit(0);
    }
    unsigned long int *K;
   //  M = &V[0] + k*TC + j;
   //(img->pData) + L*img->w + C
   //*((img->pData) + L*img->w + C)
    K = (img->pData) + L*img->w + C;
   *K = v;

    return (1);
}

// ---------------------------------------------------------------------------------------

// -----------------------Funções de Processamento de Imagens-----------------------------

int MorphGrad33(pgm* img, pgm* grad) {
    /// computar o gradiente morfologico da imagem img
    /// armazenar o resultado na imagem grad.
    MemImgZero(img, grad);

    /// fazer a convolucao da superficie da imagem com o
    /// elemento estruturante 3x3 (janela 3x3)

    int L, C, k, j;
    Tpixel max, p;
    for (L = 1; L < img->h - 1; L++) {
        for (C = 1; C < img->w - 1; C++) {
            max = 0;
            /// convolucao para dilatacao cinza 3x3
            for (k = -1; k<=1; k++) {    /// elemento estruturante EE 3x3
                for (j = -1; j<=1; j++){
                    p = GetPixel(img, L + k, C + j);
                    if (p > max) max = p;  /// valor de cinza maximo coberto pelo EE
                } // for j
            } // for k
            /// encontrou o valor de cinza maximo max coberto pelo elemento estruturante
            /// armazenar o valor max nas coordenadas (L, C) da matrix grad
            p = max - GetPixel(img, L , C);
            PutPixel(grad, L, C, p);
        } // for C

    } // for L
    printf("\n ..... Processado o Gradiente Morfologico da Imagem.");
  return 0;
}

int GrowingRegion(pgm* img, pgm* reg, int L, int C) {
    // GrowingRegion --> crescer a regiao de interesse a partir do pixel semente (L, C)
    //                   com valor de brilho T.
    //                   A regiao de interesse será armazenada na imagem reg.
    //                   A imagem img é a imagem original.
    //                   A imagem reg é uma imagem binária (0 ou 255).
    //                   A imagem reg é inicializada com zeros.
    //                   A região de interesse é crescente e conectada.
    
    MemImgZero(img, reg);
    TpPILHA *p;
    p = (TpPILHA*) malloc(sizeof(TpPILHA));
    InicializaPilha(p);
    TpDADO dado;
    dado.L = L;
    dado.C = C;
    push(dado, p);
    Tpixel PixelSemente = GetPixel(img, L, C);
    PutPixel(reg, L, C, 255);
    Tpixel pixel; // pixel atual
    int T = 10; // tolerância

    while (p->topo) {
        TpDADO dado;
        pop(&dado, p);
        L = dado.L;
        C = dado.C;
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                if (k == 0 && j == 0) {
                    continue;
                }
                if (L + k < 0 || L + k >= img->h || C + j < 0 || C + j >= img->w) {
                    continue;
                }
                pixel = GetPixel(img, L + k, C + j);
                if (abs(pixel - PixelSemente) <= T && GetPixel(reg, L + k, C + j) == 0) {
                    dado.L = L + k;
                    dado.C = C + j;
                    push(dado, p);
                    PutPixel(reg, L + k, C + j, 255);
                }
            }
        }
    }
    printf("\n ..... Processada a Regiao de Interesse.");
}


int Border(pgm* img, pgm* border) {
    // Border --> detectar a borda da região de interesse.
    //            A imagem img é a imagem original.
    //            A imagem border é uma imagem binária (0 ou 255).
    //            A imagem border é inicializada com zeros.
    //            A borda da região de interesse é detectada e armazenada na imagem border.
    //            A região de interesse é a região crescente e conectada.
    //            A borda da região de interesse é a fronteira da região de interesse.
    MemImgZero(img, border);
    Tpixel pixel;
    for (int L = 0; L < img->h; L++) {
        for (int C = 0; C < img->w; C++) {
            pixel = GetPixel(img, L, C);
            if (pixel == 255) {
                for (int k = -1; k <= 1; k++) {
                    for (int j = -1; j <= 1; j++) {
                        if (k == 0 && j == 0) {
                            continue;
                        }
                        if (L + k < 0 || L + k >= img->h || C + j < 0 || C + j >= img->w) {
                            continue;
                        }
                        if (GetPixel(img, L + k, C + j) == 0) {
                            PutPixel(border, L, C, 255);
                        }
                    }
                }
            }
        }
    }
    printf("\n ..... Processada a Borda da Regiao de Interesse.");
}

int ColorBorder(pgm* img, pgm* border, pgm* colorBorder) {
    // ColorBorder --> colorir a borda da região de interesse.
    //                 A imagem img é a imagem original.
    //                 A imagem border é a imagem binária (0 ou 255) que representa a borda da região de interesse.
    //                 A imagem colorBorder é a imagem colorida que representa a borda da região de interesse.
    //                 A imagem colorBorder é inicializada com zeros.
    //                 A borda da região de interesse é colorida na imagem colorBorder.
    //                 A região de interesse é a região crescente e conectada.
    //                 A borda da região de interesse é a fronteira da região de interesse.
    MemImgZero(img, colorBorder);
    Tpixel pixel;
    for (int L = 0; L < img->h; L++) {
        for (int C = 0; C < img->w; C++) {
            pixel = GetPixel(border, L, C);
            if (pixel == 255) {
                PutPixel(colorBorder, L, C, 255);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------

int main(){

    /// caminho e nome do arquivo em disco
    const char* arqNirUmu   = "C:/Repositorios_GitHub/Trabalhos-PS/UmuNirGeoEye.pgm";
    const char* arqGrowUmu  = "C:/Repositorios_GitHub/Trabalhos-PS/UmuGrowGeoEye.pbm";
    const char* arqGradUmu  = "C:/Repositorios_GitHub/Trabalhos-PS/UmuGradGeoEye.pgm";
    const char* arqBorderUmu = "C:/Repositorios_GitHub/Trabalhos-PS/UmuBorderGeoEye.pbm";
    const char* arqColorBorderUmu = "C:/Repositorios_GitHub/Trabalhos-PS/UmuColorBorderGeoEye.ppm";

    /// descritor para o buffer de arquivo em memoria RAM (resultados)
    FILE *fnirUmu;

    /// descritor para os dados da imagem na mem�ria principal
    pgm *nirUmuPgm, *growUmuPgm, *gradUmuPgm, *borderUmuPgm, *colorBorderUmuPgm;

    nirUmuPgm = malloc (sizeof(pgm)); /// alocacao do descritor dos dados da imagem
    growUmuPgm = malloc (sizeof(pgm));
    gradUmuPgm = malloc (sizeof(pgm));
    borderUmuPgm = malloc (sizeof(pgm));
    colorBorderUmuPgm = malloc (sizeof(pgm));

    ReadPGMP2(arqNirUmu, nirUmuPgm);
    
    /// Escolha do pixel semente para crescer a regiao de interesse
    int L = 340, C = 470;
    GrowingRegion(nirUmuPgm, growUmuPgm, L, C);
    MorphGrad33(nirUmuPgm, gradUmuPgm);
    Border(growUmuPgm, borderUmuPgm);
    ColorBorder(nirUmuPgm, borderUmuPgm, colorBorderUmuPgm);

    /// gravar a imagem crescente em disco
    WritePGM(arqGrowUmu, "P2", growUmuPgm);
    WritePGM(arqGradUmu, "P2", gradUmuPgm);
    WritePGM(arqBorderUmu, "P2", borderUmuPgm);
    WritePGM(arqColorBorderUmu, "P3", colorBorderUmuPgm);

    /// a liberação da memória alocada dinamicamente (em C)
    /// esse procedimento é responsabilidade do programador.
    free(nirUmuPgm->pData);    free(nirUmuPgm);
    free(growUmuPgm->pData);      free(growUmuPgm);
    free(gradUmuPgm->pData);      free(gradUmuPgm);
    free(borderUmuPgm->pData);    free(borderUmuPgm);
    free(colorBorderUmuPgm->pData); free(colorBorderUmuPgm);

    return 0;
}
