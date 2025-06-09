#include <stdio.h>
int buscaBinaria(int v[],int tam,int valor){
    int baixo=0;
    int alto= tam-1;

    while(baixo<=alto){
        int meio=(alto+baixo)/2;
        if(v[meio]==valor){
            return meio;
        }if(valor<v[meio]){
            alto=meio-1;
        }else{
            baixo=meio+1;
        }
    }
    return -1;
}


int main() {
    int vetor[15] = {1, 2, 3, 5, 7, 9, 10, 13, 15, 18, 21, 25, 30, 98};
    int valor = 10;

    int posicao = buscaBinaria(vetor, 15, valor);

    if (posicao != -1) {
        printf("Valor %d encontrado na posição %d\n", valor, posicao);
    } else {
        printf("Valor %d não encontrado no vetor\n", valor);
    }

    return 0;
}