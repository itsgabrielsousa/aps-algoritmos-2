#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* STRUCT para Filmes */
typedef struct FILMES
{
	int cod_filme; //codigo do filme
	char nome_filme[50]; //nome do filme
	char gen_filme[20]; //genero do filme
	char form_filme[10]; //formato do filme, e.g. 2D, 3D
	char data_filme[10]; //data do filme, e.g. dd-mm-aaaa
	int hora_filme; //horario do filme
	float valor_bilhete; //valor do bilhete
} FILMES;

/* STRUCT para Bilhetes */
typedef struct BILHETES
{
	//add um codigo so para controle dos bilhetes?
	int cod_bil_filme; //codigo do filme
	char nome_cliente[50]; //nome do cliente
	int tel_cliente; //telefone do cliente
	int poltrona; //alterar? poltrona 11, 12..
	float valor_bil_bilhete; //valor do bilhete
} BILHETES;

void limpaTela();
void reservarBilhete(FILMES *, BILHETES *, int *, int *, int *);
void buscarBilhete(FILMES *, BILHETES *, int *, int *, int *);
void addFilme(FILMES *, int *);
void mostrarListaFilmes(FILMES *, int *);

int main(){
	/* CRIANDO VETOR DINAMICO "LISTA DE FILMES" */
	int qtd_filmes = 5;       //de inicio tera espaco para 5 filmes, mas esse numero pode aumentar
	FILMES *lista_filmes;     //criar vetor dinamico do tipo FILMES que vai armazenar a lista de filmes
	lista_filmes = malloc(qtd_filmes * sizeof(FILMES));
	
	if(lista_filmes != NULL){ // verificar se a alocacao foi bem sucedida
		//nao fazer nada, continuar com o programa
	}else{
		printf("Erro ao alocar memoria, saindo do programa...\n");
		return 0; //sair do programa
	}

	/* CRIANDO VETOR DINAMICO "VETOR DE BILHETES" */
	int qtd_bilhetes = 10;
	BILHETES *vetor_bilhetes;
	vetor_bilhetes = malloc(qtd_bilhetes * sizeof(BILHETES));
	if(vetor_bilhetes != NULL){ //verificar se a alocacao foi bem sucedida
		//nao fazer nada, continuar com o programa
	}else{
		printf("Erro ao alocar memoria, saindo do programa...\n");
		return 0; //sair do programa
	}

	// os ponteiros abaixo servem para contar em que posicao do vetor eu estou quando add um novo filme, assim, na primeira vez que add um novo filme ele valera 0, depois 1, depois 2, etc, assim eu sei a partir de que posicao do vetor eu irei add um novo filme */
	int cont_parou_addFilme = 0; 
	int cont_parou_reservarBilhete = 0;

	int op;   //variavel para o menu
	int resp; //variavel para repetir o menu

	do{
		limpaTela();
		printf("MENU PRINCIPAL --------------\n\n");
		printf("1) Reservar bilhete\n");
		printf("2) Pesquisar bilhete\n");
		printf("3) Verificar poltronas\n");
		printf("4) Adicionar novo filme\n");
		printf("5) Editar filme\n");
		printf("6) Deletar filme\n");
		printf("7) Mostrar lista de filmes\n\n");

		printf("Escolha uma das opcoes acima: ");
		scanf("%d", &op);

		switch(op){
			case 1: //Reservar bilhete
				limpaTela();
				reservarBilhete(lista_filmes, vetor_bilhetes, &cont_parou_addFilme, &cont_parou_reservarBilhete, &qtd_bilhetes);
			break;

			case 2: //Pesquisar bilhete
				limpaTela();
				buscarBilhete(lista_filmes, vetor_bilhetes, &cont_parou_addFilme, &cont_parou_reservarBilhete, &qtd_bilhetes);
			break;

			case 3: //Verificar poltronas
				printf("Opcao 3\n");
			break;

			case 4: //Adicionar novo filme
				limpaTela();
				addFilme(lista_filmes, &cont_parou_addFilme); //respectivamente: nome do vetor, contador
			break;

			case 5: //Editar filme
				printf("Opcao 5\n");
			break;

			case 6: //Deletar filme
				printf("Opcao 6\n");
			break;

			case 7: //Mostrar lista de filmes
				limpaTela();
				mostrarListaFilmes(lista_filmes, &cont_parou_addFilme);
			break;

			default:
				printf("Opcao invalida.\n");
		}

	printf("\n--------------------");
	printf("\nDigite 0 para voltar ao Menu Principal e 1 para sair: ");
	scanf("%d", &resp);

	}while(resp == 0);

	/* Desacolar blocos de memoria */
	free(lista_filmes);
	return 0;
}

