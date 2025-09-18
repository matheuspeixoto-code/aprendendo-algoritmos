#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
typedef struct No {
    int chave;
    char cor;
    struct No *esq, *dir, *p;
} No;

typedef struct {
    No *raiz;
    No *nill;
} Arvore;

Arvore* criarArvoreRB() {
    Arvore *T = malloc(sizeof(Arvore));
    T->nill = malloc(sizeof(No));
    T->nill->cor = 'N';  
    T->nill->esq = T->nill->dir = T->nill->p = T->nill;
    T->raiz = T->nill;
    return T;
}

void RBTransplate(Arvore *T, No *u, No *v) {
    if (u->p == T->nill) {
        T->raiz = v;
    } else if (u == u->p->esq) {
        u->p->esq = v;
    } else {
        u->p->dir = v;
    }
    v->p = u->p;
}

void REsquerda(Arvore *T, No *x) {
    No *y = x->dir;
    x->dir = y->esq;
    if (y->esq != T->nill) {
        y->esq->p = x;
    }
    y->p = x->p;
    if (x->p == T->nill) {
        T->raiz = y;
    } else if (x == x->p->esq) {
        x->p->esq = y;
    } else {
        x->p->dir = y;
    }
    y->esq = x;
    x->p = y;
}

void RDireita(Arvore *T, No *x) {
    No *y = x->esq;
    x->esq = y->dir;
    if (y->dir != T->nill) {
        y->dir->p = x;
    }
    y->p = x->p;
    if (x->p == T->nill) {
        T->raiz = y;
    } else if (x == x->p->dir) {
        x->p->dir = y;
    } else {
        x->p->esq = y;
    }
    y->dir = x;
    x->p = y;
}

void RBInsertFixUp(Arvore *T, No *z) {
    while (z->p->cor == 'R') {
        if (z->p == z->p->p->esq) {
            No *y = z->p->p->dir;
            if (y->cor == 'R') { // Caso 1
                z->p->cor = 'N';
                y->cor = 'N';
                z->p->p->cor = 'R';
                z = z->p->p;
            } else if(z == z->p->dir) {// Caso 2
                z = z->p;
                REsquerda(T, z);
            }else{// Caso 3
                z->p->cor = 'N';
                z->p->p->cor = 'R';
                RDireita(T, z->p->p);
            }
        } else {
            No *y = z->p->p->esq;
            if (y->cor == 'R') { // Caso 1
                z->p->cor = 'N';
                y->cor = 'N';
                z->p->p->cor = 'R';
                z = z->p->p;
            } else if(z == z->p->esq){
                z = z->p;
                RDireita(T, z);
            }else{// Caso 3
                z->p->cor = 'N';
                z->p->p->cor = 'R';
                REsquerda(T, z->p->p);
                
            }
        }
    }
    T->raiz->cor = 'N';
}

void RBInsert(Arvore *T, No *z) {
    No *y = T->nill;
    No *x = T->raiz;
    while (x != T->nill) {
        y = x;
        if(z->chave == x->chave){
            //printf("Chave %d ja existe",z->chave);
            //printf("\n");
            free(z);
            return;
        }else if (z->chave < x->chave) {
            x = x->esq;
        } else {
            x = x->dir;
        }
    }
    z->p = y;
    if (y == T->nill) {
        T->raiz = z;
    } else if (z->chave < y->chave) {
        y->esq = z;
    } else {
        y->dir = z;
    }
    z->esq = T->nill;
    z->dir = T->nill;
    z->cor = 'R';
    RBInsertFixUp(T, z);
}
No *Tree_Minimum(Arvore *T, No* x) {
    while (x->esq != T->nill) {
        x = x->esq;
    }
    return x;
}
void RBDeleteFixUp(Arvore *T, No *x) {
    while (x != T->raiz && x->cor == 'N') {
        No *w;
        if (x == x->p->esq) {
            w = x->p->dir;
            if (w->cor == 'R') { // Caso 1
                w->cor = 'N';
                x->p->cor = 'R';
                REsquerda(T, x->p);
                w = x->p->dir;
            }

            if (w->esq->cor == 'N' && w->dir->cor == 'N') { // Caso 2
                w->cor = 'R';
                x = x->p;
            } else {
                if (w->dir->cor == 'N') { // Caso 3
                    w->esq->cor = 'N';
                    w->cor = 'R';
                    RDireita(T, w);
                    w = x->p->dir;
                }
                // Caso 4
                w->cor = x->p->cor;
                x->p->cor = 'N';
                w->dir->cor = 'N';
                REsquerda(T, x->p);
                x = T->raiz;
            }
        } else {
            w = x->p->esq;
            if (w->cor == 'R') { // Caso 1
                w->cor = 'N';
                x->p->cor = 'R';
                RDireita(T, x->p);
                w = x->p->esq;
            }

            if (w->dir->cor == 'N' && w->esq->cor == 'N') { // Caso 2
                w->cor = 'R';
                x = x->p;
            } else {
                if (w->esq->cor == 'N') { // Caso 3
                    w->dir->cor = 'N';
                    w->cor = 'R';
                    REsquerda(T, w);
                    w = x->p->esq;
                }
                // Caso 4
                w->cor = x->p->cor;
                x->p->cor = 'N';
                w->esq->cor = 'N';
                RDireita(T, x->p);
                x = T->raiz;
            }
        }
    }
    x->cor = 'N';
}


