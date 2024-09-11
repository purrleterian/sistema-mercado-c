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
    float total;

} Carrinho;

// Sistema = resgistra os produtos
// Carrinho = guarda os produtos ja registrados

typedef struct {
    Produto *registro;
    int n;
} Sistema;

void linhaDivi(char c, int n);
void banner(char p[]);
void infoProduto(Produto p);

void registrarProduto(Produto p, Sistema *s);
void mostrarRegistro(Sistema s);

void adicCarrinho(int id, Sistema s, Carrinho *c);
void listarCarrinho(Carrinho c);

int main() {
    Carrinho carrinho;
    Sistema sistema;

    carrinho.quantidade = 0;
    carrinho.produtos = NULL;

    sistema.n = 0;
    sistema.registro = NULL;

    Produto arroz = {1, "Arroizin", 17.40, 0.5};
    Produto paes = {2, "Naes", 9.90, 0};
    Produto suco = {3, "Suquin", 11.99, 0};
    Produto bolo = {4, "Bolo de Cenoura", 15.50, 0};

    // 4 items registrados no sistema
    registrarProduto(arroz, &sistema);
    registrarProduto(paes, &sistema);
    registrarProduto(suco, &sistema);
    registrarProduto(bolo, &sistema);

    // 1 item adicionado ao carrinho
    adicCarrinho(3, sistema, &carrinho);
    listarCarrinho(carrinho);

    free(sistema.registro);
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

void registrarProduto(Produto p, Sistema *s) {
    s->n++;
    if (s->n >= 1) {
        Produto *temp = realloc(s->registro, s->n * sizeof(Produto));

        if (temp == NULL) {
            printf("Erro ao realocar memoria");
            exit(1);
        }

        s->registro = temp;
    }

    s->registro[s->n - 1] = p;
}

void adicCarrinho(int id, Sistema s, Carrinho *c) {
    // ao adicionar um produto do registro para o carrinho,
    // percorrer o registro em busca do produto desejado. Caso o produto
    // nao for encontrado, ele ainda nao foi registrado. Se encontrado,
    // adicionar ao carrinho, perguntando a quantidade a ser adicionada.
    int encontrado = 0;
    for (int i = 0; i < s.n; i++) {
        if (id == s.registro[i].id) {
            c->quantidade++;
            if (c->quantidade >= 1) {
                Produto *temp =
                    realloc(c->produtos, c->quantidade * sizeof(Produto));

                if (temp == NULL) {
                    printf("Erro ao realocar memoria");
                    exit(1);
                }

                c->produtos = temp;
            }

            encontrado = 1;
            c->produtos[c->quantidade - 1] = s.registro[i];
        }
    }
    if (!encontrado) {
        printf("ID do produto fornecido nao encontrado no registro do sistema");
    }
}

void mostrarRegistro(Sistema s) {
    for (int i = 0; i < s.n; i++) {
        infoProduto(s.registro[i]);
    }
}

void listarCarrinho(Carrinho c) {
    for (int i = 0; i < c.quantidade; i++) {
        infoProduto(c.produtos[i]);
    }
}