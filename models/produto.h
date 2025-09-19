#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
using namespace std;

class Produto {
public:
    int id;
    string nome;
    string unidade;
    double valor;
    int quantidade;

    Produto(int id, const string& nome, const string& unidade, double valor, int quantidade);
};

#endif