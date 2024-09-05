
#include <stdio.h>
#include <string.h> // para usar a fun��o strcmp() que compara duas strings
#include <stdlib.h> // para usar a fun��o exit() que interrompe (aborta) a execu��o do programa.

typedef unsigned char Tpixel; // tipo Tpixel para valores em [0, 255]

typedef struct pgm
{
    int w;         // largura da imagem em pixels (TC - Total de pixels em cada coluna da imagem)
    int h;         // altura da imagem em pixel   (TL - Total de pixels em cada linha da imagem )
    int max;       // valor de brilho m�ximo registrado na imagem (use 255 sempre)
    Tpixel *pData; // ponteiro para o reticulado (matriz) da immagem alocada como um vetor.
} pgm;

int WritePGM(const char *arq, const char *tpPGM, pgm *pPgm)
{
    FILE *f;

    f = fopen(arq, "w"); /// modo "w" --> abrir para escrita
    if (!f)
    {
        printf("\n ERRO: Incapaz de abrir arquivo: %s.", arq);
        return -1; // algum c�digo de erro - Arquivo nao existe.
    }

    //      //gravar no arquivo o cabe�alho de imagens PGM cinza

    fprintf(f, "%s\n", tpPGM);               ///  assinatura PGM cinza "P2" ou binario "P1"
    fprintf(f, "%d %d\n", pPgm->w, pPgm->h); // largura e altura da imagem em pixel
    fprintf(f, "255\n");                     // valor de brilho m�ximo na imagem (use sempre 255

    // gravar no arquivo os valores dos pixels da imagem computada
    for (unsigned int k = 0; k < (pPgm->w * pPgm->h); k++)
    {
        fprintf(f, "%d ", pPgm->pData[k]);
    }

    fclose(f);
}

int ReadPGMP2(const char *arq, pgm *pPgm)
{
    // ReadPGMP2 l� uma imagem gravada em arquivo com formato PGM "P2"
    //      INPUT: arq � uma string que aponta o caminho e o nome do arquivo PGM P2 que vai ser lido.
    //             exemplo: const char* arq = "D:\\AulasAlgoritimosEstruturas\\ignNIR.pgm";
    //      OUTPUT: fd retorna o descritor de arquivo (ponteiro) que atuar� como tratador do arquivo arq.
    //              Se o arquivo arq n�o existir, ou n�o for encontrado no caminho fornecido,  ou n�o for um
    //              arquivo PGM "P2", a execu��o desta fun��o � abortada e fd e pPgm ficam indefinidos.
    //              pPgm � um ponteiro para uma struct com campos definidos em pgm, a qual vai armazenar
    //              dados relevantes que est�o gravados no arquivo PGM arq.

    int word;               // inteiro de prop�sito geral
    unsigned int nRead = 0; // �ndice para o vetor/matriz de dados (pixels) da imagem
    char readChars[256];    // buffer para ler caracteres do arquivo (prop�sito geral)

    FILE *fd; /// descritor para um arquivo

    // abrir arquivo de entrada arq e checar se teve sucesso
    fd = fopen(arq, "r"); // modo "r" --> abrir somente para leitura
    if (!fd)
    {
        printf("\n ERRO: Incapaz de abrir arquivo: %s.\n\n", arq);
        exit(1); // ERRO 1: arquivo inexistente ou n�o encontrado no caminho especificado.
                 // encerra a execu��o do programa e fecha todos os arquivos abertos
    }
    printf("\n Arquivo '%s' foi aberto", arq);
    // se o arquivo existe, ele pode ser um PGM. Ent�o,
    fscanf(fd, "%s", readChars); // leia a primeira linha (string) do arquivo fd cujo valor esperado � "P2"

    if ((strcmp(readChars, "P2")))
    { // tipo PGM n�o � v�lido? strcmp(s1,s2) compara os caracteres das
      //    strings s1 e s2 e retorna o valor zero se s1 � exatamente igual a s2
        printf("\n\nErro em PGM: %s. Formato nao suportado em:  ", readChars);
        fclose(fd);
        exit(2); // c�digo de erro para "Arquivo n�o � um PGM P2"
    }
    printf("\n ... tem assinatura de arquivo de imagem PGM 'P2'");
    // o arquivo arq vinculado ao descritor fd tem assinatura PGM "P2", ent�o
    fscanf(fd, "%s", readChars); // leia a segunda linha

    while (readChars[0] == '#')
    {                              // se no cabe�alho do arquivo existe uma linha de coment�rio,
        fgets(readChars, 255, fd); // ela come�a com o char "#".

        fscanf(fd, "%s", readChars); // Pular essa linha (ela � irrelevante)
    }
    sscanf(readChars, "%d", &pPgm->w); // para preencher os campos da struct � importante manter a
    fscanf(fd, "%d", &pPgm->h);        // mesma ordem da defini��o desses campos.
    fscanf(fd, "%d", &pPgm->max);

    unsigned int Totalpixels = (pPgm->w) * (pPgm->h);

    printf("\n ... Total de Pixels = %d", Totalpixels);
    // printf("\n ... Criar estrutura para alocar valores de brilho de cada pixel.");

    pPgm->pData = (Tpixel *)malloc(sizeof(Tpixel) * (Totalpixels)); // pData � um vetor alocado dinamicamente
    // ler cada o valor de brilho de cada pixel do arquivo da imagem e armazen�-lo corretamente no
    // suporte do reticulado (matriz) da imagem, o qual � um vetor criado dinamicamente.

    for (nRead = 0; nRead < Totalpixels; nRead++)
    {
        fscanf(fd, "%d", &word);   // l� o valor de brilho de um pixel do arquivo
        pPgm->pData[nRead] = word; // armazena o valor deste pixel no vetor alocado
    } // for

    fclose(fd); // sempre fechar o arquivo se n�o � o mesmo n�o � mais necess�rio

    return 0; // retorne os dados de imagem no nome da fun��o
} // ReadPGMP2 - fim da fun��o

