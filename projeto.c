#include <stdio.h>
#include <stdlib.h>

typedef struct ListaSimples
{
  short int chave;
  struct ListaSimples * prox;
}TipoListaSimples;

TipoListaSimples * criaListaSimples() //Cria Lista Simples
{
  TipoListaSimples * cabeca = (TipoListaSimples *)malloc(sizeof(TipoListaSimples));
  if(cabeca != NULL) //Verifica se a alocação foi realizada com sucesso
    {
      cabeca->chave=-1;
      cabeca->prox=NULL;
    }
  return cabeca;
}

void insereInicioListaSimples(short int k,  TipoListaSimples *cabeca)//Insere elemento no inicio da lista
{
  TipoListaSimples * end = (TipoListaSimples *)malloc(sizeof(TipoListaSimples));
  end->chave = k;
  end->prox = cabeca->prox;
  cabeca->prox = end;
}

void exibirListaInvertida(TipoListaSimples *elemento, FILE *fp) //Recebe o endereço do primeiro elemento e exibe ao contrário
{
  if(elemento != NULL)
    {
      exibirListaInvertida(elemento->prox, fp);
      fprintf(fp, "%d", elemento->chave);
    }
}

short int verificaCaracter(char c) //Verifica o caractere encontrado
{
  if(c == '0')
    return 0;
  else if(c == '1')
    return 1;
  else if(c == '2')
    return 2;
  else if(c == '3')
    return 3;
  else if(c == '4')
    return 4;
  else if(c == '5')
    return 5;
  else if(c == '6')
    return 6;
  else if(c == '7')
    return 7;
  else if(c == '8')
    return 8;
  else if(c == '9')
    return 9;
}

void insereStringLista(char * numero, TipoListaSimples * cabeca)//Converte string e insere em uma lista
{
  if(*numero != '\0')
    {
      insereInicioListaSimples(verificaCaracter(*numero),cabeca);
      insereStringLista((char *)(numero+1),cabeca);
    }
}


TipoListaSimples * insereFimListaSimples(short int k, TipoListaSimples *no) //Insere um novo elemento no final de uma lista
{
  if(no->prox == NULL)
    {
      TipoListaSimples *insere = (TipoListaSimples *)malloc(sizeof(TipoListaSimples));
      insere->chave = k;
      insere->prox = NULL;
      no->prox = insere;
      return insere;
    }
  else
    insereFimListaSimples(k,no->prox);
}

void Multiplicacao(TipoListaSimples * fator1, TipoListaSimples * fator2, TipoListaSimples * produto)
{
  TipoListaSimples * elementoFator1; // Percorre o primeiro fator
  TipoListaSimples * cabecaProduto; //Armazena o ponteiro para o elemento da lista onde será feita a soma da multiplicação
  TipoListaSimples * elementoProduto; //Percorre a lista de produtos em todo multiplicao
  TipoListaSimples * p;
  fator2 = fator2->prox; //Percorre o segundo fator, multiplicando o primeiro
  cabecaProduto =    produto;
  while(fator2 != NULL) //Percorre a lista até o final
    {
      elementoFator1 = fator1->prox; //Inicia o primeiro fator em toda Multiplicacao
      elementoProduto = cabecaProduto->prox; //Indica em que elemento da lista será o primeiro a receber a soma

      while(elementoFator1 != NULL) //Percorre a lista até o final
        {

    	  if(elementoProduto == NULL) //Caso o elemento atual da lista do produto seja NULO, cria um novo elemento do final da lista para receber o valor
    	    elementoProduto = insereFimListaSimples(0,produto);

    	  elementoProduto->chave += elementoFator1->chave * fator2->chave; //Na posicao atual da lista de produto, recebe a multiplicação
    	  p = produto->prox;
        while(p != NULL)
        {
          if(p->chave > 9) //Caso na posicao atual o valor seja maior que 9, é enviado para a próxima cédula, a dezena correspondente.
              {
          if(p->prox == NULL) // Caso a próxima posição esteja vazia, uma nova posição no final da lista é criada.
            insereFimListaSimples(0,produto);

            (p->prox)->chave += (((p->chave)-(p->chave % 10))/10);
            //A próxima cédula da lista irá receber o seu próprio conteúdo + o resultado da "dezena" da cédula atual.
            p->chave = p->chave % 10;
            //A cédula atual recebe o resto do seu contéudo dividido por 10.
          }
          p = p->prox;
        }
        elementoProduto = elementoProduto->prox;//Passa para o próximo elemento da lista de produtos
    	  elementoFator1 = elementoFator1->prox; //Passa para o próximo elemento da lista de fatores
        }
      fator2 = fator2->prox; 
      cabecaProduto = cabecaProduto->prox; //Variável que mantém o controle sobre e
    }


}

void destroiLista(TipoListaSimples **cabeca) //Desaloca uma lista
{
  if(*cabeca != NULL)
    {
      destroiLista(&((*cabeca)->prox));
      free(*cabeca);
    }
}

int main()
{
  char *num1, *num2;
  FILE *fp, *fpr;

  fp = fopen("resultado", "a"); //Abre o arquivo para escrita.
  if (fp == NULL) {
    printf("Nao foi possivel abrir um resultado.txt para a escrita.\n");
    exit(0);
  }

  fpr = fopen("parametros", "r"); //Abre o arquivo para leitura.
  if (fpr == NULL){
    printf("Nao foi possivel abrir um arquivo chamado parametros.txt para a leitura. \n");
    exit(0);
  }

  while (fscanf(fpr, "%ms %ms", &num1, &num2) != EOF){ //Leitura de cada elemento por linha.

  TipoListaSimples * fator1 = criaListaSimples();
  TipoListaSimples * fator2 = criaListaSimples();
  TipoListaSimples * produto = criaListaSimples();
  
  insereStringLista(num1,fator1); //Recebe string, converte para inteiro e coloca na lista
  insereStringLista(num2,fator2);

  Multiplicacao(fator1,fator2,produto);

  exibirListaInvertida(produto->prox, fp);
  fprintf(fp, "\n");

  destroiLista(&fator1);
  destroiLista(&fator2); 
  destroiLista(&produto);
  free(num1);
  free(num2);
  }

  fclose(fpr);
  fclose(fp);
  return 0;
}
