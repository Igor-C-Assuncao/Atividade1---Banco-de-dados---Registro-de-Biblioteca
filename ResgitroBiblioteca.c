#include <stdio.h>
#include <stdlib.h>


typedef struct{ int isbn;
    char titulo[50];
    int ano;
} TLivro;

FILE *plivro;

TLivro livro_aux, livro_nulo;

void linha(){
	int i;
    
	for (i=1; i<=80; i++)
    {
		printf("_");
    }
    printf("\n");

}
void cabec() { 
	system("cls");
	printf("Biblioteca Unicap\n");
    linha();
}
void abre_arquivo(){ 
    plivro = fopen("livro.dat", "r+b");
	if (plivro == NULL)
		plivro = fopen("livro.dat", "w+b");
}
void inserir(){ 
    int resp;
    do { 
        cabec();
        printf("\n\nCadastrar novo livro\n\n");
        printf("\nISBN: ");
        scanf("%d", &livro_aux.isbn);
        printf("\nTitulo: ");
        fflush(stdin);
        gets(livro_aux.titulo);
       // scanf("%s",livro_aux.titulo);
        printf("\nAno....: ");
        scanf("%d", &livro_aux.ano);
        fseek(plivro, 0, SEEK_END);
        fwrite(&livro_aux, sizeof(TLivro), 1, plivro);
        printf("\n\nlivro cadastrado com sucesso!\n\n");
        printf("\nDeseja cadastrar outro Livro: (1-sim/0-nao)? ");
        scanf("%d", &resp);
    } while (resp ==1);
}
int procura(int isbnp)
{ int p;
    p = 0;
    rewind(plivro);
    fread(&livro_aux, sizeof(TLivro), 1, plivro);
    while (feof(plivro)==0)
    { if (livro_aux.isbn == isbnp)
        return p;
    else
    { fread(&livro_aux, sizeof(TLivro), 1,
            plivro);
        p++;
    }
    }
    return -1;
}
void mostre(int pos)
{ fseek(plivro, pos*sizeof(TLivro), SEEK_SET);
    fread(&livro_aux, sizeof(TLivro), 1, plivro);
    printf("\n\n");
    linha();
    printf("ISBN titulo ano\n");
    linha();
    printf("%9d | %-20s |  %d\n", livro_aux.isbn,
           livro_aux.titulo, livro_aux.ano);
    linha();
}

void consultar(){ 
    int resp, isbncon, posicao;
    do{ cabec();
        printf("\n\nConsultar livro\n\n\n");
        printf("ISBN do livro: ");
        scanf("%d", &isbncon);
        posicao = procura(isbncon);
        if (posicao == -1)
            printf("\n\nISBN nao encontrada!\n\n");
        else
            mostre(posicao);
        printf("\n\nDeseja consultar outro (1-sim/0-nao)?");
        scanf("%d", &resp);
    } while (resp == 1);
}

void remover(){ 
    int isbnrem, conf, resp, posicao;
    livro_nulo.isbn = 0;
    livro_nulo.ano = 0;
    do{ cabec();
        printf("\n\nRemover livro\n\n\n");
        printf("ISBN: ");
        scanf("%d", &isbnrem);
        posicao = procura(isbnrem);
        if (posicao == -1)
            printf("\nlivro nao encontrado!!\a");
        else { mostre(posicao);
            printf("\n\nDeseja remover o livro(1-sim/0-nao)? ");
            scanf("%d", &conf);
            if (conf == 1){ fseek(plivro,posicao*sizeof
                                  (TLivro),SEEK_SET);
                fwrite( &livro_nulo,
                             sizeof(TLivro), 1, plivro);
                printf("\n\nlivro removido com sucesso!");
            }
            else
                printf("\nRemocao cancelada!");
        }
        printf("\n\n\nDeseja remover outro(1-sim/0-nao)? ");
        scanf("%d", &resp);
    } while (resp ==1);
}
void alterar()
{ int isbnalt, conf, resp, posicao;
    do { cabec();
        printf("\n\nAlterar ano do livro\n\
               n\n");
        printf("ISBN: ");
        scanf("%d", &isbnalt);
        posicao = procura(isbnalt);
        if (posicao == -1)
            printf("\nlivro,nao encontrado!!\a");
        else
        { mostre(posicao);
            printf("\n\nAlterar a ano do livro(1-sim/0-nao)? ");
            scanf("%d", &conf);
            if (conf == 1)
            { printf("\nNovo ano: ");
                scanf("%d", &livro_aux.ano);
                printf("\nAno alterado com sucesso! \n\n");
                fseek(plivro,posicao*sizeof(TLivro),
                      SEEK_SET);
                fwrite(&livro_aux,sizeof(TLivro), 1,
                       plivro);
                mostre(posicao);
                printf("\nAno do livro alterado com sucesso!\n");
            }
            else
            printf("\n\nAlteracao cancelada!\n\n");
        }
        printf("\n\nDeseja alterar outro (1-sim/0-nao)? ");
        scanf("%d", &resp);
    }while (resp ==1);
}
void listagem(){ 
    int resp = 0;
    do
        {
        cabec();
        printf("\n\nListagem Geral\n\n\n");
        linha();
        printf("ISBN    |        titulo        |   ano\n");
        linha();
        rewind(plivro);
        fread(&livro_aux, sizeof(TLivro), 1, plivro);
        while (feof(plivro)==0){ 
            if (livro_aux.isbn != 0)
                printf("%9d | %-20s |  %d\n", livro_aux.
                    isbn,
                    livro_aux.titulo, livro_aux.ano);
            fread(&livro_aux, sizeof(TLivro), 1, plivro);
        }
        linha();
        printf("tecle 1 para voltar ao menu...");
        scanf("%d", &resp);
    } while (resp == 0);
    
    
    //getche();
}
int main(){ 
    int op;
    abre_arquivo();
    do{ 
        cabec();
        printf("\n\nOpcoes: \n\n\n");
        printf(" 1- Cadastrar novo livro\n\n");
        printf(" 2- Remover livro\n\n");
        printf(" 3- Consultar livro por ISBN\n\n");
        printf(" 4- Alterar ano do livro\n\n");
        printf(" 5- Listagem geral\n\n");
        printf(" 0- Sair\n\n");
        linha();
        printf("Informe a opcao desejada: ");
        scanf("%d", &op);
        switch(op){ 
            case 1: inserir(); break;
            case 2: remover(); break;
            case 3: consultar(); break;
            case 4: alterar(); break;
            case 5: listagem(); break;
            case 0: fclose(plivro); break;
            default: printf("\n\n\aOpcao invalida!");
                break;
        }
    } while (op != 0);
}