void limpaTela(){
	system("clear"); //limpa tela no Linux
	//system("cls"); //limpa tela no Windows
}

void reservarBilhete(FILMES *lista_filmes, BILHETES *vetor_bilhetes, int *p_cont_parou_addFilme, int *p_cont_parou_reservarBilhete, int *qtd_bilhetes){
	// 1) imprimir lista basica dos filmes
	printf("# Lista basica de filmes cadastrados\n\n");
	int ate_onde = *p_cont_parou_addFilme;
	int i; //contador comum
	for (i = 0; i < ate_onde; i++){
		printf("Codigo do filme: %d \n", lista_filmes[i].cod_filme);
		printf("Nome do filme: %s \n", lista_filmes[i].nome_filme);
		printf("Formato: %s \n", lista_filmes[i].form_filme);
		printf("Data do filme: %s \n", lista_filmes[i].data_filme);
		printf("Horario do filme: %d \n", lista_filmes[i].hora_filme);
		printf("Valor do bilhete: %.2f \n\n", lista_filmes[i].valor_bilhete);
	}

	// 2) entrar com os dados do bilhete
	int j = *p_cont_parou_reservarBilhete;

	printf("# Reservar um novo bilhete\n\n");

	printf("Entre com o codigo do filme escolhido: ");
	scanf("%d", &vetor_bilhetes[j].cod_bil_filme);
	printf("Entre com o nome do cliente: ");
	scanf("%s", vetor_bilhetes[j].nome_cliente);
	printf("Entre com o telefone do cliente: ");
	scanf("%d", &vetor_bilhetes[j].tel_cliente);

	// 3) mostrar poltronas disponiveis
	printf("\n# Escolher poltrona\n\n");
	printf("Escolha uma poltrona: ");
	scanf("%d", &vetor_bilhetes[j].poltrona);

	// 4) imprimir bilhete
	printf("\n# Imprimindo bilhete\n\n");
	printf("Codigo do filme: %d \n", vetor_bilhetes[j].cod_bil_filme);
	printf("Poltrona: %d \n", vetor_bilhetes[j].poltrona);

	// pesquisando pelo nome, pelo formato e valor do bilhete usando o codigo fornecido
	int k;
    for (k = 0; k < (*qtd_bilhetes); k++){ //varrendo o vetor lista_filmes a procura dos dados
		if (vetor_bilhetes[j].cod_bil_filme == lista_filmes[k].cod_filme){
			printf("Nome do filme: %s \n", lista_filmes[k].nome_filme);
			printf("Formato: %s \n", lista_filmes[k].form_filme);
			printf("Valor do bilhete: %.2f \n", lista_filmes[k].valor_bilhete);
		}
    }

	/* depois de reservar um novo bilhete, incrementar +1 ao contador */
	*p_cont_parou_reservarBilhete = *p_cont_parou_reservarBilhete + 1;
}

void addFilme(FILMES *lista_filmes, int *p_cont_parou_addFilme){
	int i = *p_cont_parou_addFilme;

	printf("# Adicionar um novo filme\n\n");

	lista_filmes[i].cod_filme = i + 100; //o proprio codigo vai definir o codigo do filme
	printf("Entre com o nome: ");
	scanf("%s", lista_filmes[i].nome_filme);
	printf("Entre com o genero: ");
	scanf("%s", lista_filmes[i].gen_filme);
	printf("Entre com o formato: ");
	scanf("%s", lista_filmes[i].form_filme);
	printf("Entre com a data do filme (dd-mm-aaaa): ");
	scanf("%s", lista_filmes[i].data_filme);
	printf("Entre com o horario do filme: ");
	scanf("%d", &lista_filmes[i].hora_filme);
	printf("Entre com o valor do bilhete: ");
	scanf("%f", &lista_filmes[i].valor_bilhete);	

	/* depois de add um novo filme, incrementar +1 ao contador */
	*p_cont_parou_addFilme = *p_cont_parou_addFilme + 1;
}

