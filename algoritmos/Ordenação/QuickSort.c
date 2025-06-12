#include <stdio.h>
#include <stdlib.h>
int particionar(int *v,int inicio,int fim){
    int pivo=(v[inicio]+v[fim]+v[(inicio+fim)/2])/3;
    while (inicio<fim){
        while(inicio<fim && v[inicio]<=pivo){
            inicio ++;
        }
        
        while(inicio<fim && v[fim]>pivo){
            fim--;
        }
        int aux;
        aux=v[inicio];
        v[inicio]=v[fim];
        v[fim]=aux;
        
        
    }
    return inicio;
}
void QuickSort(int *v,int inicio,int fim){
    if(inicio<fim){
        int posicao=particionar(v,inicio,fim);
        QuickSort(v,inicio,posicao-1);
        QuickSort(v,posicao,fim);
    }
}
void imprimir(int *v,int tam){
    for(int i=0;i<tam+1;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}
int main()
{
    int vetor[]={12,0,65,23,33,43,12,43,642,78,1,11};//tam=12
    printf("=== Vetor Original ===\n");
    imprimir(vetor,11);
    QuickSort(vetor,0,11);
    printf("=== Vetor Ordenado ===\n");
    imprimir(vetor,11);
    return 0;
}