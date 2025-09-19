#include "produto.h"
#include "banco.h"
#include <sqlite3.h>

int main() {
    if (!abrirBanco()) {
        return 1;
    }
    criarTabela();
    menu();
    sqlite3_close(db);
    return 0;
}