void RBDelete(Arvore *T, No *z) {
    No *y = z;
    char corOriginal = y->cor;
    No *x;

    if (z->esq == T->nill) {
        x = z->dir;
        RBTransplate(T, z, z->dir);

    } else if (z->dir == T->nill) {
        x = z->esq;
        RBTransplate(T, z, z->esq);

    } else {
        y = Tree_Minimum(T, z->dir);
        corOriginal = y->cor;
        x = y->dir;

        if (y->p == z) {
            x->p = y;
        } else {
            RBTransplate(T, y, y->dir);
            y->dir = z->dir;
            y->dir->p = y;
        }

        RBTransplate(T, z, y);
        y->esq = z->esq;
        y->esq->p = y;
        y->cor = z->cor;
    }

    if (corOriginal == 'N') {
        RBDeleteFixUp(T, x);
    }
}


int qtd_Nos(No *no,Arvore *T){
    if(no ==T->nill){
        return 0;
    }
    return 1+qtd_Nos(no->esq,T)+ qtd_Nos(no->dir,T);
}

void imprimirPreOrdem(No *no, Arvore *T) {
    if (no != T->nill) {
        printf("%d(%c) ", no->chave, no->cor);
        imprimirPreOrdem(no->esq, T);
        imprimirPreOrdem(no->dir, T);
    }
}

void liberarNos(No *no, Arvore *T) {
    if (no == T->nill) return;
    
    liberarNos(no->esq, T);
    liberarNos(no->dir, T);
    free(no);
}

void liberarArvore(Arvore *T) {
    liberarNos(T->raiz, T);
    free(T->nill);
    free(T);
}

int alturaNegra(No *no,Arvore *T){
    if(no==T->nill){
        return 0;
    }
    
    int AltDir=alturaNegra(no->dir,T);
    int AltEsq=alturaNegra(no->esq,T);
    
    int x;
    if(no->cor=='N'){
        x=1;
    }else{
        x=0;
    }
    
    if(AltEsq==-1 || AltDir==-1 || AltEsq!=AltDir){
        return -1;
    }else{
        return AltEsq+x;
    }
    
    
}


int main() {
    srand(time(NULL));
    int Num_nos;

    for (int y = 0; y < 1000; y++) {
        printf("=======================================================\n");
        printf("Árvore %d\n", y + 1);

        Arvore *T = criarArvoreRB();
        char chaves_usadas[100000] = {0}; 
        int inseridos = 0;

        while (inseridos < 100) {
            int chave = rand() % 100000;

            if (!chaves_usadas[chave]) {
                chaves_usadas[chave] = 1;

                No *novo = malloc(sizeof(No));
                novo->chave = chave;
                RBInsert(T, novo);

                inseridos++;
            }
        }

        Num_nos = qtd_Nos(T->raiz, T);
        printf("Após a inserção, essa árvore possui: %d nós\n", Num_nos);


        if(alturaNegra(T->raiz,T)==-1){
            printf("Não é RN\n");
        }else{
            printf("é RN\n");
        }
        
        

        int removidos = 0;
        int chave_remover;
        while (removidos < 10) {
            chave_remover = rand() % 100000;
            if (chaves_usadas[chave_remover]) {
                No *atual = T->raiz;
                while (atual != T->nill && atual->chave != chave_remover) {
                    if (chave_remover < atual->chave){
                        atual = atual->esq;
                    }
                    else{
                        atual = atual->dir;
                    }
                }
                if (atual != T->nill) {
                    RBDelete(T, atual);
                    chaves_usadas[chave_remover] = 0;
                    removidos++;
                }
            }
        }


        
        Num_nos = qtd_Nos(T->raiz, T);
        printf("após a remoção, essa árvore possui: %d nós\n", Num_nos);

        if(alturaNegra(T->raiz,T)==-1){
            printf("Não é RN\n");
        }else{
            printf("é RN\n");
        }


        liberarArvore(T); 
    }

    return 0;
}



