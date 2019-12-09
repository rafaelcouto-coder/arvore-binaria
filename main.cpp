#include <iostream>
#include <locale.h> // Usada para inserir assentuação
#include <stdlib.h>
#include <ctype.h> 

typedef struct{
	int CPF;
	char nome[50];
}Info;

typedef struct t_no{
	Info *info;
	struct t_no *sae;
	struct t_no *sad;
}Node;

// Inicializa árvore 
Node *initializeTree(){
	return NULL;
}

//Retorna informações dos funcionários
Info *createInfo(){
	Info *aux;
	aux = new Info;

	printf("\nInserir: <nome> <CPF>\n");
	scanf("%s %d", &aux->nome, &aux->CPF);
	return aux;
}

/* Verifica se o CPF já existe para evitar duplicidade de dados
   Retorna true caso exista, false caso não exista  */  
bool existCPF(Node *root, int cpf){	
	if(root != NULL){ // Caso árvore seja diferente de nulo 
		if(root->info->CPF == cpf){
			return true;
		}
		existCPF(root->sae, cpf);
		existCPF(root->sad, cpf);
	}
	return false;
}

// Inseri informações na árvore
Node *insertTree(Node *root, Info *aux){
	
	if(existCPF(root, aux->CPF) == true){ //Caso o número de CPF já exista
		printf("\nNão serão cadastrados dois CPFs iguais");	
		return root;
	}else{
		if(root == NULL){	 // Caso árvore seja diferente de nulo, ou seja, exista elementos
			Node *newElement = new Node; // Aloca espaço para armazenar novo Elemento
			newElement->info = aux;
			newElement->sad = NULL;
			newElement->sae = NULL;
			printf("\nInseriu: %s", newElement->info->nome);
			return newElement;
		}else{
			if(aux->CPF > root->info->CPF){ 
				root->sad = insertTree(root->sad, aux); // Caso CPF inserido seja maior valor enviado para sub árvore direita
			}else{
				root->sae = insertTree(root->sae, aux); // Caso CPF inserido seja menor valor enviado para sub árvore direita
			}
		}
		return root;		
	}
}

//Imprime árvore completa
Node *printTree(Node *root){
	if(root != NULL){ // Caso árvore seja diferente de nulo, ou seja, exista elementos
		printf("\nFuncionario: %s CPF: %d", root->info->nome, root->info->CPF);
		printTree(root->sae);
		printTree(root->sad);
	}
}

//Pesquisa e imprime elemento via CPF
Node *searchNo(Node *root, int cpf){	
	if(root != NULL){ // Caso árvore seja diferente de nulo, ou seja, exista elementos
		if(cpf == root->info->CPF){ // Caso encontra informação, imprime
			printf("\nEncontrou: %s %d", root->info->nome, root->info->CPF);
			return root;
		}else{
			if(cpf > root->info->CPF){
				return searchNo(root->sad, cpf);
			}else{
				return searchNo(root->sae, cpf);
			}
		}
	}
	printf("\nCPF %d não localizado", cpf);
	return NULL;
}

// Pede ao usuário digitar CPF
int writeCPF(){
	int cpf;
	printf("Digite CPF: ");
	scanf("%d", &cpf);
	
	return cpf;
}

//Limpa memória do programa
Node freeTree(Node *root){
	if(root != NULL){ // Caso árvore seja diferente de nulo, ou seja, exista elementos
		freeTree(root->sae);
		freeTree(root->sad);
		free(root);
	}
}

// Retorna o nó folha da sub árvore esquerda, recebe como parametro sub árvore direita
Node* minTree(Node *root){
	if(root != NULL){ // Caso árvore seja diferente de nulo, ou seja, exista elementos
		Node *aux = root;
		while(aux->sae != NULL){
			aux = aux->sae;
		}
		return aux;
	}
	return NULL;
}

// Remove elemento 
Node* removeNo(Node *root, int cpf){
	if(root != NULL){ // Caso árvore seja diferente de nulo, ou seja, exista elementos
		
		if(cpf > root->info->CPF){
			root->sad = removeNo(root->sad, cpf);			
		}
		else if(cpf < root->info->CPF){		
			root->sae = removeNo(root->sae, cpf);
		}
		else{
			//encontrou o elemento a ser removido
			printf("\nRemoveu %s %d", root->info->nome, root->info->CPF);
			
			//quando não tem nenhum filho
			if(root->sae == NULL && root->sad == NULL){
				free(root);
				return NULL;
			}
			
			//quando tem filho da direita
			else if(root->sae == NULL && root->sad != NULL){
				Node * aux = root->sad;
				free(root);
				return aux;
			}
			
			//quando tem filho a esquerda
			else if(root->sae != NULL && root->sad == NULL){
				Node* aux = root->sae;
				free(root);
				return aux;
				
			//quando tem filho para os dois lados 	
			}else{
				Node* aux = minTree(root->sad);
				Info *infoAux = aux->info;
				
				root = removeNo(root, infoAux->CPF);
				root->info = infoAux;
				return root;
			}
		}
		return root;
	}
	printf("\nCPF %d não localizado", cpf);
	return NULL;
}

// Controla menu para limpar informações e pausar quando necessario 
void clean(){
	printf("\n\n");
	system("pause");
	system("cls");
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese"); // Usada para inserir assentuação
	
	Node *arvoreCPF = initializeTree();
	
	char opc;
	
	do{
		printf("\n\n>MENU \n\nI-> Inserir\nR-> Remover por CPF\nB-> Buscar\nL-> Listar\nS-> Sair\n\nEscolha a operação desejada: ");
		scanf("%c", &opc);
		opc = toupper(opc);	//Transforma caracter minusculo para maiusculo
		switch(opc){
			case 'I':
				arvoreCPF = insertTree(arvoreCPF, createInfo());
				clean();
			break;
			
			case 'L':
				printTree(arvoreCPF);
				clean();				
			break;
			
			case 'R':
				removeNo(arvoreCPF, writeCPF());
				clean();
			break;
			
			case 'B':
				searchNo(arvoreCPF, writeCPF());
				clean();
			break;	
		}
		fflush(stdin);
	}while(opc != 'S');

	//printTree(arvoreCPF);
	freeTree(arvoreCPF);

	return 0;
}
