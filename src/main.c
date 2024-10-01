#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rodando;

Sistema sistemaMercado;
Carrinho carrinhoMercado;

int main() {
    rodando = 1;
    carrinhoMercado.quantidade = 0;
    sistemaMercado.quantidade = 0;

    cadastrarProduto(&sistemaMercado,
                     (Produto){4, "Suco de Laranja", 4.90, 0, 1});
    cadastrarProduto(&sistemaMercado, (Produto){7, "Pao", 9.60, 0, 1});
    cadastrarProduto(&sistemaMercado, (Produto){9, "Cenouras", 7.50, 0.1, 1});

    while (rodando) {
        menu();
    }

    return 0;
}

void menu() {
    char escolhaFluxo[10];

    printf("\nSistema interno de compras do Mercado %s\n", MERCADO_NOME);
    linhaDiv(30, '-');
    printf("(1) Adicionar produto ao registro do sistema\n");
    printf("(2) Adicionar produto ao carrinho\n");
    printf("(3) Listar os produtos no registro\n");
    printf("(4) Listar os produtos no carrinho\n");
    printf("(5) Concluir compras\n");
    printf("(6) Sair\n");

    printf(">> ");
    fgets(escolhaFluxo, 10, stdin);

    switch (atoi(escolhaFluxo)) {
        case 1:
            break;

        case 2:
            char idBuffer[MAX_BUFFER];
            int novoId;

            printf(">> ");
            fgets(idBuffer, MAX_BUFFER, stdin);
            int resultado = sscanf(idBuffer, "%d", &novoId);
            if (resultado == 1) {
                comprarProduto(sistemaMercado, &carrinhoMercado, novoId);
            } else {
                printf("\nErro ao receber input\n");
            }

            break;

        case 3:
            listarProdutos(sistemaMercado);
            break;

        case 4:
            visualizarCarrinho(carrinhoMercado);
            break;

        case 5:
            // Ao concluir as compras:
            // - esvaziar o carrinho
            // - somar os precos no carrinho
            // - retornar o total
            break;

        case 6:
            rodando = 0;
            exit(0);
            break;
    }
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

void linhaDiv(int n, char c) {
    for (int i = 0; i < n; i++) {
        printf("%c", c);
    }
    printf("\n");
}

void infoProduto(Produto p) {
    banner(p.nome);
    if (p.n > 1) printf("- x%d\n", p.n);
    printf("- ID: %d\n", p.id);

    if (p.desconto > 0) {
        printf("- Preco: %.2f (%.2f) // %0.f%% de desconto",
               p.preco - (p.preco * p.desconto), p.preco, p.desconto * 100);
    } else {
        printf("- Preco: %.2f", p.preco);
    }
    printf("\n");
    linhaDiv(20, '*');
}

int temNoCarrinho(Carrinho c, int novoId) {
    int encontrado = 0;
    for (int i = 0; i < c.quantidade; i++) {
        if (c.produtos[i].id == novoId) {
            encontrado = 1;
        }
    }
    return encontrado;
}

int temNoSistema(Sistema s, int novoId) {
    int encontrado = 0;
    for (int i = 0; i < s.quantidade; i++) {
        if (s.produtos[i].id == novoId) {
            encontrado = 1;
        }
    }

    return encontrado;
}

void comprarProduto(Sistema s, Carrinho *c, int novoId) {
    int encontrado = 0;
    for (int i = 0; i < s.quantidade; i++) {
        if (s.produtos[i].id == novoId) {
            encontrado = 1;
            if (temNoCarrinho(*c, novoId)) {
                c->produtos[i].n++;
            } else {
                c->produtos[c->quantidade] = s.produtos[i];
                c->quantidade++;
            }
        }
    }

    if (!encontrado) {
        printf("Produto com ID %d nao registrado no sistema\n", novoId);
    }
}

void listarProdutos(Sistema s) {
    printf("Registro de Produtos: \n");
    for (int i = 0; i <= s.quantidade - 1; i++) {
        infoProduto(s.produtos[i]);
    }
    linhaDiv(25, '-');
}

void visualizarCarrinho(Carrinho c) {
    printf("Carrinho: \n");
    for (int i = 0; i < c.quantidade; i++) {
        infoProduto(c.produtos[i]);
    }

    linhaDiv(25, '-');
}

void cadastrarProduto(Sistema *s, Produto p) {
    int duplicado = 0;
    for (int i = 0; i < s->quantidade; i++) {
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