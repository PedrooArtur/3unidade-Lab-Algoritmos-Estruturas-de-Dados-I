#include "biblioteca.h"

NoUsuario* listaUsuarios = NULL;
NoLivro* listaLivros = NULL;
NoUsuario* usuarioLogado = NULL;

// =================== ARQUIVOS ===================

void salvarUsuarios() {
    FILE* f = fopen("usuarios.txt", "w");
    NoUsuario* atual = listaUsuarios;
    while (atual) {
        fprintf(f, "%s %s %s\n", atual->usuario.login, atual->usuario.senha, atual->usuario.email);
        atual = atual->prox;
    }
    fclose(f);
}

void carregarUsuarios() {
    FILE* f = fopen("usuarios.txt", "r");
    if (!f) return;
    Usuario u;
    while (fscanf(f, "%s %s %s", u.login, u.senha, u.email) != EOF) {
        NoUsuario* novo = malloc(sizeof(NoUsuario));
        novo->usuario = u;
        novo->prox = listaUsuarios;
        listaUsuarios = novo;
    }
    fclose(f);
}

void salvarLivros() {
    FILE* f = fopen("livros.txt", "w");
    NoLivro* atual = listaLivros;
    while (atual) {
        fprintf(f, "%s|%s\n", atual->livro.nome, atual->livro.autor);
        atual = atual->prox;
    }
    fclose(f);
}

void carregarLivros() {
    FILE* f = fopen("livros.txt", "r");
    if (!f) return;
    char linha[200];
    while (fgets(linha, sizeof(linha), f)) {
        Livro l;
        char* sep = strchr(linha, '|');
        if (sep) {
            *sep = '\0';
            strcpy(l.nome, linha);
            strcpy(l.autor, sep + 1);
            l.autor[strcspn(l.autor, "\n")] = '\0';
            NoLivro* novo = malloc(sizeof(NoLivro));
            novo->livro = l;
            novo->prox = listaLivros;
            listaLivros = novo;
        }
    }
    fclose(f);
}

// =================== MENUS ===================

void menuLogin() {
    printf("\n1 - Login\n2 - Cadastrar Usuario\n0 - Sair\n");
}

void menuUsuario() {
    printf("\nBem-vindo à Biblioteca Virtual!\n");
    printf("1 - Cadastrar livro\n2 - Excluir livro\n3 - Emitir comprovante\n");
    printf("4 - Editar livro\n5 - Buscar livro\n6 - Listar livros\n");
    printf("7 - Encerrar sessao\n0 - Sair\n");
}

// =================== USUÁRIOS ===================

