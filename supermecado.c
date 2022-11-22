#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define TAM 50

typedef struct info_itens{ // Estrutura contendo informa��es dos itens
	
	float qtd;
	float preco;
	char nome[50];
	
} t_itens;

typedef struct info_total{ // Estrutura contendo info sobre os pre�os
	
	float preco_total[TAM];
	float total_final;
} t_total;


enum opcoes{produto = 1, caro, barato, qtd_itens, nota_fiscal, pagar_sair}; // ENUM para melhorar a legibilidade

enum pagamentos{cartao = 1, dinheiro, boleto};


void interface_inicial(){ // Fun��o contendo a interface inicial do supermecado
	
	printf("\n\n\n-------------------------------------------------------------\n");
	printf("\t*** SEJA BEM VINDO AO SUPERMECADO UNIP� ***");
	printf("\n-------------------------------------------------------------\n\n\n");
}


void inicializacao_menu(){ // Fun��o contendo as op��es do menu
	
	printf("\n===========================================\n");
	printf("\nESCOLHA UMA DAS OP��ES ABAIXO\n\n");
	printf("1 - Inserir item\n");
	printf("2 - Mostrar o item(unidade) mais caro\n");
	printf("3 - Mostrar o item(unidade) mais barato\n");
	printf("4 - Quantidade total dos itens cadastrados\n");
	printf("5 - Nota fiscal\n");
	printf("6 - Pagar e sair\n");
	printf("\n");
}

void interface_fiscal(){ // Fun��o contendo a interface da nota fiscal
	
	printf("\n");
	printf("\t\t***** NOTA FISCAL *****\n\n");
	printf("NOME\tPRE�O\tQUANTIDADE\t|R$ TOTAL\n");
}


void interface_pagar(){ // Fun��o dos tipos de pagamento
	
	printf("\n--------- PAGAMENTO ---------\n");
	printf("1 - Cart�o\n");
	printf("2 - Dinheiro\n");
	printf("3 - Boleto\n");
}


int f_cartao(int num, char nome[50], int venc, int ccv){ // Fun��o do pagamento em CART�O
	
	printf("N�mero do cart�o: ");
	scanf("%d", &num);
	printf("Nome do titular: ");
	scanf("%s", &nome);
	printf("Vencimento do cart�o: ");
	scanf("%d", &venc);
	printf("C�digo de seguran�a: ");
	scanf("%d", &ccv);
}
 

