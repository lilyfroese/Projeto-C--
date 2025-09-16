#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

class Produto {
public:
    int id;
    string nome;
    string unidade;
    double preco;
    int quantidade;

    Produto(int id, const string& nome, const string& unidade, double preco, int quantidade)
        : id(id), nome(nome), unidade(unidade), preco(preco), quantidade(quantidade) {}
};

sqlite3* db;

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

void inserirProduto(const string& nome, const string& unidade, double preco, int quantidade) {
    string sql = "INSERT INTO produtos (nome, unidade, preco, quantidade) VALUES ('"
                 + nome + "', '" + unidade + "', " + to_string(preco) + ", " + to_string(quantidade) + ");";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Erro ao inserir produto: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Produto inserido com sucesso!" << endl;
    }
}

static int listarCallback(void* NotUsed, int argc, char** argv, char** azColName) {
    cout << "ID: " << argv[0] 
         << " | Nome: " << argv[1] 
         << " | Unidade: " << argv[2]
         << " | Preço: " << argv[3] 
         << " | Quantidade: " << argv[4] << endl;
    return 0;
}

void listarProdutos() {
    const char* sql = "SELECT * FROM produtos;";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql, listarCallback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Erro ao listar produtos: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void editarProduto(int id, const string& nome, const string& unidade, double preco, int quantidade) {
    string sql = "UPDATE produtos SET nome = '" + nome + "', unidade = '" + unidade + 
                 "', preco = " + to_string(preco) + ", quantidade = " + to_string(quantidade) + 
                 " WHERE id = " + to_string(id) + ";";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Erro ao editar produto: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Produto editado com sucesso!\n" << endl;
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
        cout << "Produto excluído com sucesso!\n" << endl;
    }
}

void menu() {
    int opcao;
    do {
        cout << "\n=== MENU DE PRODUTOS ===\n";
        cout << "1. Inserir Produto\n";
        cout << "2. Listar Produtos\n";
        cout << "3. Editar Produto\n";
        cout << "4. Excluir Produto\n";
        cout << "5. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            string nome, unidade;
            double preco;
            int quantidade;
            cout << "Nome do Produto: ";
            getline(cin, nome);
            cout << "Unidade do Produto (ex: kg, L, un): ";
            getline(cin, unidade);
            cout << "Preço do Produto: ";
            cin >> preco;
            cout << "Quantidade do Produto: ";
            cin >> quantidade;
            cin.ignore();
            inserirProduto(nome, unidade, preco, quantidade);
        } else if (opcao == 2) {
            listarProdutos();
        } else if (opcao == 3) {
            int id; string nome, unidade; double preco; int quantidade;
            cout << "ID do Produto a ser editado: ";
            cin >> id; cin.ignore();
            cout << "Novo Nome do Produto: ";
            getline(cin, nome);
            cout << "Nova Unidade do Produto: ";
            getline(cin, unidade);
            cout << "Novo Preço do Produto: ";
            cin >> preco;
            cout << "Nova Quantidade do Produto: ";
            cin >> quantidade;
            cin.ignore();
            editarProduto(id, nome, unidade, preco, quantidade);
        } else if (opcao == 4) {
            int id; 
            cout << "ID do Produto a ser excluído: ";
            cin >> id;
            cin.ignore();
            excluirProduto(id);
        }

    } while (opcao != 5);
        
}

int main() {
    if (!abrirBanco()) return 1;
    criarTabela();
    menu();
    sqlite3_close(db);
    return 0;
}