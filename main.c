#include "biblioteca.h"

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