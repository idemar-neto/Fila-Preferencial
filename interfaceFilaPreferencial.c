#include "filaPreferencial.c"

void inserir(PFILA f){
	int id;
	int ehPreferencial;
	char Preferencial = ' ';
	int res;
	printf("\nInsira o id:");
  scanf("%i",&id);
  printf("\nÉ Preferencial? [si/ni] ");
  scanf("%c",&Preferencial);
  while(Preferencial != 'i'){
  	switch(Preferencial){
			case 's' :  ehPreferencial = 1;break;
			case 'n' :  ehPreferencial = 0;break;
			default: {while (Preferencial != '\n') scanf("%c",&Preferencial);};
		}
		scanf("%c",&Preferencial);
	}
  res = inserirPessoaNaFila(f, id, ehPreferencial);
	if(res) printf("\nInsercao retornou true. O elemento de id: %i foi adicionado\n", id);
	else printf("Insercao retornou false.\n");
	exibirLog(f);
}

void atenderPreferencial(PFILA f){
	int res;
	int id;
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true. A pessoal de id=%i foi atendida (Preferencialmente).\n",id);
	else printf("Atendimento retornou false.\n");
	exibirLog(f);
}

void atenderGeral(PFILA f){
	int res;
	int id;
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if(res) printf("Atendimento retornou true. A pessoa de id=%i foi atendida.\n",id);
	else printf("Atendimento retornou false.\n");
	exibirLog(f);
}

void desistir(PFILA f){
	int res;
	int id;
	printf("\nInsira o id:");
  scanf("%i",&id);
	res = desistirDaFila(f, id);
	if(res) printf("Desistindo da fila retornou true. A pessoa de id=%i desistiu da fila\n", id);
	else printf("Desistindo da fila retornou false.\n");
	exibirLog(f);
}

void exibir(PFILA f){
	exibirLog(f);
}

void fimfila(PFILA f){
	printf("\n   p : Exibir fim da fila preferencial");
	printf("\n   g : Exibir fim da fila geral");
  printf("\n   k : sair\n");
  printf("\n");
	char comand = ' ';
	scanf("%c",&comand);
	while(comand != 'k'){
		switch(comand){
			case 'p' :  {if(f->fimPref != NULL)printf("\nFim fila preferencial: [%i, %i]\n", f->fimPref->id, f->fimPref->ehPreferencial);
										else printf("\nFim fila preferencial: NULL\n");}break;
			case 'g' :  {if(f->fimGeral != NULL)printf("\nFim fila geral: [%i, %i]\n", f->fimGeral->id, f->fimGeral->ehPreferencial);
										else printf("\nFim fila geral: NULL\n");}break;
			default: {while (comand != '\n') scanf("%c",&comand);};
		}
		scanf("%c",&comand);
	}
	printf("\n");
}

void iniciofila(PFILA f){
	printf("\n   p : Exibir inicio da fila preferencial");
	printf("\n   g : Exibir inicio da fila geral");
  printf("\n   k : sair\n");
  printf("\n");
	char comand = ' ';
	scanf("%c",&comand);
	while(comand != 'k'){
		switch(comand){
			case 'p' :  {if(f->inicioPref != NULL)printf("\nFim fila preferencial: [%i, %i]\n", f->inicioPref->id, f->inicioPref->ehPreferencial);
										else printf("\nFim fila preferencial: NULL\n");}break;
			case 'g' :  {if(f->inicioGeral != NULL)printf("\nFim fila geral: [%i, %i]\n", f->inicioGeral->id, f->inicioGeral->ehPreferencial);
										else printf("\nFim fila geral: NULL\n");}break;
			default: {while (comand != '\n') scanf("%c",&comand);};
		}
		scanf("%c",&comand);
	}
	printf("\n");
}

void help(){
  printf("Comandos validos: \n");
  printf("   i : menu inserir pessoa\n");
  printf("   a : atender fila geral\n");
  printf("   p : atender fila preferencial\n");
  printf("   d : menu de desistir da fila\n");
  printf("   e : exibir Log\n");
  printf("   f : exibir menu fim da fila\n");
  printf("   n : exibir menu inicio da fila\n");
  printf("   h : ajuda\n");
  printf("   q : sair\n");
  printf("\n");
}

int main(){
  PFILA f = criarFila();
  help();
  char comando = ' ';
  scanf("%c",&comando);
  while (comando != 'q'){
    switch (comando) {
      case 'i' : inserir(f); break;
      case 'p' : atenderPreferencial(f); break;
      case 'a' : atenderGeral(f); break;
      case 'd' : desistir(f); break;
      case 'e' : exibir(f); break;
      case 'f' : fimfila(f);break;
      case 'n' : iniciofila(f); break;
      case 'h' : help(); break;

      default: {while (comando != '\n') scanf("%c",&comando);};
    }
    scanf("%c",&comando);
  } 

  return 0;
}
