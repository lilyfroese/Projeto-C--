Sistema de Gestão de Produtos 

O projeto consiste em uma implemetação de um sistema de gerenciamento de produtos em C++, utilizando SQLite como banco de dados.
O sistema permite inserir, listar, editar e excluir produtos diretamente pelo terminal. 

Pré-requisitos:

- Compilador C++ (G++/GCC)
- SQLite (código fonte incluído no projeto)

Estrutura do projeto:

frontend/main.cpp          
> Menu e interface do usuário

backend/banco.cpp          
> Funções de banco de dados

backend/banco.h            
> Header do banco

models/produto.cpp         
> Model do Produto

models/produto.h           
> Header do produto

lib/sqlite3.c              
> Código fonte SQLite3

lib/sqlite3.h              
> Header do SQLite3

include/                   
> Headers adicionais

Compilação:

1. Compilar o SQLite:
>gcc -c lib/sqlite3.c -Iinclude -o lib/sqlite3.o

2. Compilar os arquivos C++ e linkar com o SQLite:
>g++ frontend/main.cpp backend/banco.cpp models/produto.cpp lib/sqlite3.o -Iinclude -Ibackend -Imodels -o programa

Execução:

Após a compilação, execute:
> ./programa.exe              

O programa exibirá um menu interativo para gerenciar os produtos.


Observações:

> 1. O banco de dados "produtos.db" é criado automaticamente na primeira execução. 
> 2. É preciso ter permissão de escrita na pasta do projeto para criação do banco de dados. (O programa precisa poder criar arquivos na pasta em que está rodando).
