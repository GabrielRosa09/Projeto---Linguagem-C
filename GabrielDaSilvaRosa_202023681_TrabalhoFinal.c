#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Struct para registra um jogador
typedef struct jogador{
    int id;
    char nome[50];
    char posicao[4];
    int idade;
} Jogador;

//Struct para registra um time e seus jogadores
typedef struct time{
    Jogador jogadores[5];
    char nomeTime[50];
    char nomeTecnico[50];
} Time;

//Struct para registra os jogadores da partida
typedef struct jogadores_partida{
    int id_jogador;
    int numAssist;
    int numKills;
    int numDeaths;
    int calcKDA;
    int pontuacaoFinal;
} JogadorPartida;

//Struct para registra a partida
typedef struct partida{
    int total_kills_time;
    int total_kills_adversario;
    int resultPartida;
    int total_torres_destruidas_time;
    int total_torres_destruidas_adversario;
    int total_deaths_time;
    int total_kills_time_geral;
    int total_assist_time_geral;
    JogadorPartida jogadoresPartida[5];
} Partida;

// Declaracoes
int menu;
// Assinar Funcao
int menuOpcoes();
void distribuirOpcoes(), listarTime(), editarTime(), cadastrarTime(), listarPartida(), pesquisarJogador(), imprimiKillsAssist();
void imprimiJogadorMenorPontuacao(), imprimiJogadorMaiorPontuacao(), cadastrarPartida();

//FUNCAO PRINCIPAL
int main(){
    Time time;
    Partida partidas[100];
    int quantPartidas = 0;
    int *ponteiroQuant = &quantPartidas; 
    do{
    	//Variavel que recebe a funcao menuOpcoes();
        menu = menuOpcoes(); 
        //Void que vai distribuir as alternativas fornecidas pelo usuario
        distribuirOpcoes(menu, &time, partidas, quantPartidas, ponteiroQuant);
    }while(menu != 10);

    return 0;
}

int menuOpcoes(){
    int opcoes;
    printf("-------- MENU DE OPCOES -------- \n");
    printf("1 - Cadastrar Time \n");
    printf("2 - Listar Time \n");
    printf("3 - Editar Time \n");
    printf("4 - Cadastrar Partida \n");
    printf("5 - Listar Partidas \n");
    printf("6 - Pesquisar Jogador \n");
    printf("7 - Mostrar numero total de kills e assistencias \n");
    printf("8 - Mostrar jogador com menor pontuacao \n");
    printf("9 - Mostrar jogador com maior pontuacao \n");
    printf("10 - Sair \n");
    printf("-------------------------------- \n");
    scanf("%d", &opcoes);
    return opcoes;
}

void distribuirOpcoes(int menu, Time * time, Partida partidas[], int quantPartidas, int * ponteiroQuant){
    switch(menu){
        case 1:
        	//Void de cadastro de time
            cadastrarTime(time);
            break;
        case 2:
        	//Void de listar time
            listarTime(time);
            break;
        case 3:
        	//Void de editar time
        	editarTime(time, partidas);
        	break;
        case 4:
        	//Void de cadastrar partida
        	cadastrarPartida(partidas, ponteiroQuant);
        	break;
        case 5:
        	//Void para listar partida
        	listarPartida(time, partidas, quantPartidas);
        	break;
        case 6:
        	//Void para pesquisar jogador
        	pesquisarJogador(time);
        	break;
        case 7:
        	//Void de imprimir Total de Kills e Assistencias
        	imprimiKillsAssist(partidas);
        	break;
        case 8:
        	//Void para imprimir a menor Pontuacao do Jogador
        	imprimiJogadorMenorPontuacao(time, partidas, quantPartidas);
        	break;
        case 9:
        	//Void para imprimir a maior Pontuacao do Jogador
        	imprimiJogadorMaiorPontuacao(time, partidas, quantPartidas);
        	break;
        case 10:
        	//Encerrar o programa
            printf("Programa Finalizado! \n");
            break;
        default:
            printf("Opcao invalida! Digite novamente! \n");
    }
}


