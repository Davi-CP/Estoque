//DAVI COSTA PEREIRA
#include <stdio.h>
#include <string.h>

typedef struct Produto{
	char descricao[40];
	int quantidadeEstoque;
    	int minimoEstoque;
    	float precoVenda;
}	Produto;

void incluir_produto(FILE *arquivoPtr);
void registrar_venda(FILE *arquivoPtr);
void buscarPorCodigo(FILE *arquivoPtr);
void buscarPorDescricao(FILE *arquivoPtr);
void relatorioEstoqueAbaixoMinimo(FILE *arquivoPtr);



int main()
{
	FILE *arquivo;
	arquivo = fopen("estoque.bin", "rb+");
	if(arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo\n");
		return 1;
	}
	else
	{
		int opcao;
		do
		{
			printf("\nESTOQUE\n");
			printf("1. Incluir Produto\n");
			printf("2. Registrar Venda\n");
			printf("3. Buscar codigo\n");
			printf("4. Buscar por Descricao\n");
			printf("5. Relatorio de produtos com Estoque Abaixo do minimo");;
			printf("6. Sair\n");
			printf("Escolha uma opçao: ");
			scanf("%d", &opcao);

			switch(opcao)
			{
			case 1: 
				incluir_produto(arquivo); 
				break;
			case 2: 
				registrar_venda(arquivo);
				break;
			case 3: 
				buscarPorCodigo(arquivo);
				break;
			case 4: 
				buscarPorDescricao(arquivo);
				break;
			case 5: 
				relatorioEstoqueAbaixoMinimo(arquivo);
				break;
			case 6: 
				printf("Saindo...\n");
				break;
			default:
				printf("Opção Inválida");
			}	
		}while(opcao != 6);
	}
	
	fclose(arquivo);
	return 0;
}

void incluir_produto(FILE *arquivoPtr)
{
	struct Produto produto = {"", 0, 0, 0};
	fseek(arquivoPtr,0, SEEK_END);
	printf("Digite descricao, quantidade no estoque, minimo no estoque e preco de venda: ");
	scanf("%s%d%d%f", produto.descricao,&produto.quantidadeEstoque,&produto.minimoEstoque,&produto.precoVenda);
	fwrite(&produto, sizeof(Produto), 1, arquivoPtr);
}

void registrar_venda(FILE *arquivoPtr)
{
	int cod, qtdVendida;
	Produto p;
	printf("Codigo do produto: ");
	scanf("%d", &cod);

	fseek(arquivoPtr, cod * sizeof(Produto), SEEK_SET);
	if(fread(&arquivoPtr, sizeof(Produto), 1, arquivoPtr) == 1)
	{
		printf("Quantidade vendida: ");
		scanf("%d", &qtdVendida);

		if(p.quantidadeEstoque >= qtdVendida){
			p.quantidadeEstoque -= qtdVendida;

			fseek(arquivoPtr, cod * sizeof(Produto), SEEK_SET);
			fwrite(&p, sizeof(Produto), 1, arquivoPtr);
			printf("Venda registrada com sucesso!\n");
		} 
		else
		{
			printf("Erro: Estoque insuficiente!\n");
		}
	}

	else
	{
		printf("Erro: Produto não encontrado\n");
	}
}

void buscarPorCodigo(FILE *arquivoPtr)
{
	
	int cod;
	struct Produto p;
	printf("\nCódigo do produto: ");
	scanf("%d", &cod);

	fseek(arquivoPtr, cod * sizeof(Produto), SEEK_SET);	
	if(fread(&arquivoPtr, sizeof(Produto), 1, arquivoPtr) == 1){
		printf("Descrição: %s\n", p.descricao);
		printf("Quantidade em estoque: %d\n", p.quantidadeEstoque);
		printf("Estoque minimo: %d\n ", p.minimoEstoque);
		printf("Preço de venda: %.2f\n", p.precoVenda);
	}
	else
	{
		printf("Erro: Produto não encontrado!\n");
	}

}


void buscarPorDescricao(FILE *arquivoPtr)
{
	char descricao[40];
	Produto p;
	int encontrado = 0;

	printf("Descricao do produto: ");
	scanf(" %[^\n]", descricao);

	fseek(arquivoPtr, 0, SEEK_SET);
	while(fread(&p, sizeof(Produto), 1, arquivoPtr) == 1)
	{
		if(strstr(p.descricao, descricao) != NULL);
		printf("Descricao: %s\n", p.descricao);
		printf("Quantidade em estoque: %d\n", p.quantidadeEstoque);
		printf("Estoque minimo: %d\n", p.minimoEstoque);
		printf("Preco de venda: %.2f\n\n", p.precoVenda);
		encontrado = 1;
	}

	if(!encontrado){
		printf("Nenhum produto encontrado com a descricao fornecida.\n");
	}
}

void relatorioEstoqueAbaixoMinimo(FILE *arquivoPtr){
	Produto p;
	int encontrado = 0;

	fseek(arquivoPtr, 0, SEEK_SET);
	printf("Produtos com estoque abaixo do nível mínimo:\n");
	while(fread(&p, sizeof(Produto), 1, arquivoPtr) == 1){
		if(p.quantidadeEstoque < p.minimoEstoque) {
			printf("Descricao: %s\n", p.descricao);
			printf("Quantidade em estoque: %d\n", p.quantidadeEstoque);
			printf("Estoque minimo: %d\n", p.minimoEstoque);
			printf("Preço de venda: %.2f\n\n", p.precoVenda);
			encontrado = 1;
		}
	}

	if(!encontrado) {
		printf("Nenhum produto com estoque abaixo do mínimo.\n");
	}
}


