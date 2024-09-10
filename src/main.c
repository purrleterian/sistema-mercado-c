#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[30];
    double preco;
    float desconto;

} Produto;

void banner(char p[]);
void infoProduto(Produto p);

int main() {
    banner("Hello");
    return 0;
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
}

// void infoProduto(Produto p) {}