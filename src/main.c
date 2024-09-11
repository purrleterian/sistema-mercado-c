#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[30];
    double preco;
    float desconto;

} Produto;

typedef struct {
    Produto *produtos;
    int quantidade;

} Carrinho;

void linhaDivi(char c, int n);
void banner(char p[]);
void infoProduto(Produto p);

void adicCarrinho(Produto p, Carrinho *c);

int main() {
    Carrinho carrinho;
    carrinho.produtos = malloc(sizeof(Produto));

    free(carrinho.produtos);
    return 0;
}

void linhaDivi(char c, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", c);
    }
    printf("\n");
}

void banner(char p[]) {
    size_t tamanhoP = strlen(p);
    for (int i = 0; i < tamanhoP + 4; i++) {
        printf("=");
    }
    printf("\n");
    printf("= %s =", p);
    printf("\n");

    for (int i = 0; i < tamanhoP + 4; i++) {
        printf("=");
    }
    printf("\n");
}

void infoProduto(Produto p) {
    banner(p.nome);

    printf("- ID: %d\n", p.id);
    if (p.desconto > 0) {
        printf("- Preco: %.2f (%.2f) // %.0f%% de desconto",
               p.preco - (p.preco * p.desconto), p.preco, p.desconto * 100);
    } else {
        printf("- Preco: %.2f", p.preco);
    }
    printf("\n");
    linhaDivi('-', 15);
}

void adicCarrinho(Produto p, Carrinho *c) {
    Produto *temp = realloc(c->produtos, sizeof(c->produtos) + sizeof(Produto));
    if (temp == NULL) {
        printf("Error reallocating memory");
        exit(1);
    }

    c->produtos = temp;
    c->produtos[c->quantidade - 1] = p;
}