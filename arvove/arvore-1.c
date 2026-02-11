/*
 * Detective Quest - mapa da mansão
 * A árvore binária representa salas e conexões permitidas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char *nome;
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/* criaSala() – cria, de forma dinâmica, uma sala com nome e nós filhos nulos. */
Sala *criarSala(const char *nome) {
    Sala *sala = malloc(sizeof(Sala));
    if (!sala) {
        fprintf(stderr, "Erro ao alocar sala\n");
        exit(EXIT_FAILURE);
    }
    sala->nome = malloc(strlen(nome) + 1);
    if (!sala->nome) {
        fprintf(stderr, "Erro ao alocar nome da sala\n");
        free(sala);
        exit(EXIT_FAILURE);
    }
    strcpy(sala->nome, nome);
    sala->esquerda = sala->direita = NULL;
    return sala;
}

/* liberarMapa() – solta toda a memória alocada pela árvore. */
void liberarMapa(Sala *raiz) {
    if (!raiz) return;
    liberarMapa(raiz->esquerda);
    liberarMapa(raiz->direita);
    free(raiz->nome);
    free(raiz);
}

/* explorarSalas() – permite a navegação do jogador pela árvore. */
void explorarSalas(Sala *atual) {
    char opcao[8];
    while (atual) {
        printf("\nVocê está em %s.\n", atual->nome);
        if (!atual->esquerda && !atual->direita) {
            printf("Este cômodo não possui mais caminhos.\n");
            break;
        }
        puts("Escolha um caminho:");
        if (atual->esquerda)
            printf("  (e) Ir para %s\n", atual->esquerda->nome);
        if (atual->direita)
            printf("  (d) Ir para %s\n", atual->direita->nome);
        puts("  (s) Sair da exploração");
        printf("Opção: ");
        if (!fgets(opcao, sizeof opcao, stdin)) {
            puts("Entrada encerrada.");
            break;
        }
        char escolha = opcao[0];
        if (escolha == 's' || escolha == 'S') {
            puts("Exploração encerrada pelo jogador.");
            break;
        }
        if ((escolha == 'e' || escolha == 'E') && atual->esquerda) {
            atual = atual->esquerda;
        } else if ((escolha == 'd' || escolha == 'D') && atual->direita) {
            atual = atual->direita;
        } else {
            puts("Opção inválida. Tente novamente.");
        }
    }
}

/* main() – monta o mapa inicial e dá início à exploração. */
int main(void) {
    Sala *hall = criarSala("Hall de entrada");
    Sala *biblioteca = criarSala("Biblioteca silenciosa");
    Sala *salap = criarSala("Salão principal");
    Sala *estufa = criarSala("Estufa misteriosa");
    Sala *cozinha = criarSala("Cozinha gourmet");
    Sala *laboratorio = criarSala("Laboratório secreto");
    Sala *torre = criarSala("Torre do vigia");
    Sala *jardim = criarSala("Jardim das estátuas");

    hall->esquerda = biblioteca;
    hall->direita = salap;

    biblioteca->esquerda = estufa;
    biblioteca->direita = cozinha;

    salap->esquerda = laboratorio;
    salap->direita = torre;

    torre->direita = jardim;

    puts("Bem-vindo a Detective Quest! Explore a mansão a partir do Hall.");
    explorarSalas(hall);
    liberarMapa(hall);
    puts("Obrigado por jogar Detective Quest!");

    return 0;
}