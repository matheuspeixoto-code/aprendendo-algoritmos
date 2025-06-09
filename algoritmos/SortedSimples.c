#include <stdio.h>
#include <stdlib.h>

int buscar_menor(int vet[],int tam){
    int menor=vet[0];
    int menorIndice=0;
    for(int i=0;i<tam;i++){
        if(vet[i]<menor){
            menor=vet[i];
            menorIndice=i;

        }
    }
    return menorIndice;
}
void remover(int vet[], int *tam, int indice){
    for(int i = indice; i < (*tam) - 1; i++){
        vet[i] = vet[i + 1];
    }
    (*tam)--;
}

int *arrayOrdenado(int vet[],int tam,int *tamanhoOrdenado){
    int* novoArray = malloc(tam * sizeof(int));
    int tamAtual = tam;
    *tamanhoOrdenado=tam;

    for(int i=0;i<tam;i++){
        int menor=buscar_menor(vet,tamAtual);
        novoArray[i]=vet[menor];
        remover(vet,&tamAtual,menor);
        
    }
    return novoArray;
}


int main()
{
    int vet[5]={2,3,0,55,1};
    int tam= sizeof(vet)/sizeof(vet[0]);
    int tamanhoOrdenado;
    int *ordenado=arrayOrdenado(vet,tam,&tamanhoOrdenado);
    
    for (int i=0;i<tamanhoOrdenado;i++){
        printf("%d ",ordenado[i]);
    }
    free(ordenado);
    return 0;
}