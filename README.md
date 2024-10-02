# Sistema de Supermercado

## Weldesmart

### Implementação de um sistema de supermerccdo simples, capaz de realizar as seguintes funções:

- Adicionar produtos ao registro do sistema do mercado
- Adicionar e remover produtos ao carrinho
- Obter listas detalhadas e formatadas dos produtos presentes no sistema e no carrinho

### Estrutura do programa

Para otimizar a flexibilidade do programa, sua estrutura foi separada em diversas funções.
O Arquivo header 'main.h' contém protótipos de funções, definições de structs e constantes com a palavra chave 'define'

O fluxo principal do programa é controlado por uma estrutura switch, tornando o programa expansível para o futuro.
Entre os conceitos estudados em sala implementados no programa, estão:

- Algoritmos de ordenação
- Arrays
- Structs
- Ponteiros
- etc

---

### Funcionalidades de Destaque/Funcionalidades adicionais:

- Remoção de produtos do carrinho
- Organização dos produtos no carrinho e no sistema através do algoritmo de ordenação por seleção
- Implementação de um sistema de descontos ao registrar um produto ao sistema

### Instruções de Compilação:

- (Opção 1) Ferramanta 'make' através da Makefile inclusa
- (Opção 2) Compilação pelo gcc. Digite `gcc ./src/main.c -o mercado.exe`

Ambas as opções irão gerar um executavel capaz de ser iniciado pelo terminal
