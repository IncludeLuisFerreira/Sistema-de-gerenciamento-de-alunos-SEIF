/*  BIBLIOTECA PADRÃO DO SEIF
        O S.E.I.F(Sistema de Ensino Instituto Federal) é uma tentativa de um primeiro software com objetivo de gerenciamento de uma sala
        de aula. O programa tem funções insersão, remoção, busca, editar alunos. O tamanho da sala de aula pode ser modificado no inicio 
        do programa.
*/

#ifndef SEIF_H
#define SEIF_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define NAME 100
#define MAX_SALA 30
#define ARQ_ERROR  "\nNao foi possivel abrir o arquivo!\n"
#define WRITE_ERROR "\nErro na escrita no arquivo!\n"
#define DATA_ERROR "\nNenhum dado encontrado\n"
#define DATA_NFOUND "\nAluno nao encontrado\n"
#define NO_OPTION "\nOpcao invalida!\n"
#define arq "arq.dat"

typedef struct _data {
    int dia, mes, ano;
}Data;

typedef struct _materia {
    char professor[NAME];
    float nota;
    int frequencia;
}Materia;

typedef struct _aluno {
    char id[4];
    char nome[NAME];
    int idade;
    float media;
    Data nasc;
    Materia matematica;
    Materia portugues;
    Materia ingles;
    Materia ciencia;
}Aluno;

Aluno sala[MAX_SALA];

//Protótipos de todos os procedimentos usados pelo sistema.
void init_list(void);
int backUp(int modo);
void menu(Aluno aluno);
//void completeData(Aluno *aluno, FILE *arch);
void exam(Aluno *aluno);
void edit_dadosPessoais(Aluno *aluno);
void edit(Aluno *aluno);
void enter(void);
void display(void);
void save(void);
void id_Search(void);
void name_Search(void);
void removeAluno(void);

//Inicia o vetor sala com nome nulo
void init_list(void) {
    register int t;
    for(t = 0; t < MAX_SALA; t++) {
        *sala[t].nome = '\0';
    }
}

int backUp(int modo) {
    FILE *arch;
    Aluno aux;
    register int i = 0;
    
    if((arch = fopen(arq, "rb")) == NULL) {
        if(modo == 1)
            printf(DATA_ERROR);
        return 0;
    }
    
    while(!feof(arch)) {
        if(fread(&aux, sizeof(Aluno), 1, arch) != 0) {
            sala[i] = aux;
            i++;
        }
    }

    if(modo == 2){
        if(i > 1)
            printf("%d alunos cadastrados!\n", i);
        else
            printf("%d aluno cadastrado!\n", i);
    } else {
        return 0;
    }
    return i;
}

//Função para editar e lançar notas
void menu(Aluno aluno) {
    FILE *arch;
    int op;
    printf("\n");
    do {
        printf("\n------Menu de gerenciamento de aluno------\n");
        printf("\n1-Excluir aluno\n2-Editar dados pessoais\n0-Sair\n:");
        scanf("%d", &op);
        
        switch (op)
        {
        case 1:   
            for(int i = 0; i < MAX_SALA; i++) {
                if((strcmp(aluno.nome, sala[i].nome)) == 0) {
                    *sala[i].nome = '\0';
                    printf("Dado excluido com sucesso!\n");
                }
            }
            op = 0;
            break;
        case 2:
            for(int i = 0; i < MAX_SALA; i++) {
                if((strcmp(aluno.nome, sala[i].nome)) == 0) {
                    edit_dadosPessoais(&sala[i]);
                    break;
                }
            }
            save();
            break;
        default:
            if(op != 0)
                printf(NO_OPTION);  
            break;
        }
        
    }while(op != 0);
    save();
    backUp(0);
}

void exam(Aluno *aux) {
    FILE *arch;
    Aluno aluno;
    
    if((arch = fopen(arq, "rb+")) == NULL) {
        printf(ARQ_ERROR);
        return;
    }

    while(!feof(arch)){
        if(fread(&aluno, sizeof(Aluno), 1, arch) != 0 && strcmp(aluno.nome, aux->nome) == 0){
            printf("Nome: %s", aluno.nome);
            printf("Idade: %d", aluno.idade);
            break;
        }
    }
    aluno.idade = 90;
    fwrite(&aluno, sizeof(Aluno), 1, arch);
    fclose(arch);
}

