#include <iostream>
#include <cstdlib>
#include "banco.h"

sqlite3* db;

int contProdutos = 0;

bool abrirBanco(){
    int rc = sqlite3_open("produtos.db", &db);
    if (rc) {
        cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    return true;
}

void criarTabela() {
    const char* sql =
     "CREATE TABLE IF NOT EXISTS produtos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome TEXT NOT NULL,"
        "unidade TEXT NOT NULL,"
        "preco REAL NOT NULL,"
        "quantidade INTEGER NOT NULL DEFAULT 0);";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Erro ao criar tabela: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void inserirProduto(const string& nome, const string& unidade, double valor, int quantidade) {
    string sql = "INSERT INTO produtos (nome, unidade, preco, quantidade) VALUES ('"
                 + nome + "', '" + unidade + "', " + to_string(valor) + ", " + to_string(quantidade) + ");";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Erro ao inserir produto: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Produto inserido com sucesso!\nPressione Enter para voltar." << endl;
    }
}

static int listarCallback(void* NotUsed, int argc, char** argv, char** azColName) {
    contProdutos++;
cout << "ID: " << argv[0] 
         << " | Nome: " << argv[1] 
         << " | Unidade: " << argv[2]
         << " | Valor: " << argv[3] 
         << " | Quantidade: " << argv[4] << "\n";
    return 0;
}

void listarProdutos() {
    const char* sql = "SELECT * FROM produtos;";
    char* errMsg = 0;

    contProdutos = 0;
    int rc = sqlite3_exec(db, sql, listarCallback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Erro ao listar produtos: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else if (contProdutos == 0) {
        cout << "Nenhum produto cadastrado." << endl;
    }
}

void editarProduto(int id, const string& nome, const string& unidade, double valor, int quantidade) {
    string sql = "UPDATE produtos SET nome = '" + nome + "', unidade = '" + unidade + 
                 "', preco = " + to_string(valor) + ", quantidade = " + to_string(quantidade) + 
                 " WHERE id = " + to_string(id) + ";";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Erro ao editar produto: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Produto editado com sucesso!\nPressione Enter para voltar." << endl;
    }
}

void excluirProduto(int id) {
    string sql = "DELETE FROM produtos WHERE id = " + to_string(id) + ";";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Erro ao excluir produto: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Produto excluído com sucesso!\nPressione Enter para voltar." << endl;
    }
}

void menu() {
    int opcao;
    while (true) {
        system("cls"); 
        cout << "\n=== MENU DE PRODUTOS ===\n";
        cout << "1. Inserir Produto\n";
        cout << "2. Listar Produtos\n";
        cout << "3. Editar Produto\n";
        cout << "4. Excluir Produto\n";
        cout << "5. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            string nome, unidade;
            double valor;
            int quantidade;
            cout << "Nome do Produto: ";
            getline(cin, nome);
            cout << "Unidade do Produto (ex: kg, L, un): ";
            getline(cin, unidade);
            cout << "Valor do Produto: ";
            cin >> valor;
            cout << "Quantidade do Produto: ";
            cin >> quantidade;
            cin.ignore();
            inserirProduto(nome, unidade, valor, quantidade);
            cin.get();
        } else if (opcao == 2) {
            listarProdutos();
            cin.get();
        } else if (opcao == 3) {
            int id; string nome, unidade; double valor; int quantidade;
            cout << "ID do Produto a ser editado: ";
            cin >> id; cin.ignore();
            cout << "Novo Nome do Produto: ";
            getline(cin, nome);
            cout << "Nova Unidade do Produto: ";
            getline(cin, unidade);
            cout << "Novo Valor do Produto: ";
            cin >> valor;
            cout << "Nova Quantidade do Produto: ";
            cin >> quantidade;
            cin.ignore();
            cin.get();
            editarProduto(id, nome, unidade, valor, quantidade);
        } else if (opcao == 4) {
            int id; 
            cout << "ID do Produto a ser excluido: ";
            cin >> id;
            cin.ignore();
            cin.get();
            excluirProduto(id);
        } else if (opcao == 5) {
            cout << "Saindo do programa.";
            break;
        } else {
            cout << "Opcao invalida! Tente novamente." << endl;
            cin.get();
        }

    }while (opcao != 5);
}