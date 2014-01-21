/*  Trabalho Prático - Programação I
    Departamento de Eng. Informática
    EI PL TP 1 2009/2010
    
    Bruno Tereso EIPL 2091066
    Marco Ferreira EIPL 2092016 



    ###############################################################
                       DECLARAÇÃO DE LIVRARIAS
    ############################################################### */
    
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


/*  ###############################################################
                       DECLARAÇÃO DE CONSTANTES
    ############################################################### */
    
#define MAX_PILOTOS 200 // 200 número máximo de pilotos
#define MAX_PILOTOS_ETAPA 20 // 20 número máximo de pilotos por etapa
#define MAX_ETAPAS 10 // 10 número máximo de etapas

#define PROGRAMA "\n\n\t\t\t\tESTG Air Race 2010\n" // titulo do programa

#define ERRO_NOME 500 // introduzidos dados inválidos, um nome curto demais
#define ERRO_DUPLICADO 998 // erro, existem nomes repetidos
#define ERRO_NAOEXISTE 999 // nome da etapa ou piloto não existe
#define SAIR '.' // sai do programa depois de gravar
#define NAOSAIR ',' 
#define NUMTOPS 3 // numero de pilotos/etapas a aprensentar nos tops ( estatisticas)

#define ETAPA_EXTREMO 501 // devolve extremos das etapas quando se compara a data
#define DIAS_MAX 99999999 /* valor máximo em dias para a etapa seguinte,
                          usado para validar data, significa que não existe um etapa com data posterior à inserida */
#define DIAS_MIN 1 /* valor máximo em dias para a etapa anterior,
                   usado para validar data, significa que não existe um etapa com data anterior à inserida*/
#define CHARS_NOME 31


/*  ###############################################################
                       DECLARAÇÃO DE ESTRUTURAS
    ############################################################### */

typedef struct { // estrutura para a data
	int dia, mes, ano;
	}data_t;

typedef struct { // estrutura para tempos
	int min, seg, mseg;
	}tmp_t;

typedef struct { // estrutura para ficha de piloto
	char nome[CHARS_NOME];  // último nome
	int idade;         // idade
	int aviao;      // numero aviao
	int pontos;
	} ficha_t;

typedef struct { // estrutura para as etapas
	char nome[CHARS_NOME];  // designação da etapa
	int ordem;         // ordem da etapa
	data_t data;      // estrutra data_t que guarda a data da etapa
	int participantes;      // numero de pilotos a participar (max20)
    int totalinscritos;     
	int inscritos[MAX_PILOTOS_ETAPA]; // vector q vai guardar os numeros dos avioes inscritos
    int tempos[MAX_PILOTOS_ETAPA];
    int pontos[MAX_PILOTOS_ETAPA];
	int realizada; // variável logica 0 - por realizar 1 - realizada
	} etapa_t;

typedef struct { // estrutura que guarda os pilotos inscritos e etapas inseridas
	int pilotos;
	int etapas;
	int realizadas; // em testes
    int etapa_corrente;
    int grava; // 1 se houver modificações por gravar
    //int classgeral[MAX_PILOTOS];
	} conta_t;
	





/*  ###############################################################
                       PROTOTIPOS DE FUNÇÕES
    ############################################################### */

// Funções principais

// Pilotos
    char pilMenu(conta_t *ptr_contador); // Mostra o menu de Pilotos no ecrã.
ficha_t *pilFuncoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, char op, conta_t *ptr_contador); // Recebe uma opção escolhida e direcciona para a função a usar.
ficha_t *pilInserir(ficha_t *ptr_piloto, conta_t *ptr_contador); // Insere um novo registo nas fichas de pilotos
    void pilConsultar(ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador);// Consulta os dados de um piloto.
ficha_t *pilEliminar(ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador); // Apaga um piloto.
    void pilListagem(int tipo_lista, ficha_t *ptr_piloto, conta_t *ptr_contador); // Mostra a lista de pilotos, em modo normal ou reduzido.
    void pilInscricoes(etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Lista as etapas em que um determinado piloto se inscreveu.
     int pilProcurar(char nomenumero[31], ficha_t *ptr_piloto, conta_t *ptr_contador); // Procura o indice de um piloto nas fichas de piloto.
     int pilProcuraDuplicado(char nomenumero[], ficha_t *ptr_piloto, conta_t *ptr_contador); // Verifica se existe mais do que um piloto com o mesmo nome.
    void pilMostraInscricoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, int indice, int tipo); // Mostra uma lista com as inscrições de um piloto.
    void pilLimpaInscricoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, int indice); // Limpa as inscrições de um piloto em todas as etapas.
ficha_t *pilApaga(ficha_t *ptr_piloto, conta_t *ptr_contador, int indice); // Apaga o registo de um piloto.
     int pilIndiceAviao(int numero_aviao, ficha_t *ptr_piloto, conta_t *ptr_contador); // Procura o avião indicado na lista de pilotos e devolve o indice correspondente.