int MemImgZero(pgm *atual, pgm *zeropgm)
{
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

    zeropgm->pData = (Tpixel *)malloc(sizeof(Tpixel) * (Totalpixels)); // pData � um vetor alocado dinamicamente.
    // pData eh o suporte do reticulado (matriz) da imagem, o qual � um vetor criado dinamicamente.
    if (!(zeropgm->pData))
    {
        printf("ERRO na alocacao de matriz de zeros.");
        return -1;
    }

    const Tpixel ZERO = 0;
    for (tp = 0; tp < Totalpixels; tp++)
    {
        zeropgm->pData[tp] = ZERO;
    } // for

    printf("\n ... Criada a Matriz %d x %d  com ZEROS (na memoria RAM).", zeropgm->w, zeropgm->h);

    return 1; /// Sucesso
}

Tpixel GetPixel(pgm *img, int L, int C)
{

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) || (C >= img->w) || (L < 0) || (C < 0))
    {
        printf("\n ..... Coordenada de imagem esta fora dos limites da grade da imagem.");
        exit(0);
    }
    Tpixel K;
    K = *((img->pData) + L * img->w + C);

    return (K);
}

int PutPixel(pgm *img, int L, int C, Tpixel v)
{

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) || (C >= img->w) || (L < 0) || (C < 0))
    {
        printf("\n ..... Coordenada de imagem esta fora dos limites da grade da imagem.");
        exit(0);
    }
    unsigned long int *K;
    //  M = &V[0] + k*TC + j;
    //(img->pData) + L*img->w + C
    //*((img->pData) + L*img->w + C)
    K = (img->pData) + L * img->w + C;
    *K = v;

    return (1);
}

int MorphGrad33(pgm *img, pgm *grad)
{
    /// computar o gradiente morfologico da imagem img
    /// armazenar o resultado na imagem grad.
    MemImgZero(img, grad);

    /// fazer a convolucao da superficie da imagem com o
    /// elemento estruturante 3x3 (janela 3x3)

    int L, C, k, j;
    Tpixel max, p;
    for (L = 1; L < img->h - 1; L++)
    {
        for (C = 1; C < img->w - 1; C++)
        {
            max = 0;
            /// convolucao para dilatacao cinza 3x3
            for (k = -1; k <= 1; k++)
            { /// elemento estruturante EE 3x3
                for (j = -1; j <= 1; j++)
                {
                    p = GetPixel(img, L + k, C + j);
                    if (p > max)
                        max = p; /// valor de cinza maximo coberto pelo EE
                } // for j
            } // for k
            /// encontrou o valor de cinza maximo max coberto pelo elemento estruturante
            /// armazenar o valor max nas coordenadas (L, C) da matrix grad
            p = max - GetPixel(img, L, C);
            PutPixel(grad, L, C, p);
        } // for C

    } // for L
    printf("\n ..... Processado o Gradiente Morfologico da Imagem.");
    return 0;
}

int main()
{

    /// caminho e nome do arquivo em disco
    const char *arqnirUmu = "C:\\Users\\Airton\\SistComp\\PGM\\UmuNirGeoEye.pgm";
    const char *arqgradUmu = "D:\\ProgamasC\\UmuGradGeoEye.pgm";

    /// descritor para o buffer de arquivo em memoria RAM (resultados
    FILE *fnirUmu;

    /// descritor para os dados da imagem na mem�ria principal
    pgm *nirUmuPgm, *imggrad;

    nirUmuPgm = malloc(sizeof(pgm)); /// alocacao do descritor dos dados da imagem
    imggrad = malloc(sizeof(pgm));

    ReadPGMP2(arqnirUmu, nirUmuPgm);
    MorphGrad33(nirUmuPgm, imggrad);

    WritePGM(arqgradUmu, "P2", imggrad);
    /// a libera��o da mem�ria alocada dinamicamente (em C)
    /// esse procedimento � responsabilidade do programador.
    free(nirUmuPgm->pData);
    free(nirUmuPgm);
    free(imggrad->pData);
    free(imggrad);

    return 0;
}
