#include <stdio.h>

typedef struct {
    char Name[50];
    float Price;
    int Quantity;
}Product;

typedef struct {
    int id;
    Product items[99];
    float Total;
}Order;

int main() {
    int status = 1,
        id = 0,
        c;

    Order orders[99];

    while (status)
    {
        printf("Escolha uma opção: ");
        int option;
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                orders[id].id = id;
                printf("Ordem do produto: %d", id + 1);
                float total = 0;

                for(int i = 0; i < 99; i++) {
                    while(
                        c = getchar() != '\n' && c != EOF
                    );

                    printf("Nome do produto: ");
                    char name[50];
                    fgets(name, sizeof(name), stdin);

                    printf("Preço do produto: ");
                    float price;
                    scanf("%f", &price);

                    printf("Quantidade do produto: ");
                    int quantity;
                    scanf("%d", &quantity);

                    Product product = {.Price = price, .Quantity = quantity};
                    strcpy(
                        product.Name, name
                    );

                    orders[id].Products[i] = product;

                    total += price * quantity;

                    printf("Deseja adicionar outro produto? (1-Sim / 2-Não): ");
                    char newProduct;
                    scanf(" %c", &newProduct);

                    if (newProduct != 'y')
                    {
                        break;
                    }    
                }
                orders[id].Total = total;
                id++;
                break;
            case 2:
                break;
            case 3:
                status = 0;
                break;
        }
    }
    
    return 0;
}