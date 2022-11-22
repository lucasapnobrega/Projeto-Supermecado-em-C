#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define TAM 50

typedef struct info_itens{ // Estrutura contendo informações dos itens
	
	float qtd;
	float preco;
	char nome[50];
	
} t_itens;

typedef struct info_total{ // Estrutura contendo info sobre os preços
	
	float preco_total[TAM];
	float total_final;
} t_total;


enum opcoes{produto = 1, caro, barato, qtd_itens, nota_fiscal, pagar_sair}; // ENUM para melhorar a legibilidade

enum pagamentos{cartao = 1, dinheiro, boleto};


void interface_inicial(){ // Função contendo a interface inicial do supermecado
	
	printf("\n\n\n-------------------------------------------------------------\n");
	printf("\t*** SEJA BEM VINDO AO SUPERMECADO UNIPÊ ***");
	printf("\n-------------------------------------------------------------\n\n\n");
}


void inicializacao_menu(){ // Função contendo as opções do menu
	
	printf("\n===========================================\n");
	printf("\nESCOLHA UMA DAS OPÇÕES ABAIXO\n\n");
	printf("1 - Inserir item\n");
	printf("2 - Mostrar o item(unidade) mais caro\n");
	printf("3 - Mostrar o item(unidade) mais barato\n");
	printf("4 - Quantidade total dos itens cadastrados\n");
	printf("5 - Nota fiscal\n");
	printf("6 - Pagar e sair\n");
	printf("\n");
}

void interface_fiscal(){ // Função contendo a interface da nota fiscal
	
	printf("\n");
	printf("\t\t***** NOTA FISCAL *****\n\n");
	printf("NOME\tPREÇO\tQUANTIDADE\t|R$ TOTAL\n");
}


void interface_pagar(){ // Função dos tipos de pagamento
	
	printf("\n--------- PAGAMENTO ---------\n");
	printf("1 - Cartão\n");
	printf("2 - Dinheiro\n");
	printf("3 - Boleto\n");
}


int f_cartao(int num, char nome[50], int venc, int ccv){ // Função do pagamento em CARTÃO
	
	printf("Número do cartão: ");
	scanf("%d", &num);
	printf("Nome do titular: ");
	scanf("%s", &nome);
	printf("Vencimento do cartão: ");
	scanf("%d", &venc);
	printf("Código de segurança: ");
	scanf("%d", &ccv);
}
 

int main(){
	
	setlocale(LC_ALL, "Portuguese"); // Permitindo que aceite acentuações
	
	
	int op, i = 0,j = 0, cont = 0, cont2 = 0, op_pagar, cart; 
	int num, venc, ccv, num_boleto; // cartão
	float preco_maior, preco_menor, valor, troco;
	char nome, nome_maior, nome_menor, resposta, cpf[15];
	
	
	interface_inicial(); // Chamando a função
	
	t_itens item[TAM]; // Chamando a STRUCT itens
	t_total total; // Chamando a STRUCT total
	
	total.total_final = 0;
	
	
	do{ // Esse DO WHILE só vai parar quando o usuário digitar 5 e pagar;
		
		//entrada - Perguntar para o usuário qual opção ele quer
		inicializacao_menu(); // Chamando a função
		
		do{ // Caso o usuário digite uma opção incorreta (menor que 1 e maior que 6) vai repetir até que digite uma correta
		printf("\nQual opção você deseja escolher? ");
		scanf("%d", &op);
		} while(op < 1 || op > 6);
		
		cont++;
		
		// processamento - De acordo com a opção escolhida, utilizamos Switch Case para fazer o funcionamento de cada opção
		switch(op){ 
			
			// Perguntar o nome, preço e quantidade do produto e calcular os preços
			case produto:
				
				printf("\nNome: ");
				scanf("%s", &item[i].nome);
				
				printf("\nPreço R$"); // Preço por unidade ou KG
				scanf("%f", &item[i].preco);
				
				printf("\nQuantidade: "); // Quantidade por unidade ou KG
				scanf("%f", &item[i].qtd);
				
				total.preco_total[i] = item[i].preco * item[i].qtd; // Preço final do produto de acordo com a quantidade
				
				total.total_final += total.preco_total[i]; // Preço final de todos os produtos (somados)
				
				i++;
				j++;
				break;
				
			// Calculando, com o FOR, qual foi o item que teve o maior preço
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
				
				printf("\nO item mais caro é %s, custando R$%.2f a UNIDADE\n", item[cont2].nome, preco_maior);	
				
				break;
				
			// Calculando, com o FOR, qual foi o item que teve o menor preço			
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
						
				printf("\nO item mais barato é %s, custando R$%.2f a UNIDADE\n", item[cont2].nome, preco_menor);
				
				break;
			
			case qtd_itens:
				
				printf("\n\n*** Quantidade total de itens cadastrados: %d ***\n\n", j);
				
				break;
				
			// Mostrar a nota fiscal para o usuário, tendo informações como nome, preço, quantidade, preço total e preço final
			case nota_fiscal:
				
				printf("CPF na nota[s/n]? ");
				scanf(" %c", &resposta);
				
				if(resposta == 's'){
					printf("Digite seu CPF: ");
					scanf("%s", &cpf);
				}
				
				printf("\n");
				interface_fiscal(); // Chamando a função
				for(i = 0; i < j; i++){
					
						printf("\n");
						printf("%s \t", item[i].nome);
						printf("%.2f \t", item[i].preco);
						printf("%.2f \t", item[i].qtd);
						printf("\t|R$ %.2f", total.preco_total[i]);
						printf("\n");
				}
				printf("\nPreço final \t\t\t|R$ %.2f", total.total_final);
				
				if(resposta == 's'){
					printf("\n\nCPF: %s", cpf);
				}
				
				printf("\n");
				break;
			
			// O usuário vai escolher uma forma de pagamento e depois irá sair automaticamente do programa
			case pagar_sair:
				
				interface_pagar(); // Chamando a função
				
				printf("\nEscolha a forma de pagamento: ");
				scanf("%d", &op_pagar);
				
				while(op_pagar < 0 || op_pagar > 3){ // Caso o usuário digite a forma de pagamento errada. Vai repetir até digitar uma correta
					
					printf("Opção inválida. Tente novamente.");
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
					printf("Número do boleto: ");
					scanf("%d", &num_boleto);
				}
				
				printf("\nPAGAMENTO REALIZADO!!!\n");
				
				op = 7; // Op = 7, pois encerrará o loop
				
				break;
				
		}
		
	} while(op != 7);
	
	printf("\n\n---> Obrigado pela preferência, VOLTE SEMPRE! <---\n");
	
	return 0;
}