void mostrarListaFilmes(FILMES *lista_filmes, int *p_cont_parou_addFilme){
	printf("# Lista de filmes cadastrados\n\n");

	int ate_onde = *p_cont_parou_addFilme;
	int i; //contador comum
	for (i = 0; i < ate_onde; i++){
		printf("Codigo do filme: %d \n", lista_filmes[i].cod_filme);
		printf("Nome do filme: %s \n", lista_filmes[i].nome_filme);
		printf("Genero: %s \n", lista_filmes[i].gen_filme);
		printf("Formato: %s \n", lista_filmes[i].form_filme);
		printf("Data do filme: %s \n", lista_filmes[i].data_filme);
		printf("Horario do filme: %d \n", lista_filmes[i].hora_filme);
		printf("Valor do bilhete: %.2f \n\n", lista_filmes[i].valor_bilhete);
	}
}

void buscarBilhete(FILMES *lista_filmes, BILHETES *vetor_bilhetes, int *p_cont_parou_addFilme, int *p_cont_parou_reservarBilhete, int *qtd_bilhetes){
	/* Legenda
	[1] = FOR para percorrer todas as posições que contem os bilhetes reservados
	[2] = imprimindo os bilhetes reservados
	[3] = AUX para garantir que apenas os bilhetes reservado serao impressos
	[4] = TESTE para caso não exista bilhetes reservados */

	int i, cod, tel, op; //variaveis: contador; variavel para teste de busca por codigo; variavel para teste de busca por telefone; variavel para o menu
	int aux;			 //vaiavel aux para testar caso nao haja nenhum bilhete reservado
	char nome[50];		 //variavel para teste de busca por nome do cliente
	
	//menu da funcao buscarBilhete
	printf("# Como deseja buscar o bilhete reservado\n");
	printf("1) Codigo do filme:\n");
	printf("2) Nome do cliente:\n");
	printf("3) Telefone do cliente:\n");
	scanf("%d", &op);

	switch(op){
		case 1:
			printf("# Voce escolheu Codigo\n");
			printf("Digite o codigo do filme reservado\n");
			scanf("%d", &cod);

			//[1]
			for(i=0; i < *qtd_bilhetes; i++){
				if(cod ==  vetor_bilhetes[i].cod_bil_filme){//
					//[2]
					printf("Seu bilhete e:\n");
					printf("\n# Imprimindo bilhetes que reservaram esse filme:\n\n");
					printf("Codigo do filme: %d \n", vetor_bilhetes[i].cod_bil_filme);
					printf("Nome do cliente: %s \n", vetor_bilhetes[i].nome_cliente);
					//[3]
					aux = 1;
				}
			}

			if (aux != 1)// [4]
				printf("Nenhum bilhete reservado para esse codigo\n");
		break;

		case 2:
			printf("# Voce escolheu nome\n");
			printf("Digite o nome do cliente que reservou o bilhete:\n");
			scanf("%s", nome);
			//[1]
			for(i=0; i < *qtd_bilhetes; i++){
				if((strcmp (vetor_bilhetes[i].nome_cliente, nome)) == 0){// [2] usando strcmp para comparação de strings
					printf("Seu bilhete e:\n");
					printf("\n# Imprimindo bilhetes que reservaram esse filme:\n\n");
					printf("Codigo do filme: %d \n", vetor_bilhetes[i].cod_bil_filme);
					printf("Nome do cliente: %s \n", vetor_bilhetes[i].nome_cliente);
					printf("Telefone do cliente: %d \n", vetor_bilhetes[i].tel_cliente);
					//[3]
					aux = 1;
				}
			}

			if(aux != 1)//[4]
			printf("Nenhum bilhete reservado para esse nome\n");
		break;

		case 3:
			printf("# Voce escolheu Telefone\n");
			printf("Digite o telefone do cliente \n");
			scanf("%d", &tel);

			//[1]
			for(i=0; i < *qtd_bilhetes; i++){
				if(tel ==   vetor_bilhetes[i].tel_cliente){//[2]
					printf("Seu bilhete e:\n");
					printf("\n# Imprimindo bilhetes que reservaram esse filme:\n\n");
					printf("Codigo do filme: %d \n", vetor_bilhetes[i].cod_bil_filme);
					printf("Nome do cliente: %s \n", vetor_bilhetes[i].nome_cliente);
					printf("Telefone do cliente: %d \n", vetor_bilhetes[i].tel_cliente);
					//[3]
					aux = 1;
				}
			}

			if (aux != 1)//[4]
			printf("Nenhum bilhete reservado para esse telefone \n");
		break;

		default:
			printf("Opcao invalida.\n");
	}

}

