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

    // Loop infinito gerenciado pela variavel 'rodando', assim posso parar o
    // loop alterando-a
    while (rodando) {
        menu();
    }

    return 0;
}

void menu() {
    // Buffer pra guardar o input do usuario que determina a acao
    char escolhaFluxo[MAX_BUFFER];

    printf("\nSistema interno de compras do Mercado %s\n", MERCADO_NOME);
    linhaDiv(30, '-');
    printf("(1) Adicionar produto ao registro do sistema\n");
    printf("(2) Adicionar produto ao carrinho\n");
    printf("(3) Listar os produtos no registro\n");
    printf("(4) Listar os produtos no carrinho\n");
    printf("(5) Concluir compras\n");
    printf("(6) Sair\n");

    printf(">> ");
    fgets(escolhaFluxo, MAX_BUFFER, stdin);

    // 'atoi' converte ascii para integer, assim o input de fget pode ser usado
    // pra comparar os numeros em switch
    switch (atoi(escolhaFluxo)) {
        case 1:
            // definir variaveis que vao compor o novo produto
            char regiBuffer[MAX_BUFFER];
            char novoNome[MAX_NOME];
            int idNovoSistema;
            float novoPreco, novoDesc;

            int teveErro = 0;
            int resultadoProd;
            Produto novoProduto;

            printf("ID unico do produto: \n");
            printf(">> ");

            // fgets combinado com sscanf e um bom jeito de evitar deixar
            // linhas (\n) indesejadas no buffer, e ao mesmo tempo convertendo
            // input para outros tipos (nesse caso buffer armazenando no %d)
            fgets(regiBuffer, MAX_BUFFER, stdin);

            // Scanf sempre retorna o numero de inputs registrados com
            // sucesso...
            resultadoProd = sscanf(regiBuffer, "%d", &idNovoSistema);

            // ...ou seja se esse numero for '1' entao nao houveram erros
            if (resultadoProd == 1) {
                novoProduto.id = idNovoSistema;
            } else {
                // se tiveram erros, lembrar disso para impedir que info com
                // erro seja adicionada mais na frente
                teveErro = 1;
                printf("Erro ao registrar ID do produto\n");
            }

            // repetir o processo acima pros outros parametros
            printf("Nome do produto: \n");
            printf(">> ");

            fgets(regiBuffer, MAX_BUFFER, stdin);
            resultadoProd = sscanf(regiBuffer, "%s", novoNome);

            if (resultadoProd == 1) {
                strcpy(novoProduto.nome, novoNome);
            } else {
                teveErro = 1;
                printf("Erro ao registrar nome do produto\n");
            }

            printf("Preco do produto: \n");
            printf(">> ");

            fgets(regiBuffer, MAX_BUFFER, stdin);
            resultadoProd = sscanf(regiBuffer, "%f", &novoPreco);

            if (resultadoProd == 1) {
                novoProduto.preco = novoPreco;
            } else {
                teveErro = 1;
                printf("Erro ao registrar o preco do produto\n");
            }

            printf("Desconto do produto: \n");
            printf(">> ");

            fgets(regiBuffer, MAX_BUFFER, stdin);
            resultadoProd = sscanf(regiBuffer, "%f", &novoDesc);

            if (resultadoProd == 1) {
                novoProduto.desconto = novoDesc;
            } else {
                teveErro = 1;
                printf("Erro ao registrar o desconto do produto\n");
            }

            // produtos sempre vao comecar com apenas 1, nao e possivel
            // registrar 2 do mesmo produto ao mesmo tempo
            novoProduto.n = 1;

            // se nenhum erro foi registrado no caminho, cadastrar o produto
            if (!teveErro) {
                cadastrarProduto(&sistemaMercado, novoProduto);
            }

            break;

        case 2:
            char idBuffer[MAX_BUFFER];
            int idNovoCarrinho;

            printf("ID unico do produto: \n");
            printf(">> ");
            fgets(idBuffer, MAX_BUFFER, stdin);
            int resultadoCarr = sscanf(idBuffer, "%d", &idNovoCarrinho);
            if (resultadoCarr == 1) {
                comprarProduto(sistemaMercado, &carrinhoMercado,
                               idNovoCarrinho);
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
            // - somar os precos no carrinho
            // - retornar o total
            // - esvaziar o carrinho
            printf("Total: %.2f", obterTotal(&carrinhoMercado));
            finalizarCompras(&carrinhoMercado);
            break;

        case 6:
            rodando = 0;
            exit(0);
            break;
    }
}

void banner(char s[]) {
    // funcao simples pra evitar repetir esse loop sempre que quiser formatar
    // texto com caracteres envolta
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
    // funcao de utilidade pra desenhar uma linha horizontal divisoria
    for (int i = 0; i < n; i++) {
        printf("%c", c);
    }
    printf("\n");
}

void infoProduto(Produto p, int incluirN) {
    banner(p.nome);

    // apenas mostrar a quantia de um produto se ela for maior de que 1.
    // A variavel 'incluirN' serve pra eu poder esconder essa informacao quando
    // mostrando o registro (visto que n faria muito sentido mostrar mais do que
    // um do mesmo produto no registro do sistema)
    if ((p.n > 1) && incluirN) printf("- x%d\n", p.n);
    printf("- ID: %d\n", p.id);

    // caso houver desconto...
    if (p.desconto > 0) {
        // ... adicione esse desconto para as informacoes do produto...
        printf("- Preco: %.2f (%.2f) // %0.f%% de desconto",
               p.preco - (p.preco * p.desconto), p.preco, p.desconto * 100);
        // ...e calcule o desconto multiplicando pelo preco e subtraindo do
        // total
    } else {
        // se n houver desconto, n precisa mostrar
        printf("- Preco: %.2f", p.preco);
    }
    printf("\n");
    linhaDiv(20, '*');
}

int temNoCarrinho(Carrinho c, int novoId) {
    // loop simples que passa pela array da struct Carrinho ate encontrar um id,
    // se n for encontrado, produto nao esta no carrinho
    int encontrado = 0;
    for (int i = 0; i < c.quantidade; i++) {
        if (c.produtos[i].id == novoId) {
            encontrado = 1;
        }
    }
    return encontrado;
}

int temNoSistema(Sistema s, int novoId) {
    // mesma funcao que acima, apenas que para analisar o sistema
    int encontrado = 0;
    for (int i = 0; i < s.quantidade; i++) {
        if (s.produtos[i].id == novoId) {
            encontrado = 1;
        }
    }

    return encontrado;
}

void comprarProduto(Sistema s, Carrinho *c, int novoId) {
    // caso o produto sendo comprado esteja presente no sistema...
    if (temNoSistema(s, novoId)) {
        // ... faca um loop pelos elementos do sistema
        for (int i = 0; i < s.quantidade; i++) {
            // se no sistema estiver um produto com o mesmo id do produto sendo
            // comprado...
            if (s.produtos[i].id == novoId) {
                // ...verifique se esse produto ja esta no carrinho.
                if (!temNoCarrinho(*c, novoId)) {
                    // se n estiver, adicione ele pro primeiro espaco vazio na
                    // array, indo pro final e depois aumente a quantidade de
                    // produtos total no carrinho
                    c->produtos[c->quantidade] = s.produtos[i];
                    c->quantidade++;

                } else {
                    // se o produto ja estiver no carrinho, faca um segundo
                    // loop. A diferenca e que esse loop e para passar pelo
                    // carrinho, nao pelo sistema como o acima
                    for (int j = 0; j < c->quantidade; j++) {
                        // ao encontrar a posicao do produto ja presente...
                        if (s.produtos[i].id == c->produtos[j].id) {
                            // adicionar 1 para seu n, definindo que ha
                            // multiplos dele presente obs: c->quantidade
                            // armazena apenas o numero de produtos unicos, logo
                            // aumentar o n do produto n quer dizer que
                            // c->quantidade tambem aumenta
                            c->produtos[j].n++;
                        }
                    }
                }
            }
        }
    } else {
        printf("Produto com ID %d nao registrado no sistema\n", novoId);
    }
}

void listarProdutos(Sistema s) {
    printf("Registro de Produtos: \n");
    // loop simples que aplica a funcao infoProduto a todos os produtos do
    // sistema
    for (int i = 0; i < s.quantidade; i++) {
        infoProduto(s.produtos[i], 0);
    }
    linhaDiv(25, '-');
}

void visualizarCarrinho(Carrinho c) {
    printf("Carrinho: \n");

    // loop simples que aplica a funcao infoProduto a todos os produtos do
    // carrinho
    for (int i = 0; i < c.quantidade; i++) {
        infoProduto(c.produtos[i], 1);
    }

    linhaDiv(25, '-');
}

void cadastrarProduto(Sistema *s, Produto p) {
    if (temNoSistema(*s, p.id)) {
        printf("O Produto de ID %d ja foi registrado.\n", p.id);
    } else {
        // se o produto ja n estiver no sistema, adicionar ele pro
        // primeiro espaco vazio na array
        s->produtos[s->quantidade] = p;
        ++s->quantidade;
    }
}

void finalizarCompras(Carrinho *c) {
    // memset e uma funcao de string.h que permite resetar todas as posicoes de
    // uma array pra um certo valor, nesse caso, 0
    // Obs: c->quantidade * sizeof(Produto) e uma maneira de determinar o
    // tamanho da array, multiplicando o numero de elementos pelo tamanho da
    // struct criada
    memset(c->produtos, 0, c->quantidade * sizeof(Produto));
    // depois, resetar a quantidade para 0
    c->quantidade = 0;
}

float obterTotal(Carrinho *c) {
    // adquirir o total passando por todos os items no carrinhos, lembrando
    // de levar em consideracao os descontos
    float total = 0;
    for (int i = 0; i < c->quantidade; i++) {
        total += (c->produtos[i].preco -
                  (c->produtos[i].preco * c->produtos[i].desconto)) *
                 c->produtos[i].n;
    }
    return total;
}