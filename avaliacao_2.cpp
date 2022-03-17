#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>

 int Sequencia=0;
 int iOpcao;

// rotina para podermos utilizar cor do sTexto (textcolor)
// e cor do fundo (textbackground) em um único comando.
// para chama-la de dentro do programa use  cores(x,y);
// onde x = numero da cor do sTexto  (textcolor)
//      y = numero da cor do fundo  (textbackground)
void cores(int ForgC, int BackC){   // para chamar
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
// esta rotina é só para a cor do sTexto
void textcolor(int newcolor){
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
     (csbi.wAttributes & 0xf0) | newcolor);
}
// rotina para podermos utilizar o comando gotoxy(linha,coluna)
// sem precisar carregar bibliotecas não disponíveis na Feevale.
void gotoxy(int x, int y) {
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void imp_autor(){
  setlocale(LC_ALL, "Portuguese");
  gotoxy(27,12);
  textcolor(10);
  printf("JOSÉ GARIBALDI DE CARVALHO");
  Sleep(1500);
  system("cls"); // comando para limpar o conteúdo da tela.
  textcolor(15);
}

bool NotNumero(int n){

  if(isdigit(n)){
    return false;
  }
  else{
    return true;
  }
}

struct Produto
{
 int Codigo;
 char Nome[30];
 int EstMinimo;
 float PrecoMedUnit;
 int Quantidade;
};
struct Produto oProduto[10];

void cadastrar_produto(int pSequencia){
int i;
int Codigo;

  textcolor(2);
  printf("\n                      |******************** Cadastro de produto *******************|");
  pSequencia=pSequencia+1;
  Sequencia=pSequencia;
	textcolor(7);
	printf("\n\nDigite o código do produto: ");
	scanf("%d",&Codigo);
  setbuf(stdin,NULL);

  for(i=1; i<=pSequencia; i++){
    if((Codigo==oProduto[i].Codigo)){
      printf("\nProduto %d já cadastrado digite outro código: ",Codigo);
      scanf("%d",&Codigo);
      setbuf(stdin,NULL);
      i=i-i;
    }
  }

	oProduto[pSequencia].Codigo=Codigo;
  printf("\nDigite o nome do produto: ");
	gets(oProduto[pSequencia].Nome);
  setbuf(stdin,NULL);
  printf("\nDigite o estoque minímo do produto: ");
	scanf("%d",&oProduto[pSequencia].EstMinimo);
  setbuf(stdin,NULL);
  oProduto[pSequencia].PrecoMedUnit=0;
  oProduto[pSequencia].Quantidade=0;

  printf("\nProduto %d cadastrado com sucesso!",oProduto[pSequencia].Codigo);
  printf("\n         Digite qualquer tecla para limpar a tela e voltar ao menu");
  getch();
}

void listar_todos_produtos(int pSequencia){
int i,j;
int espaco=0;
float valorTotal=0;

  textcolor(2);
  printf("\n                      |****************** Listagem de todos os produtos *****************|\n");
  textcolor(7);
	printf("    _____________________________________________________________________________________________________\n");
	printf("    |   Codigo do   ||        Nome do produto       ||   Quantidade   ||   Preço Médio   ||   Estoque   |\n");
	printf("    |   produto     ||                              ||   em estoque   ||   Unitário      ||   mínimo    |\n");
	printf("    |---------------------------------------------------------------------------------------------------|\n");
	for(i=1; i<=pSequencia; i++){
    valorTotal=valorTotal+(oProduto[i].Quantidade * oProduto[i].PrecoMedUnit);
    printf("    |%12d   ||",oProduto[i].Codigo);
    if(strlen(oProduto[i].Nome)-1 < 30){
      espaco=30-(strlen(oProduto[i].Nome)-1);
      printf("%s",oProduto[i].Nome);
      for(j=1; j<espaco; j++){
        printf(" ");
      }
    }
    else{
      printf("%s",oProduto[i].Nome);
    }
    printf("||%12d    ||%14.2f   ||%10d   |",oProduto[i].Quantidade,oProduto[i].PrecoMedUnit,oProduto[i].EstMinimo);
    printf("\n");
    printf("    |---------------------------------------------------------------------------------------------------|\n");
	}
  printf("\n         Valor total em estoque: %f",valorTotal);
  printf("\n         Digite qualquer tecla para limpar a tela e voltar ao menu");
  getch();
}

void listar_produto(int pProduto, int pSequencia){
int i,j;
int espaco;
char sVerificaProduto='N';
float valorTotal=0;

	for(i=1; i<=pSequencia; i++){
    if(pProduto==oProduto[i].Codigo){
      sVerificaProduto='S';
    }
	}

	if(sVerificaProduto=='S'){
    for(i=1; i<=pSequencia; i++){
      if(pProduto==oProduto[i].Codigo){
        valorTotal=valorTotal+(oProduto[i].Quantidade * oProduto[i].PrecoMedUnit);
        textcolor(2);
        printf("\n                      |****************** Listagem do Produto %d *****************|\n",pProduto);
        textcolor(7);
        printf("    _____________________________________________________________________________________________________\n");
        printf("    |   Codigo do   ||        Nome do produto       ||   Quantidade   ||   Preço Médio   ||   Estoque   |\n");
        printf("    |   produto     ||                              ||   em estoque   ||   Unitário      ||   mínimo    |\n");
        printf("    |---------------------------------------------------------------------------------------------------|\n");
        printf("    |%12d   ||",oProduto[i].Codigo);
        if(strlen(oProduto[i].Nome)-1 < 30){
          espaco=30-(strlen(oProduto[i].Nome)-1);
          printf("%s",oProduto[i].Nome);
          for(j=1; j<espaco; j++){
            printf(" ");
          }
        }
        else{
          printf("%s",oProduto[i].Nome);
        }
        printf("||%12d    ||%14.2f   ||%10d   |",oProduto[i].Quantidade,oProduto[i].PrecoMedUnit,oProduto[i].EstMinimo);
        printf("\n");
        printf("    |---------------------------------------------------------------------------------------------------|\n");

        printf("\n         Produto %d Valor total em estoque: %f",oProduto[i].Codigo,valorTotal);
        if(oProduto[i].Quantidade<oProduto[i].EstMinimo){
          textcolor(12);
          printf("\nQuantidade em estoque: %d do produto %d está abaixo do estoque mínimo %d ",oProduto[i].Quantidade,oProduto[i].Codigo,oProduto[i].EstMinimo);
          textcolor(7);
        }
      }
    }
	}
	else if(sVerificaProduto=='N'){
    gotoxy(45,14);
    textcolor(12);
    printf("O produto %d não está cadastrado",pProduto);
	}
	textcolor(7);
	printf("\n         Digite qualquer tecla para limpar a tela e voltar ao menu");
  getch();
}
void entrada_mercadoria(int pProduto, int pSequencia){
int i;
int quantidade;
float valorCompra;
char sVerificaProduto='N';

  for(i=1; i<=pSequencia; i++){
    if(pProduto==oProduto[i].Codigo){
      sVerificaProduto='S';
    }
	}

	if(sVerificaProduto=='S'){
    textcolor(2);
    printf("\n                      |****************** Entrada de mercadoria do produto %d *****************|\n",pProduto);
    textcolor(7);
    printf("\nDigite a quantidade da entrada: ");
    scanf("%d",&quantidade);
    setbuf(stdin,NULL);
    printf("\nDigite o valor total da entrada: ");
    scanf("%f",&valorCompra);
    setbuf(stdin,NULL);

    for(i=1; i<=pSequencia; i++){
      if(pProduto==oProduto[i].Codigo){
        oProduto[i].PrecoMedUnit = (oProduto[i].PrecoMedUnit+valorCompra)/(oProduto[i].Quantidade+quantidade);
        oProduto[i].Quantidade   =  oProduto[i].Quantidade+quantidade;
        printf("\nEntrada do produto %d efetuada com sucesso!",oProduto[i].Codigo);
        printf("\n         Digite qualquer tecla para limpar a tela e voltar ao menu");
        getch();
      }
    }
	}
	else if(sVerificaProduto=='N'){
    gotoxy(75,14);
    textcolor(12);
    printf("O produto %d não está cadastrado",pProduto);
    textcolor(7);
    printf("\n         Digite qualquer tecla para limpar a tela e voltar ao menu");
    getch();
	}
}

void saida_mercadoria(int pProduto, int pSequencia){
int i;
int quantidade;
char sVerificaProduto='N';
char sVerificaQuantidade='S';

  for(i=1; i<=pSequencia; i++){
    if(pProduto==oProduto[i].Codigo){
      sVerificaProduto='S';
    }
	}

	if(sVerificaProduto=='S'){
    textcolor(2);
    printf("\n                      |****************** Saída de mercadoria do produto %d *****************|\n",pProduto);
    textcolor(7);
    printf("\nDigite a quantidade da saída: ");
    scanf("%d",&quantidade);
    setbuf(stdin,NULL);

    for(i=1; i<=pSequencia; i++){
      if(pProduto==oProduto[i].Codigo){
        if(quantidade > oProduto[i].Quantidade){
          printf("\nA quantidade de saída %d é maior que a quantidade em estoque %d.",quantidade,oProduto[i].Quantidade);
          printf("\nDigite uma nova quantidade: ");
          scanf("%d",&quantidade);
          setbuf(stdin,NULL);
        }
      }
    }

    for(i=1; i<=pSequencia; i++){
      if(pProduto==oProduto[i].Codigo){
        if(quantidade>oProduto[i].Quantidade){
          printf("\nA quantidade de saída %d é maior que a quantidade em estoque %d.",quantidade,oProduto[i].Quantidade);
          sVerificaQuantidade='N';
        }
      }
    }

    if(sVerificaQuantidade=='S'){
      for(i=1; i<=pSequencia; i++){
        if(pProduto==oProduto[i].Codigo){
          oProduto[i].Quantidade   =  oProduto[i].Quantidade-quantidade;
          if(oProduto[i].Quantidade<oProduto[i].EstMinimo){
            printf("\nSaída do produto %d efetuada com sucesso!",oProduto[i].Codigo);
            textcolor(12);
            printf("\nQuantidade em estoque: %d do produto %d está abaixo do estoque mínimo %d ",oProduto[i].Quantidade,oProduto[i].Codigo,oProduto[i].EstMinimo);
            textcolor(7);
            printf("\n         Digite qualquer tecla para limpar a tela e voltar ao menu");
            getch();
          }
          else{
            printf("\nSaída do produto %d efetuada com sucesso!",pProduto);
            printf("\n         Digite qualquer tecla para limpar a tela e voltar ao menu");
            getch();
          }
        }
      }
    }
	}
	else if(sVerificaProduto=='N'){
    gotoxy(75,14);
    textcolor(12);
    printf("O produto %d não está cadastrado",pProduto);
    textcolor(7);
    printf("\n         Digite qualquer tecla para limpar a tela e voltar ao menu");
    getch();
	}
}

void Opcao_Menu(){
int i;

  textcolor(7);
  gotoxy(10,13);
  printf("Insira a opção:");
  scanf("%d",&iOpcao);
  setbuf(stdin,NULL);

  while((iOpcao<1)||(iOpcao>6)){
    textcolor(12);
    gotoxy(25,13);
    printf("Deve escolher uma opção correta do menu!!");
    Sleep(1500);
    gotoxy(25,13);
    for(i=0; i<=50; i++){
      printf(" ");
    }
    gotoxy(25,13);
    textcolor(15);
    scanf("%d",&iOpcao);
    setbuf(stdin,NULL);
  }
}

void limpar_tela(){
int i,j, x=25, y=13;

  for(i=0; i<=80; i++){
      gotoxy(x,y);
      for(j=0; j<=200; j++){
        printf(" ");
      }
    x=1;
    y=y+1;
  }
}

void chama_menu(){
  textcolor(7);
  printf("                      +============================================================+\n");
  printf("                      |                  Gerenciador de estoque                    |\n");
  printf("                      |              Escolha uma das opções do programa            |\n");
  printf("                      |                                                            |\n");
  printf("                      |Tecla 1: Cadastrar um produto                               |\n");
  printf("                      |Tecla 2: Listar os produtos cadastrados                     |\n");
  printf("                      |Tecla 3: Consultar os dados de um produto                   |\n");
  printf("                      |Tecla 4: Processar uma saída de mercadoria do estoque       |\n");
  printf("                      |Tecla 5: Processar uma entrada de mercadoria no estoque     |\n");
  printf("                      |Tecla 6: Sair do programa                                   |\n");
  printf("                      +============================================================+\n");
}

//-------------- AQUI COMEÇA O PROGRAMA -----------------//

main()
{

  int iCodigoProduto=0;

  setlocale(LC_ALL, "Portuguese");
  textcolor(7);
  chama_menu();
  Opcao_Menu();

  while(iOpcao!=6){
  switch(iOpcao)
  {
    case 1:
      cadastrar_produto(Sequencia);
      limpar_tela();
      Opcao_Menu();
      break;
    case 2:
      listar_todos_produtos(Sequencia);
      limpar_tela();
      Opcao_Menu();
      break;
    case 3:
      gotoxy(10,14);
      printf("Qual produto deseja listar?");
      scanf("%d",&iCodigoProduto);
	    setbuf(stdin,NULL);
      listar_produto(iCodigoProduto,Sequencia);
      limpar_tela();
      Opcao_Menu();
      break;
    case 4:
      gotoxy(10,14);
      printf("Para qual produto deseja fazer saída de mercadoria?");
      scanf("%d",&iCodigoProduto);
	    setbuf(stdin,NULL);
      saida_mercadoria(iCodigoProduto, Sequencia);
	    limpar_tela();
	    Opcao_Menu();
      break;
    case 5:
      gotoxy(10,14);
      printf("Para qual produto deseja fazer entrada de mercadoria?");
      scanf("%d",&iCodigoProduto);
	    setbuf(stdin,NULL);
	    entrada_mercadoria(iCodigoProduto,Sequencia);
	    limpar_tela();
	    Opcao_Menu();
      break;
    case 6:
      exit(0);
      break;
    default:
      printf("\n Fora da regra");
  }
  }
  exit(0);
  getch();
}