// Etapas
    char etaMenu(conta_t *ptr_contador); // Mostra o menu etapas
    void etaFuncoes(etapa_t *ptr_etapa, ficha_t *ptr_piloto, char op, conta_t *ptr_contador); // Recebe a opção escolhida e direcciona para a função a usar.
    void etaInserir(); // Insere um novo registo na lista de etapas
    void etaActCorrente(etapa_t *ptr_etapa, conta_t *ptr_contador);
    void etaEditar(etapa_t *ptr_etapa, conta_t *ptr_contador); // Lista as etapas e altera uma à escolha do utilizador
    void etaInscreverPiloto(etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Mostra as etapas, inscreve um piloto na etapa escolhida.
    void etaDados(etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Lista etapas e mostra os dados de uma delas à escolha do utilizador.
    void etaListar(int tipo, etapa_t *ptr_etapa, conta_t *ptr_contador); // Mostra uma lista de etapas para auxílio em funções
     int etaProcurar(char nomenumero[40], etapa_t *ptr_etapa, conta_t *ptr_contador); // Analisa o nome ou ordem de uma etapa e devolve o indice desta.
     int etaVerificaInscricao(ficha_t *ptr_piloto, etapa_t *ptr_etapa, int aviao_piloto, int indice_etapa, conta_t *ptr_contador); // Verifica se o avião está inscrito numa etapa ou qualquer outra etapa.
     int etaProcuraDuplicada(char nomenumero[], etapa_t *ptr_etapa); // Verifica se existe mais do que uma etapa com o mesmo nome.
     int etaInscricoesVagas(etapa_t *ptr_etapa, conta_t *ptr_conta); // Conta o número de vagas do campeonato, em todas as etapas.
    void etaLimpaInscricoes(int indice_etapa, etapa_t *ptr_etapa); // Apaga todas as inscrições de uma etapa.
     int etaNumRealizadas(etapa_t *ptr_etapa); // Conta o número de etapa realizadas para apresentar no menu principal.
     int etaProcuraPiloto (int etapa, int aviao, etapa_t *ptr_etapa); // Procura um piloto dentro da etapa especificada

// Resultados
    char resMenu(conta_t *ptr_contador, etapa_t *ptr_etapa); // Mostra o menu de Resultados no ecrã.
    void resFuncoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, char op, conta_t *ptr_contador); // Recebe a opção escolhida e direcciona para a função a usar.
    void resLeCorrente(etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Verifica a Etapa corrente e recebe os tempos dados pelo utilizador.
    void resCabecalho(etapa_t *ptr_etapa, conta_t *ptr_contador); // Cabeçalho para o menu Resultados.
    void resAlterarResultados (etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Lista as etapas e permite alterar os resultados de uma delas
    void resOrdenaTempos (int etapa, etapa_t *ptr_etapa); // Ordena todos os tempos recebidos crescentemente e actualiza as posições no vector de inscritos
    void resPontuacao (int etapa, ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador); // Preenche o vector das pontuações para a etapa indicada, le os tempos.
    void resRemPontuacao (int etapa, ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador); // Limpa as pontuações atribuidas a pilotos e etapa
    void resLeTempos(int etapa, etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Lista o nome do piloto e Recebe o valor do tempo no formato mm.ss,mseg.
    void resConsultar (etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Lista etapas, recebe a ordem da etapa a visualizar e chama a função que mostra os resultados.
     int resLeSegundos(); // Le um valor de tempo no formato mm.ss,mseg
    void resOrdenaClass (ficha_t *ptr_piloto, conta_t *ptr_contador); // Ordena a Classificação Geral do campeonato
    void resEtapa (int etapa, etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Mostra os dados de um etapa realizada
    void resOrdenaClassAviao (ficha_t *ptr_piloto, conta_t *ptr_contador); // Ordena a classificação geral pelo número do avião

// Estatisticas
    char estMenu(conta_t *ptr_contador); // Mostra o menu de Pilotos no ecrã
    void estFuncoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, char op, conta_t *ptr_contador); // Recebe a opção escolhida e direcciona para a função a usar
    void estHistorico (etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Mostra uma tabela de Pilotos/Etapas com a classificação de cada
    void estCabecalhoHistorico (etapa_t *ptr_etapa, conta_t *ptr_contador); // Cabeçalho para a Listagem do Histórico.
    void estMostraClassificacao (int simples, ficha_t *ptr_piloto, conta_t *ptr_contador); // Lista a classificação geral nas estatísticas
    void estDados (conta_t *ptr_contador, etapa_t *ptr_etapa, ficha_t *ptr_piloto); // Mostra os dados estatísticos do campeonato
    void estNumVitorias ( int pilotos[][2], int vencedores[], ficha_t *ptr_piloto, conta_t *ptr_contador, char tipo); // Preenche a matriz pilotos e ordena
    void estPctVictorias ( int pilotos[][2], ficha_t *ptr_piloto, conta_t *ptr_contador); // Conta o número de vitórias e calcula a média com o número total de pilotos
    void estEtapas ( int etapas[][2], etapa_t *ptr_etapa, conta_t *ptr_contador, char tipo); // Ordena os inscritos e mostra
    void estMediaParticipantes ( etapa_t *ptr_etapa, conta_t *ptr_contador); // mostra ao utilizador a média de pilotos por etapa
    void estVitoriasConsecutivas (int vencedores[], etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador); // Analisa o vector vencedores e procura pilotos com 2 ou mais vitórias consecutivas

// Ficheiros
    void fichGravar(conta_t *ptr_contador, etapa_t *ptr_etapa, ficha_t *ptr_piloto); // Grava a informação num ficheiro binário
ficha_t *fichLer(conta_t *ptr_contador, etapa_t *ptr_etapa); // Le a informação de num ficheiro binário

// Funções diversas
    char menuPrincipal(conta_t *ptr_contador); // Mostra o menu principal no ecrã.
    void menuCabecalho(int tipo, conta_t *ptr_contador); // Mostra o cabeçalho do Programa.
    void auxLeString(int tipo, char texto[], char pergunta[30], char erro[50], int inferior, int superior); // Le e valida um vector de caracteres.
     int auxLeInteiro (char pergunta[40], int menor, int maior); // Le e valida um número inteiro
    void auxLeData(int numero_etapa, etapa_t *ptr_etapa); // Le uma data válida para inserir uma etapa.
    void auxPausa(); // Muda de linha e pausa o sistema.
    void auxIniciaValores(ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador); // inicializa valores das estruturas a zero
    char auxSair(conta_t *ptr_contador, ficha_t *ptr_piloto, etapa_t *ptr_etapa); // pergunta ao utilizador se quer gravar antes de sair
   tmp_t auxConverteMseg (int tempo_mseg); // Converte o tempo de milesimos de segundos para o formato mm.ss,mseg
    void auxVencedores ( int vencedores[], etapa_t *ptr_etapa); // Preenche um vector Vencedores com o numero dos aviões que venceram cada etapa
    void auxOrdenaMatriz (int vector[][2], int max, char tipo); // Função auxiliar para ordenar matrizes
ficha_t *auxLer(conta_t *ptr_contador, ficha_t *ptr_piloto, etapa_t *ptr_etapa); // Função auxiliar para perguntar ao utilizador se quer ler os dados à entrada




/*  ###############################################################
                       PROGRAMA PRINCIPAL
    ############################################################### */

main (void) {

	char opcao_menu;
	
	ficha_t *ptr_piloto; // ponteiro que aponta para o inicio da estrutura de pilotos
	etapa_t ptr_etapa[MAX_ETAPAS]; // vector de estruturas que guarda 10 etapas
	conta_t ptr_contador; // estrutura com contadores

    ptr_piloto = NULL; // inicia o ponteiro a null

    ptr_piloto = auxLer(&ptr_contador, ptr_piloto, ptr_etapa); // le dados de um ficheiro ou inicializa os valores a zero

	do {
	    ptr_contador.realizadas = etaNumRealizadas(ptr_etapa); // conta as etapas realizadas antes de desenhar o menu
        opcao_menu = menuPrincipal(&ptr_contador);
		switch (opcao_menu) {
			case 'P': 
					do { // espera pela tecla V, mantem o menu nos pilotos indeterminadamente
						opcao_menu = pilMenu(&ptr_contador);
						ptr_piloto = pilFuncoes(ptr_piloto, ptr_etapa, opcao_menu, &ptr_contador);
						}
					while (opcao_menu != 'V');
					break;
					
			case 'E':
					do { // espera pela tecla V, mantem o menu nas etapas indeterminadamente
						opcao_menu = etaMenu(&ptr_contador);
						etaFuncoes(ptr_etapa, ptr_piloto, opcao_menu, &ptr_contador); 
						}
					while (opcao_menu != 'V');
					break;

			case 'R': 
					do { // espera pela tecla V, mantem o menu nos resultados indeterminadamente
						opcao_menu = resMenu(&ptr_contador, ptr_etapa);
						resFuncoes(ptr_piloto, ptr_etapa, opcao_menu, &ptr_contador); 
						}
					while (opcao_menu != 'V');
					break;

			case 'T': 
                    do { // espera pela tecla V, mantem o menu nas estatisticas indeterminadamente
                    	opcao_menu = estMenu(&ptr_contador);
                    	estFuncoes(ptr_piloto, ptr_etapa, opcao_menu, &ptr_contador); 
                    	}
                    while (opcao_menu != 'V');					
                    break;

			case 'G': 
					fichGravar(&ptr_contador, ptr_etapa, ptr_piloto);
					break;

			case 'S': 
					opcao_menu = auxSair(&ptr_contador, ptr_piloto, ptr_etapa);
					break;
					
			}
		}
	while (opcao_menu != SAIR);
    free(ptr_piloto); // liberta a memoria
}


/*  ###############################################################
                       FUNÇÕES PRINCIPAIS
    ############################################################### */

char menuPrincipal(conta_t *ptr_contador) {
	/*  Mostra o menu principal no ecrã.
	    Recebe:
	        op: letra/opção introduzida pelo utilizador
	    Devolve:
	        op: Guarda a letra introduzida pelo utilizador
	    */
	
	char op;
	
	do {
		menuCabecalho(0, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
		printf("\n\n\tP - Pilotos");
		printf("\n\tE - Etapas");
		printf("\n\tR - Resultados");
		printf("\n\tT - Estatisticas");
		if ( ptr_contador->grava == 1 ) // avisa o utilizador que precisa de gravar
            printf("\n\tG - Gravar Dados ( Necessario )");
        else
            printf("\n\tG - Gravar Dados");
		printf("\n\tS - Sair\n\t");	
		fflush(stdin);
		op = getch();
		op = toupper(op);
		}
	while (op != 'S' && op != 'P' && op != 'E' && op != 'R' && op != 'T' && op != 'G');
	
	return op;
}


char pilMenu(conta_t *ptr_contador) {
	/*  Mostra o menu de Pilotos no ecrã.
	    Recebe:
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    Devolve:
	        op: letra/opção introduzida pelo utilizador
	    */
	
	char op;
	
	do {
		menuCabecalho(1, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
		printf("\n\n\tI - Inserir Piloto");
		printf("\n\tE - Eliminar Piloto");
		printf("\n\tC - Consultar Dados Piloto");
		printf("\n\tL - Listar todos os Pilotos");
		printf("\n\n\tV - Voltar ao Menu Principal");
		fflush(stdin);
		op = getch();
		op = toupper(op);
		}
	while (op != 'V' && op != 'I' && op != 'E' && op != 'C' && op != 'L');
	
	return op;
}


ficha_t *pilFuncoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, char op, conta_t *ptr_contador) {
	/*  Recebe a opção escolhida e direcciona para a função a usar.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_etapa: vector ponteiro com a lista de etapas
	        op: letra/opção escolhida na função pilMenu
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	switch (op) {
		case 'I':  //inserir piloto
				if (ptr_contador->pilotos < MAX_PILOTOS) // se não atingiu o limite máximo de pilotos, insere
					ptr_piloto = pilInserir(ptr_piloto, ptr_contador);
				else {
					printf("\n\tLamento, atingiu o numero maximo de pilotos...");
					auxPausa();
					}
				break;
				
		case 'E':  //elimitar piloto
				if (ptr_contador->pilotos > 0) // se não existem pilotos, não tenta eliminar
					pilEliminar(ptr_piloto, ptr_etapa, ptr_contador);
				else {
					printf("\n\n\tImpossivel eliminar pilotos, de momento nao tem nenhum inscrito...");
					auxPausa();
					}
				break;
				
		case 'C':  //consultar dados de piloto
				if (ptr_contador->pilotos > 0) // se não existem pilotos, não deixa consultar
					pilConsultar(ptr_piloto, ptr_etapa, ptr_contador);
				else {
					printf("\n\n\tImpossivel consultar pilotos, de momento nao tem nenhum inscrito...");
					auxPausa();
					}
				break;
				
		case 'L':  //lista de pilotos
				if (ptr_contador->pilotos > 0) { // se existe 1 ou mais pilotos, mostra uma lista com nome, idade e avião
					menuCabecalho(1, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
					pilListagem(0, ptr_piloto, ptr_contador); // 0 = lista completa , 1 = lista 2 colunas
					auxPausa();
					}
				else {
					printf("\n\n\tLista vazia, de momento nao tem nenhum inscrito...");
					auxPausa();
					}
				break;
		}
    return ptr_piloto;
}


ficha_t *pilInserir(ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Insere um novo registo nas fichas de pilotos
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	char apelido[15], nome[15]; // vectores de caracteres temporarios
	int i, aviao_validado = 1, numero_aviao, idade, indice;
    ficha_t *aux; // ponteiro auxiliar para salvaguardar o ptr_pilotos no caso de erros

    aux = NULL;
	
	menuCabecalho(1, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
	printf("\n\n\tInserir Piloto: \n\n");
	
	auxLeString(1, apelido, "\tApelido:", "Erro, O Apelido do piloto deve ter entre 2 e 15 caracteres\n", 2, 15);
	auxLeString(1, nome, "\tNome:", "Erro, O Nome do piloto deve ter entre 2 e 15 caracteres\n", 2, 15);
	
	strcat(nome, " "); // coloca um espaço a seguir ao nome
	strcat(nome, apelido);   // completa a string do nome com o apelido, max 31 caracteres
	
	do { // certifica-se que o número de avião é unico
		numero_aviao = auxLeInteiro("\tNumero do Aviao: ", 1, ERRO_NAOEXISTE);
		for (i = 0; i < ptr_contador->pilotos; i++) // percorre todas as estruturas à procura de um aviao com o mesmo numero
			if (numero_aviao == ptr_piloto[i].aviao) {
				printf("\tErro, ja existe um piloto com esse numero de aviao.\n");
				aviao_validado = 0;
				i = ptr_contador->pilotos; // se encontrou 1, sai do ciclo ( break; )
				}
			else
				aviao_validado = 1; // se não encontra um avião igual, considera validado
		}
	while (aviao_validado == 0);
	
	idade = auxLeInteiro ("\tIdade do Piloto: ", 18, 80); //le a idade entre 18 e 80, *podem ser constantes
	printf("\n\tPiloto inserido com sucesso...");
	aux = (ficha_t*)realloc(ptr_piloto, (ptr_contador->pilotos+1)*sizeof(ficha_t)); // realoca a memória para ter espaço para mais um piloto
	if ( aux == NULL) { // se deu erro de memoria avisa, e nãp mexe no ptr_piloto
        printf("\n\tErro de Memoria."); 
        auxPausa();
        return ptr_piloto; // devolve o endereço de memoria 
        }
    else {
        ptr_piloto = aux; // leu sem erros, aponta para o piloto
        strcpy(ptr_piloto[ptr_contador->pilotos].nome, nome); // grava nome
        ptr_piloto[ptr_contador->pilotos].idade = idade; // grava idade
        ptr_piloto[ptr_contador->pilotos].aviao = numero_aviao; // grava aviao
        ptr_piloto[ptr_contador->pilotos].pontos = 0; // inicia os pontos a zero

        ptr_contador->pilotos++; // incrementa os pilotos depois de inserir com sucesso.
        ptr_contador->grava = 1; // houve alterações, pergunta se quer gravar antes de sair
        auxPausa();
        return ptr_piloto; // devolve o endereço de memoria para o inicio da estrutura de pilotos
        }
}


void pilConsultar(ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador) {
	/*  Pergunta ao utilizador o número ou nome de um piloto e mostra os seus dados no ecrã.
	    Incluido Nome, Nº do Avião, Idade, Pontuação, Etapas onde está inscritos e o pontos destas.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	char nomenumero[31];
	int duplicados = 0, i, j, indice;
	
	menuCabecalho(1, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
	printf("\n\n\tConsultar dados de Piloto \n");
	pilListagem(1, ptr_piloto, ptr_contador); // lista os pilotos para facilitar; valor 1 para lista reduzida
	
	do {
		auxLeString(2, nomenumero, "\n\n\tInsira o nome do piloto ou o numero do aviao:", "Erro, nome ou numero invalido\n", 1, 31);
		indice = pilProcurar(nomenumero, ptr_piloto, ptr_contador);
		if (indice == ERRO_DUPLICADO) { // ==ERRO_NOME removido, para não apresentar duas mensagens de erro. se o nome
                                        // não pode existir n faz sentido avisar que a etapa n foi encontrada.
			printf("\n\tExiste mais do que um piloto com esse nome\n\tPor favor use o numero de aviao para a pesquisa.");
			}
		if (indice == ERRO_NAOEXISTE) // ==ERRO_NOME removido, para não apresentar duas mensagens de erro. se o nome não
                                      //  pode existir n faz sentido avisar que o piloto n foi encontrado.
			printf("\n\tPiloto não encontrado...");
		}
	while (indice == ERRO_NOME || indice == ERRO_NAOEXISTE || indice == ERRO_DUPLICADO);
	
	system("cls");
	puts(PROGRAMA);
	printf("\n\n\n\tEncontrado o piloto:\n\n\t%s, de %d anos, a correr no aviao com o numero: %d",
           ptr_piloto[indice].nome, ptr_piloto[indice].idade, ptr_piloto[indice].aviao);
	printf("\n\tActualmente com %d pontos no campeonato.", ptr_piloto[indice].pontos);
    printf("\n\tAtribuidos nas seguintes etapas:\n\n");

    pilMostraInscricoes(ptr_piloto, ptr_etapa, indice, 1); // lista com etapa e pontuação
	auxPausa();
}


void pilListagem(int tipo_lista, ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Mostra a lista de pilotos, em modo normal ou reduzido.
	    Recebe:
	        tipo_lista: define o tipo de lista, 0= normal, 1= reduzida (nome/aviao)
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	int i;

	if (tipo_lista == 0) { // lista simples com nome, idade e nº de aviao
		printf("\n\n\t\t\t\t\t         Nome | Idade | Aviao\n");
		for (i = 0; i < (ptr_contador->pilotos); i++) { // lista os pilotos ate ao ultimo inscrito
			printf("\n\t\t      %31.31s |   %2.d  |  %3.d  ", ptr_piloto[i].nome, ptr_piloto[i].idade, ptr_piloto[i].aviao);
			if (i != 0 && i % 10 == 0) // de 10 em 10 nomes, faz uma pausa para o utilizador ver os nomes, ignora o 0 porque senão pausa na primeira linha
				auxPausa();
			}
		}
	else { // lista de 2 colunas para apoio em funções
		printf("\n\n\t    Nome | Aviao\n");
		for (i = 0; i < (ptr_contador->pilotos); i++) { // lista os pilotos ate ao ultimo inscrito
			printf("\n\t  %18.18s | %3.d  ", ptr_piloto[i].nome, ptr_piloto[i].aviao);
            if ( ptr_contador->pilotos > 1 && i+1 < ptr_contador->pilotos) { // se terminar em numero impar n mostra o ultimo piloto que n existe
                printf("\t  %18.18s | %3.d    ", ptr_piloto[i+1].nome, ptr_piloto[i+1].aviao); // se só tem um piloto, não mostra nome seguinte
                i++;
                }
			if (i != 0 && i % 10 == 0) // de 10 em 10 nomes, faz uma pausa para o utilizador ver os nomes, ignora o 0 porque senão pausa na primeira linha
				auxPausa();
			}
		}
}


ficha_t *pilEliminar(ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador) {
	/*  Lista os pilotos, recebe o nome ou numero de avião do utilizador e apaga o piloto.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	char nomenumero[31], confirma, nome[31];
	int confirmaapaga=0, verifica_inscrito, i, j, numero_aviao, saiciclo = 1, indice;
    ficha_t *aux; // ponteiro temporario

    aux = NULL;
	
	menuCabecalho(1, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
	printf("\n\n\tEliminar Piloto \n");
	pilListagem(1, ptr_piloto, ptr_contador); // lista os pilotos para facilitar; valor 1 para lista reduzida
	do {
		printf("\n\n\tInsira o nome do piloto ou o numero do aviao: "); // detecta automaticamente se e' aviao ou nome
		fflush(stdin);
		//gets(nomenumero); // usar scanf
        scanf("%31[^\n]", nomenumero);
		indice = pilProcurar(nomenumero, ptr_piloto, ptr_contador); // devolve o indice do piloto com o nome ou número de aviao inserido
		if (indice != ERRO_NOME && indice != ERRO_NAOEXISTE && indice != ERRO_DUPLICADO)
			saiciclo = 0;
		else
			if (indice == ERRO_NAOEXISTE)
				printf("\tO nome\\aviao nao existe na base de dados\n");
			else
				if (indice == ERRO_DUPLICADO)
					printf("\n\tExiste mais do que um piloto com esse nome\n\tPor favor use o numero de aviao para a pesquisa.");
		}
	while (saiciclo);
	// verifica se o piloto está inscrito em alguma etapa ; max_etapas+1 para salvaguardar que e' uma etapa que nao existe
	verifica_inscrito = etaVerificaInscricao(ptr_piloto, ptr_etapa, ptr_piloto[indice].aviao, MAX_ETAPAS + 1, ptr_contador); 
	if (verifica_inscrito == -2) { // se o etaVerificaInscricao devolveu -2, o piloto está inscrito numa etapa realizada, logo, n pode apagar
		printf ("\n\tImpossivel apagar o piloto.");
		printf ("\n\t%s encontra-se inscrito numa etapa ja realizada...", ptr_piloto[indice].nome);
		auxPausa();
    }                          
	else {
		do { // pedir confirmação para apagar
            if (verifica_inscrito == -1) { // se o etaVerificaInscricao devolveu -1, o piloto está inscrito em uma ou mais etapas, mas n realizadas
                printf ("\n\tATENCAO: O piloto esta inscrito nas seguintes etapas:\n");
                pilMostraInscricoes(ptr_piloto, ptr_etapa, indice, 2); // mostra as inscrições
                confirmaapaga = 1; // para 1 para o proximo ciclo, pq se tiver inscrições e ele confirmar o apagar, tem que limpar inscrições
                } // se não tem inscrições, não mostra avisas e pede apenas confirmação para apagar
            printf("\n\tTem a certeza que pretente eliminar o piloto");
			printf("\n\t%s, com o aviao numero %d, [S]im [N]ao", ptr_piloto[indice].nome, ptr_piloto[indice].aviao);
			confirma = getch();
			confirma = toupper(confirma);
			}
		while (confirma != 'S' && confirma != 'N');
		
		if (confirma == 'S') {
			if (confirmaapaga) // se vem com 1, tem que limpar inscrições
                pilLimpaInscricoes(ptr_piloto, ptr_etapa, indice); // limpa todas as inscrições de um piloto
            ptr_piloto = pilApaga(ptr_piloto, ptr_contador, indice); // apaga o piloto 
		    printf("\n\tPiloto apagado com sucesso...");
            ptr_contador->grava = 1; // houve alterações, pergunta se quer gravar antes de sair
			}
		else
			printf("\n\tCancelado.");
		auxPausa();
		}
    return ptr_piloto;
}


char etaMenu(conta_t *ptr_contador) {
	/*  Mostra o menu de Etapas no ecrã.
	    Recebe:
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    Devolve:
	        op: letra/opção introduzida pelo utilizador
	    */
	
	char op;
	
	do {
		menuCabecalho(2, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
		printf("\n\n\tI - Inserir Etapa");
		printf("\n\tE - Editar Etapa");
		printf("\n\tN - Inscrever Piloto em Etapa");
		printf("\n\tD - Dados da Etapa");
		printf("\n\tL - Listar Inscricoes de Piloto");
		printf("\n\n\tV - Voltar ao Menu Principal");
		fflush(stdin);
		op = getch();
		op = toupper(op);
		}
	while (op != 'V' && op != 'I' && op != 'E' && op != 'N' && op != 'D' && op != 'L');
	
	return op;
}


void etaFuncoes(etapa_t *ptr_etapa, ficha_t *ptr_piloto, char op, conta_t *ptr_contador) {
	/*  Recebe a opção escolhida e direcciona para a função a usar.
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        op: letra/opção escolhida na função pilMenu
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	    
    int vagas=1;
	
	switch (op) {
		case 'I':  //inserir etapa
				if (ptr_contador->etapas < MAX_ETAPAS) // se houver etapas disponiveis permite inserir
					etaInserir(ptr_etapa, ptr_contador);
				else {
					printf("\n\tLamento, atingiu o numero maximo de etapas...");
					auxPausa();
					}
				break;
				
		case 'E':  //editar etapa
				if (ptr_contador->etapas > 0) // certifica que existem etapas para editar
					etaEditar(ptr_etapa, ptr_contador);
				else {
					printf("\n\tNao existe qualquer etapa para editar...\n\n\t");
					system("PAUSE");
					}
				break;
				
		case 'N':  //Inscrever piloto em etapa 				
                vagas = etaInscricoesVagas(ptr_etapa, ptr_contador); // vai contar o numero de vagas, se for igual a 0 não faz sentido tentar inserir piloto.      
                if (ptr_contador->etapas > 0 && ptr_contador->pilotos > 0 && vagas !=0) // se existem pilotos, existem etapas e existem vagas, inscreve
					etaInscreverPiloto(ptr_etapa, ptr_piloto, ptr_contador);
                else
                if (vagas == 0 && ptr_contador->etapas > 0) {
					printf("\n\n\tImpossivel inscrever piloto.\n\tTodas as etapas estao preenchidas...\n\n\t");
					system("PAUSE");                   
                    }
				else {
					printf("\n\tImpossivel inscrever piloto em etapas...");
					printf("\n\tCertifique-se que tem pelo menos 1 piloto e 1 etapa.\n\n\t");
					system("PAUSE");
					}
				break;
				
		case 'D':  //dados da etapa
				if (ptr_contador->etapas > 0) // certifica-se que existem etapas antes de mostrar dados
					etaDados(ptr_etapa, ptr_piloto, ptr_contador);
				else {
					printf("\n\tNao existem etapas disponiveis...\n\n\t");
					system("PAUSE");
					}
				break;
				
		case 'L':  //lista inscrições de piloto
				if (ptr_contador->etapas > 0 && ptr_contador->pilotos > 0) // se existem etapas e pilotos, mostra lista
					pilInscricoes(ptr_etapa, ptr_piloto, ptr_contador);
				else {
					printf("\n\tImpossivel listar inscricoes...");
					printf("\n\tCertifique-se que tem pelos menos 1 piloto e 1 etapa.\n\n\t");
					system("PAUSE");
					}
				break;
				
		}
}


void etaInserir(etapa_t *ptr_etapa, conta_t *ptr_contador) {
	/*  Insere um novo registo na lista de etapas
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	char nome_etapa[31], data[10];
	int i, validado = 0, ordem_etapa, participantes, indice;
	
	menuCabecalho(2, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
	printf("\n\n\tInserir Etapa | Listagem das etapas actuais");	
	etaListar(1, ptr_etapa, ptr_contador); // lista etapas, 1 = todas as etapas
	printf("\n\n");

	auxLeString(2, nome_etapa, "\n\tDesignacao da nova etapa: ", "\n\tInsira um nome de etapa entre 3 e 30 caracteres.\n", 3, 30);
	
	do { // verifica se ja existe uma etapa na ordem inserida
		ordem_etapa = auxLeInteiro("\tOrdem da etapa no campeonato: ", 1, MAX_ETAPAS);
		if (ptr_etapa[ordem_etapa-1].data.ano != 0) { // verifica a data, se for 0 e' pq n ha etapa para esse indice, ou seja a posição esta' vazia
			printf("\tErro, ja existe uma etapa nessa posicao.\n");
			validado = 0;
			i = MAX_ETAPAS;
			}
		else
			validado = 1;
		}
	while (validado == 0);
	
	ordem_etapa--; // decrementa 1 para passar a usar o indice correcto do vector ; depois do ciclo	
	auxLeData(ordem_etapa, ptr_etapa); // aqui preciso da ordem da etapa, nao do indice
	participantes = auxLeInteiro ("\tNumero de participantes: ", 0, MAX_PILOTOS_ETAPA); //le um valor inteiro entre o 'menor' e o 'maior' inclusive
	ptr_etapa[ordem_etapa].participantes = participantes;	
	strcpy(ptr_etapa[ordem_etapa].nome, nome_etapa);
	ptr_contador->etapas++; // incrementa uma etapa depois de inserir com sucesso.
	printf("\n\tEtapa inserida com sucesso...");
    for ( i = 0; i < participantes; i++) { // limpa os vectores usados nos resultados e estatisticas para a etapa inserida
        ptr_etapa[ordem_etapa].inscritos[i] = 0;
        ptr_etapa[ordem_etapa].pontos[i] = 0;
        ptr_etapa[ordem_etapa].tempos[i] = 0;
        }
    ptr_etapa[ordem_etapa].realizada = 0; // inicia a etapa como 'por realizar'
    ptr_etapa[ordem_etapa].totalinscritos = 0; // inicia a etapa com 0 inscritos
    etaActCorrente(ptr_etapa, ptr_contador); // verifica qual e proxima etapa corrente
    ptr_contador->grava = 1; // houve alterações, pergunta se quer gravar antes de sair
	auxPausa();
}


void etaActCorrente(etapa_t *ptr_etapa, conta_t *ptr_contador) {
	/*  Actualiza a etapa corrente e certifica-se que é uma etapa q existe
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
            
    int i;

    for ( i = 0 ; i < MAX_ETAPAS; i++) // vai procura a etapa mais proxima por realizar
        if ( ptr_etapa[i].realizada == 0 && ptr_etapa[i].data.ano != 0) {// se não foi realizada 
            ptr_contador->etapa_corrente = i;
            break;
            }
}


void etaEditar(etapa_t *ptr_etapa, conta_t *ptr_contador) {
	/*  Lista as etapas e altera uma à escolha do utilizador
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	int numero_etapa, participantes;
	char confirma, nome_etapa[31];
	
	menuCabecalho(2, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
	printf("\n\n\tEditar Etapa | Listagem por ordem de realizacao");
	
	etaListar(1, ptr_etapa, ptr_contador);
	printf("\n\n");
	
	do {
		numero_etapa = auxLeInteiro("\n\tInsira a ordem da etapa a editar: ", 1, MAX_ETAPAS);
		numero_etapa--; // coloca a variavel no indice correcto
		if (ptr_etapa[numero_etapa].data.ano == 0)
			printf("\tEtapa nao existe.\n");
		}
	while (ptr_etapa[numero_etapa].data.ano == 0);
	
	if (ptr_etapa[numero_etapa].realizada != 1) { // le a designação da etapa
    	auxLeString(2, nome_etapa, "\n\tDesignacao da etapa: ", "\n\tInsira um nome de etapa entre 3 e 30 caracteres.\n", 3, 30);
    	strcpy(ptr_etapa[numero_etapa].nome, nome_etapa);
    	
    	auxLeData(numero_etapa, ptr_etapa); // recebe e valida uma data para a etapa
    	
        do {
            printf("\n\tDeseja alterar as inscricoes actuais na etapa?\n");
            printf("\n\tM - Manter inscricoes\n");
            printf("\tA - Apagar todas as inscricoes (pede novo valor de inscritos)\n");        
            if (ptr_etapa[numero_etapa].participantes < MAX_ETAPAS) // esconde o C no caso de n dar para acrescentar
                printf("\tC - Acrescentar incricoes (mantem as actuais)\n\t");        
            confirma = getch();
    		confirma = toupper(confirma);
    		}
    	while (confirma != 'M' && confirma != 'A' && confirma != 'C');
    		
    	if (confirma == 'A') { // confirma apagar todas as inscrições
            etaLimpaInscricoes(numero_etapa, ptr_etapa); // limpa as inscrições de um piloto
            printf("\n\tInscricoes apagadas...\n");
            participantes = auxLeInteiro ("\tNovo Numero de participantes: ", 0, MAX_PILOTOS_ETAPA); //le um valor inteiro entre o 'menor' e o 'maior' inclusive
            ptr_etapa[numero_etapa].participantes = participantes;
            }
        else
        if (confirma == 'C') { // aumenta o número de inscrições e mantem as actuais
            printf("\n\tAumentar as inscricoes para:");
            participantes = auxLeInteiro (" ", (ptr_etapa[numero_etapa].participantes)+1, MAX_PILOTOS_ETAPA); //le um valor inteiro entre o 'menor' e o 'maior' inclusive
            ptr_etapa[numero_etapa].participantes = participantes;
            printf("\n\tNumero de inscricoes aumentado com sucesso...");
            }
        printf("\n\tEtapa editada com sucesso...");
        }
    else
        printf("\n\tImpossivel editar a etapa porque ja foi realizada...");
    etaActCorrente(ptr_etapa, ptr_contador); // verifica qual e proxima etapa corrente
    ptr_contador->grava = 1; // houve alterações, pergunta se quer gravar antes de sair
	auxPausa();
}


void etaInscreverPiloto(etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Mostra as etapas, inscreve um piloto na etapa escolhida.
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	int verifica_inscrito, indice, num_etapa, numero_aviao;
	char nomenumero[40], nome[40];
	
	menuCabecalho(2, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
	printf("\n\n\tInscrever Piloto em Etapa\n");	
	printf("\n\tEtapas disponiveis:\n"); // lista etapas matriz	etaListar(1, ptr_etapa, ptr_contador);	
	etaListar(1, ptr_etapa, ptr_contador);
	do {
		num_etapa = auxLeInteiro("\n\n\tPretende inscrever piloto na etapa de ordem: ", 0, MAX_ETAPAS); //le a etapa onde se quer inscrever, de entre as possiveis
		num_etapa--; // coloca o valor no indice correcto para trabalhar com o vector
		if (ptr_etapa[num_etapa].data.ano == 0) // se a etapa escolhida não ano definido, não passa ciclo
			printf("\tErro, a etapa que escolheu nao existe...\n");
		else
		if (ptr_etapa[num_etapa].realizada == 1) // se a etapa escolhida está realizada, não passa ciclo
			printf("\tErro, a etapa que escolheu ja se realizou...\n");
		else // se a etapa atingiu o número máximo de inscritos, não passa ciclo
		if (ptr_etapa[num_etapa].totalinscritos >= ptr_etapa[num_etapa].participantes) 
			printf("\tErro, a etapa que escolheu atingiu o limite maximo de inscritos...\n");
		}
	while (ptr_etapa[num_etapa].realizada == 1 || ptr_etapa[num_etapa].data.ano == 0 || (ptr_etapa[num_etapa].totalinscritos >= ptr_etapa[num_etapa].participantes));	
	pilListagem(1, ptr_piloto, ptr_contador); // lista os pilotos para facilitar; valor 1 para lista reduzida	
	do {
		auxLeString(2, nomenumero, "\n\n\tInsira o nome do piloto ou o numero do aviao: ", "Erro, nome ou numero invalido\n", 1, 31);
		indice = pilProcurar(nomenumero, ptr_piloto, ptr_contador);
		if (indice == ERRO_NAOEXISTE) // ==ERRO_NOME removido, para não apresentar duas mensagens de erro.
                                      //   se o nome não pode existir n faz sentido avisar que o piloto n foi encontrado.
			printf("\n\tPiloto nao encontrado...");
		if (indice == ERRO_DUPLICADO) {
			printf("\n\tExiste mais do que um piloto com esse nome\n\tPor favor use o numero de aviao.");
			}
		}
	while (indice == ERRO_NOME || indice == ERRO_NAOEXISTE || indice == ERRO_DUPLICADO);	
	// verifica se o piloto já se encontra inscrito na etapa escolhida
	verifica_inscrito = etaVerificaInscricao(ptr_piloto, ptr_etapa, ptr_piloto[indice].aviao, num_etapa, ptr_contador);
	if (verifica_inscrito == 1) {
		printf ("\n\tErro, o piloto ja esta inscrito nesta etapa...");
		printf ("\n\tPor favor tente de novo.");
		auxPausa();
		}
	else {
		printf("\n\n\tSucesso, inscreveu o piloto na etapa: %s", ptr_etapa[num_etapa].nome);
		ptr_etapa[num_etapa].inscritos[ptr_etapa[num_etapa].totalinscritos] = ptr_piloto[indice].aviao; // guarda o nº do avião nos inscritos
        ptr_etapa[num_etapa].pontos[ptr_etapa[num_etapa].totalinscritos] = 0; // inicia os pontos a zero (causava erros)
        ptr_etapa[num_etapa].tempos[ptr_etapa[num_etapa].totalinscritos] = 0; // inicia o tempo a zero
		ptr_etapa[num_etapa].totalinscritos++;
        printf("\n\tA etapa conta actualmente com %d piloto(s)...\n", ptr_etapa[num_etapa].totalinscritos);
		auxPausa();
		}
    ptr_contador->grava = 1; // houve alterações, pergunta se quer gravar antes de sair
}


void etaDados(etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Lista etapas e mostra os dados de uma delas à escolha do utilizador.
	    Mostra Designação, Ordem da etapa no campeonato, Data, Nº participantes,
	    Nº de inscritos, Pilotos inscritos e, caso já se tenha realizado, Resultados.
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	int indice_aviao, inscritos, j = 5, i, indice;
	char nomenumero[31];
	
	menuCabecalho(2, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
	printf("\n\n\tListagem de Etapas\n");
	etaListar(1, ptr_etapa, ptr_contador);
	
	do {
		auxLeString(2, nomenumero, "\n\n\tInsira o nome da etapa ou a sua ordem:", "Erro, nome ou numero invalido\n", 1, 30);
		indice = etaProcurar(nomenumero, ptr_etapa, ptr_contador);
		if (indice == ERRO_DUPLICADO) {
			printf("\n\tExiste mais do que uma etapa esse nome\n\tPor favor use a ordem de etapa a pesquisa.");
			}
		if (indice == ERRO_NAOEXISTE) // ==ERRO_NOME removido, para não apresentar duas mensagens de erro. 
                                      //  se o nome não pode existir n faz sentido avisar que a etapa n foi encontrada.
			printf("\n\tEtapa nao encontrada...");
		}
	while (indice == ERRO_NOME || indice == ERRO_NAOEXISTE || indice == ERRO_DUPLICADO);
	
	system("cls");
	puts(PROGRAMA);
	printf("\n\tDesignacao da etapa: %s", ptr_etapa[indice].nome);
	printf("\n\tOrdem da etapa no campeonato: %d", ptr_etapa[indice].ordem);
	printf("\t   Data [ %.2d.%.2d.%.4d ]", ptr_etapa[indice].data.dia, ptr_etapa[indice].data.mes, ptr_etapa[indice].data.ano);
	printf("\n\tTem um maximo de %d inscricoes", ptr_etapa[indice].participantes);
	printf(" actualmente com %d", ptr_etapa[indice].totalinscritos);
	if (ptr_etapa[indice].totalinscritos > 0) { // Se não tem inscritos não faz sentido mostrar listas
		printf("\n\n\tLista de pilotos e pontuacoes para a etapa escolhida:");
	    resEtapa (indice, ptr_etapa, ptr_piloto, ptr_contador); // lista etapa
		}
	auxPausa();
}


void pilInscricoes(etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Lista as etapas em que um determinado piloto se inscreveu.
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	int cont=0, indice, i, j; //temp
	char nomenumero[31];
	
	system("cls");
	puts(PROGRAMA);
	printf("\n\n\tInscricoes Pilotos\n");
    pilListagem(1, ptr_piloto, ptr_contador); // lista os pilotos para facilitar; valor 1 para lista reduzida
	printf("\n");
	do {
		auxLeString(2, nomenumero, "\n\tInsira o nome do piloto ou o numero do aviao: ", "Erro, nome ou numero invalido\n", 1, 31);
		indice = pilProcurar(nomenumero, ptr_piloto, ptr_contador);
		if (indice == ERRO_NAOEXISTE) // ==ERRO_NOME removido, para não apresentar duas mensagens de erro.
			printf("\n\tPiloto não encontrado...");
		if (indice == ERRO_DUPLICADO) {
			printf("\n\tExiste mais do que um piloto com esse nome\n\tPor favor use o numero de aviao para a pesquisa.");
			}
		}
	while (indice == ERRO_NOME || indice == ERRO_NAOEXISTE || indice == ERRO_DUPLICADO);

	system("cls");
	puts(PROGRAMA);
	printf("\n\n\tInscricoes Piloto | %s\n\n", ptr_piloto[indice].nome);
	printf("\t\t\t\t\t\t  Etapa  |     Data\n\n");
	
	for (i = 0; i <= MAX_ETAPAS - 1; i++) // de i ate max etapas (-1 para ter indice 9) senao usa o /0 e pumm
		for (j = 0;j <= ptr_etapa[i].participantes;j++) { // de j ate ao numero actual de participantes na etapa i
			if (ptr_etapa[i].inscritos[j] == ptr_piloto[indice].aviao) {// se o vector tiver um inscrito com o numero de aviao do piloto indice
				printf("\t\t\t%31.31s  |  %.2d.%.2d.%.4d\n", ptr_etapa[i].nome, 
                ptr_etapa[i].data.dia, ptr_etapa[i].data.mes, ptr_etapa[i].data.ano);	
				cont++;
                }
			}
	if ( cont == 0 )
        printf("\n\tO piloto escolhido nao esta inscrito em nenhuma etapa...");     
	auxPausa();
}





/*  ###############################################################
                       FUNÇÕES DIVERSAS
    ############################################################### */

void menuCabecalho(int tipo, conta_t *ptr_contador) {
	/*  Mostra o cabeçalho do Programa.
	    Recebe:
	        tipo: inteiro para escolha do submenu
	            tipo 0 : menu principal
	            tipo 1 : menu pilotos
	            tipo 2 : menu etapas
	            tipo 3 : menu resultado
	            tipo 4 : menu estatisticas
	            tipo 5 : gravação
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	    
    int etapas_realizadas;
	
	system("cls");
	puts(PROGRAMA);
	switch (tipo) {
		case 0:
			printf("\n\n\tPilotos Incritos: %.2d/%.2d", ptr_contador->pilotos, MAX_PILOTOS);
            printf("\t\tEtapas Realizadas: %.2d", ptr_contador->realizadas); // 2ª parte do trabalho
			printf("\n\t\t\t\t\t\t     Inseridas: %.2d/%.2d", ptr_contador->etapas, MAX_ETAPAS);
			break;
		case 1:
			printf("\n\n\tPilotos Incritos: %.2d/%.2d", ptr_contador->pilotos, MAX_PILOTOS);
			break;
		case 2:
			printf("\n\n\tEtapas Realizadas/Inseridas: %.2d/%.2d\t\tMaximo: %2d", 
            ptr_contador->realizadas, ptr_contador->etapas, MAX_ETAPAS);
			break;
	/*	case 3:
            if (ptr_contador->etapa_corrente != 0)        
        		printf("\n\n\tEtapa Corrente: %.2d", 
                ptr_contador->etapa_corrente); //inwork so mostra a ordem
			break;*/
		case 4:
			printf("\n\n\tEstatisticas");
			break;
		}
}


void resCabecalho(etapa_t *ptr_etapa, conta_t *ptr_contador) {
    /*  Cabeçalho para o menu Resultados. Independente porque precisa das etapas
        Recebe:
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */

	system("cls");
	puts(PROGRAMA);
    if (ptr_contador->etapa_corrente == 0 || ptr_etapa[ptr_contador->etapa_corrente].realizada == 1) // INWORK =0 n da, se for a primeira
    //  verifica se está sem etapas ou se a ultima etapa já foi lida
        printf("\n\tNenhuma Etapa actualmente em curso");
    else {
		printf("\n\n\tEtapa Corrente: %.2d", ptr_contador->etapa_corrente+1);
        printf(" - %s", ptr_etapa[ptr_contador->etapa_corrente].nome);
        }
}


int pilProcurar(char nomenumero[], ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Procura o indice de um piloto nas fichas de piloto.
	    Recebe:
	        nomenumero: vector de caracteres que recebe o nome ou o número do avião
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    Devolve:
	        i: posição onde encontrou o piloto
	        ERRO_NOME: quando foram introduzidos dados inválidos
	        ERRO_DUPLICADO: quando existem 2 ou mais nomes iguais
	        ERRO_NAOEXISTE: se o nome de piloto ou nº de avião não existe
	    */
	
	int duplicados, i, numero_aviao;
	
	if (strlen(nomenumero) <= 3 && atoi(nomenumero) != 0) { //entao e' um numero de aviao
		numero_aviao = atoi(nomenumero);
		for (i = 0; i < ptr_contador->pilotos; i++) { // procura a posição com o aviao inserido
			if (numero_aviao == ptr_piloto[i].aviao)
				return i;
			}
		}
	else
		if (strlen(nomenumero) <= 3 && atoi(nomenumero) == 0) {
			printf("\tInseriu um nome muito curto, ou um numero de aviao invalido\n");
			return ERRO_NOME;
			}
		else {
			for (i = 0; i < ptr_contador->pilotos; i++) // procura um nome igual
				if (strcasecmp(nomenumero, ptr_piloto[i].nome) == 0) {
					duplicados = pilProcuraDuplicado(ptr_piloto[i].nome, ptr_piloto, ptr_contador);
					if (duplicados == 1)
						return ERRO_DUPLICADO;
					return i;
					}
			}
			
	return ERRO_NAOEXISTE;
}


void auxLeString(int tipo, char texto[], char pergunta[30], char erro[50], int inferior, int superior) {
	/*  Le e valida um vector de caracteres.
	    Recebe:
	        tipo: 1 le só texto
	              2 le texto e numeros
            texto: ponteiro que guarda o texto
	        pergunta: questão a colocar ao utilizador
	        erro: erro a apresentar no caso de leitura inválida
	        inferior: valor minimo de caracteres da frase
	        superior: valor máximo de caracteres da frase
	    */
	
    int i, numero=0;

	do {
		printf("%s ", pergunta);  // mostra a pergunta
		fflush(stdin);
		gets(texto);
        numero = 0;

        if (tipo == 1){ // se for apenas texto
            for (i = 0; i < strlen(texto); i++) // do inicio ate ao final do vector
                if (!isalpha(texto[i])) // verifica se o caracter é alfanumérico
                    numero++;
    		if (numero > 0)
    		    printf("\tErro, introduza apenas texto...\n");
            }

        if ( ( strlen(texto) < inferior || strlen(texto) > superior ) && numero == 0)
			printf("\t%s", erro);
		}
	while (numero > 0 || strlen(texto) < inferior || strlen(texto) > superior);
}


int auxLeInteiro (char pergunta[40], int menor, int maior) {
	/*  Le e valida um número inteiro
	    Recebe:
	        pergunta: questão a colocar ao utilizador
	        menor: valor minimo de caracteres da frase
	        maio: valor máximo de caracteres da frase
	    Devolve:
	        cont: valor do inteiro depois de validado
	    */
	
	int comp = 0, cont = 0, aux;
	char astring[10]; // string usada para ler valor inteiro
	
	do {
		cont = comp = 0;
		printf("%s", pergunta);
		fflush(stdin);
		//gets(astring);
		scanf("%10[^\n]", astring);
		cont = atoi(astring); // converte a string para um inteiro, sem os caracteres misturados
		aux = cont; // cria um auxiliar para n alterar o valor do cont
		while (aux > 0) { // comp conta o numero de digitos do numero, dividindo por 10
			comp++;
			aux /= 10;
			} // vai comparar o comprimento da string inicial com caracteres com o comprimento do numero convertido
		if (strlen(astring) != comp || cont == 0 || cont < menor || cont > maior)
			printf("\tValor incorrecto. Entre %d e %d", menor, maior);
		} while (strlen(astring) != comp || cont == 0 || cont < menor || cont > maior); // se os comprimentos n forem iguais, n colocou um numero
		
	return(cont); // devolve inteiro validado
}


void etaListar(int tipo, etapa_t *ptr_etapa, conta_t *ptr_contador) {
	/*  Mostra uma lista de etapas para auxílio em funções
	    Recebe:
	        tipo: 1: mostra todas as etapas
                  2: mostra apenas as realizadas
            ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	int inscritos, i;
	
	printf("\n\n\t\t           Designacao |  Ordem  |     Data       | Pilotos\n");
	
    if (tipo == 1){
        for (i = 0; i <= MAX_ETAPAS - 1; i++) {  // tem que usar max etapas pq senao salta ordens de etapa n usadas
        	if (ptr_etapa[i].data.ano != 0) { // se a etapa tem dados, mostra no ecra
        		printf("\n\t\t %20.20s |     %.2d  |  %.2d.%.2d.%.4d ", ptr_etapa[i].nome, ptr_etapa[i].ordem, 
                ptr_etapa[i].data.dia, ptr_etapa[i].data.mes, ptr_etapa[i].data.ano); 
                if ( ptr_etapa[i].realizada == 1)
                    printf(" R"); // mostra R ou outro simbolo para etapas realizadas
                else
                    printf("  ");
                printf("  |  %.2d/%.2d    ", ptr_etapa[i].totalinscritos, ptr_etapa[i].participantes);
        		}
        	if (i != 0 && i % 10 == 0) // de 10 em 10 nomes, faz uma pausa para o utilizador ver os nomes, ignora o 0 porque senão pausa na primeira linha
        		auxPausa();
        	}
         }
    else
    if (tipo == 2) {
        for (i = 0; i <= MAX_ETAPAS - 1; i++) {  // tem que usar max etapas pq senao salta ordens de etapa n usadas
        	if (ptr_etapa[i].data.ano != 0 && ptr_etapa[i].realizada == 1) { 
        		//inscritos = auxCompVector(ptr_etapa[i].inscritos, 20);
        		printf("\n\t\t %20.20s |     %.2d  |  %.2d.%.2d.%.4d  R", ptr_etapa[i].nome, ptr_etapa[i].ordem, 
                ptr_etapa[i].data.dia, ptr_etapa[i].data.mes, ptr_etapa[i].data.ano); 
                printf("  |  %.2d/%.2d    ", ptr_etapa[i].totalinscritos, ptr_etapa[i].participantes);
        		}
        	if (i != 0 && i % 10 == 0) // de 10 em 10 nomes, faz uma pausa para o utilizador ver os nomes, ignora o 0 porque senão pausa na primeira linha
        		auxPausa();
        	}
         }
}


int etaProcurar(char nomenumero[40], etapa_t *ptr_etapa, conta_t *ptr_contador) {
	/*  Analisa o nome ou ordem de uma etapa e devolve o indice desta.
	    Recebe:
	        nomenumero: vector de caracteres que recebe o nome ou ordem da etapa
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    Devolve:
	        i: posição onde encontrou a etapa
	        ERRO_NOME: quando foram introduzidos dados inválidos
	        ERRO_DUPLICADO: quando existe mais do que uma etapa com o mesmo nome
	        ERRO_NAOEXISTE: se o nome da etapa ou ordem não existe
	    */
	
	int duplicados, i, ordem_etapa;
	
	if (strlen(nomenumero) <= 2 && atoi(nomenumero) != 0) { //entao e' ordem de etapa
		ordem_etapa = atoi(nomenumero);
		if (ptr_etapa[ordem_etapa-1].data.ano != 0 && ordem_etapa<=MAX_ETAPAS)// a ordem da etapa pode corresponder a uma etapa vazia
			return ordem_etapa -1; // devolve o indice, nao a ordem
		else
			return ERRO_NAOEXISTE;
		}
	else
	if (strlen(nomenumero) <= 2 && atoi(nomenumero) == 0) {
		printf("\tInseriu um nome muito curto, ou uma ordem invalida\n");
		return ERRO_NOME;
		}
	else {
		for (i = 0; i <= MAX_ETAPAS; i++) // procura um nome igual
			if (strcasecmp(nomenumero, ptr_etapa[i].nome) == 0) { // compara as strings case insensitive
				duplicados = etaProcuraDuplicada(ptr_etapa[i].nome, ptr_etapa);
				if (duplicados == 1)
					return ERRO_DUPLICADO;
				return i; // devolve o indice com o nome inserido
	      		}
		}
	return ERRO_NAOEXISTE;
}


void auxLeData(int numero_etapa, etapa_t *ptr_etapa) {
	/*  Le uma data válida para inserir uma etapa.
	    Recebe:
	        numero_etapa: indice da etapa em questão (não ordem, indice=ordem-1)
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	
	int i, passaciclo = 1, dataactual_dias, datainserida_dias, etapaseguinte_dias,
						etapaanterior_dias, etapa_anterior, etapa_seguinte;
	data_t data_inserida;
	
	// declarações para data do sistema
	time_t  dataactual;
	struct tm *infodata;
	char string_data[32] = {0};
	
	time(&dataactual);
	infodata = localtime(&dataactual);
	
	// INWORK considera todos os meses com 30 dias
	infodata->tm_mon++; //corrige bug mes
	dataactual_dias = ( ((infodata->tm_mon) - 1) * 30 + (infodata->tm_mday) + ((infodata->tm_year + 1900) - 1) * 365 );
	
	do {
		data_inserida.ano = auxLeInteiro("\n\tData da etapa, ano: ", 2010, 2100);
		data_inserida.mes = auxLeInteiro("\tData da etapa, mes: ", 1, 12);
		switch (data_inserida.mes) {
			case 2: 
					data_inserida.dia = auxLeInteiro("\tData da etapa, dia: ", 1, 28);
					break;
					
			case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:                                                           
					data_inserida.dia = auxLeInteiro("\tData da etapa, dia: ", 1, 31);
					break;
			default: 
					data_inserida.dia = auxLeInteiro("\tData da etapa, dia: ", 1, 30);
					break;
					
			}

		datainserida_dias = ( ((data_inserida.mes) - 1) * 30 + (data_inserida.dia) + ((data_inserida.ano) - 1) * 365 );

		// vai verificar se a data esta' entre a data da etapa anterior e da etapa seguinte
		// obtem a contagem de dias para a etapa seguinte
		if (numero_etapa + 1 == MAX_ETAPAS) { // se inseriu a ultima etapa
			etapaseguinte_dias = DIAS_MAX;  // se nao tem nenhum etapa seguinte, guarda um valor mais alto imaginario
			etapa_seguinte = ETAPA_EXTREMO;
            }
		else
			for (i = numero_etapa + 1; i < MAX_ETAPAS; i++) {
				if (ptr_etapa[i].data.ano != 0) {
					etapaseguinte_dias =  ( ((ptr_etapa[i].data.mes) - 1) * 30 + (ptr_etapa[i].data.dia) + ((ptr_etapa[i].data.ano) - 1) * 365 );
					etapa_seguinte = i; // guarda o indice da etapa seguinte para mostrar no caso de erro
					i = MAX_ETAPAS; //se encontrou uma etapa seguinte, sai do ciclo
					}
				else {
					etapaseguinte_dias = DIAS_MAX;
					etapa_seguinte = ETAPA_EXTREMO; // uma etapa que está em primeiro ou ultimo lugar
					}
				}
		if (numero_etapa == 0) { // se esta a referir-se à primeira etapa
			etapaanterior_dias = DIAS_MIN; // se nao tem nenhum etapa antes, guarda o valor mais baixo e aceita todas
			etapa_anterior = ETAPA_EXTREMO;
            }
		else
			for (i = numero_etapa - 1; i >= 0; i--) { 
				if (ptr_etapa[i].data.ano != 0) {
					etapaanterior_dias =  ( ((ptr_etapa[i].data.mes) - 1) * 30 + (ptr_etapa[i].data.dia) + ((ptr_etapa[i].data.ano) - 1) * 365 );
					etapa_anterior = i; // guarda o indice da etapa seguinte para mostrar no caso de erro
					i = 0; //se encontrou uma etapa anterior, i=0 para sair o ciclo for
					}
				else {
					etapaanterior_dias = DIAS_MIN;
					etapa_anterior = ETAPA_EXTREMO; // uma etapa que está em primeiro ou ultimo lugar
					}
				}
				
		if (dataactual_dias > datainserida_dias) {
			printf("\n\tErro, inseriu uma data passada...");
			passaciclo = 0;
			}
		else
			if ( (datainserida_dias > dataactual_dias) &&
                 (datainserida_dias > etapaanterior_dias) && (datainserida_dias < etapaseguinte_dias) )
				passaciclo = 1;
			else {
				printf("\n\tData Invalida, para inserir a etapa na ordem %d,", numero_etapa + 1);
				if (etapa_anterior != ETAPA_EXTREMO && etapa_seguinte != ETAPA_EXTREMO) {
					printf("\n\ttem que escolher uma data entre a etapa de %s e %s.",
                           ptr_etapa[etapa_anterior].nome, ptr_etapa[etapa_seguinte].nome);
					printf("\n\tOu seja entre %d.%d.%d e", ptr_etapa[etapa_anterior].data.dia,
                           ptr_etapa[etapa_anterior].data.mes, ptr_etapa[etapa_anterior].data.ano);
					printf(" %d.%d.%d\n", ptr_etapa[etapa_seguinte].data.dia,
                           ptr_etapa[etapa_seguinte].data.mes, ptr_etapa[etapa_seguinte].data.ano);
					}
				else
				if (etapa_anterior != ETAPA_EXTREMO) {
					printf("\n\ttem que escolher uma etapa posterior a %s.", ptr_etapa[etapa_anterior].nome);
					printf("\n\tOu seja com data depois de %d.%d.%d e", ptr_etapa[etapa_anterior].data.dia,
                           ptr_etapa[etapa_anterior].data.mes, ptr_etapa[etapa_anterior].data.ano);
                    }
                else
				if (etapa_seguinte != ETAPA_EXTREMO) {
					printf("\n\ttem que escolher uma etapa anterior a %s.", ptr_etapa[etapa_seguinte].nome);
					printf("\n\tOu seja com data antes de %d.%d.%d e", ptr_etapa[etapa_seguinte].data.dia,
                           ptr_etapa[etapa_seguinte].data.mes, ptr_etapa[etapa_seguinte].data.ano);
                    }
				passaciclo = 0;
				}
		}
	while (passaciclo != 1);
	
	//guarda os valores da data depois de validados
	ptr_etapa[numero_etapa].data.ano = data_inserida.ano;
	ptr_etapa[numero_etapa].data.mes = data_inserida.mes;
	ptr_etapa[numero_etapa].data.dia = data_inserida.dia;
}


int pilIndiceAviao(int numero_aviao, ficha_t *ptr_piloto, conta_t *ptr_contador) { 
	/*  Procura o avião indicado na lista de pilotos e devolve o indice correspondente.
	    Recebe:
	        numero_aviao: número do avião a pesquisar
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	    Devolve:
	        i: indice correspondente ao avião
	    */
	
	int i;
	
	for (i = 0; i < ptr_contador->pilotos; i++)
		if (ptr_piloto[i].aviao == numero_aviao)
			return i;
}


void auxPausa() {
     // Muda de linha e pausa o sistema.

	printf("\n\n\t");
	system("PAUSE");
	}


int etaVerificaInscricao(ficha_t *ptr_piloto, etapa_t *ptr_etapa, int aviao_piloto, int indice_etapa, conta_t *ptr_contador) {
	/*  Verifica se o avião está inscrito numa etapa ou qualquer outra etapa.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_etapa: vector ponteiro com a lista de etapas
	        aviao_piloto: número do avião a pesquisar
	        indice_etapa: indice da etapa que queremos verificar
            ptr_contador: estrutura que contem os contadores de pilotos e etapas
	    Devolve:
	        0: se o piloto não tem qualquer inscrição
	        1: se o piloto está inscrito na etapa recebida
	        -1: se o piloto está inscrito em qualquer outra etapa
	        -2: se o piloto está inscrito numa etapa já realizada
	    */
	
	int i, j, aux=1;
	
	if (indice_etapa < MAX_ETAPAS) // se for maior do que max_etapas, não estamos a comparar com um etapa, estamos so a ver se esta inscrito em alguma
		for (i = 0; i < ptr_contador->pilotos; i++) // ve se esta' inscrito na etapa dada
			if (ptr_etapa[indice_etapa].inscritos[i] == aviao_piloto)
				return 1;
				
	for (i = 0; i <= MAX_ETAPAS - 1; i++) // ve se esta' inscrito em qualquer etapa
		for (j = 0;j <= MAX_PILOTOS_ETAPA - 1;j++)
			if (ptr_etapa[i].inscritos[j] == aviao_piloto && ptr_etapa[i].realizada == 1)
				return -2;
			else
			if (ptr_etapa[i].inscritos[j] == aviao_piloto && ptr_etapa[i].realizada == 0)
				return -1;			
			else
				aux = 0;
	return aux;
}


int pilProcuraDuplicado(char nomenumero[], ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Verifica se existe mais do que um piloto com o mesmo nome.
	    Recebe:
	        nomenumero: Nome do Piloto
	        ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: estrutura que contem os contadores de pilotos e etapas
	    Devolve:
	        1: Se existe algum nome repetido
	        0: Se o nome é único	        
	    */
	    
	int contador = 0, i;
	
	for (i = 0; i < ptr_contador->pilotos; i++) // de 0 ate ao numero actual de pilotos, percorre o indice
		if (strcasecmp(nomenumero, ptr_piloto[i].nome) == 0) // e se o nome recebido for igual ao guarda na estrutura
			contador++; // incrementa o contador de nomes iguais, faz sentido se mais tarde precisar de verificar quandos
	if (contador > 1) { //  (cont)pilotos existem com o mesmo nome
		return 1; // existem nomes repetidos
		}
	return 0; // o nome é unico
}


int etaProcuraDuplicada(char nomenumero[], etapa_t *ptr_etapa) {
	/*  Verifica se existe mais do que uma etapa com o mesmo nome.
	    Recebe:
	        nomenumero: Designação da etapa
	        ptr_etapa: vector ponteiro com a lista de etapas
	    Devolve:
	        1: Se existe algum nome repetido
	        0: Se o nome é único	        
	    */
	    
	int contador = 0, i;
	
	for (i = 0; i < MAX_ETAPAS; i++) // percorre todas as etapas
		if (strcasecmp(nomenumero, ptr_etapa[i].nome) == 0) // e procura nomes iguais
			contador++;
	if (contador > 1) {
		return 1;
		}
	return 0;
}


int etaInscricoesVagas(etapa_t *ptr_etapa, conta_t *ptr_contador) {
	/*  Conta o número de vagas do campeonato, em todas as etapas.
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas.
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos.
	    Devolve:
	        contador: Número de inscrições máximo possivel.
	    */

	int i, j, contador = 0;
	
	for (i = 0; i < MAX_ETAPAS; i++) // percorre todas as etapas
		for (j = 0; j <= (ptr_etapa[i].participantes) - 1; j++) // percorre o vector que está dentro das etapas
			if (ptr_etapa[i].inscritos[j] == 0) // se não tem um aviao na posição j dos inscritos
				contador++; // conta +1 vaga
	return contador;
}


void etaLimpaInscricoes(int indice_etapa, etapa_t *ptr_etapa) {
	/*  Apaga todas as inscrições de uma etapa.
	    Recebe:
            indice_etapa: Indice da etapa a limpar.
	        ptr_etapa: Vector ponteiro com a lista de etapas.
	    */
             
     int i;
     
     for(i = 0; i < ptr_etapa[indice_etapa].participantes; i++) // do indice 0 ao número de participantes-1
           ptr_etapa[indice_etapa].inscritos[i] = 0; // limpa a inscrição
}


int etaNumRealizadas(etapa_t *ptr_etapa) {
	/*  Conta o número de etapa realizadas para apresentar no menu principal.
	    Recebe:
	        ptr_etapa: vector ponteiro com a lista de etapas.
	    Devolve:
	        cont: Número de etapas realizadas.
	    */
            
    int i, cont=0;
    
    for( i=0 ; i< MAX_ETAPAS ; i++ ) // percorre todas as etapas
        if( ptr_etapa[i].realizada == 1 ) // se está realizada
            cont++; // inscrementa
 
    return cont;
}


int etaProcuraPiloto (int etapa, int aviao, etapa_t *ptr_etapa) {
	/*  Procura um piloto dentro da etapa especificada.
	    Recebe:
	        etapa: etapa onde vai procurar o piloto
	        aviao: número do avião do piloto
            ptr_etapa: vector ponteiro com a lista de etapas.
	    Devolve:
	        i: indice do aviao no menu etapa.inscritos
	        ERRO_NAOEXISTE: se o piloto não está inscrito na estapa
	    */
        	
	int i;

    for ( i = 0 ; i < MAX_PILOTOS_ETAPA ; i++) // de 0 ao maximo de pilotos por etapa
        if ( ptr_etapa[etapa].inscritos[i] == aviao ) // se encontrou um piloto com o aviao dado
            return i; // devolve o indice no vector de inscritos

    return ERRO_NAOEXISTE;
}


void pilMostraInscricoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, int indice, int tipo){
	/*  Mostra uma lista com as inscrições de um piloto.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            indice: indice do piloto a mostras
            tipo: 2 para lista com nome e data
                  1 para lista com etapa e pontuações
	    */     
     
    int i, j;
    
    if (tipo == 1){
        printf("\n\t\t\t\t\t   Etapa | Posicao | Pontuacao\n\n");
        
        
        for (i = 0; i < MAX_ETAPAS; i++) // de i ate max etapas 
            for (j = 0;j < ptr_etapa[i].participantes;j++)  // de j ate ao numero actual de participantes na etapa i
            	if (ptr_etapa[i].inscritos[j] == ptr_piloto[indice].aviao) {  // se o vector tiver um inscrito com o numero de aviao do piloto indice
                    if ( ptr_etapa[i].realizada == 1 ) // se a etapa já tem pontos e posição ( se esta realizada )
                		printf("\t\t%31.31s  |    %2.d   |    %3.d\n", ptr_etapa[i].nome, j+1 ,ptr_etapa[i].pontos[j]);
                    else // se n está realizada, mostra não disponivel
                        printf("\t\t%31.31s  |   N/D   |     N/D \n", ptr_etapa[i].nome);
                    }
        }
    else
    if (tipo == 2){
        printf("\n\t\t\t\t\t  Etapa  |   Data\n\n");
        for (i = 0; i < MAX_ETAPAS; i++) // de i ate max etapas
            for (j = 0;j < ptr_etapa[i].participantes;j++)  // de j ate ao numero actual de participantes na etapa i
            	if (ptr_etapa[i].inscritos[j] == ptr_piloto[indice].aviao)  // se o vector tiver um inscrito com o numero de aviao do piloto indice
            		printf("\t\t%31.31s  | %.2d.%.2d.%d\n", ptr_etapa[i].nome,
                    ptr_etapa[i].data.dia, ptr_etapa[i].data.mes, ptr_etapa[i].data.ano);
        }
       		
}


void pilLimpaInscricoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, int indice){
	/*  Limpa as inscrições de um piloto em todas as etapas.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            indice: indice do piloto a mostras	        
	    */
	    
	int inscritos, i, j, k;
    
    for (i = 0; i < MAX_ETAPAS; i++) 
		for (j = 0; j < ptr_etapa[i].participantes; j++)  // de j ate ao numero actual de participantes na etapa i
            if (ptr_etapa[i].inscritos[j] == ptr_piloto[indice].aviao){ // se o vector tiver um inscrito com o numero de aviao do piloto indice
                ptr_etapa[i].totalinscritos--; // decrementa um inscrito, porque encontrou o aviao no vector
                for (k = j; k < ptr_etapa[i].totalinscritos; k++) // da posição actual até ao ultimo inscrito
                    ptr_etapa[i].inscritos[k] = ptr_etapa[i].inscritos[k+1];
                }
}


ficha_t *pilApaga(ficha_t *ptr_piloto, conta_t *ptr_contador, int indice){
	/*  Apaga o registo de um piloto.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            indice: indice do piloto a mostras	        
	    */     

    int i;

    for (i = indice; i < ptr_contador->pilotos; i++) { // percorre a estrutura de pilotos passa todos os valores 1 indice para tras
        strcpy(ptr_piloto[i].nome, ptr_piloto[i+1].nome);
        ptr_piloto[i].idade = ptr_piloto[i+1].idade;
        ptr_piloto[i].aviao = ptr_piloto[i+1].aviao;
        }

    ptr_contador->pilotos--; // decrementa os pilotos depois de eliminar com sucesso.
    ptr_piloto = (ficha_t*)realloc(ptr_piloto, (ptr_contador->pilotos)*sizeof(ficha_t)); // e realoca a memória para o número actual de pilotos

    return ptr_piloto;
}


char resMenu(conta_t *ptr_contador, etapa_t *ptr_etapa) {
	/*  Mostra o menu de Resultados no ecrã.
	    Recebe:
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    Devolve:
	        op: letra/opção introduzida pelo utilizador
	    */
	
	char op;
	
	do {
		resCabecalho(ptr_etapa, ptr_contador); 
		printf("\n\n\tR - Resultados da Etapa Corrente");
		printf("\n\tA - Alterar Resultados de uma Etapa");
		printf("\n\tO - Consultar Resultados de uma Etapa");
		printf("\n\tC - Classificacao Final");
		printf("\n\n\tV - Voltar ao Menu Principal");
		fflush(stdin);
		op = getch();
		op = toupper(op);
		}
	while (op != 'V' && op != 'R' && op != 'A' && op != 'O' && op != 'C');
	
	return op;
}


void resFuncoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, char op, conta_t *ptr_contador) {
	/*  Recebe a opção escolhida e direcciona para a função a usar.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_etapa: vector ponteiro com a lista de etapas
	        op: letra/opção escolhida na função pilMenu
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
    
    int vagas, aux;
    
    aux = etaNumRealizadas(ptr_etapa);	

	switch (op) {
		case 'R':  // le os valores da etapa corrente
					resLeCorrente(ptr_etapa, ptr_piloto, ptr_contador);
                    break;
	
		case 'A':  // se existe uma ou mais etapas realizadas, permite alteração
                    if ( aux > 0 )
                        resAlterarResultados(ptr_etapa, ptr_piloto, ptr_contador);
                    else {
                        printf("\n\n\tNao existem etapa realizadas para editar...");
                        auxPausa();
                        }
                    break;				

		case 'O':  //se existe uma ou mais etapas realizadas, consulta 
                    if ( aux > 0 )
                        resConsultar (ptr_etapa, ptr_piloto, ptr_contador);
                    else {
                        printf("\n\n\tAinda nao existem etapa realizadas...");
                        auxPausa();
                        }
                    break;	
				
		case 'C':  // se existem uma ou mais etapas realizadas, mostra classificação
                    if ( aux > 0 ) {
                        estMostraClassificacao (1, ptr_piloto, ptr_contador); // listagem simples sem opções
                        auxPausa();
                        }
                    else {
                        printf("\n\n\tAinda nao existem etapa realizadas...");
                        auxPausa();
                        }
                    break;
		}
}


void resLeCorrente(etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Verifica a Etapa corrente e recebe os tempos dados pelo utilizador.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	    
    int i, totalpilotos, etapa, piloto, resultado;
    
  	resCabecalho(ptr_etapa, ptr_contador); 
    etapa = ptr_contador->etapa_corrente; // guarda o indice da etapa em questao
    if ( ptr_etapa[etapa].totalinscritos == 0) //se a etapa n tem inscritos, para logo.
        printf("\n\n\tA etapa corrente nao tem inscritos, adicione pilotos primeiro...");
    else
    if ( ptr_etapa[etapa].realizada == 1) // se esta realizada não lê nada
        printf("\n\n\tJa leu resultados para todas as etapas...");
    else {
        printf("\n\n\tResultados da Etapa: %s \n\tTotal Inscritos: %d\n", ptr_etapa[etapa].nome, ptr_etapa[etapa].totalinscritos);
        resLeTempos(etapa, ptr_etapa, ptr_piloto, ptr_contador); // le e preenche os tempos
        printf("\n\n\tValores recolhidos com sucesso...");
        for ( i=etapa+1 ; i < MAX_ETAPAS; i++)
            if (ptr_etapa[i].realizada != 1 && ptr_etapa[i].data.ano!=0) { // procura a proxima etapa inserida
               ptr_contador->etapa_corrente = i; // guarda o indice da proxima etapa valida
               break;
               }
        ptr_etapa[etapa].realizada = 1;
        ptr_contador->grava = 1; // houve alterações, pergunta se quer gravar antes de sair
        }
    auxPausa();
}


void resLeTempos(int etapa, etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
	/*  Lista o nome do piloto e Recebe o valor do tempo no formato mm.ss,mseg.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_etapa: vector ponteiro com a lista de etapas
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
             
    int piloto, totalpilotos, i, resultado;

    printf("\n\tInsira os valores do piloto: [ Exemplo 00:00.000 ]");
    for (i = 0 ; i < ptr_etapa[etapa].totalinscritos; i++) { // percorre todos os inscritos
        piloto = pilIndiceAviao(ptr_etapa[etapa].inscritos[i], ptr_piloto, ptr_contador); // guarda o indice do piloto
        do {
            printf("\n\t%.3d | %s : ", ptr_piloto[piloto].aviao, ptr_piloto[piloto].nome); // mostra o nome
            resultado = resLeSegundos(); // le e valida o tempo, devolve em msegs
            if ( resultado == 0) // se devolveu 0, colocou valores errados e volta a pedir
                printf("\tValor Invalido.");
            }
        while( resultado == 0);
        ptr_etapa[etapa].tempos[i] = resultado; // se passou o ciclo, tem tempo valido, guarda o resultado
        }
    fflush(stdin);
    resOrdenaTempos (etapa, ptr_etapa); // ordena logo os vectores crescentemente tendo em conta os tempos
    fflush(stdin);
    resPontuacao (etapa, ptr_piloto, ptr_etapa, ptr_contador); // preenche logo as pontuações para a etapa
}


int resLeSegundos() {
    /*  Le um valor de tempo no formato mm.ss,mseg. e transforma em milesimos de segundo para guardar no vector etapas
        Devolve:
            total: valor lido e transformado em milesimos de segundo
        */

    int aux=0, valido=0;
    int min, seg, mseg, total;

    fflush(stdin);
    aux = scanf("%2d:%2d.%d", &min, &seg, &mseg);

    if (min < 0 || seg < 0 || mseg <0 )
        valido++; // encontrou erro com valores negativos 
    if (min > 59 || seg > 60 || mseg > 999 )
        valido++; // encontrou valores impossiveis
    if ( aux != 3)
        valido++; // encontrou um erro de leitura com virgula e ponto

    if ( valido != 0) // se alguma das validações tinha erro
        return 0; // devolve valor invalido

    total = mseg + seg*1000 + min*60*1000;
    return total; // devolve total convertido em ms
}


void resAlterarResultados (etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Lista as etapas e permite alterar os resultados de uma delas à escolha do utilizador.
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */

    int i, etapa;
    
    resCabecalho(ptr_etapa, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
    printf("\n\tEscolha a etapa para alterar resultados:");
    etaListar(2, ptr_etapa, ptr_contador);
	do {
		etapa = auxLeInteiro("\n\tInsira a ordem da etapa a editar: ", 1, ptr_contador->etapa_corrente+1);
		etapa--; // coloca a variavel no indice correcto
		if (ptr_etapa[etapa].data.ano == 0) // verifica se a etapa existe
			printf("\tEtapa nao existe.\n");
		else
		if (ptr_etapa[etapa].realizada == 0) // verifica se esta realizada
			printf("\tEssa etapa ainda nao esta realizada.\n");

		}
	while (ptr_etapa[etapa].data.ano == 0 || ptr_etapa[etapa].realizada == 0);  
	fflush(stdin);	
    resRemPontuacao (etapa, ptr_piloto, ptr_etapa, ptr_contador); // remove os pontos anteriores
	fflush(stdin);	
    resLeTempos(etapa, ptr_etapa, ptr_piloto, ptr_contador); // le os novos tempos e distribui a pontuação
    printf("\n\tEtapa alterada com sucesso....");
    ptr_contador->grava = 1; // houve alterações, pergunta se quer gravar antes de sair
    auxPausa();
}


void resOrdenaTempos (int etapa, etapa_t *ptr_etapa) {
    /*  Ordena todos os tempos recebidos crescentemente e actualiza as posições no vector de inscritos.
        Mantem os tempos, aviao e pontos no mesmo indice para fazer correspondecia.
        Recebe:
            etapa: Indice da etapa a ordenar
            ptr_etapa: vector ponteiro com a lista de etapas
        */
        
    int aux, aux2, aux3, ha_trocas,totalpilotos, i,j; 

    for( i = 0; i < ptr_etapa[etapa].totalinscritos && ha_trocas; i++){
        ha_trocas = 0;
        
        for ( j = 0; j < ptr_etapa[etapa].totalinscritos - i - 1; j++)
            if( ptr_etapa[etapa].tempos[j] > ptr_etapa[etapa].tempos[j+1]){ // Inverte para decrescemaxte
                ha_trocas=1;

                aux=ptr_etapa[etapa].tempos[j]; //guarda o aviao
                aux2=ptr_etapa[etapa].inscritos[j]; // guarda o tempo
                aux3=ptr_etapa[etapa].pontos[j]; // guarda os pontos
                
                ptr_etapa[etapa].tempos[j]=ptr_etapa[etapa].tempos[j+1]; // troca o numero do aviao
                ptr_etapa[etapa].inscritos[j]=ptr_etapa[etapa].inscritos[j+1]; // troca o tempo
                ptr_etapa[etapa].pontos[j]=ptr_etapa[etapa].pontos[j+1]; // troca os pontos
                
                ptr_etapa[etapa].tempos[j+1]=aux;
                ptr_etapa[etapa].inscritos[j+1]=aux2;
                ptr_etapa[etapa].pontos[j+1]=aux3;
                
                }
        }
}


void resPontuacao (int etapa, ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador) {
    /*  Preenche o vector das pontuações para a etapa indicada, le os tempos.
        Recebe:
            etapa: Etapa a pontuar.
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: estrutura que contem os contadores de pilotos e etapas
        */ 
    
    int indice, i, pontos=10;   
    
    // do primeiro ao sexto classificado
    for (i = 0; i < 6;i++){
        indice = pilIndiceAviao(ptr_etapa[etapa].inscritos[i], ptr_piloto, ptr_contador);
        if ( ptr_etapa[etapa].inscritos[i] != 0 ) {// se existe um piloto para pontuar
            if ( i != 5 ) { // se for 1 dos 5 primeiros tempos
                ptr_piloto[indice].pontos += pontos; // aumenta os pontos do piloto
                ptr_etapa[etapa].pontos[i] = pontos; // pontua a etapa
                pontos-=2; // o proximo piloto vai ter -2 pontos
                }
            else { // se for o 6º classificado, atribui 1 ponto
                ptr_etapa[etapa].pontos[i] = 1;
                ptr_piloto[indice].pontos += 1;
                }
            }
        }
}


void resRemPontuacao (int etapa, ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador) {
    /*  Limpa as pontuações atribuidas a pilotos e etapa, 
        usada quando se pretende alterar os resultados de uma etapa.
        Recebe:
            etapa: Indice da etapa onde vai limpar os valores
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: estrutura que contem os contadores de pilotos e etapas
        */    
    int indice, i, pontos=10;   
    
    
    // do primeiro ao sexto classificado
    for (i = 0; i < 6;i++){
        indice = pilIndiceAviao(ptr_etapa[etapa].inscritos[i], ptr_piloto, ptr_contador);
        if ( i != 5) {
            ptr_piloto[indice].pontos -= pontos;
            ptr_etapa[etapa].pontos[i] = 0;
            pontos-=2;
            }
        else { // se for o 6º classificado, atribui 1 ponto
            ptr_etapa[etapa].pontos[i] = 0;
            ptr_piloto[indice].pontos -= 1;
            }
        }
}


void resConsultar (etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Lista etapas, recebe a ordem da etapa a visualizar e chama a função que mostra os resultados.
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */

    int pontos, tempo, totalpilotos, etapa, i;
    
    resCabecalho(ptr_etapa, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
    printf("\n\tEscolha a etapa para consultar resultados:");
    etaListar(2, ptr_etapa, ptr_contador);
	do { // INWORK mudar verificação para se esta realizada ou nao, pode ler de 1 a max_etapas pq depois vai dar erro na mesma
		etapa = auxLeInteiro("\n\tInsira a ordem da etapa: ", 1, MAX_ETAPAS);
		etapa--; // coloca a variavel no indice correcto
		if (ptr_etapa[etapa].data.ano == 0)
			printf("\tEtapa nao existe.\n");
        if (ptr_etapa[etapa].realizada == 0)
			printf("\tErro, Etapa por realizar.\n");
		}
	while (ptr_etapa[etapa].data.ano == 0 || ptr_etapa[etapa].realizada == 0); 
        
    resEtapa(etapa, ptr_etapa, ptr_piloto, ptr_contador);
    auxPausa();
}


void resEtapa (int etapa, etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Mostra os dados de um etapa realizada, Nº Aviao, Nome do Piloto, Tempo e Pontos.
        Ordenado pela classificação.
        Recebe:
            etapa: Indice da etapa a listar
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */
        
    int piloto, i, totalpilotos;
    tmp_t tempo;

	printf("\n\n\t  Aviao |\t\t\t     Nome |   Tempo   | Pontos\n");
    for (i=0; i< ptr_etapa[etapa].totalinscritos; i++) {
        piloto = pilIndiceAviao(ptr_etapa[etapa].inscritos[i], ptr_piloto, ptr_contador); // guarda o indice do piloto 
        tempo = auxConverteMseg( ptr_etapa[etapa].tempos[i] ); // converte o tempo para min/seg/mseg para mostrar no ecra
        printf("\n\t    %.3d | %31.31s | ", ptr_etapa[etapa].inscritos[i], ptr_piloto[piloto].nome); //inwork
        printf("%.2d:%.2d.%.3d |", tempo.min, tempo.seg, tempo.mseg);
        printf(" %d", ptr_etapa[etapa].pontos[i]);
        }
}


tmp_t auxConverteMseg (int tempo_mseg) {
    /*  Converte o tempo de milesimos de segundos para o formato mm.ss,mseg
        de modo a imprimir no ecrã
        Recebe:
            tempo_mseg: Inteiro com o tempo em msegundos, guardado na estrutura etapas.
        Devolve:
            tempo: Estrutura tempo com os minutos, segundos e milesimos de segundos separados
        */
        
    tmp_t tempo;
    float min, seg, mseg;

    min = tempo_mseg / (1000 * 60);
    seg = tempo_mseg - ( min * 60 * 1000 );
    mseg = seg - ( ((int)seg/1000) * 1000 );

    tempo.min = (int)min;
    tempo.seg = (int)seg/1000;
    tempo.mseg = (int)mseg;
    
    return tempo;
}
    

void resOrdenaClass (ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Ordena a Classificação Geral do campeonato, com os valores guardados em cada piloto
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
        */
        
    ficha_t aux;
    int i, j, ha_trocas,posmenor;

    for( i = 0; i < ptr_contador->pilotos && ha_trocas; i++){
        ha_trocas = 0;
        for ( j = 0; j < ptr_contador->pilotos - i - 1; j++)
            if( ptr_piloto[j].pontos < ptr_piloto[j+1].pontos){ 
                ha_trocas=1;
                
                strcpy(aux.nome, ptr_piloto[j].nome);
                aux.aviao = ptr_piloto[j].aviao;
                aux.idade = ptr_piloto[j].idade;
                aux.pontos = ptr_piloto[j].pontos;
    
                strcpy(ptr_piloto[j].nome,ptr_piloto[j+1].nome);
                ptr_piloto[j].aviao = ptr_piloto[j+1].aviao;
                ptr_piloto[j].idade = ptr_piloto[j+1].idade;
                ptr_piloto[j].pontos = ptr_piloto[j+1].pontos;
                
                strcpy(ptr_piloto[j+1].nome,aux.nome);
                ptr_piloto[j+1].aviao = aux.aviao;
                ptr_piloto[j+1].idade = aux.idade;
                ptr_piloto[j+1].pontos = aux.pontos;
                }
        }
}


void resOrdenaClassAviao (ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Ordena a classificação geral pelo número do avião
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos

        Nota: tentar usar void resOrdenaClass (ficha_t *ptr_piloto) {
        */
        
    ficha_t aux;
    int i, j, ha_trocas,posmenor;

    for( i = 0; i < ptr_contador->pilotos && ha_trocas; i++){
        ha_trocas = 0;
        for ( j = 0; j < ptr_contador->pilotos - i - 1; j++)
            if( ptr_piloto[j].aviao > ptr_piloto[j+1].aviao){ 
                ha_trocas=1;
                
                strcpy(aux.nome, ptr_piloto[j+1].nome);
                aux.aviao = ptr_piloto[j+1].aviao;
                aux.idade = ptr_piloto[j+1].idade;
                aux.pontos = ptr_piloto[j+1].pontos;
    
                strcpy(ptr_piloto[j+1].nome,ptr_piloto[j].nome);
                ptr_piloto[j+1].aviao = ptr_piloto[j].aviao;
                ptr_piloto[j+1].idade = ptr_piloto[j].idade;
                ptr_piloto[j+1].pontos = ptr_piloto[j].pontos;
                
                strcpy(ptr_piloto[j].nome,aux.nome);
                ptr_piloto[j].aviao = aux.aviao;
                ptr_piloto[j].idade = aux.idade;
                ptr_piloto[j].pontos = aux.pontos;
                }
        }
}


void estMostraClassificacao (int simples, ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Lista a classificação geral nas estatísticas, ordenada por pontos ou avião.
        Recebe:
            simples: Opção de escolha para listagem
                1: Listagem normal sem opção de alternação
                0: Listagem completa com opção para ordenar por pontos ou avião
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */
        
    int i, aux = 0, alternador = 0;
    char opcao;

    do {
        fflush(stdin);
        aux = 0;
        if ( alternador % 2 == 0)// se for par mostra ordenado por pontuação, impar por aviao, o X alterna
            resOrdenaClass (ptr_piloto, ptr_contador);
        else
            resOrdenaClassAviao (ptr_piloto, ptr_contador);
            
        system("CLS");
    	puts(PROGRAMA);
        printf("\n\n\tClassificacao Geral: ( Pilotos sem pontuacao omitidos )\n\n");
        printf("\n\t\t\t\t\t\t Nome | Aviao |  Pontos\n"); 
    
        for (i=0 ; i< ptr_contador->pilotos; i++) {
            if ( ptr_piloto[i].aviao != 0 && ptr_piloto[i].pontos != 0) {       
                printf("\n\t\t      %31.31s |  %3.d  |  %3.d", ptr_piloto[i].nome, ptr_piloto[i].aviao, ptr_piloto[i].pontos);
                aux++; // conta os pilotos que vai mostrar, para fazer pausa a cada 10
                }
        	if (aux != 0 && aux % 10 == 0) // de 10 em 10 nomes, faz uma pausa para o utilizador ver os nomes, ignora o 0 porque senão pausa na primeira linha
                auxPausa();
            }
        if ( simples != 1 ) { // se for listagem com opcoes para Estatisticas
            printf("\n\n\n\t[ X ] - Alterna a ordem Pontos/Aviao\t\t [ S ] - Sair\n\t");
            opcao = getch();
            opcao = toupper(opcao);
            if ( opcao == 'X' ) 
                alternador++; // se carregou X muda a visualização
            }
        else // se nao, sai de imediato
            opcao = 'S';
        }
    while( opcao != 'S' );
}


char estMenu(conta_t *ptr_contador) {
	/*  Mostra o menu de Pilotos no ecrã.
	    Recebe:
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    Devolve:
	        op: letra/opção introduzida pelo utilizador
	    */
	
	char op;

	do {
		menuCabecalho(4, ptr_contador); // 0 = menu principal | 1 = menu pilotos | 2 = menu etapas
		printf("\n\n\tR - Resultados do Campeonato");
		printf("\n\tH - Historico por Piloto");
		printf("\n\tD - Dados Estatísticos");
		printf("\n\n\tV - Voltar ao Menu Principal");
		fflush(stdin);
		op = getch();
		op = toupper(op);
		}
	while (op != 'V' && op != 'R' && op != 'H' && op != 'D');
	
	return op;
}



void estFuncoes(ficha_t *ptr_piloto, etapa_t *ptr_etapa, char op, conta_t *ptr_contador) {
	/*  Recebe a opção escolhida e direcciona para a função a usar.
	    Recebe:
	        ptr_piloto: vector ponteiro com as fichas de pilotos
	        ptr_etapa: vector ponteiro com a lista de etapas
	        op: letra/opção escolhida na função pilMenu
	        ptr_contador: ponteiro que guarda o total de etapas e pilotos
	    */
	    
    int aux;
    
    aux = etaNumRealizadas(ptr_etapa);
	
	switch (op) {
    	case 'R':  // (R)esultados do Campeonato
                if ( aux > 0 )
                    estMostraClassificacao (0, ptr_piloto, ptr_contador); // 0 = listagem com opções
                else {
                    printf("\n\tAinda nao existem etapas realizadas...");
                    auxPausa();
                    }
				break;
				
		case 'H':  // (H)istórico por Piloto
                if ( aux > 0 )
                    estHistorico (ptr_etapa, ptr_piloto, ptr_contador);
                else {
                    printf("\n\tAinda nao existem etapas realizadas...");
                    auxPausa();
                    }
				break;				
				
		case 'D':  // (D)ados Estatísticos
                if ( aux > 2 ) {
                    estDados (ptr_contador, ptr_etapa, ptr_piloto);
                    auxPausa();
                    }
                else {
                    printf("\n\tPara ver as estatisticas precisa de pelo menos 3 etapas realizadas...");
                    auxPausa();
                    }
				break;              
		}
}


void estHistorico (etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Mostra uma tabela de Pilotos/Etapas com a classificação de cada.
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */

    int encontrou_piloto, pontos, tempo, piloto, totalpilotos, etapa, i,j;
  
    fflush(stdin);
    resOrdenaClass (ptr_piloto, ptr_contador); // ordena a classificação geral
    estCabecalhoHistorico (ptr_etapa, ptr_contador); // mostra o cabeçalho

    for( i = 0 ; i < ptr_contador->pilotos ; i++ ) { // percorre todos os pilotos
        printf("\n| %.3d-%15.15s | %.3d |", ptr_piloto[i].aviao, ptr_piloto[i].nome, ptr_piloto[i].pontos);
        for ( j = 0; j < MAX_ETAPAS; j++ ) { // percorre todas as etapas
            encontrou_piloto = etaProcuraPiloto (j, ptr_piloto[i].aviao, ptr_etapa); // verifica se o piloto esta inscrito na etapa
            if ( encontrou_piloto != ERRO_NAOEXISTE )  // se sim, mostra os pontos
                printf(" %2d |", ptr_etapa[j].pontos[encontrou_piloto]);
            else
                printf("  0 |"); // se nao, preenche a zero
            }
        printf("\n+-----------------------------------------------------------------------------+");  
        if (i != 0 && i % 5 == 0 && i <ptr_contador->pilotos) { // de 5 em 5 nomes, faz uma pausa para o utilizador ver os nomes, ignora o 0 porque senão pausa na primeira linha
            auxPausa(); // se não tiver i <ptr_contador->pilotos faz um pause a mais no fim da listagem quando o fim dá resto 0
            system("CLS");
            estCabecalhoHistorico (ptr_etapa, ptr_contador);
            }
    }
    auxPausa();
}


void estCabecalhoHistorico (etapa_t *ptr_etapa, conta_t *ptr_contador) {
    /*  Cabeçalho para a Listagem do Histórico.
        Recebe:
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */
        
    int i;
    char titulo[5];

    system("CLS");
    printf("\n\n                        Tabela Geral de Classificacoes\n");
    printf("+-----------------------------------------------------------------------------+\n");
    printf("|                     |     |    |    |    |    |    |    |    |    |    |    |\n");
    printf("| Aviao / Nome        |Total|");
    
    for( i=0 ; i<MAX_ETAPAS ; i++ ) { // pereorre todas as etapas
        strncpy(titulo, ptr_etapa[i].nome, 4); // trunca o nome para 3 caracteres
        titulo[3] = '.'; titulo[4] = '\0'; // e termina com .
        if ( ptr_etapa[i].data.ano != 0) // se a etapa existir mostra o nome truncado
            printf("%s|", titulo); 
        else // senao, preenche --
            printf(" -- |");
        }
    printf("\n|                     |(pts)|");
    for( i=0 ; i<MAX_ETAPAS ; i++ ) // mostra as ordens
            printf("(%2.d)|", i+1);
    printf("\n|                     |     |    |    |    |    |    |    |    |    |    |    |");
    printf("\n|---------------------+-----+----+----+----+----+----+----+----+----+----+----|");
}


void estDados (conta_t *ptr_contador, etapa_t *ptr_etapa, ficha_t *ptr_piloto) {
    /*  Mostra os dados estatísticos do campeonato.
        número e percentagem de etapas já realizadas, etapa(s) com maior e menor número de participantes,
        número médio de participantes por etapas, piloto(s) com maior número de vitórias,
        número e percentagem de pilotos com vitórias em etapas, piloto(s) com o maior número de vitórias consecutivas.
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */
        
    int i;
    int vencedores[MAX_ETAPAS]; // Vector para auxilio a outras funções.
    int pilotos[ptr_contador->pilotos][2]; // Matriz para auxilio a outras funções, usada para ordenações.
    int etapas[MAX_ETAPAS][2]; // Matriz para auxilio a outras funções, usada para ordenações.

    float pct_realizadas; 

    system("CLS");
    //puts(PROGRAMA); falta de espaço
    printf("\n\tESTG AIR RACE | Estatisticas Gerais:\n");
       
    
    pct_realizadas = ( (float)ptr_contador->realizadas * 100 ) / (float)ptr_contador->etapas;
    printf("\n\tEstao actualmente %.2f%% [ %d em %d ] de Etapas Realizadas.\n", pct_realizadas, 
        ptr_contador->realizadas, ptr_contador->etapas ); // percentagem de etapas realizadas
 
    auxVencedores ( vencedores, ptr_etapa); // preenche o vector vencedores com o vencedor de cada etapa
    printf("\n\tPilotos com mais Vitorias:");
    estNumVitorias ( pilotos, vencedores, ptr_piloto, ptr_contador, 'D'); // pilotos com mais vitorias
    fflush(stdin);
    estPctVictorias ( pilotos, ptr_piloto, ptr_contador); 
    printf("\n\n\tEtapas com menos inscritos:");
    fflush(stdin); // limpa buffers porque mostrava resultados inválidos
    estEtapas ( etapas, ptr_etapa, ptr_contador, 'A');
    printf("\n\n\tEtapas com mais inscritos:");
    fflush(stdin);
    estEtapas ( etapas, ptr_etapa, ptr_contador, 'D');
    fflush(stdin);
    estMediaParticipantes ( ptr_etapa, ptr_contador ); //media de participantes
    fflush(stdin);
    estVitoriasConsecutivas (vencedores, ptr_etapa, ptr_piloto, ptr_contador);
}


void auxVencedores ( int vencedores[], etapa_t *ptr_etapa) {
    /*  Preenche um vector Vencedores com o numero dos aviões que venceram cada etapa.
        Vector para auxilio a outras funções.
        Recebe:
            vencedores: vector a preencher, passa por referencia
            ptr_etapa: vector ponteiro com a lista de etapas
        */
        
    int i;

    for ( i = 0; i < MAX_ETAPAS; i++) { // preenche o vector vencedores com o vencedor de cada etapa
        fflush(stdin);
        resOrdenaTempos (i, ptr_etapa);
        if ( ptr_etapa[i].realizada == 1) // se a etapa não esta realizada preenche com 0
            vencedores[i] = ptr_etapa[i].inscritos[0];
        else
            vencedores[i] = 0;
        }
}


void estNumVitorias ( int pilotos[][2], int vencedores[], ficha_t *ptr_piloto, conta_t *ptr_contador, char tipo) {
    /*  Preenche a matriz pilotos com o numero do aviao [][0] e numero de vitorias [][1],
        ordena pelo numero de vitorias e mostra ao utilizador.
        Recebe:
            pilotos: Matriz auxiliar para calculos, guarda avião/Nº Vitorias
            vencedores: Vector que tem o vendedor de cada etapa.
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
            tipo: Tipo de ordenação, Ascendente ou Descendente
        */
        
    int aux = 0, indice, i,j;
    

    for (i = 0; i < ptr_contador->pilotos; i++) { // copia os numeros de avioes para um vector temporario
        pilotos[i][0] = ptr_piloto[i].aviao;
        pilotos[i][1] = 0;
        }
    for(j = 0; j < ptr_contador->pilotos; j++) // percorre a matriz pilotos
        for (i = 0; i < MAX_ETAPAS; i++) // percorre o vector q tem os vencedores de todas as etapas (tinha contador-1)
            if ( vencedores[i] == pilotos[j][0] ) // se um dos vencedores é o pilotos[j]
                pilotos[j][1]++; // aumenta o numero de vitorias na matriz

    if ( tipo == 'D' ) {
        fflush(stdin);
        auxOrdenaMatriz ( pilotos, ptr_contador->pilotos, tipo); // vai ordenar
        for (i=0 ; i < ptr_contador->pilotos && aux < NUMTOPS; i++) {
            indice = pilIndiceAviao( pilotos[i][0], ptr_piloto, ptr_contador); // procura o indice do aviao pilotos[i][0]
            if ( pilotos[i][1] != 0 ) { // esconde os pilotos q n têm vitorias     
                printf("\n\t\t%2.d |  %.31s", pilotos[i][1], ptr_piloto[indice].nome);          
                aux++;
                }
            }
        }
    else
    if ( tipo == 'A' ) {
        fflush(stdin);
        auxOrdenaMatriz ( pilotos, ptr_contador->pilotos, tipo); // vai ordenar
        for (i=0 ; i < ptr_contador->pilotos; i++)
            printf("\n -vitorias: o piloto %d tem %d victorias", pilotos[i][0], pilotos[i][1]);           
        }        
}


void estPctVictorias ( int pilotos[][2], ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Recebe a matriz pilotos com o numero do aviao [][0] e numero de vitorias [][1],
        Conta o número de vitórias e calcula a média com o número total de pilotos
        Recebe:
            pilotos: Matriz auxiliar para calculos, guarda avião/Nº Vitorias
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */

    int i, numpilotos, contavitorias = 0;
    float media;
    
    for ( i = 0; i < ptr_contador->pilotos - 1; i++)
        if ( pilotos[i][1] != 0 ) // se 1 piloto tem uma ou mais vitorias
           contavitorias++;
           
    numpilotos = ptr_contador->pilotos;
    media = (contavitorias*100) / numpilotos;
    printf("\n\n\t%.2f%% [ %d em %d ] dos pilotos tem pelo menos uma vitoria.", media, contavitorias, numpilotos );
}


void estEtapas ( int etapas[][2], etapa_t *ptr_etapa, conta_t *ptr_contador, char tipo) {
    /*  Preenche a matriz etapas com o numero do aviao [][0] e numero de inscritos [][1],
        ordena pelo numero de inscritos ascendente ou descendente e mostra ao utilizador.
        Recebe:
            etapas: Matriz auxiliar para calculos, guarda avião/Nº inscritos
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
            tipo: Tipo de ordenação, Ascendente ou Descendente
        */
        
    int aux = 0, i,j;

    for (i = 0; i < MAX_ETAPAS; i++) { // copia os numeros de avioes para um vector temporario
        etapas[i][0] = i;
        etapas[i][1] = ptr_etapa[i].totalinscritos;
        }

    auxOrdenaMatriz ( etapas, MAX_ETAPAS, tipo); // vai ordenar

    if ( tipo == 'D' )  // mais inscritos
        for (i=0 ; i < MAX_ETAPAS & aux < NUMTOPS; i++) 
            if ( ptr_etapa[etapas[i][0]].data.ano != 0 ) {// esconde etapas vazias     
                aux++;
                printf("\n\t\t%2d |  %.31s", etapas[i][1], ptr_etapa[etapas[i][0]].nome);          
                } // ptr_etapa[etapas[i][0]].nome  -> etapas[i][0] é o indice da etapa em questão
    
    if ( tipo == 'A' )  // menos inscritos
        for (i=0 ; i < MAX_ETAPAS && aux < NUMTOPS; i++) 
            if ( ptr_etapa[etapas[i][0]].data.ano != 0 ) { // esconde etapas vazias     
                aux++;
                printf("\n\t\t%2d |  %.31s", etapas[i][1], ptr_etapa[etapas[i][0]].nome);          
                } // ptr_etapa[etapas[i][0]].nome  -> etapas[i][0] é o indice da etapa em questão
}


void estMediaParticipantes (etapa_t *ptr_etapa, conta_t *ptr_contador) {
    /*  Conta o número de etapas inseridas e os participantes de cada uma e
        mostra ao utilizador a média de pilotos por etapa.
        Recebe:
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */
        
    int total = 0, aux = 0, i;

    for (i=0 ; i < MAX_ETAPAS; i++)     
        if ( ptr_etapa[i].data.ano !=0) {  
             aux++; // encontrou uma etapa  
             total += ptr_etapa[i].participantes;
        } // ptr_etapa[etapas[i][0]].nome  -> etapas[i][0] é o indice da etapa em questão
    printf("\n\n\tExiste um total maximo de %2d Participantes, distribuidos por %d Etapas", total, ptr_contador->etapas);
    printf("\n\tO que resulta numa Media de %.2f pilotos por etapa.", (float)total/aux);
}


void estVitoriasConsecutivas (int vencedores[], etapa_t *ptr_etapa, ficha_t *ptr_piloto, conta_t *ptr_contador) {
    /*  Analisa o vector vencedores e procura pilotos com 2 ou mais vitórias consecutivas.
        Recebe:
            vencedores: Vector que tem o vendedor de cada etapa.
            ptr_etapa: vector ponteiro com a lista de etapas
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
        */
        
    int contatops = 0, aux = 0, i, indice;
    int vitorias[MAX_ETAPAS][2];
    
    for ( i = 0; i < MAX_ETAPAS; i++) 
        vitorias[i][1] = 0; // inicia o contador de vitorias a zero      
    for ( i = 0; i < MAX_ETAPAS; i++) {
        if ( vencedores[i] != 0){
            indice = pilIndiceAviao( vencedores[i], ptr_piloto, ptr_contador);
            if ( indice == vitorias[aux-1][0] && i!=0)
                vitorias[aux-1][1]++;
            else {
                vitorias[aux][0] = indice; // guarda o indice do piloto
                vitorias[aux][1]++; // conta uma vitoria para o piloto
                aux++; // auxiliar usado porque o i tem valores que não vamos usar na matriz ( quando salta etapas )
                }
            
            }
        }
    auxOrdenaMatriz ( vitorias, aux, 'D'); // ordena a matriz criada, descencente
    printf("\n\n\tPilotos com maior numero de vitorias consecutivas:");
    for ( i = 0; i < aux && contatops++ < NUMTOPS; i++) // mostra top 3 
        if ( vitorias[i][1] > 1 ) // esconde os que só têm uma vitória
            printf("\n\t\t%2d | %s", vitorias[i][1], ptr_piloto[vitorias[i][0]].nome);        
}


void auxOrdenaMatriz (int vector[][2], int max, char tipo) { // ordena pelo segundo valor da matriz [][1]
    /*  Função auxiliar para ordenar matrizes com base no valor [][x].
        Recebe:
            vector: Matriz a ordenar
            max: valor máximo de colunas
            tipo: Tipo de ordenação, Ascendente ou Descendente
        */
        
    int aux, aux2;
    int i, j, ha_trocas, posmenor;

    fflush(stdin);
    if ( tipo == 'D')
        for( i = 0; i < max && ha_trocas; i++){
            ha_trocas = 0;
            for ( j = 0; j < max - i - 1; j++)
                if( vector[j][1] < vector[j+1][1]){ // Inverte para decrescemaxte
                    ha_trocas=1;
    
                    aux = vector[j][0];
                    aux2 = vector[j][1];
    
                    vector[j][0] = vector[j+1][0];
                    vector[j][1] = vector[j+1][1];
    
                    vector[j+1][0] = aux;
                    vector[j+1][1] = aux2;
                    }
            }
    else
        if ( tipo == 'A')
        for( i = 0; i < max && ha_trocas; i++){
            ha_trocas = 0;
            for ( j = 0; j < max - i - 1; j++)
                if( vector[j][1] > vector[j+1][1]){ // Inverte para decrescemaxte
                    ha_trocas=1;
    
                    aux = vector[j][0];
                    aux2 = vector[j][1];
    
                    vector[j][0] = vector[j+1][0];
                    vector[j][1] = vector[j+1][1];
    
                    vector[j+1][0] = aux;
                    vector[j+1][1] = aux2;
                    }
            }
    
}


void fichGravar(conta_t *ptr_contador, etapa_t *ptr_etapa, ficha_t *ptr_piloto) {
    /*  Grava a informação num ficheiro binário
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
            ptr_etapa: estrura de etapas
        */  
           
    FILE *f;
    int num;
    
    f = fopen( "dados.dat", "wb");
    if ( f == NULL )
        printf("\n\tErro ao criar ficheiro...");
    else {
        
        num = fwrite(ptr_contador, sizeof(conta_t), 1, f);        
        
        if ( num != 1  )  {
            printf("\n\tErro de gravação...");
            auxPausa();
            }
        else {
            num = fwrite(ptr_piloto, sizeof(ficha_t), ptr_contador->pilotos , f);
            if ( num != ptr_contador->pilotos ) {
                printf("\n\tErro ao escrever a estrutura de pilotos no ficheiro...");
                auxPausa();
                }            
            num = fwrite(ptr_etapa, sizeof(etapa_t), MAX_ETAPAS, f);
            if ( num != MAX_ETAPAS ) {
                printf("\n\tErro ao escrever a estrutura de etapas no ficheiro...");
                auxPausa();
                }             
            }
        }   
    
    fclose(f);
    system("CLS");
    printf("\n\n\tInformacao guardada com sucesso...");
    ptr_contador->grava = 0;
    auxPausa();
}


ficha_t *fichLer(conta_t *ptr_contador, etapa_t *ptr_etapa) {
     /*  Le a informação de num ficheiro binário
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
            ptr_etapa: estrura de etapas
        */ 
            
    FILE *f;
    int num;
    ficha_t *aux;

    aux = NULL;
    
    f = fopen( "dados.dat", "rb");
    if ( f == NULL ) {
        printf("\n\tErro ao ler ficheiro...");
        auxPausa();
        return NULL; // se não consegue encontrar o ficheiro, devolte endereço NULL
        }
    else {
      
        num = fread(ptr_contador, sizeof(conta_t), 1, f);        
        if ( num != 1 ) {
            printf("\n\tErro de memoria...");
            auxPausa();
            return NULL; // se não consegue encontrar o ficheiro, devolte endereço NULL
            }
        else {
            aux = (ficha_t*)malloc((ptr_contador->pilotos)*sizeof(ficha_t));
            if ( aux == NULL )  {
            printf("\n\tErro de alocacao de memoria...");
            auxPausa();
            return NULL; // se não consegue encontrar o ficheiro, devolte endereço NULL
            }
            else {
                num = fread(aux, sizeof(ficha_t), ptr_contador->pilotos , f);
                if ( num != ptr_contador->pilotos ) {
                    printf("\n\tErro na memoria a ler a estrutura de pilotos...");
                    auxPausa();
                    return NULL; // se não consegue encontrar o ficheiro, devolte endereço NULL
                    }
                num = fread(ptr_etapa, sizeof(etapa_t), MAX_ETAPAS, f);
                if ( num != 10 ) {
                    printf("\n\tErro na memoria a ler a estrutura de etapas...");
                    auxPausa();
                    return NULL; // se não consegue encontrar o ficheiro, devolte endereço NULL
                    }                
                }  
            }
        }  
    fclose(f);
    printf("\n\n\tInformacao recuperada com sucesso...");
    ptr_contador->grava = 0;
    auxPausa();

    return aux;
}


char auxSair(conta_t *ptr_contador, ficha_t *ptr_piloto, etapa_t *ptr_etapa) {
    /*  Função auxiliar para perguntar ao utilizador se quer gravar antes de sair
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
            ptr_etapa: estrutura de etapas
        */ 
        
	char op;
	
    if ( ptr_contador->grava == 0) // se não precisa de gravar, sai logo
        return SAIR;

    do {
		system("CLS");
        puts(PROGRAMA);
        printf("\n\n\tNao gravou o seu trabalho, deseja:\n");
		printf("\n\tS - Sair sem gravar");
		printf("\n\tG - Gravar e Sair");
		printf("\n\tC - Cancelar e voltar ao menu principal");
		fflush(stdin);
		op = getch();
		op = toupper(op);
		}
	while (op != 'S' && op != 'G' && op != 'C');
	
    if ( op == 'G') {
        fichGravar(ptr_contador, ptr_etapa, ptr_piloto);
        return SAIR;
        }
    else
    if ( op == 'C')
        return NAOSAIR;
    else
        return SAIR;
}


ficha_t *auxLer(conta_t *ptr_contador, ficha_t *ptr_piloto, etapa_t *ptr_etapa) {
    /*  Função auxiliar para perguntar ao utilizador se quer ler os dados à entrada
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
            ptr_etapa: estrutura de etapas
        */ 
        
    char op;          
    FILE *f;
    int num;
    
    f = fopen( "dados.dat", "rb");
    
    if ( f != NULL ) {
        do {
            system ("CLS");
            puts(PROGRAMA);
            
            printf("\n\n\tDeseja ler os dados armazenados?");
            printf("\n\t\tS - Sim");
            printf("\n\t\tN - Nao");
            fflush(stdin);
            op = getch();
            op = toupper(op);
            }
        while ( op != 'S' && op !='N');
        
        
        if ( op == 'S' )
            ptr_piloto = fichLer(ptr_contador, ptr_etapa);
        else
            auxIniciaValores(ptr_piloto, ptr_etapa, ptr_contador);
        }   
    else
        auxIniciaValores(ptr_piloto, ptr_etapa, ptr_contador);

    return ptr_piloto;
}


void auxIniciaValores(ficha_t *ptr_piloto, etapa_t *ptr_etapa, conta_t *ptr_contador) {
    /*  Função auxiliar para inicializar valores das estruturas a zero
        Recebe:
            ptr_piloto: vector ponteiro com as fichas de pilotos
            ptr_contador: ponteiro que guarda o total de etapas e pilotos
            ptr_etapa: estrutura de etapas
        */ 
        
	int i, j;
	
	ptr_contador->etapas = 0;
	ptr_contador->pilotos = 0;
    ptr_contador->etapa_corrente = 0;
    ptr_contador->grava = 0;
 		
	for (i = 0; i < MAX_ETAPAS; i++) {
		for (j = 0;j < MAX_PILOTOS_ETAPA;j++) {
			ptr_etapa[i].inscritos[j] = 0;
            ptr_etapa[i].tempos[j] = 0;
            ptr_etapa[i].pontos[j] = 0;
            }
        ptr_etapa[i].totalinscritos = 0;
		ptr_etapa[i].data.dia = 0;
		ptr_etapa[i].data.mes = 0;
		ptr_etapa[i].data.ano = 0;
		ptr_etapa[i].ordem = i + 1; // inicia logo as posições todas
		ptr_etapa[i].participantes = 0;
		strcpy(ptr_etapa[i].nome, "\0");
		ptr_etapa[i].realizada = 0;
		}
}
