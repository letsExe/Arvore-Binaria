#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no* esq;
    struct no* dir;
};

typedef struct no* arv;

int vazia(arv r){
    return (r == NULL); 
}

arv insere(arv r, int info){
    if(vazia(r)){
        r = (struct no*) malloc (sizeof(struct no));
        r->info = info;
        r->dir = NULL;
        r->esq = NULL;
    }

    else
        if(info < r->info)
            r->esq = insere(r->esq, info);

        else 
            r->dir = insere(r->dir, info);

    return r;
}

void print_inOrden(arv r){
    if(!vazia(r)){
        print_inOrden(r->esq);
        printf("%d ", r->info);
        print_inOrden(r->dir);
    }
}

void print_raiz(arv r){
    if(!vazia(r)){
        printf("%d ", r->info);
        print_raiz(r->esq);
        print_raiz(r->dir);
    }
}

void imprime_chaves(arv r){
    if(vazia(r)){
        printf("[]");
        return;
    }
    printf("[%d, ", r->info);
    imprime_chaves(r->esq);
    printf(", ");
    imprime_chaves(r->dir);
    printf("]");

}

int busca(arv r, int info){
    if(vazia(r))
        return 0;

    if(info < r->info)
        return busca(r->esq, info);

    if (info > r->info)
        return busca(r->dir,info);
    
    return 1;    
}

int minimo(arv r){
    while(r->esq != NULL)
        r = r->esq;
    
    return r->info;
}

int maximo(arv r){
    while(r->dir != NULL)
        r = r->dir;
    
    return r->info;
}

int conta_elementos(arv r){
    if(vazia(r))
        return 0;

    return 1 + conta_elementos(r->dir) + conta_elementos(r->esq);  
}

int soma_elementos(arv r){
    if(vazia(r))
        return 0;

    return r->info + soma_elementos(r->dir) + conta_elementos(r->esq);  
}

int soma_maiores(arv r, int k){
    if(vazia(r))
        return 0;
    
    if(r->info > k)
        return r->info + soma_maiores(r->dir, k) + soma_maiores(r->esq, k);  
    
    return soma_maiores(r->esq, k) + soma_maiores(r->dir, k);
}

int altura(arv r){
    if(vazia(r))
        return 0;

    int esq = altura(r->esq) + 1;
    int dir = altura(r->dir) + 1;

    return esq > dir ? esq : dir;
}

arv remocao(arv r, int info) {
    if (vazia(r)) 
        return NULL;

    if (info < r->info) 
        r->esq = remocao(r->esq, info);

    else if (info > r->info) 
        r->dir = remocao(r->dir, info);

    else { // Achamos o nó a ser removido
        if (r->esq == NULL && r->dir == NULL) { // Caso 1: Nó folha
            free(r);
            r = NULL;
        } 
        else if (r->esq == NULL) { // Caso 2: Só tem filho à direita
            r->info = minimo(r->dir);
            r->dir = remocao(r->dir, r->info);
        } 
        else { // Caso 3: Nó tem dois filhos
            r->info = maximo(r->esq); // Sucessor in-order
            r->esq = remocao(r->esq, r->info);
        }
    }

    return r;
}

void imprime_intervalo(arv r, int a, int b){
    if(vazia(r)) return ;

    if(r->info > b){
        imprime_intervalo(r->esq, a, b);
        return;
    }

    if(r->info < a){
        imprime_intervalo(r->dir, a, b);
        return;
    }

    imprime_intervalo(r->esq, a, b);
    printf("%d ", r->info);
    imprime_intervalo(r->dir, a, b);
}

arv libera_Arvbin(arv r){
    if(vazia(r))
        return NULL;

    if(r->esq == NULL && r->dir == NULL){
        free(r);
        return NULL;
    }
    r->esq = libera_Arvbin(r->esq);

    r->dir = libera_Arvbin (r->dir);
}

int conta_no_interno(arv r){
    if (vazia(r)) return 0;

    if(r->dir != NULL || r->esq != NULL)
        return 1 + conta_no_interno(r->esq) + conta_no_interno(r->dir);
    
    return conta_no_interno(r->esq) + conta_no_interno(r->dir);
}

int conta_no_filho_unico(arv r){
    if (vazia(r)) return 0;

    if((r->dir != NULL && r->esq == NULL) || (r->dir == NULL && r->esq != NULL))
        return 1 + conta_no_filho_unico(r->esq) + conta_no_filho_unico(r->dir);
    
    return conta_no_filho_unico(r->esq) + conta_no_filho_unico(r->dir);
}

//acha o menor valor maior q k
int maior_menor(arv root, int k) {
    if (root == NULL) {
        return -1;  // Caso base: se a árvore está vazia, retorna -1
    }

    // Se o valor do nó atual for maior que k
    if (root->info > k) {
        // Verifica na subárvore esquerda se existe um valor menor que root->info, mas maior que k
        int esqResult = maior_menor(root->esq, k);
        return (esqResult != -1) ? esqResult : root->info;
    } else {
        // Se o valor do nó atual não é maior que k, verifica a subárvore direita
        return maior_menor(root->dir, k);
    }
}

arv liberar_outro(arv r){
    if(!vazia(r)){
        if(r->esq)
            r->esq = liberar_outro(r->esq);

        if(r->dir)
            r->dir = liberar_outro(r->dir);

        free(r);
    }  
    return NULL;
}

int main(){
    arv r = NULL;

    r = insere(r, 11);
    r = insere(r, 5);
    r = insere(r, 2);
    r = insere(r, 8);
    r = insere(r, 14);
    r = insere(r, 22);
    r = insere(r, 15);

    //imprime_chaves(r);

    //int bus = busca(r, 5);
    //printf("\n%d", bus);
    //printf("\n%d", altura(r));

    //r = remocao(r, 7);

    //printf("%d ", conta_no_interno(r));
    //printf("%d", soma_maiores(r, 1));
    //printf("%d", conta_no_filho_unico(r));
    printf("%d", maior_menor(r,12));


    r = libera_Arvbin(r);
    print_inOrden(r);

    return 0;
}

/*
for
    if
        for
*/