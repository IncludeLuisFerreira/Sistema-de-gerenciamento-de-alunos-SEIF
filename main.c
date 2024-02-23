#include <stdio.h>
#include "seif.h"

int main() {
    int user, op;
    
    printf("Bem vindo ao Seif\n");
    printf("Sistema Educacional Instituto Federal\n");
    do {
        printf("----------------------------------------\n");
        backUp(2);
        fflush(stdin);
        printf("\nSelecione a opcao que deseja:\n1-Imprimir sala\n2-Inserir aluno\n3-Remover aluno\n4-Buscar aluno por nome\n5-Editar dados de aluno\n0-Sair\n: ");
        scanf("%d", &user);

        switch (user)
        {
        case 1:
            display();
            break;
        case 2:
            enter();
            break;
        case 3:
            removeAluno();
            break;
        case 4:
            name_Search();
            break;
        case 5:
            name_Search();
            break;
        default:
            if(user != 0)
                printf(NO_OPTION);
            break;
        }
    }while(user != 0);
}