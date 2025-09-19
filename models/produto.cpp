#include "produto.h"

Produto::Produto(int id, const string& nome, const string& unidade, double valor, int quantidade)
    : id(id), nome(nome), unidade(unidade), valor(valor), quantidade(quantidade) {}