void edit_dadosPessoais(Aluno *aux) {
    int op;

    do {
        printf("\n1-Editar nome\n2-Editar idade\n3-Editar a data de nascimento\n0-Para voltar\n:");
        scanf("%d", &op);
        getchar();
        
        switch (op)
        {
        case 1:

            printf("Nome atual: %s\n", aux->nome);
            printf("Digite o nome editado: ");
            gets(aux->nome);
            break;
        case 2:
            printf("Idade atual: %d\n", aux->idade);
            printf("Digite a idade editada: ");
            scanf("%d", &aux->idade);
            break;
        case 3:
            printf("Data de nascimento atual: %02d/%02d/%4d\n", aux->nasc.dia, aux->nasc.mes, aux->nasc.ano);
            printf("Digite a data de nascimento editada: ");
            scanf("%d %d %d", &aux->nasc.dia, &aux->nasc.mes, &aux->nasc.ano);
            break;
        default:
            if(op != 0)
                printf(NO_OPTION);
            break;
        }
        
    }while(op != 0);
    save();
}

void edit(Aluno *aux) {
    char c;
    do {
        printf("Selecione o que deseja editar\n");
        printf("----------------------------------");
        printf("1-Dados pessoais(nome, idade, data de nascimento)\n2-Avaliação semestral(frequência e notas finais)\n0-Para voltar:");
        scanf("%c", &c);
        
        switch (c)
        {
        case 1:
            edit_dadosPessoais(aux);
            break;
        case 2:
            exam(aux);
            break;
        default:
            if(c != 0) 
                printf(NO_OPTION);
            break;
        }

    }while(c != 0);
}


void enter(void) {
    register int i;

    for(i = backUp(0); i < MAX_SALA; i++) {
        if(!*sala[i].nome) break;
    }

    if(i == MAX_SALA) {
        printf("Sala cheia!\n");
        return;
    }
    
    fflush(stdin);
    printf("Nome: ");
    gets(sala[i].nome);
    printf("Idade: ");
    scanf("%d", &sala[i].idade);
    printf("Data de nascimento(digite no modelo 10 03 2000): ");
    scanf("%d %d %d", &sala[i].nasc.dia, &sala[i].nasc.mes, &sala[i].nasc.ano);
    save();
}

void display(void) {
    FILE *arch;
    Aluno aux;
    int cont = 0;

    if((arch = fopen(arq,"r")) == NULL) {
        printf(ARQ_ERROR);
        return;
    } 
    
    system("cls");
    printf("\tLISTA DE ALUNOS\n\n");
    while(!feof(arch)) {
        if((fread(&aux, sizeof(Aluno), 1, arch) != 0 && aux.nome)) {
            printf("Nome: %s\n", aux.nome);
            printf("Idade: %d\n", aux.idade);
            printf("Data de nascimento: %02d/%02d/%04d\n", aux.nasc.dia, aux.nasc.mes, aux.nasc.ano);
            printf("Media: %2.2f", aux.media);
            printf("\n\n");
            cont++;
        }
    }

    if(cont == 0) {
        printf("Sala vazia!\n");
        fclose(arch);
        return;
    }
    fclose(arch);
    Sleep(250);
}

void save(void) {
    FILE *arch;
    register int i;
    
    if((arch = fopen(arq, "wb")) == NULL) {
        printf(ARQ_ERROR);
        return;
    }
    
    for(i = 0; i < MAX_SALA; i++) {
        if(*sala[i].nome) {
            if(fwrite(&sala[i], sizeof(Aluno), 1, arch) != 1) {
                printf(WRITE_ERROR);
            }
        }
    }
    fclose(arch);
}

