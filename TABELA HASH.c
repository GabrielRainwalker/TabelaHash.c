/* PROGRAMA DE TABELA HASH */
/* AUTORES:
Elter Rodrigues - 22309480,
João Jardim - 22307063,
Vinicius César - 22307319 ,
Gabriel Duarte - 22303292 */

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

void IniciaTB() { 		/* INICIA TABELA VAZIA */
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

int funHash1(int chave) { 	/* FUNÇÃO HASH REQUISITADA */
	return chave % M;
}

int funHash2(int chave){ 	/* FUNÇÃO HASH REQUISITADA */
	return(int)(M * (chave * 0.9 - (int)(chave * 0.9)));
}

int Busca(int chave){ 		/* FUNÇÃO DE BUSCA */
	int pos = funHash1(chave);
	
	if(T1[pos].chave == chave) { 	/* SE ESTIVER NA TABELA 1 RETORNA A POSIÇÃO */
		return pos;
	} else {		/* SE NÃO ESTIVER NA TABELA 1 RETORNA A POSIÇÃO NA TABELA 2 */
		pos = funHash2(chave);
		if (T2[pos].chave == chave) {
			return pos;
		}
	}
	return -1;
}

void Insere (int chave) {  		/* FUNÇÃO INSERE */
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

void Excluir (int chave) { 			/* RESPONSÁVEL POR EXCLUIR ELEMENTOS*/
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

void Imprime() {		/* IMPRIME ELEMENTOS DA TABELA BEM COMO O QUE SÃO E ONDE ESTÃO */
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

int main() {		/* FUNÇÃO PRINCIPAL */
    IniciaTB();
	
	int dados[] = {10, 25, 20, 20, 30, 40, 50};
    int tamanhoDados = sizeof(dados) / sizeof(dados[0]);

    int i = 0;
    while (i < tamanhoDados) {
        Insere(dados[i]);
        i++;
    }

	Excluir(30);

	Imprime();
	
    return 0;
}
