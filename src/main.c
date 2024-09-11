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
void produtosNoCarrinho(Carrinho c);

int main() {
    Carrinho carrinho;

    carrinho.quantidade = 0;
    carrinho.produtos = malloc(sizeof(Produto));

    Produto arroz = {1, "Arroizin", 17.40, 0.5};
    Produto paes = {2, "Naes", 9.90, 0};
    Produto suco = {3, "Suquin", 11.99, 0};
    Produto bolo = {4, "Bolo de Cenoura", 15.50, 0};

    adicCarrinho(arroz, &carrinho);
    adicCarrinho(paes, &carrinho);
    adicCarrinho(suco, &carrinho);
    adicCarrinho(bolo, &carrinho);

    produtosNoCarrinho(carrinho);

    // TODO: verificar o tamanho do ponteiro dos produtos com o debugger
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
    c->quantidade++;
    if (c->quantidade >= 1) {
        Produto *temp = realloc(c->produtos, c->quantidade * sizeof(Produto));

        if (temp == NULL) {
            printf("Erro ao realocar memoria");
            exit(1);
        }

        c->produtos = temp;
    }

    c->produtos[c->quantidade - 1] = p;
}

void produtosNoCarrinho(Carrinho c) {
    for (int i = 0; i < c.quantidade; i++) {
        infoProduto(c.produtos[i]);
    }
}