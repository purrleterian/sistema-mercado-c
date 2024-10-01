#ifndef MYHEADER_H
#define MYHEADER_H

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
void linhaDiv(int n, char c);

void infoProduto(Produto p);
int temNoCarrinho(Carrinho c, int novoId);
Produto pegarProdutoPorCodigo(int id);

void comprarProduto(Sistema s, Carrinho *c, int novoId);
void visualizarCarrinho(Carrinho c);

void listarProdutos(Sistema s);
void cadastrarProduto(Sistema *s, Produto p);

#endif