void realizarLogin() {
    char login[50], senha[50];
    printf("Login: "); scanf("%s", login);
    printf("Senha: "); scanf("%s", senha);
    NoUsuario* atual = listaUsuarios;
    while (atual) {
        if (strcmp(atual->usuario.login, login) == 0 && strcmp(atual->usuario.senha, senha) == 0) {
            usuarioLogado = atual;
            printf("Login com sucesso!\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Login falhou.\n");
}

void cadastrarNovoUsuario() {
    Usuario u;
    printf("Novo login: "); scanf("%s", u.login);
    printf("Senha: "); scanf("%s", u.senha);
    printf("Email: "); scanf("%s", u.email);
    if (strchr(u.email, '@') == NULL || strlen(u.email) >= 80) {
        printf("Email inválido.\n"); return;
    }
    NoUsuario* atual = listaUsuarios;
    while (atual) {
        if (strcmp(atual->usuario.email, u.email) == 0 || strcmp(atual->usuario.login, u.login) == 0) {
            printf("Email ou login já cadastrado.\n"); return;
        }
        atual = atual->prox;
    }
    NoUsuario* novo = malloc(sizeof(NoUsuario));
    novo->usuario = u;
    novo->prox = listaUsuarios;
    listaUsuarios = novo;
    salvarUsuarios();
    printf("Usuário cadastrado!\n");
}

void encerrarSessao() {
    usuarioLogado = NULL;
    printf("Sessão encerrada.\n");
}

// =================== LIVROS ===================

void cadastrarLivro() {
    Livro l;
    getchar();
    printf("Nome do livro: "); fgets(l.nome, sizeof(l.nome), stdin);
    l.nome[strcspn(l.nome, "\n")] = '\0';
    printf("Autor: "); fgets(l.autor, sizeof(l.autor), stdin);
    l.autor[strcspn(l.autor, "\n")] = '\0';
    NoLivro* novo = malloc(sizeof(NoLivro));
    novo->livro = l;
    novo->prox = listaLivros;
    listaLivros = novo;
    salvarLivros();
    printf("Livro cadastrado!\n");
}

void listarLivros() {
    if (!listaLivros) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    NoLivro* atual = listaLivros;
    int i = 1;
    while (atual) {
        printf("Livro %d: %s - Autor: %s\n", i++, atual->livro.nome, atual->livro.autor);
        atual = atual->prox;
    }
}

void excluirLivro() {
    char nome[100];
    getchar();
    printf("Informe o nome do livro a excluir: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    NoLivro *atual = listaLivros, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->livro.nome, nome) == 0) {
            if (anterior == NULL) {
                listaLivros = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Livro excluído com sucesso!\n");
            salvarLivros();
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Livro não encontrado.\n");
}

void editarLivro() {
    char nome[100];
    getchar();
    printf("Informe o nome do livro a editar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    NoLivro* atual = listaLivros;
    while (atual != NULL) {
        if (strcmp(atual->livro.nome, nome) == 0) {
            printf("Novo nome: ");
            fgets(atual->livro.nome, sizeof(atual->livro.nome), stdin);
            atual->livro.nome[strcspn(atual->livro.nome, "\n")] = '\0';

            printf("Novo autor: ");
            fgets(atual->livro.autor, sizeof(atual->livro.autor), stdin);
            atual->livro.autor[strcspn(atual->livro.autor, "\n")] = '\0';

            printf("Livro editado com sucesso!\n");
            salvarLivros();
            return;
        }
        atual = atual->prox;
    }
    printf("Livro não encontrado.\n");
}

void emitirComprovante() {
    if (listaLivros == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    printf("Comprovante de livros cadastrados:\n");
    NoLivro* atual = listaLivros;
    int i = 1;
    while (atual != NULL) {
        printf("%d. Livro: %s | Autor: %s\n", i++, atual->livro.nome, atual->livro.autor);
        atual = atual->prox;
    }
}

// =================== ORDENAR + BUSCA ===================

int compararLivros(const void* a, const void* b) {
    Livro* l1 = *(Livro**)a;
    Livro* l2 = *(Livro**)b;
    return strcmp(l1->nome, l2->nome);
}

void ordenarLivros() {
    int n = 0;
    NoLivro* atual = listaLivros;
    while (atual) {
        n++;
        atual = atual->prox;
    }

    Livro** array = malloc(n * sizeof(Livro*));
    atual = listaLivros;
    for (int i = 0; i < n; i++) {
        array[i] = &atual->livro;
        atual = atual->prox;
    }

    qsort(array, n, sizeof(Livro*), compararLivros);

    atual = listaLivros;
    for (int i = 0; i < n; i++) {
        atual->livro = *array[i];
        atual = atual->prox;
    }

    free(array);
}

int buscaBinariaLivro(const char* nome, int inicio, int fim) {
    int n = 0;
    NoLivro* atual = listaLivros;
    while (atual) {
        n++;
        atual = atual->prox;
    }

    Livro** array = malloc(n * sizeof(Livro*));
    atual = listaLivros;
    for (int i = 0; i < n; i++) {
        array[i] = &atual->livro;
        atual = atual->prox;
    }

    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int cmp = strcmp(nome, array[meio]->nome);
        if (cmp == 0) {
            free(array);
            return meio;
        } else if (cmp < 0) {
            dir = meio - 1;
        } else {
            esq = meio + 1;
        }
    }

    free(array);
    return -1;
}

void buscarLivro() {
    ordenarLivros();
    char nome[100];
    getchar();
    printf("Informe o nome do livro: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = buscaBinariaLivro(nome, 0, -1);
    if (pos >= 0) {
        printf("Livro encontrado!\n");
    } else {
        printf("Livro não encontrado.\n");
    }
}


int main() {
    carregarUsuarios();
    carregarLivros();
    int opcao;

    while (1) {
        do {
            menuLogin();
            scanf("%d", &opcao);
            switch (opcao) {
                case 1: realizarLogin(); break;
                case 2: cadastrarNovoUsuario(); break;
                case 0: return 0;
                default: printf("Opção inválida.\n");
            }
        } while (!usuarioLogado);

        do {
            menuUsuario();
            scanf("%d", &opcao);
            switch (opcao) {
                case 1: cadastrarLivro(); break;
                case 2: excluirLivro(); break;
                case 3: emitirComprovante(); break;
                case 4: editarLivro(); break;
                case 5: buscarLivro(); break;
                case 6: listarLivros(); break;
                case 7: encerrarSessao(); break;
                case 0: return 0;
                default: printf("Opção inválida.\n");
            }
        } while (usuarioLogado);
    }
}