void id_Search(void) {
    FILE *arch;
    Aluno aux;
    register int i;
    char id[4];
    int cont = 0;

    if((arch = fopen(arq, "rb+")) == NULL) {
        printf(ARQ_ERROR);
        return;
    } else {
        while(!feof(arch)) {
            if((fread(&aux, sizeof(Aluno), 1, arch)) != 0) {
                cont++;
            }
        }
    }

    fclose(arch);
    if(cont == 0) {
        printf(DATA_ERROR);
        return;
    }

    fflush(stdin);
    printf("Digite o id do aluno: ");
    gets(id);

    cont = 0;
    for(i = 0; i < MAX_SALA; i++) {
        if(strcmp(id, sala[i].id) == 0) {
            printf("Nome: %s\n", sala[i].nome);
            printf("Idade: %d\n", sala[i].idade);
            printf("Data de nascimento: %02d/%02d/%04d\n", sala[i].nasc.dia, sala[i].nasc.mes, sala[i].nasc.ano);
            cont++;
        }
    }
     
    if(cont == 0) {
        printf(DATA_NFOUND);
        return;
    } 
}

void name_Search(void) {
    FILE *arch;
    Aluno aux;
    int cont = 0;
    char name[100];

    if((arch = fopen(arq, "rb")) == NULL) {
        printf(ARQ_ERROR);
        return;
    } else {
        while(!feof(arch)) {
            if((fread(&aux, sizeof(Aluno), 1, arch)) != 0) {
                cont++;
            }
        }
    }
    
    if(cont == 0) {
        printf(DATA_ERROR);
        fclose(arch);
        return;
    }

    fflush(stdin);
    printf("Digite o nome do aluno: ");
    gets(name);
    
    cont = 0;
    rewind(arch);
    while(!feof(arch)) {
        if((fread(&aux, sizeof(Aluno), 1, arch) != 0)) {
            if(strcmp(name, aux.nome) == 0) {
                printf("\nNome: %s\n", aux.nome);
                printf("Idade: %d\n", aux.idade);
                printf("Data de nascimento: %02d/%02d/%04d\n", aux.nasc.dia, aux.nasc.mes, aux.nasc.ano);
                cont++;
                break;
            }
        }
    }

    if(cont == 0) {
        printf(DATA_ERROR);
        fclose(arch);
        return;
    }

    menu(aux);
    return;
}

void removeAluno(void) {
    FILE *arch;
    Aluno aux;
    register int i;
    int op, cont = 0;
    char name[100], c, id[4];
    
    if((arch = fopen(arq, "rb+")) == NULL) {
        printf(ARQ_ERROR);
        return;
    }

    while(!feof(arch)){
        if(fread(&aux, sizeof(Aluno), 1, arch)) {
            cont++;
        }
    }

    if(cont == 0) {
        printf(DATA_ERROR);
        return;
    }
    
    op = 2;
    switch (op)
    {
    case 1:
        fflush(stdin);
        printf("Digite o id: ");
        gets(id);

        cont = 0;
        for(i = 0; i < MAX_SALA; i++) {
            if((strcmp(id, sala[i].id) == 0))
                break;
            cont++;
        }
        
        if(cont != 0){
            printf("Nome: %s\nIdade: %d", sala[i].nome, sala[i].idade);
            printf("Deseja continuar a exclusao deste dado?(S ou N): ");
            scanf("%c", &c);
            
            if(toupper(c) == 'S') {
                *sala[i].nome = '\0';
                printf("Acao concluida com sucesso!\n");
            } else {
                printf("Acao cancelada!\n");
            }
        } else {
            printf(DATA_ERROR);
        }
        break;
    case 2:
        fflush(stdin);
        printf("Digite o nome: ");
        gets(name);
        
        rewind(arch);
        for(i = 0; i < MAX_SALA; i++) {
            if((strcmp(name, sala[i].nome)) == 0){
                cont++;
                break;
            }
        }

        if(cont != 0){
            printf("Nome: %s\tIdade: %d\n", sala[i].nome, sala[i].idade);
            printf("Deseja continuar a exclusao deste dado?(S ou n): ");
            scanf("%c", &c);

            if(toupper(c) == 'S') {
                *sala[i].nome = '\0';
                printf("Acao concluida com sucesso!\n");
            } else {
                printf("Acao cancelada!\n");
            }
        } else {
            printf(DATA_ERROR);
        }
        break;
    default:
        break;
    }
    save();
}


#endif