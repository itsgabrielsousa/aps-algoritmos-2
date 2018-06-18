#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estruturas.h"

// macro para identificar se o programa esta rodando em plataforma Windows ou Unix
#if defined (_WIN32) || defined(_WIN64)
    int isWindows = 1;
	#else
		#ifdef __linux
			int isWindows = 0;
		#endif
#endif

// implementacoes das variaveis globais do programa
int auto_cod_filme = 1;// global, gera codigo filme automaticamente
int auto_cod_bilhete = 1;// global, gera codigo bilhete automaticamente
// variavel global que conta o index em que o vetor bilhetes esta, para que na hora de add um novo bilhete:
// se nunca foi adicionado, entao ele vale 1 | se ja foi adicionado, entao ele vale n
int cont_vBilhetes = 0;// conta o tamanho do vetor bilhetes
int continuar = 0;// continuar se inicia como falso idicando que nao a acao nao sera continuada dentro da funcao

void LimpaTela(){
	if (isWindows == 1){
		//limpa tela no Windows
		system("cls"); 	
	}else if (isWindows == 0){
		//limpa tela em sistemas baseados em Unix
		system("clear"); 
	}
}

// funcao que imprime bilhetes que recebe o vetor de Bilhetes e a posicao atual daquele bilhete
void ImprimirBilhetes(BILHETES *vBilhetes, int pos){
    printf("\nCodigo do bilhete: %d\n", vBilhetes[pos].cod_bilhete);
    printf("Codigo do filme: %d\n\n", vBilhetes[pos].cpcod_filme);
    printf("Nome do cliente: %s\n", vBilhetes[pos].nome_cliente);
    printf("RG do cliente: %s\n\n", vBilhetes[pos].rg);
    printf("Titulo do filme: %s\n", vBilhetes[pos].cptitulo_filme);    
    printf("Poltrona: %d\n", vBilhetes[pos].poltrona);
    printf("Data do filme: %s\n", vBilhetes[pos].cpdata);
    printf("Horario do filme: %s\n\n", vBilhetes[pos].cphorario);
    printf("Preco final: R$ %.2f\n", vBilhetes[pos].preco);
}

// funcao que reserva novos bilhetes no vetor Bilhetes
void Reservar(BILHETES *vBilhetes, int tam_vet, FILMES *head){
    do{
        int i = cont_vBilhetes;
        // [1] imprimir lista de filmes (operacao já feita no menu principal)
        // [2] popular bilhete com dados, entrada: teclado
        vBilhetes[i].cod_bilhete = auto_cod_bilhete;
        auto_cod_bilhete++;
        printf("Informe o codigo do filme: ");
        scanf("%d", &vBilhetes[i].cpcod_filme);
        printf("Informe o nome do cliente: ");
        scanf("%s", vBilhetes[i].nome_cliente);
        printf("Informe o RG do cliente: ");
        scanf("%s", vBilhetes[i].rg);

        // [2.1] popular bilhete com dados, receber a poltrona, entrada: teclado
        printf("\nEscolha uma poltrona: ");
        scanf("%d", &vBilhetes[i].poltrona);

        // [2.2] popular bilhete com copias dos dados do filme, entrada: automatico
        // para ter acesso aos dados do filme escolhido pelo usuario, precisa-se varrer a Lista Filmes
        // entao, armazenar uma copia de cada variavel no Vetor de Bilhetes
        // varrer a Lista Filmes
        while(head != NULL){
            if(vBilhetes[i].cpcod_filme == head->cod_filme){
                break;// se o codigo do filme for encontrado na Lista Filmes, parar a procura
            }
            head = head->prox;
        }
        // agora, head aponta para o nó em que está o filme escolhido, ou seja, tenho acesso ao filme escolhido + suas variaveis
        // fazer uma copia das variaveis de Filmes para aquele bilhete
        strcpy(vBilhetes[i].cptitulo_filme, head->titulo_filme);
        strcpy(vBilhetes[i].cpdata, head->data);
        strcpy(vBilhetes[i].cphorario, head->horario);
        vBilhetes[i].preco = head->valor_filme + 10.0;

        // [3] imprimir o bilhete
        // chamar funcao que imprime bilhetes que recebe o vetor de Bilhetes e a posicao atual daquele bilhete
        ImprimirBilhetes(vBilhetes, i);

        cont_vBilhetes++;// indica o tamanho do vetor, pois toda a vez que se adiciona um bilhete, o vetor aumenta + 1
    
    printf("\nDigite [1] para continuar reservando bilhetes e [0] para voltar ao Menu Principal: ");
    scanf("%d", &continuar);
    printf("\n");
    }while(continuar == 1);
}

void Pesquisar(BILHETES *vBilhetes){
    do{
        // [1] receber o codigo do bilhete que sera pesquisado
        printf("Informe o codigo do bilhete: ");
        int cod_bilhete_x;
        scanf("%d", &cod_bilhete_x);

        // [2] varrer o Vetor de Bilhetes a procura do codigo do bilhete
        int i;
        int aux = 0;
        for(i = 0; i < cont_vBilhetes; i++){
            // se o cod desejado foi encontrado, imprimir o bilhete
            if(vBilhetes[i].cod_bilhete == cod_bilhete_x){
                ImprimirBilhetes(vBilhetes, i);
                aux = 1;
            }
        }
        if(aux != 1) printf("Nenhum bilhete foi encontrado.");
    
    printf("\nDigite [1] para pesquisar novamente e [0] para voltar ao Menu Principal: ");
    scanf("%d", &continuar);
    printf("\n");
    }while(continuar == 1);
}