void cadastrarTime(Time time){
	//Cadastrar o time
	printf("Nome da Equipe: ");
	scanf(" %[^\n]%*c", time.nomeTime);
	
	printf("Nome do Tecnico: ");
	scanf(" %[^\n]%*c", time.nomeTecnico);
	
	int i;
	
    for(i = 0; i < 5; ++i){
    	
    	//ID do jogador a partir do laco 
    	time.jogadores[i].id = i + 1;
    	
		//Entrada do nome, posicao e idade do jogador
		printf("Nome do %d jogador: ", i + 1);
    	scanf(" %[^\n]%*c", time.jogadores[i].nome);
    	
    	do{
            printf("Digite a posicao do jogador: ");   
            scanf(" %[^\n]%*c", time.jogadores[i].posicao);

            if(strcmp(time.jogadores[i].posicao, "SUP") && 
               strcmp(time.jogadores[i].posicao, "ADC") && 
               strcmp(time.jogadores[i].posicao, "MID") && 
               strcmp(time.jogadores[i].posicao, "JG") && 
               strcmp(time.jogadores[i].posicao, "TOP")){
                printf("Posicao invalida! \n");
            }
            
        }while(strcmp(time.jogadores[i].posicao, "SUP") && 
               strcmp(time.jogadores[i].posicao, "ADC") && 
               strcmp(time.jogadores[i].posicao, "MID") && 
               strcmp(time.jogadores[i].posicao, "JG") && 
               strcmp(time.jogadores[i].posicao, "TOP"));
               
    	do{
    		printf("Idade do jogador: ");
    		scanf("%d", &time.jogadores[i].idade);
    
    		if(time.jogadores[i].idade < 1 || time.jogadores[i].idade > 150){
    			printf("Idade invalida! \n");
			}
		}while(time.jogadores[i].idade < 1 || time.jogadores[i].idade > 150);
    }  
}

void listarTime(Time time){
	//Listar o time cadastrado
	int i;
    for(i = 0; i < 5; ++i){
        printf("%d - %s - %s \n", time.jogadores[i].id, 
								  time.jogadores[i].nome,
								  time.jogadores[i].posicao);
    }
}

void editarTime(Time time, Partida partidas){
	int idJogador, escolha;
	//Pesquisar o jogador e caso for necessario editar ele
	do{
		printf("Digite o ID do jogador: \n");
	    scanf("%d", &idJogador);
		if(idJogador < 0 || idJogador > 5){
			printf("Id invalido \n");
		}
		idJogador = idJogador - 1;	
	}while(idJogador < 0 || idJogador > 5);
	
	printf("%d - %s - %s - %d \n", time.jogadores[idJogador].id, 
						   time.jogadores[idJogador].nome,
						   time.jogadores[idJogador].posicao,
						   partidas.jogadoresPartida[idJogador].pontuacaoFinal);
						   
	printf("Deseja alterar esse jogador? Pressione 1 para continuar ou qualquer outro numero para voltar ao menu! \n");
	scanf("%d", &escolha);
	
	if(escolha == 1){
		printf("Nome do novo jogador: ");
    	scanf(" %[^\n]%*c", time.jogadores[idJogador].nome);
    	
    	do{
            printf("Digite a posicao do jogador: ");   
            scanf(" %[^\n]%*c", time.jogadores[idJogador].posicao);

            if(strcmp(time.jogadores[idJogador].posicao, "SUP") && 
               strcmp(time.jogadores[idJogador].posicao, "ADC") && 
               strcmp(time.jogadores[idJogador].posicao, "MID") && 
               strcmp(time.jogadores[idJogador].posicao, "JG") && 
               strcmp(time.jogadores[idJogador].posicao, "TOP")){
                printf("Posicao invalida! \n");
            }
            
        }while(strcmp(time.jogadores[idJogador].posicao, "SUP") && 
               strcmp(time.jogadores[idJogador].posicao, "ADC") && 
               strcmp(time.jogadores[idJogador].posicao, "MID") && 
               strcmp(time.jogadores[idJogador].posicao, "JG") && 
               strcmp(time.jogadores[idJogador].posicao, "TOP"));
               
    	do{
    		printf("Idade do jogador: ");
    		scanf("%d", &time.jogadores[idJogador].idade);
    
    		if(time.jogadores[idJogador].idade < 1 || time.jogadores[idJogador].idade > 150){
    			printf("Idade invalida! \n");
			}
		}while(time.jogadores[idJogador].idade < 1 || time.jogadores[idJogador].idade > 150);
	}else{
		printf("Edicao encerrada! \n");
	}
}

