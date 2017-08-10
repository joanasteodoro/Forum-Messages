/* PROJETO 1 - IAED */
/* Daniela Lopes - 86403 */
/* Joana Teodoro - 86440 */

/* Bibliotecas */
#include <stdio.h>
#include <string.h>

/* Abstracoes */
#define MAX_USERS 1000
#define MAX_MENSAGENS 10000
#define MAX_CARACTERES 140
#define MAX_ID_USERS 1000
#define MAX_PALAVRAS 70 //o maximo de palavras numa mensagem e 70 quando cada palavra e composta apenas por 1 letra
#define TRUE 1
#define FALSE 0

typedef int Item;
#define key(A) (A)
#define exch(A, B) { Item t = A; A = B; B = t; }

typedef struct{
	int user, n_letras; //n_letras representa o comprimento de cada frase
	int n_palavras; //numero de palavras da frase da mensagem
	char frase[MAX_CARACTERES + 1];
} Mensagem;

/* Variaveis Globais */
Mensagem msg[MAX_MENSAGENS]; 
int index_msgs = 0, user, n_msgs_user[MAX_USERS];

/* Prototipos */
void limpaVector();
void leLinha();
void addMensagem();
void listaMensagens();
void listaMensagens_user(int user);
void frase_maisLonga(); 
void user_maisAtivo(); /*retorna o indice do user mais ativo*/
int contaPalavra(char word[]);
void ordenaMensagens(); /*criar outro vetor com mensagens ordenadas*/

int main(){
	int executa = TRUE;
	char command, word[MAX_CARACTERES + 1];
	limpaVector();
	while (executa == TRUE){
		command = getchar();
		switch (command){
			case 'A':
				getchar();
				addMensagem();
				index_msgs++; //aumento do indice no vetor da estrutura Mensagem para poder receber outra
				break;
			case 'L':
				printf("*TOTAL MESSAGES:%d\n", index_msgs); //o total de mensagens e dado pelo indice de mensagens no forum
				listaMensagens();
				getchar();
				break;
			case 'U':
				scanf("%d", &user);
				printf("*MESSAGES FROM USER:%d\n", user);
				listaMensagens_user(user);
				getchar();
				break;
			case 'O':
				frase_maisLonga();
				getchar();
				break;
			case 'T':
				user_maisAtivo();
				getchar();
				break;
			case 'C':
				scanf("%s", word);
				printf("*WORD %s:%d\n", word, contaPalavra(word));
				getchar();
				break;
			case 'S':
				printf("*SORTED MESSAGES:%d\n", index_msgs); //o total de mensagens e dado pelo indice de mensagens no forum
				ordenaMensagens();
				getchar();
				break;
			case 'X':
				printf("%d\n", index_msgs); //imprime o numero de mensagens total do forum
				executa = FALSE;
				break;
			default:
				printf("ERRO: Comando desconhecido.\n");
				getchar();
		}
	}
	return 0;

}

void leLinha(){
    int j = 0; //indice de frase
    int letras = 0, palavras = 0; //contador que conta quantas letras e palavras tem cada mensagem
    char car;
    while ((car = getchar()) != EOF && car != '\n'){
        msg[index_msgs].frase[j] = car;
        j++; 
        letras++;
        if ((car < '0' || car > '9') && (car < 'A' || car > 'Z') && (car < 'a' || car > 'z')){
			palavras++;
		}
    }
    msg[index_msgs].n_letras = letras;
    msg[index_msgs].n_palavras = palavras + 1; //acrescentar a ultima palavra que nao fica no contador por causa do fim de ficheiro
    msg[index_msgs].frase[j] = '\0';
}

void limpaVector(){ //coloca todas as posicoes do vetor n_msgs_user a 0
	int j;
	for(j = 0; j < MAX_USERS; j++){
		n_msgs_user[j] = 0;
	}
}

void addMensagem(){
	scanf("%d ", &user);
	msg[index_msgs].user = user;
	leLinha();
	n_msgs_user[user - 1]++; //adiciona uma mensagem no vector que contabiliza o numero de mensagens introduzidas por cada user
}

