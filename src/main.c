#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_CARR 50
#define MAX_SIST 50

typedef struct {
    int id;
    char nome[MAX_NOME];
    float preco;
    float desconto;

} Produto;

typedef struct {
    Produto produtos[MAX_CARR];
    int quantidade;

} Carrinho;

typedef struct {
    Produto produtos[MAX_SIST];
    int quantidade;

} Sistema;

void banner(char s[]);

void infoProduto(Produto p);
void temNoCarrinho(Produto p);

void comprarProduto(Sistema s, Carrinho *c, int novoId);
void visualizarCarrinho(Carrinho c);

void listarProdutos(Sistema s);
void cadastrarProduto(Sistema *s, Produto p);

int main() {
    Sistema sistemaMercado;
    Carrinho carrinhoMercado;

    carrinhoMercado.quantidade = 0;
    sistemaMercado.quantidade = 0;

    Produto paes = {4, "Naes", 14.60, 0.1};

    Produto suco = {1, "Suco de Laranja", 9.90, 0};

    cadastrarProduto(&sistemaMercado, paes);
    cadastrarProduto(&sistemaMercado, suco);
    // listarProdutos(sistemaMercado);

    comprarProduto(sistemaMercado, &carrinhoMercado, 1);
    comprarProduto(sistemaMercado, &carrinhoMercado, 4);
    visualizarCarrinho(carrinhoMercado);

    return 0;
}

void banner(char s[]) {
    size_t sTamanho = strlen(s);
    for (int i = 0; i < sTamanho + 4; i++) {
        printf("=");
    }

    printf("\n= %s =\n", s);
    for (int i = 0; i < sTamanho + 4; i++) {
        printf("=");
    }
    printf("\n");
}

void infoProduto(Produto p) {
    banner(p.nome);
    printf("- ID: %d\n", p.id);

    if (p.desconto > 0) {
        printf("- Preco: %.2f (%.2f) // %0.f%% de desconto",
               p.preco - (p.preco * p.desconto), p.preco, p.desconto * 100);
    } else {
        printf("- Preco: %.2f", p.preco);
    }
    printf("\n");
}

void comprarProduto(Sistema s, Carrinho *c, int novoId) {
    int encontrado = 0;
    for (int i = 0; i <= s.quantidade - 1; i++) {
        if (s.produtos[i].id == novoId) {
            encontrado = 1;
            c->produtos[c->quantidade] = s.produtos[i];
            c->quantidade++;
        }
    }

    if (!encontrado) {
        printf("Produto com ID %d nao registrado no sistema\n", novoId);
    }
}

void listarProdutos(Sistema s) {
    for (int i = 0; i <= s.quantidade - 1; i++) {
        infoProduto(s.produtos[i]);
    }
}

void visualizarCarrinho(Carrinho c) {
    for (int i = 0; i <= c.quantidade - 1; i++) {
        infoProduto(c.produtos[i]);
    }
}

void cadastrarProduto(Sistema *s, Produto p) {
    int duplicado = 0;
    for (int i = 0; i <= s->quantidade - 1; i++) {
        if (s->produtos[i].id == p.id) {
            duplicado = 1;
        }
    }

    if (duplicado) {
        printf("O Produto de ID %d ja foi registrado.\n", p.id);
    } else {
        s->produtos[s->quantidade] = p;
        ++s->quantidade;
    }
}