#include <stdio.h>
#include <stdlib.h>

#define MAX_BOOK_LENGTH 100
#define MAX_AUTHOR_LENGTH 100

typedef struct {
    char title[MAX_BOOK_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
} Book;

typedef struct Node {
    Book data;
    struct Node* next;
} Node;

Node* createNode(Book book) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = book;
    newNode->next = NULL;
    return newNode;
}

Node* push(Node* top, Book book) {
    Node* newNode = createNode(book);
    newNode->next = top;
    return newNode;
}

Node* pop(Node* top) {
    if (top == NULL) {
        printf("A pilha está vazia.\n");
    } else {
        Node* temp = top;
        top = top->next;
        free(temp);
    }
    return top;
}

void displayBook(Book book) {
    printf("%s; %s\n", book.title, book.author);
}

void displayStack(Node* top) {
    Node* current = top;
    while (current != NULL) {
        displayBook(current->data);
        current = current->next;
    }
}

Node* enqueue(Node* rear, Book book) {
    Node* newNode = createNode(book);
    if (rear == NULL) {
        return newNode;
    } else {
        rear->next = newNode;
        return newNode;
    }
}

Node* dequeue(Node* front) {
    if (front == NULL) {
        printf("A fila está vazia.\n");
    } else {
        Node* temp = front;
        front = front->next;
        free(temp);
    }
    return front;
}

void displayQueue(Node* front) {
    Node* current = front;
    while (current != NULL) {
        displayBook(current->data);
        current = current->next;
    }
}

int main() {
    Node* stackTop = NULL;
    Node* queueFront = NULL;

    char filenameStack[] = "pilha_de_livros.txt";
    char filenameQueue[] = "fila_de_livros.txt";

    FILE* fileStack = fopen(filenameStack, "r");
    if (fileStack == NULL) {
        printf("Erro ao abrir o arquivo da pilha de livros.\n");
        return 1;
    }

    char lineStack[MAX_BOOK_LENGTH + MAX_AUTHOR_LENGTH + 3];
    while (fgets(lineStack, sizeof(lineStack), fileStack) != NULL) {
        Book book;
        sscanf(lineStack, "%[^;];%[^\n]", book.title, book.author);
        stackTop = push(stackTop, book);
    }
    fclose(fileStack);

    FILE* fileQueue = fopen(filenameQueue, "r");
    if (fileQueue == NULL) {
        printf("Erro ao abrir o arquivo da fila de livros.\n");
        return 1;
    }

    char lineQueue[MAX_BOOK_LENGTH + MAX_AUTHOR_LENGTH + 3];
    Node* queueRear = NULL;
    while (fgets(lineQueue, sizeof(lineQueue), fileQueue) != NULL) {
        Book book;
        sscanf(lineQueue, "%[^;];%[^\n]", book.title, book.author);
        queueRear = enqueue(queueRear, book);
        if (queueFront == NULL) {
            queueFront = queueRear;
        }
    }
    fclose(fileQueue);

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Exibir fila de livros\n");
        printf("2. Inserir livro na fila\n");
        printf("3. Inserir livro na pilha\n");
        printf("4. Remover livro da fila\n");
        printf("5. Remover livro da pilha\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayQueue(queueFront);
                break;
            case 2:
                Book newBook;
                printf("Digite o título do livro a ser inserido na fila: ");
                scanf(" %[^\n]s", newBook.title);
                printf("Digite o autor do livro: ");
                scanf(" %[^\n]s", newBook.author);
                queueRear = enqueue(queueRear, newBook);
                if (queueFront == NULL) {
                    queueFront = queueRear;
                }
                FILE* fileQueue = fopen(filenameQueue, "a");
                if (fileQueue == NULL) {
                    printf("Erro ao abrir o arquivo da fila de livros.\n");
                    return 1;
                }
                fprintf(fileQueue, "%s; %s\n", newBook.title, newBook.author);
                fclose(fileQueue);
                break;
            case 3:
                Book newBook;
                printf("Digite o título do livro a ser inserido na pilha: ");
                scanf(" %[^\n]s", newBook.title);
                printf("Digite o autor do livro: ");
                scanf(" %[^\n]s", newBook.author);
                stackTop = push(stackTop, newBook);
                FILE* fileStack = fopen(filenameStack, "a");
                if (fileStack == NULL) {
                    printf("Erro ao abrir o arquivo da pilha de livros.\n");
                    return 1;
                }
                fprintf(fileStack, "%s; %s\n", newBook.title, newBook.author);
                fclose(fileStack);
                break;
            case 4:
                queueFront = dequeue(queueFront);
                FILE* fileQueue = fopen(filenameQueue, "w");
                if (fileQueue == NULL) {
                    printf("Erro ao abrir o arquivo da fila de livros.\n");
                    return 1;
                }
                Node* current = queueFront;
                while (current != NULL) {
                    fprintf(fileQueue, "%s; %s\n", current->data.title, current->data.author);
                    current = current->next;
                }
                fclose(fileQueue);
                break;
            case 5:
                stackTop = pop(stackTop);
                FILE* fileStack = fopen(filenameStack, "w");
                if (fileStack == NULL) {
                    printf("Erro ao abrir o arquivo da pilha de livros.\n");
                    return 1;
                }
                Node* current = stackTop;
                while (current != NULL) {
                    fprintf(fileStack, "%s; %s\n", current->data.title, current->data.author);
                    current = current->next;
                }
                fclose(fileStack);
                break;
            case 6:
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
    return 0;
}