void listaMensagens(){
	int j;
	for (j = 0; j < index_msgs; j++){
		printf("%d:%s\n",msg[j].user, msg[j].frase);
	}
}

void listaMensagens_user(int user){
	int j;
	for (j = 0; j < index_msgs; j++){
		if (msg[j].user == user){
			printf("%s\n", msg[j].frase);
		}
	}
}

void frase_maisLonga(){
	int max = 0, j; //variavel max que contem o comprimento maximo de uma mensagem
	for (j = 0; j < index_msgs; j++){
		if (msg[j].n_letras > max){
			max = msg[j].n_letras;
		}
	}
	for (j = 0; j < index_msgs; j++){
		if (msg[j].n_letras == max){
			printf("*LONGEST SENTENCE:%d:%s\n", msg[j].user, msg[j].frase);
		}
	}
	
}

void user_maisAtivo(){
	int i, j, max_mensagens = 0;
	for (j = 0; j < MAX_USERS; j++){ //o vetor onde esta o numero de mensagens introduzidas por cada user e percorrido para
		if (n_msgs_user[j] > max_mensagens){ //encontrar o maior numero de mensagens
			max_mensagens = n_msgs_user[j];
		}
	}
	for(i = 0; i < MAX_USERS; i++){ //obtencao dos users com o maior numero de mensagens 
		if (n_msgs_user[i] == max_mensagens){
			printf("*MOST ACTIVE USER:%d:%d\n", i + 1, n_msgs_user[i]);
		}
	}
}

int contaPalavra(char word[]){
	int j, palavras, letra = 0, count = 0, car = 0;
	char palavra[MAX_CARACTERES + 1]; //vetor que ira conter todas as palavras das palavras
	for(j = 0; j < index_msgs; j++){
		car = 0; //inicializacao do caracter da frase da mensagem a 0
		for(palavras = 0; palavras < msg[j].n_palavras; palavras++){ //preenchimento do vetor palavra a partir da verificacao do caracter
			while((msg[j].frase[car] >= 'a' && msg[j].frase[car] <= 'z') || (msg[j].frase[car] >= 'A' && msg[j].frase[car] <= 'Z') || (msg[j].frase[car] >= '0' && msg[j].frase[car] <= '9')){
				palavra[letra] = msg[j].frase[car];
				car++;
				letra++;
			}
			palavra[letra] = '\0';
			if(strcmp(palavra, word) == 0){ //comparar se a palavra resultante e igual a que queremos contar
				count++;
			}
			palavra[0] = '\0';
			letra = 0; //colocacao do indice do vetor palavra a 0 para poder escrever novamente nesta posicao
			car++; //incremento do caracter na frase pois neste momento estamos num caracter diferente de uma letra ou numero
		}
	}
	return count;
}

void ordenaMensagens(){ //Selection Sort
	int i, j;
	int vec_indices[index_msgs];
	for(i = 0; i < index_msgs; i++){ //vetor onde sao colocados os indices das mensagens a ordenar
		vec_indices[i] = i;
	}
	for(j = 0; j < index_msgs - 1; j++) {
   		int min = j;
   		for(i = j + 1; i < index_msgs; i++){ //ordenacao desses indices atraves de comparacoes entre as mensagens do forum
      		if((strcmp(msg[vec_indices[min]].frase, msg[vec_indices[i]].frase)) > 0){
      			min = i;
      		}
      		else if((strcmp(msg[vec_indices[min]].frase, msg[vec_indices[i]].frase)) == 0){
				if (msg[vec_indices[min]].user > msg[vec_indices[i]].user){
					min = i;
      			}
      		}
      	}
      	if (min != j){
      		exch(vec_indices[j], vec_indices[min]);
      	}
    }
	for (j = 0; j < index_msgs; j++){ //impressao da mensagem cujo indice foi ordenado
	printf("%d:%s\n", msg[vec_indices[j]].user, msg[vec_indices[j]].frase);
	}
}
