#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   book_code;
    int   book_amount;
    char* book_author;
    char* book_title;
} Book;

typedef struct {
    int   user_phone;
    int   user_code;
    char* user_name;
} User;


Book *book = NULL;

/*
 * Ponteiro de livros no escopo global para que
 * todas as funções tenham acesso a ele.
 */

User *user = NULL;

/*
 * Ponteiro de usuários no escopo global para que
 * todas as funções tenham acesso a ele.
 */

void clear_buffer() {
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
    
    /*
     * Evita problemas com o armazenamento de elementos
     * digitados pelo utilizador do programa.
     */
}

void register_book(int *book_quantity) {
    book = realloc(book, (*book_quantity + 1) * sizeof(Book));
    if (book == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    Book *new_book = &book[*book_quantity];

    printf("\nDigite o codigo do livro: ");
    scanf("%d", &new_book->book_code);
    clear_buffer();

    printf("Digite a quantidade de exemplares: ");
    scanf("%d", &new_book->book_amount);
    clear_buffer();

    char buffer[256];

    printf("Digite o nome do autor: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove o \n deixado pelo fgets

    new_book->book_author = malloc(strlen(buffer) + 1);
    strcpy(new_book->book_author, buffer);

    printf("Digite o titulo do livro: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    new_book->book_title = malloc(strlen(buffer) + 1);
    strcpy(new_book->book_title, buffer);

    *book_quantity += 1;

    printf("\nLivro cadastrado com sucesso!\n");
}

void borrow_book(int book_quantity) {
    if (book_quantity == 0) {
        printf("\nAinda não há nenhum livro cadastrado no sistema.\n");
        return;
    }

    int book_code_query;
    printf("\nDigite o código do livro que deseja pegar emprestado... ");
    
    /*
     * Dispondo do código do livro, torna-se mais fácil
     * realizar uma busca.
     */
    
    scanf("%d", &book_code_query);
    clear_buffer();

    for (int index = 0; index < book_quantity; index += 1) {
        if (book[index].book_code == book_code_query) {
            if (book[index].book_amount > 0) {
                book[index].book_amount -= 1;
                
                printf("O empréstimo do livro foi realizado com sucesso.\n");
                printf("Ainda há %d exemplares restantes.\n", book[index].book_amount);
            }
            
            else {
                printf("Desculpe, este livro encontra-se esgotado no momento.\n");
            }
            
            return;
        }
    }
    
    printf("Não foi possível encontrar um livro com o código %d.\n", book_code_query);
}

void return_book(int book_quantity) {
    if (book_quantity == 0) {
        printf("\nAinda não há nenhum livro cadastrado no sistema.\n");
        return;
    }

    int book_code_query;
    printf("\nDigite o código do livro que deseja devolver: ");
    
    scanf("%d", &book_code_query);
    clear_buffer();

    for (int index = 0; index < book_quantity; index++) {
        if (book[index].book_code == book_code_query) {
            book[index].book_amount += 1;
            
            printf("Devolução realizada com sucesso!\n");
            printf("Agora há %d exemplar(es) disponível(is) em estoque.\n", book[index].book_amount);
            return;
        }
    }
    
    printf("Não foi possível encontrar um livro com o código %d.\n", book_code_query);
}
void search_book(int book_quantity) {

    // Se nao tem livro cadastrado, saida:
    if (book_quantity == 0) {
        printf("\nAinda nao ha nenhum livro cadastrado no sistema.\n");
        return;
    }

    int opcao;
    
    printf("\n===== BUSCAR LIVRO =====\n");
    printf("[1] Buscar por codigo\n");
    printf("[2] Buscar por titulo\n");
    printf("[0] Voltar\n");

    if (scanf("%d", &opcao) != 1) {
        clear_buffer();
        return;
    }
    clear_buffer();

    int achou = 0;    //vai virar 1 se encontrar algum livro
    int i;

    //Ponteiro para percorrer o vetor de livros
    Book *pont = book;

    //buscar por código
    if (opcao == 1) {

        int codigoLivro;
        printf("Digite o codigo do livro: ");
        scanf("%d", &codigoLivro);
        clear_buffer();

        for (i = 0; i < book_quantity; i++) {
            if ((pont + i)->book_code == codigoLivro) {
                printf("\n--- Livro encontrado ---\n");
                printf("Codigo: %d\n", (pont + i)->book_code);
                printf("Titulo: %s\n", (pont + i)->book_title);
                printf("Autor: %s\n", (pont + i)->book_author);
                printf("Disponiveis: %d\n", (pont + i)->book_amount);
                achou = 1;
            }
        }
    }

   //buscar por titulo:
        else if (opcao == 2) {

        char title_query[100];
        printf("Digite o titulo do livro: ");
        scanf(" %[^\n]", title_query);
        clear_buffer();

        for (i = 0; i < book_quantity; i++) {
            //Da biblioteca <string.h>, strcmp retorna 0 quando as strings sao iguais
            if (strcmp((pont + i)->book_title, title_query) == 0) {
                printf("\n--- Livro encontrado ---\n");
                printf("Codigo: %d\n", (pont + i)->book_code);
                printf("Titulo: %s\n", (pont + i)->book_title);
                printf("Autor: %s\n", (pont + i)->book_author);
                printf("Disponiveis: %d\n", (pont + i)->book_amount);
                achou = 1;
            }
        }
    }
    
    else if (opcao == 0) {
        return;
    }

    else {
        printf("Opcao invalida.\n");
        return;
    }

    if (!achou) {
        printf("\nNenhum livro encontrado.\n");
    }
}

int main(int argc, char *argv[]) {
    int book_quantity = 0;
    
    /*
     * Esta variável guarda a quantidade de livros
     * existentes no âmbito do ponteiro "book".
     */
    
    int user_quantity = 0;
    
    /*
     * Esta variável guarda a quantidade de livros
     * existentes no âmbito do ponteiro "user".
     */
    int menu; // esta variavel vai ser usada para uso do menu
      do {
        printf("\n========== MENU ==========\n");
        printf("1. Cadastrar livro\n");
        printf("2. Cadastrar usuario\n");
        printf("3. Listar livros\n");
        printf("4. Buscar livro\n");
        printf("5. Emprestimo de livro\n");
        printf("6. Devolucao de livro\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &menu);
        clear_buffer();
           
        

        switch (menu) {
            case 1:
                //funcao de cadastro de livros
                register_book(&book_quantity);
                break;
            case 2:
                //funcao de usuario
                break;
            case 3:
                //funcao de listagem de livros
                break;
            case 4:
                search_book(book_quantity);
                break;
            case 5:
                borrow_book(book_quantity);
                break;
            case 6:
                return_book(book_quantity);
                break;
            case 7:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (menu != 7);


    for (int i = 0; i < book_quantity; i++) {
        free(book[i].book_author);
        free(book[i].book_title);
    }
    free(book);
    free(user); //liberacao dos vetores apos fim de uso
 
    return EXIT_SUCCESS;
}
