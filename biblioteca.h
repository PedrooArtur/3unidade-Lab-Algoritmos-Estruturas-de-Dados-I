#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LOGIN 50
#define MAX_EMAIL 100

typedef struct Livro {
    char nome[100];
    char autor[100];
} Livro;

typedef struct Usuario {
    char login[MAX_LOGIN];
    char senha[MAX_LOGIN];
    char email[MAX_EMAIL];
} Usuario;

typedef struct NoLivro {
    Livro livro;
    struct NoLivro* prox;
} NoLivro;

typedef struct NoUsuario {
    Usuario usuario;
    struct NoUsuario* prox;
} NoUsuario;

extern NoUsuario* listaUsuarios;
extern NoLivro* listaLivros;
extern NoUsuario* usuarioLogado;

// Arquivos
void carregarUsuarios();
void salvarUsuarios();
void carregarLivros();
void salvarLivros();

// Menus
void menuLogin();
void menuUsuario();

// Usuários
void realizarLogin();
void cadastrarNovoUsuario();
void encerrarSessao();

// Livros
void cadastrarLivro();
void excluirLivro();
void editarLivro();
void buscarLivro();
void listarLivros();
void emitirComprovante();

// Ordenação e busca
void ordenarLivros();
int buscaBinariaLivro(const char* nome, int inicio, int fim);

#endif
