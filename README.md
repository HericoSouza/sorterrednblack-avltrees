
# Sistema de Árvores Balanceadas (AVL e Rubro-Negra)

Este projeto implementa duas estruturas de dados balanceadas — Árvore AVL e Árvore Rubro-Negra — em C++.  
O usuário pode escolher qual tipo de árvore utilizar ao compilar o código.

Além disso, o programa oferece funcionalidades como a inserção de elementos, remoção e etc.

---

## Funcionalidades

O sistema oferece as seguintes operações:

- Inserção de elementos inteiros
- Remoção de elementos inteiros
- Busca por elementos
- Impressão da árvore (em ordem)
- Escolha entre Árvore AVL e Árvore Rubro-Negra na inicialização

---

## Dependências

- Compilador C++ compatível com C++17 (ex: g++ ou clang++)
- Terminal para execução do programa

---

## Como compilar

No terminal, dentro do diretório do projeto, execute o comando:

```bash
g++ -std=c++17 main.cpp -o arvore

## Estrutura do Programa
Ao compilar, o usuário será apresentado com a escolha do tipo de árvore:

Escolha o tipo de árvore:
1. Árvore AVL
2. Árvore Rubro-Negra
>

Após a escolha, o menu de funcionalidades:

1. Inserir elemento
2. Remover elemento
3. Buscar elemento
4. Imprimir árvore
0. Sair
>

## Exemplo de utilização:
Escolha o tipo de arvore:
1 - AVL
2 - Rubro-Negra
1

1-Inserir
2-Remover
3-Buscar
4-Imprimir
0-Sair
1
0

1-Inserir
2-Remover
3-Buscar
4-Imprimir
0-Sair
1
2

1-Inserir
2-Remover
3-Buscar
4-Imprimir
0-Sair
1
4

1-Inserir
2-Remover
3-Buscar
4-Imprimir
0-Sair
3
2
Encontrado

1-Inserir
2-Remover
3-Buscar
4-Imprimir
0-Sair
2
2

1-Inserir
2-Remover
3-Buscar
4-Imprimir
0-Sair
1
5

1-Inserir
2-Remover
3-Buscar
4-Imprimir
0-Sair
4
R----4
     L----0
     R----5

1-Inserir
2-Remover
3-Buscar
4-Imprimir
0-Sair
0

