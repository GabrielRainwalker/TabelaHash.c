#include <stdio.h>
#include <stdlib.h>
#define M 11

typedef struct {
    int chave;
    int val;
    int exc;
} Entrada;

Entrada T1[M];
Entrada T2[M];

void IniciaTB() {
    int i = 0;
    while (i < M) {
        T1[i].chave = -1;
        T1[i].val = 0;
        T1[i].exc = 0;
        T2[i].chave = -1;
        T2[i].val = 0;
        T2[i].exc = 0;
        i++;
    }
}

int funHash1(int chave) {
    return chave % M;
}

int funHash2(int chave){
    return (int)(M * (chave * 0.9 - (int)(chave * 0.9)));
}

int Busca(int chave){
    int pos = funHash1(chave);
    
    if(T1[pos].chave == chave) {
        return pos;
    } else {
        pos = funHash2(chave);
        if (T2[pos].chave == chave) {
            return pos;
        }
    }
    return -1;
}

void Insere (int chave) {
    int ins1 = funHash1(chave);
    int ins2 = funHash2(chave);

    if (T1[ins1].val == 0) {
        T1[ins1].chave = chave;
        T1[ins1].val = 1;
    } else if (T2[ins2].val == 0) {
        T2[ins2].chave = T1[ins1].chave;
        T2[ins2].val = 1;

        T1[ins1].chave = chave;
        T1[ins1].val = 1;
    } else {
        int aux = T1[ins1].chave;
        T1[ins1].chave = chave;
        Insere(aux);
    }
}

void Excluir (int chave) {
    int ins1 = funHash1(chave);
    int ins2 = funHash2(chave);

    if (T2[ins2].chave == chave) {
        T2[ins2].chave = 0;
        T2[ins2].val = 0;
        T2[ins2].exc = 1;
    } else {
        T1[ins1].chave = 0;
        T1[ins1].val = 0;
        T1[ins1].exc = 1;
    }
}

void Imprime() {
    int i = 0;
    while (i < M) {
        if (T1[i].val == 1) {
            printf("(%d, T1, %d)\n", T1[i].chave, i);
        }
        if (T2[i].val == 1) {
            printf("(%d, T2, %d)\n", T2[i].chave, i);
        }
        i++;
    }
}

int main() {
    IniciaTB();

    char ajd;
    int chave;

    while (scanf("%c,%d\n", &ajd, &chave) == 2) {
        if (ajd == 'i') {
            Insere(chave);
        } else if (ajd == 'r') {
            Excluir(chave);
        }
    }

    Imprime();

    return 0;
}

