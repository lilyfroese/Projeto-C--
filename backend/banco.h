#ifndef BANCO_H
#define BANCO_H

#include <sqlite3.h>
#include <string>

using namespace std;

extern sqlite3* db;

bool abrirBanco();
void criarTabela();
void inserirProduto(const string& nome, const string& unidade, double valor, int quantidade);
void listarProdutos();
void editarProduto(int id, const string& nome, const string& unidade, double valor, int quantidade);
void excluirProduto(int id);
void menu();

#endif 