// funcao que insere novos nos se a lista Filmes esta vazia/nao vazia
void Inserir(FILMES **head){
    do{
        FILMES *temp = (FILMES*)malloc(sizeof(FILMES));

        // popular lista
        temp->cod_filme = auto_cod_filme; 
        auto_cod_filme++;
        printf("Digite o titulo do filme: ");
        scanf("%s", temp->titulo_filme);
        printf("Digite o genero do filme: ");
        scanf("%s", temp->genero);
        printf("Digite o formato do filme: ");
        scanf("%s", temp->formato);
        printf("Digite a data do filme (dd-mm-aaaa): ");
        scanf("%s", temp->data);
        printf("Digite o horario do filme (hh:mm): ");
        scanf("%s", temp->horario);
        printf("Digite o valor do filme: ");
        scanf("%f", &temp->valor_filme);

        // add novo no, se a lista estiver fazia
        if(*head == NULL){
            temp->prox = NULL;
            *head = temp;
        }else{
            // se a lista nao estiver vazia, ir ate o final da lista
            FILMES *tempTrav = *head;
            while(tempTrav->prox != NULL){
                tempTrav = tempTrav->prox;
            }
            // chegando no final, ajustar
            tempTrav->prox = temp;
            temp->prox = NULL;
        }
    
    printf("\nDigite [1] para continuar adicionando filmes e [0] para voltar ao Menu Principal: ");
    scanf("%d", &continuar);
    printf("\n");
    }while(continuar == 1);
}

// funcao que edita lista de Filmes
void Editar(FILMES *head){
    do{
        // receber do usuario o codigo a ser deletado
        printf("Informe o codigo do filme que deseja editar: ");
        int cod_filme;// cod do filme a ser editado
        scanf("%d", &cod_filme);

        // percorrer a lista e encontrar o codigo solicitado
        FILMES *tempTrav = head;
        while((tempTrav->prox != NULL) && (tempTrav->cod_filme != cod_filme)){
            tempTrav = tempTrav->prox;
        }
        // agora tempTrav esta na posicao "final" i.e. posicao logo antes do novo elemento
        // editar o filme desejado
        printf("Digite o titulo do filme: ");
        scanf("%s", tempTrav->titulo_filme);
        printf("Digite o genero do filme: ");
        scanf("%s", tempTrav->genero);
        printf("Digite o formato do filme: ");
        scanf("%s", tempTrav->formato);
        printf("Digite a data do filme (dd-mm-aaaa): ");
        scanf("%s", tempTrav->data);
        printf("Digite o horario do filme (hh:mm): ");
        scanf("%s", tempTrav->horario);
        printf("Digite o valor do filme: ");
        scanf("%f", &tempTrav->valor_filme);
    
    printf("\nDigite [1] para editar mais filmes e [0] para voltar ao Menu Principal: ");
    scanf("%d", &continuar);
    printf("\n");
    }while(continuar == 1);
}

// funcao que apaga um elemento da lista de Filmes
// apaga na posicao n == cod_filme
void Deletar(FILMES **head){
    do{
        // receber do usuario o codigo do gilme a ser apagado
        printf("Informe o codigo do filme que sera apagado: ");
        // o que eh cod para o usuario, eh posicao para o programa
        int n;// == codigo/posicao do filme a ser apagado
        scanf("%d", &n);

        FILMES *temp1 = *head;
        // apagar o no cabecalho
        if(n == 1){
            *head = temp1->prox;// head agora aponta par ao segundo no
            free(temp1);
        }else{
            FILMES *temp2;
            int i;
            for(i = 0; i < n-2; i++){
                temp2 = temp1;
                temp1 = temp1->prox;
            }
            // agora, temp1 aponta para Nó na posicao (n-1)th
            temp2 = temp1->prox;// nth Nó
            temp1->prox = temp2->prox;// (n+1)th Nó
            free(temp2);
        }
    
    printf("\nDigite [1] para apagar mais filmes e [0] para voltar ao Menu Principal: ");
    scanf("%d", &continuar);
    printf("\n");
    }while(continuar == 1);
}

// funcao Iterativa que imprime lista de Filmes
// void Imprimir(FILMES *head){
//     while(head != NULL){
//         printf("Codigo do filme: %d\n", head->cod_filme);
//         head = head->prox;
//     }
// }

// funcao Recursiva que imprime lista de Filmes
void Imprimir(FILMES *head){
    // sair da condicao
    if(head == NULL){
        return;
    }   
    // primeio, imprimir os valores do nó
    printf("Codigo do filme: %d\n", head->cod_filme);
    printf("Titulo do filme: %s\n", head->titulo_filme);
    printf("Genero do filme: %s\n", head->genero);
    printf("Formato do filme: %s\n", head->formato);
    printf("Data do filme: %s\n", head->data);
    printf("Horario do filme: %s\n", head->horario);
    printf("Valor do filme: R$ %.2f\n\n", head->valor_filme);
    // chamada recursiva 
    Imprimir(head->prox);
}