int main(){
	
	setlocale(LC_ALL, "Portuguese"); // Permitindo que aceite acentua��es
	
	
	int op, i = 0,j = 0, cont = 0, cont2 = 0, op_pagar, cart; 
	int num, venc, ccv, num_boleto; // cart�o
	float preco_maior, preco_menor, valor, troco;
	char nome, nome_maior, nome_menor, resposta, cpf[15];
	
	
	interface_inicial(); // Chamando a fun��o
	
	t_itens item[TAM]; // Chamando a STRUCT itens
	t_total total; // Chamando a STRUCT total
	
	total.total_final = 0;
	
	
	do{ // Esse DO WHILE s� vai parar quando o usu�rio digitar 5 e pagar;
		
		//entrada - Perguntar para o usu�rio qual op��o ele quer
		inicializacao_menu(); // Chamando a fun��o
		
		do{ // Caso o usu�rio digite uma op��o incorreta (menor que 1 e maior que 6) vai repetir at� que digite uma correta
		printf("\nQual op��o voc� deseja escolher? ");
		scanf("%d", &op);
		} while(op < 1 || op > 6);
		
		cont++;
		
		// processamento - De acordo com a op��o escolhida, utilizamos Switch Case para fazer o funcionamento de cada op��o
		switch(op){ 
			
			// Perguntar o nome, pre�o e quantidade do produto e calcular os pre�os
			case produto:
				
				printf("\nNome: ");
				scanf("%s", &item[i].nome);
				
				printf("\nPre�o R$"); // Pre�o por unidade ou KG
				scanf("%f", &item[i].preco);
				
				printf("\nQuantidade: "); // Quantidade por unidade ou KG
				scanf("%f", &item[i].qtd);
				
				total.preco_total[i] = item[i].preco * item[i].qtd; // Pre�o final do produto de acordo com a quantidade
				
				total.total_final += total.preco_total[i]; // Pre�o final de todos os produtos (somados)
				
				i++;
				j++;
				break;
				
			// Calculando, com o FOR, qual foi o item que teve o maior pre�o
			case caro:
				
				printf("\n\n--------- ITEM MAIS CARO ---------\n\n");
				
				preco_maior = 0;
				cont2 = 0;
				for(i = 0; i < j; i++){ 
					if(item[i].preco > preco_maior){ 
						preco_maior = item[i].preco;
						cont2 = i;
					}
				}
				
				printf("\nO item mais caro � %s, custando R$%.2f a UNIDADE\n", item[cont2].nome, preco_maior);	
				
				break;
				
			// Calculando, com o FOR, qual foi o item que teve o menor pre�o			
			case barato:
				
				printf("\n\n--------- ITEM MAIS BARATO ---------\n\n");
				
				cont2 = 0;
				for(i = 0; i < j; i++){
				
					if(i == 0){
						preco_menor = item[i].preco;
					} else {
						if(item[i].preco < preco_menor){
							preco_menor = item[i].preco;
							cont2 = i;
						}
					}
				}		
						
				printf("\nO item mais barato � %s, custando R$%.2f a UNIDADE\n", item[cont2].nome, preco_menor);
				
				break;
			
			case qtd_itens:
				
				printf("\n\n*** Quantidade total de itens cadastrados: %d ***\n\n", j);
				
				break;
				
			// Mostrar a nota fiscal para o usu�rio, tendo informa��es como nome, pre�o, quantidade, pre�o total e pre�o final
			case nota_fiscal:
				
				printf("CPF na nota[s/n]? ");
				scanf(" %c", &resposta);
				
				if(resposta == 's'){
					printf("Digite seu CPF: ");
					scanf("%s", &cpf);
				}
				
				printf("\n");
				interface_fiscal(); // Chamando a fun��o
				for(i = 0; i < j; i++){
					
						printf("\n");
						printf("%s \t", item[i].nome);
						printf("%.2f \t", item[i].preco);
						printf("%.2f \t", item[i].qtd);
						printf("\t|R$ %.2f", total.preco_total[i]);
						printf("\n");
				}
				printf("\nPre�o final \t\t\t|R$ %.2f", total.total_final);
				
				if(resposta == 's'){
					printf("\n\nCPF: %s", cpf);
				}
				
				printf("\n");
				break;
			
			// O usu�rio vai escolher uma forma de pagamento e depois ir� sair automaticamente do programa
			case pagar_sair:
				
				interface_pagar(); // Chamando a fun��o
				
				printf("\nEscolha a forma de pagamento: ");
				scanf("%d", &op_pagar);
				
				while(op_pagar < 0 || op_pagar > 3){ // Caso o usu�rio digite a forma de pagamento errada. Vai repetir at� digitar uma correta
					
					printf("Op��o inv�lida. Tente novamente.");
					printf("\nEscolha a forma de pagamento: ");
					scanf("%d", &op_pagar);
				}
				
				
				if(op_pagar == cartao){
					
					printf("\n\nTOTAL A PAGAR: R$%.2f\n\n", total.total_final);
					f_cartao(num, nome, venc, ccv);
					
				} else if(op_pagar == dinheiro){
					
					printf("\n\nTOTAL A PAGAR: R$%.2f\n\n", total.total_final);
					printf("Troco para quanto? ");
					scanf("%f", &valor);
					
					troco =  valor - total.total_final;
					
					printf("\nSEU TROCO: R$%.2f\n", troco);
					
				} else if(op_pagar == boleto){
					
					printf("\n\nTOTAL A PAGAR: R$%.2f\n\n", total.total_final);
					printf("N�mero do boleto: ");
					scanf("%d", &num_boleto);
				}
				
				printf("\nPAGAMENTO REALIZADO!!!\n");
				
				op = 7; // Op = 7, pois encerrar� o loop
				
				break;
				
		}
		
	} while(op != 7);
	
	printf("\n\n---> Obrigado pela prefer�ncia, VOLTE SEMPRE! <---\n");
	
	return 0;
}
