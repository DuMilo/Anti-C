#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFA 100
#define ARQUIVO "tarefas.txt"

void adicionar_tarefa(){
	FILE *arquivo = fopen(ARQUIVO, "a");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo!");
		return;
	}
	
	char tarefa[MAX_TAREFA];
	printf("Digite a tarefa: ");
	fgets(tarefa, MAX_TAREFA, stdin);
	tarefa[strcspn(tarefa, "\n")] = '\0';
	
	fprintf(arquivo, "%s\n", tarefa);
	fclose(arquivo);
	
	printf("Tarefa adicionada com sucesso!\n");
}

void listar_tarefas(){
	FILE *arquivo = fopen(ARQUIVO, "r");
	if (arquivo == NULL){
		printf("Nenhuma tarefa encontrada!\n");
		return;
	}
	char linha[MAX_TAREFA];
	printf("\n=== Tarefas ===\n");
	int contador = 1;
	while (fgets(linha, MAX_TAREFA, arquivo)){
		linha[strcspn(linha, "\n")] = '\0';
		printf("%d. %s\n", contador, linha);
		contador++;
	}
	fclose(arquivo);
}


void remover_tarefa(){
	FILE *arquivo = fopen(ARQUIVO, "r");
	if (arquivo == NULL){
		printf("Nenhuma tarefa encontrada para remover!\n");
		return;
	}
	
	char tarefas[100][MAX_TAREFA];
	int total = 0;
	while (fgets(tarefas[total], MAX_TAREFA, arquivo)){
		tarefas[total][strcspn(tarefas[total], "\n")] = '\0';
		total++;
	}
	fclose(arquivo);
	
	if (total == 0){
		printf("Nenhuma tarefa encontrada para remover!\n");
		return;
	}
	
	printf("\n=== Tarefas ===\n");
	for(int i = 0; i < total; i++){
		printf("%d. %s\n", i + 1, tarefas[i]);
	}
	
	int opcao;
	printf("Digite o número da tarefa que deseja remover: ");
	scanf("%d", &opcao);
	getchar();
	
	if (opcao < 1 || opcao > total){
		printf("Opção Inválida!\n");
		return;
	}
	
	arquivo = fopen(ARQUIVO, "w");
	for (int i = 0; i < total; i++){
		if (i != opcao - 1){
			fprintf(arquivo, "%s\n", tarefas[i]);
		}
	}
	fclose(arquivo);
	
	printf("Tarefa removida com sucesso!\n");
}

	
int main(){
	int opcao;
	
	do {
		printf("\n=== Gerenciador de Tarefas ===\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Remover Tarefa\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
        	case 1:
        		adicionar_tarefa();
        		break;
        	case 2: 
        		listar_tarefas();
        	case 3:
        		remover_tarefa();
        	case 4:
        		printf("Saindo...\n");
        		break;
        	default:
        		printf("Opção Inválida!\n");
		} 
	} while (opcao!= 4);
	
	return 0;
}