void cadastrarPartida(Partida partidas[], int * ponteiroQuant){
	//cadastrar partida
	char escolha;
	int aux = *ponteiroQuant;
	int totalKillsGeral = 0, totalAssistGeral = 0, somaPlayer[5] = {0, 0, 0, 0, 0};
	
	do{
		int i;
		int totalKillsPartida = 0, totalAssistPartida = 0, totalDeathsPartida = 0; 
		for(i = 0; i < 5; ++i){
			int pontuacaoFinal = 0;
			partidas[aux].jogadoresPartida[i].id_jogador = i + 1;
			//Entrada do numero de kills, assistencias e mortes
			do{
				printf("Digite o numero do Kills do %d jogador: ", i + 1);
				scanf("%d", &partidas[aux].jogadoresPartida[i].numKills);
				if(partidas[aux].jogadoresPartida[i].numKills < 0){
					printf("Numero de Kills invalidas! \n");
				}
				//Contar o total de kills das partidas
				totalKillsPartida = totalKillsPartida + partidas[aux].jogadoresPartida[i].numKills;
			}while(partidas[aux].jogadoresPartida[i].numKills < 0);
			
			do{
				printf("Digite o numero de Assistencias do %d jogador: ", i + 1);
				scanf("%d", &partidas[aux].jogadoresPartida[i].numAssist);
				if(partidas[aux].jogadoresPartida[i].numAssist < 0){
					printf("Numero de Assistencias invalidas! \n");
				}
				//Contar o total de Assist das partidas
				totalAssistPartida = totalAssistPartida + partidas[aux].jogadoresPartida[i].numAssist; 
			}while(partidas[aux].jogadoresPartida[i].numAssist < 0);
			
			do{
				printf("Digite o numero de Deaths do %d jogador: ", i + 1);
				scanf("%d", &partidas[aux].jogadoresPartida[i].numDeaths);
				if(partidas[aux].jogadoresPartida[i].numDeaths < 0){
					printf("Numero de Deaths invalidas! \n");
				}
				//Contar o total de Mortes das partidas
				totalDeathsPartida = totalDeathsPartida + partidas[aux].jogadoresPartida[i].numDeaths;
				
			}while(partidas[aux].jogadoresPartida[i].numDeaths < 0);
			
			//Calc do KDA por partida
			partidas[aux].jogadoresPartida[i].calcKDA = (partidas[aux].jogadoresPartida[i].numAssist * 1) + (partidas[aux].jogadoresPartida[i].numKills * 3);
			//Soma dos KDA por partida
			pontuacaoFinal = pontuacaoFinal + partidas[aux].jogadoresPartida[i].calcKDA;
			somaPlayer[i] = somaPlayer[i] + pontuacaoFinal;
			partidas[aux].jogadoresPartida[i].pontuacaoFinal = somaPlayer[i];
		}
		
		//Total de Kills e Assist
		totalKillsGeral = totalKillsGeral + totalKillsPartida; 
		totalAssistGeral = totalAssistGeral + totalAssistPartida;
		
		partidas[aux].total_kills_time_geral = totalKillsGeral;
		partidas[aux].total_assist_time_geral = totalAssistGeral;
		
		//Total de Kills e Deaths
		partidas[aux].total_kills_time = totalKillsPartida;
		partidas[aux].total_deaths_time = totalDeathsPartida;
		
		//Entrada de torres, resultado e kills do adversário
		do{
			printf("Qual foi o resultado da partida? 1 - Vitoria || 2 - Derrota: ");
			scanf("%d", &partidas[aux].resultPartida);	
			if(partidas[aux].resultPartida != 1 && partidas[aux].resultPartida != 2){
				printf("ERRO! Entrada invalida! \n");
			}
		}while(partidas[aux].resultPartida != 1 && partidas[aux].resultPartida != 2);
		
		do{
			printf("Digite o numero de kills do adversario: ");
			scanf("%d", &partidas[aux].total_kills_adversario);
			if(partidas[aux].total_kills_adversario < 0){
				printf("Numero de Torres invalidas! \n");
			}
		}while(partidas[aux].total_kills_adversario < 0);
		
		do{
			printf("Digite o numero de torres destruidas da equipe: ");
			scanf("%d", &partidas[aux].total_torres_destruidas_time);
			if(partidas[aux].total_torres_destruidas_time < 0 || partidas[aux].total_torres_destruidas_time > 11){
				printf("ERRO! Numero de torres invalidas! \n");
			}
		}while(partidas[aux].total_torres_destruidas_time < 0 || partidas[aux].total_torres_destruidas_time > 11);
		
		do{
			printf("Digite o numero de torres destruidas do adversario: ");
			scanf("%d", &partidas[aux].total_torres_destruidas_adversario);
			if(partidas[aux].total_torres_destruidas_adversario < 0 || partidas[aux].total_torres_destruidas_adversario > 11){
				printf("ERRO! Numero de torres invalidas! \n");
			}
		}while(partidas[aux].total_torres_destruidas_adversario < 0 || partidas[aux].total_torres_destruidas_adversario > 11);	
		
		aux++;
		
		//adicionar outra partida
		printf("Deseja adicionar mais um partida? \n");
		printf("S - SIM || N - NAO \n");
		scanf(" %c", &escolha);
		
	}while(escolha != 'n' && escolha != 'N');
	
	*ponteiroQuant = aux;
}

