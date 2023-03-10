#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
    int r, g, b;
}pixel;
 
int main(){
    FILE *arquivo;
    FILE *arquivo2;
    int i, j, comando;
    char tipo[3];
    int largura, altura, cormax;
    char nomearq[10], nomesalvar[15];
    printf("Digite o nome do arquivo.\n");
    scanf("%s",nomearq);
 
    if ((arquivo = fopen(nomearq, "r")) == NULL) {
        printf("Arquivo não pode ser aberto\n");
        exit (1);
    };
 
    fscanf(arquivo, "%s", tipo);
    fscanf(arquivo, "%d", &largura);
    fscanf(arquivo, "%d", &altura);
    fscanf(arquivo, "%d", &cormax);
 
    pixel **imagem = (pixel**)malloc(altura * sizeof(pixel*));
        for(i=0;i < altura;i++){
            imagem[i]= (pixel*)malloc(largura * sizeof(pixel));
        }
   
    pixel **copia = (pixel**)malloc(altura * sizeof(pixel*));
        for(i=0;i < altura;i++){
            copia[i]= (pixel*)malloc(largura * sizeof(pixel));
        }
    
    pixel **rot = (pixel**)malloc(largura * sizeof(pixel*));
        for(i=0;i<largura;i++){
            rot[i]= (pixel*)malloc(altura * sizeof(pixel));
        }
    
 
    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            fscanf(arquivo, "%d", &imagem[i][j].r);
            fscanf(arquivo, "%d", &imagem[i][j].g);
            fscanf(arquivo, "%d", &imagem[i][j].b);
        }
    }
    printf("Cabeçalho:\n");
    printf("Tipo : %s\n", tipo);
    printf("Largura: %d\n", largura);
    printf("Altura: %d\n", altura);
    printf("Cor máxima: %d\n", cormax);
    printf(" * * * * * * * * *\n");
    printf("Que tipo de manipulação você quer fazer:\n 1)Negativa\n 2)Rotacionar para a esquerda\n 3)Tons de cinza\n 4)Refletir\n 5)AutoRelevo\n 6)Borrar\n 7)Inverter\n 8)Espelhar\n-");
    scanf("%d", &comando);
   
    switch(comando){
        case 1:
 
            for(i=0; i<altura; i++){
                for (j=0; j<largura; j++){
                    imagem[i][j].r = cormax  - imagem[i][j].r;
                    imagem[i][j].g = cormax  - imagem[i][j].g;
                    imagem[i][j].b = cormax  - imagem[i][j].b;
                }
            }
            printf("Qual nome você deseja salvar?\n");
            scanf("%s",nomesalvar);
            arquivo2 = fopen(nomesalvar, "w");
            fprintf(arquivo2, "%s\n", tipo);
            fprintf(arquivo2, "%d\n", largura);
            fprintf(arquivo2, "%d\n", altura);
            fprintf(arquivo2, "%d\n", cormax);
            for (i = 0; i < altura; i++){
                for (j = 0; j < largura; j++){
                    fprintf(arquivo2,"%d\n",imagem[i][j].r);
                    fprintf(arquivo2,"%d\n",imagem[i][j].g);
                    fprintf(arquivo2,"%d\n",imagem[i][j].b);
                }
            }
            break;
       
        case 2:
            printf("Qual nome você deseja salvar?\n");
            scanf("%s",nomesalvar);
            arquivo2 = fopen(nomesalvar, "w");
            fprintf(arquivo2, "%s\n", tipo);
            fprintf(arquivo2, "%d\n", altura);
            fprintf(arquivo2, "%d\n", largura);
            fprintf(arquivo2, "%d\n", cormax);
 
            for(i=0;i<altura;i++){
                for (j=0; j < largura; j++){
                    rot[largura-j-1][i] = imagem[i][j];
                }
            }
 
            for(i=0;i<largura;i++){
                for(j=0;j<altura;j++){
                    fprintf(arquivo2, "%d ", rot[i][j].r);
                    fprintf(arquivo2, "%d ", rot[i][j].g);
                    fprintf(arquivo2, "%d\n", rot[i][j].b);
                }
            }
            break;    
        case 3:
            printf("Qual nome você deseja salvar?\n");
            scanf("%s",nomesalvar);
            arquivo2 = fopen(nomesalvar, "w");
            fprintf(arquivo2, "%s\n", tipo);
            fprintf(arquivo2, "%d\n", largura);
            fprintf(arquivo2, "%d\n", altura);
            fprintf(arquivo2, "%d\n", cormax);
            for (i = 0; i < altura; i++){
                for (j = 0; j < largura; j++){
                    imagem[i][j].r = (int) ((0.299 * imagem[i][j].r) + (0.587 * imagem[i][j].g) + (0.144 * imagem[i][j].b));
                    imagem[i][j].g = imagem[i][j].r;
                    imagem[i][j].b = imagem[i][j].r;
                if (imagem[i][j].r > 255){
                        imagem[i][j].r = 255;
                        imagem[i][j].g = 255;
                        imagem[i][j].b = 255;
                    }
                }
            }
            for (i = 0; i < altura; i++){
                for (j = 0; j < largura; j++){
                    fprintf(arquivo2,"%d\n",imagem[i][j].r);
                    fprintf(arquivo2,"%d\n",imagem[i][j].g);
                    fprintf(arquivo2,"%d\n",imagem[i][j].b);
                }
            }
            break;
        case 4:
            printf("Qual nome você deseja salvar?\n");
            scanf("%s",nomesalvar);
            arquivo2 = fopen(nomesalvar, "w");
            fprintf (arquivo2, "%s\n", tipo);
            fprintf(arquivo2, "%d\n", largura);
            fprintf(arquivo2, "%d\n", altura);
            fprintf(arquivo2, "%d\n", cormax);
            if(largura>altura){
                for (i = 0; i < altura; i++) {
                    for (j = 0; j < largura; j++) {
                        copia[i][j] = imagem[i][largura-j];
                    }
                }
            }else{
                for (i = 0; i < altura; i++) {
                    for (j = 0; j < largura; j++) {
                        copia[i][j].r = imagem[i][largura - j-1].r;  
                        copia[i][j].g = imagem[i][largura - j-1].g;
                        copia[i][j].b = imagem[i][largura - j-1].b;
                    }
                }
            }
            for (i = 0; i < altura; i++) {
                for (j = 0; j < largura; j++) {
                    imagem[i][j].r = copia[i][j].r;
                    imagem[i][j].g = copia[i][j].g;
                    imagem[i][j].b = copia[i][j].b;  
                }
            }
            for (i = 0; i < altura; i++){
                for (j = 0; j < largura; j++){
                    fprintf(arquivo2,"%d\n",imagem[i][j].r);
                    fprintf(arquivo2,"%d\n",imagem[i][j].g);
                    fprintf(arquivo2,"%d\n",imagem[i][j].b);
                }
            }
            break;  
        case 5:
            printf("Qual nome você deseja salvar?\n");
            scanf("%s",nomesalvar);
            arquivo2 = fopen(nomesalvar, "w");
            fprintf(arquivo2, "%s\n", tipo);
            fprintf(arquivo2, "%d\n", largura);
            fprintf(arquivo2, "%d\n", altura);
            fprintf(arquivo2, "%d\n", cormax);
            for (i = 1; i < altura - 1; i++){
                for (j = 0; j < largura; j++){
                    copia[i][j].r = imagem[i + 1][j].r - imagem[i -1][j].r;
                    copia[i][j].g = imagem[i + 1][j].b - imagem[i -1][j].b;
                    copia[i][j].b = imagem[i + 1][j].b - imagem[i -1][j].b;
                if (copia[i][j].r < 0)
                    copia[i][j].r = 0;
                if (copia[i][j].g < 0)
                    copia[i][j].g = 0;
                if (copia[i][j].b < 0)
                    copia[i][j].b = 0;
                }
            }
            for (i = 1; i < altura - 1; i++){
                for(j = 0; j < largura; j++){
                    imagem[i][j].r = copia[i][j].r + 128;
                    imagem[i][j].g = copia[i][j].g + 128;
                    imagem[i][j].b = copia[i][j].b + 128;
                if (copia[i][j].r > 255)
                    copia[i][j].r = 255;
                if (copia[i][j].g > 255)
                    copia[i][j].g = 255;
                if (copia[i][j].b > 255)
                    copia[i][j].b = 255;                          
                }
            }
            for (i = 0; i < altura; i++){
               for (j = 0; j < largura; j++){
                    fprintf(arquivo2,"%d\n",imagem[i][j].r);
                    fprintf(arquivo2,"%d\n",imagem[i][j].g);
                    fprintf(arquivo2,"%d\n",imagem[i][j].b);
                }
            }
            break;
        case 6:
            printf("Qual nome você deseja salvar?\n");
            scanf("%s",nomesalvar);
            arquivo2 = fopen(nomesalvar, "w");
            fprintf(arquivo2, "%s\n", tipo);
            fprintf(arquivo2, "%d\n", largura);
            fprintf(arquivo2, "%d\n", altura);
            fprintf(arquivo2, "%d\n", cormax);
            for (i = 0; i < altura; i++){
                for (j = 0; j < largura; j++){
                    copia[i][j] = imagem[i][j];              
                }
            }
 
            for (i = 0; i < altura-1; i++){
                for (j = 0; j < largura-1; j++){
                    if(i==0 || j==0) continue;
                    imagem[i][j].r = (copia[i-1][j-1].r + copia[i-1][j].r + copia[i-1][j+1].r + copia[i][j-1].r + copia[i][j].r + copia[i][j+1].r + copia[i+1][j-1].r + copia[i+1][j].r + copia[i+1][j+1].r)/9,
                    imagem[i][j].g = (copia[i-1][j-1].g + copia[i-1][j].g + copia[i-1][j+1].g + copia[i][j-1].g + copia[i][j].g + copia[i][j+1].g + copia[i+1][j-1].g + copia[i+1][j].g + copia[i+1][j+1].g)/9,
                    imagem[i][j].b = (copia[i-1][j-1].b + copia[i-1][j].b + copia[i-1][j+1].b + copia[i][j-1].b + copia[i][j].b + copia[i][j+1].b + copia[i+1][j-1].b + copia[i+1][j].b + copia[i+1][j+1].b)/9;
               
                }
            }
 
            for (i = 0; i < altura; i++){
               for (j = 0; j < largura; j++){
                    fprintf(arquivo2,"%d\n",imagem[i][j].r);
                    fprintf(arquivo2,"%d\n",imagem[i][j].g);
                    fprintf(arquivo2,"%d\n",imagem[i][j].b);
                }
            }
            break;
        case 7:
            printf("Qual nome você deseja salvar?\n");
            scanf("%s",nomesalvar);
            arquivo2 =fopen(nomesalvar, "w");
            fprintf(arquivo2, "%s\n", tipo);
            fprintf(arquivo2, "%d\n", largura);
            fprintf(arquivo2, "%d\n", altura);
            fprintf(arquivo2, "%d\n", cormax);
            for (i = 0; i < altura; i++){
                for (j = 0; j < largura; j++){
                    copia[i][j]=imagem[i][j];
                }
            }
            for (i = 0; i < altura; i++){
                for (j = 0; j < largura; j++){
                    imagem[altura-i-1][j] = copia[i][j];
                }
            }
            for (i = 0; i < altura; i++){
               for (j = 0; j < largura; j++){
                    fprintf(arquivo2,"%d\n",imagem[i][j].r);
                    fprintf(arquivo2,"%d\n",imagem[i][j].g);
                    fprintf(arquivo2,"%d\n",imagem[i][j].b);
                }
            }
            break;
        case 8:
            printf("Qual nome você deseja salvar?\n");
            scanf("%s",nomesalvar);
            arquivo2 =fopen(nomesalvar, "w");
            fprintf(arquivo2, "%s\n", tipo);
            fprintf(arquivo2, "%d\n", largura);
            fprintf(arquivo2, "%d\n", altura);
            fprintf(arquivo2, "%d\n", cormax);
            for(i=0; i < altura;i++){
                for(j=0; j<largura; j++){
                    imagem[i][largura-j-1]=imagem[i][j];
                }
            }
            for (i = 0; i < altura; i++){
               for (j = 0; j < largura; j++){
                    fprintf(arquivo2,"%d\n",imagem[i][j].r);
                    fprintf(arquivo2,"%d\n",imagem[i][j].g);
                    fprintf(arquivo2,"%d\n",imagem[i][j].b);
                }
            }
            break;
        }
        free(imagem);
        free(copia);
        free(rot);
    printf("Programa finalizado!\n");    
    return 0;
}