void listarPartida(Time time, Partida partidas[], int quant){
	//listar as partidas cadastradas
	int i = 0, j = 0, idJogador, maiorKDA;
	for(i = 0; i < quant; ++i){
		if(partidas[i].resultPartida == 1){
		printf("Resultado: Vitoria \n");
		}else if(partidas[i].resultPartida == 2){
			printf("Resultado: Derrota \n");
		}
		printf("Numero de Kills do time: %d \n", partidas[i].total_kills_time);
		printf("Numero de Deaths do time: %d \n", partidas[i].total_deaths_time);
		printf("Numero de torres destruidas do time: %d \n", partidas[i].total_torres_destruidas_time);
		printf("Numero de torres destruidas do adversario: %d \n", partidas[i].total_torres_destruidas_adversario);
		for(j = 0; j < 5; ++j){
			if(i == 0){
				idJogador = time.jogadores[j].id;
				idJogador = idJogador - 1;
				maiorKDA = partidas->jogadoresPartida[j].calcKDA;
			}else if(partidas->jogadoresPartida[j].calcKDA > maiorKDA){
				maiorKDA = partidas->jogadoresPartida[j].calcKDA;
				idJogador = time.jogadores[j].id;
				idJogador = idJogador - 1;
			}
		}
		printf("Jogador destaque: %s - %d PONTOS \n", time.jogadores[idJogador].nome, maiorKDA);
	}
	
}

void pesquisarJogador(Time time){
	int idJogador;
	//Pesquisar jogador do time
	do{
		printf("Digite o ID do jogador: \n");
	    scanf("%d", &idJogador);
	    
	    idJogador = idJogador - 1;
		if(idJogador < 0 || idJogador > 5){
			printf("Jogador nao encontrado! \n");
		}	
	}while(idJogador < 0 || idJogador > 5);
	
	printf("ID: %d \n", time.jogadores[idJogador].id);
	printf("Nome: %s \n", time.jogadores[idJogador].nome);
	printf("Posicao: %s \n", time.jogadores[idJogador].posicao);
	printf("Idade: %d \n", time.jogadores[idJogador].idade);
}

void imprimiKillsAssist(Partida partidas){
	printf("Kills total do time: %d \n", partidas.total_kills_time_geral);
	printf("Asistencias total do time: %d \n", partidas.total_assist_time_geral);
}

void imprimiJogadorMenorPontuacao(Time time, Partida partidas[], int quant){
	//Imprimir o jogador com menor pontuacao
	int j = 0, i = 0, menorPontuacao, idJogador;
	for(j = 0; j < quant; ++j){
		for(i = 0; i < 5; ++i){
				if(i == 0){
				idJogador = time.jogadores[i].id;
				idJogador = idJogador - 1;
				menorPontuacao = partidas[j].jogadoresPartida[i].pontuacaoFinal;
			}else if(partidas[j].jogadoresPartida[i].pontuacaoFinal < menorPontuacao){
				menorPontuacao = partidas[j].jogadoresPartida[i].pontuacaoFinal;
				idJogador = time.jogadores[i].id;
				idJogador = idJogador - 1;
			}	
		}
	}
	printf("Id: %d \n", time.jogadores[idJogador].id);
	printf("Nome: %s \n", time.jogadores[idJogador].nome);
	printf("Posicao: %s \n", time.jogadores[idJogador].posicao);
	printf("Idade: %d \n", time.jogadores[idJogador].idade);
	printf("Pontuacao: %d \n", menorPontuacao);	
}

void imprimiJogadorMaiorPontuacao(Time time, Partida partidas[], int quant){
	//Imprimir o jogador com maior pontuacao
	int j = 0, i = 0, maiorPontuacao, idJogador;
	for(j = 0; j < quant; ++j){
		for(i = 0; i < 5; ++i){
				if(i == 0){
				idJogador = time.jogadores[i].id;
				idJogador = idJogador - 1;
				maiorPontuacao = partidas[j].jogadoresPartida[i].pontuacaoFinal;
			}else if(partidas[j].jogadoresPartida[i].pontuacaoFinal > maiorPontuacao){
				maiorPontuacao = partidas[j].jogadoresPartida[i].pontuacaoFinal;
				idJogador = time.jogadores[i].id;
				idJogador = idJogador - 1;
			}	
		}
	}
	printf("Id: %d \n", time.jogadores[idJogador].id);
	printf("Nome: %s \n", time.jogadores[idJogador].nome);
	printf("Posicao: %s \n", time.jogadores[idJogador].posicao);
	printf("Idade: %d \n", time.jogadores[idJogador].idade);
	printf("Pontuacao: %d \n", maiorPontuacao);	
}
