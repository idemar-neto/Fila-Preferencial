/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Seugndo Semestre de 2020                           **/
/**   <2020294> - Prof. Luciano Antonio Digiampietri                **/
/**                                                                 **/
/**   EP2 - Fila Preferencial                                       **/
/**                                                                 **/
/**   <Idemar Burssed dos Santos Neto>             <11857282>       **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
  res->inicioPref = NULL;
  res->fimPref = NULL;
  res->inicioGeral = NULL;
  res->fimGeral = NULL;
  return res;
}

int tamanho(PFILA f){
  PONT atual = f->inicioGeral;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

int tamanhoFilaPreferencial(PFILA f){
  PONT atual = f->inicioPref;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

/*Função alterada para que o elemento pudesse ser encontrado nas duas listas (Preferencial ou Geral)*/
PONT buscarID(PFILA f, int id, int filaPreferencial){
  PONT atual;
  if(filaPreferencial == false) atual = f->inicioGeral;
  if(filaPreferencial == true) atual = f->inicioPref;
   while (atual) {
    if (atual->id == id) return atual;
    atual = atual->prox;
  }
  return NULL;
}

/*Função auxiliar para encontrar o elemento anterior ao encontrado no BuscarID*/
PONT buscarIDant(PFILA f, int id, int filaPreferencial){
	PONT atual;
  if(filaPreferencial == false) atual = f->inicioGeral;
  if(filaPreferencial == true) atual = f->inicioPref;
   while (atual) {
    if (atual->prox->id == id) return atual;
    atual = atual->prox;
  }
  return NULL;
}

void exibirLog(PFILA f){
  int numElementos = tamanho(f);
  printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
  PONT atual = f->inicioGeral;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n");
  numElementos = tamanhoFilaPreferencial(f);
  printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
  atual = f->inicioPref;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n\n");
}


bool inserirPessoaNaFila(PFILA f, int id, int ehPreferencial){
  bool resposta = false;

  /* COMPLETAR */
  PONT end = buscarID(f, id, false);
  if(id < 0 || end!=NULL) resposta = false;
  else{
    PONT i = malloc(sizeof(ELEMENTO));
    i->id = id;
    i->ehPreferencial = ehPreferencial;
    if(f->inicioGeral == NULL){
    	f->inicioGeral = i;
    	f->fimGeral = i;
    }else{
    	f->fimGeral->prox = i;
    	f->fimGeral=i;
    }
    if(ehPreferencial == true){
    	PONT k = malloc(sizeof(ELEMENTO));
    	k->id = id;
    	k->ehPreferencial = ehPreferencial;
    	if(f->inicioPref == NULL){
    		f->inicioPref = k;
    		f->fimPref = k;
    	}else{
    		f->fimPref->prox = k;
    		f->fimPref = k;
    	}
    }
    resposta = true;
  }
  return resposta;
}



bool atenderPrimeiraDaFilaPreferencial(PFILA f, int* id){
  bool resposta = false;

  /* COMPLETAR */
  PONT apagar, apagar1, ant;
  int identidade;

  if(f->inicioGeral == NULL)resposta = false;
  else{
  	if(f->inicioPref!=NULL){
  		*id = f->inicioPref->id;
  		identidade = *id;
  		PONT end = buscarID(f, identidade, false);
  		if(end != f->inicioGeral) ant = buscarIDant(f, identidade, false);
  		apagar1 = end;
  		if(end == f->fimGeral){
  			if(end != f->inicioGeral) f->fimGeral = ant;
  			else f->fimGeral =NULL;
  		}
  		if(end == f->inicioGeral){
  			if(end->prox) f->inicioGeral = end->prox;
  			else f->inicioGeral = NULL;
  		}else if(end != f->inicioGeral){
  		  	if(end->prox) ant->prox = end->prox;
  		  	else ant->prox = NULL;
  		}
  		apagar = f->inicioPref;
  		if(f->inicioPref == f->fimPref) f->fimPref = NULL;
  		if(f->inicioPref->prox)f->inicioPref = f->inicioPref->prox;
  		else f->inicioPref = NULL;
  		free(apagar);
  		free(apagar1);

  	}else if(f->inicioPref == NULL && f->inicioGeral != NULL){
  		*id = f->inicioGeral->id;
  		apagar = f->inicioGeral;
  		if(f->inicioGeral->prox)f->inicioGeral = f->inicioGeral->prox;
  		else f->inicioGeral = NULL;
  		free(apagar);
  	}
  	resposta = true;
  }

  return resposta;
}



bool atenderPrimeiraDaFilaGeral(PFILA f, int* id){
  bool resposta = false;

  /* COMPLETAR */
  PONT apagar,apagar1, ant;
  int identidade;

  if(f->inicioGeral == NULL) resposta = false;
  else{
  	if(f->inicioGeral->ehPreferencial == true){
  		*id = f->inicioGeral->id;
  		identidade = *id;
  		PONT end = buscarID(f, identidade, true);
  		if(end != f->inicioPref) ant = buscarIDant(f, identidade, true);
  		apagar1 = end;
  		if(end == f->fimPref){
  			if(end != f->inicioPref)f->fimPref = ant;
  			else f->fimPref = NULL;
  		}
  		if(end == f->inicioPref){
        if(end->prox) f->inicioPref = end->prox;
        else f->inicioPref = NULL;
      }else if(end != f->inicioPref){
          if(end->prox) ant->prox = end->prox;
          else ant->prox = NULL;
      }

  		apagar = f->inicioGeral;
  		if(f->inicioGeral->prox)f->inicioGeral = f->inicioGeral->prox;
  		else f->inicioGeral=NULL;
  		free(apagar);
  		free(apagar1);
  	}else{
  		*id = f->inicioGeral->id;
  		apagar = f->inicioGeral;
  		if(f->inicioGeral == f->fimGeral)f->fimGeral = NULL;
  		if(f->inicioGeral->prox)f->inicioGeral = f->inicioGeral->prox;
  		else f->inicioGeral = NULL;
  		free(apagar);
  	}
  	resposta = true;
  }

  return resposta;
}



bool desistirDaFila(PFILA f, int id){
  bool resposta = false;

  /* COMPLETAR */
  PONT apagar, apagar1, ant, antPref;
  PONT end = buscarID(f, id, false);
  if(end == NULL) resposta = false;
  if(end != NULL){
  	if(end->ehPreferencial == true){
  		apagar = end;
  		PONT endPref = buscarID(f, id, true);
  		apagar1 = endPref;
  		if(endPref != f->inicioPref) antPref = buscarIDant(f, id, true);
  		if(endPref == f->fimPref){
  			if(endPref != f->inicioPref)f->fimPref = antPref;
  			else f->fimPref = NULL;
  		}
  		if(endPref == f->inicioPref){
  			if(endPref->prox)f->inicioPref = endPref->prox;
  			else f->inicioPref = NULL;
  		}else if(endPref != f->inicioPref){
  			if(endPref->prox) antPref->prox = endPref->prox;
  			else antPref->prox = NULL;
  		}
  		if(end != f->inicioGeral)ant = buscarIDant(f, id, false);
  		if(end == f->fimGeral){
  			if(end == f->inicioGeral)f->fimGeral = ant;
  			else f->fimGeral = NULL;
  		}
  		if(end == f->inicioGeral){
  			if(end->prox) f->inicioGeral = end->prox;
  			else f->inicioGeral = NULL;
  		}else if(end != f->inicioGeral){
  			if(end->prox) ant->prox = end->prox;
  			else ant->prox = NULL;
  		}
  		free(apagar);
  		free(apagar1);
  	}else{
  			apagar = end;
  			if(end != f->inicioGeral)ant = buscarIDant(f, id, false);
  			if(end == f->fimGeral) f->fimGeral = ant;
  			if(end == f->inicioGeral){
  				if(end->prox) f->inicioGeral = end->prox;
  				else f->inicioGeral = NULL;
  			}else if(end != f->inicioGeral){
  				if(end->prox) ant->prox = end->prox;
  				else ant->prox = NULL;
  			}
  			free(apagar);
  		}
  		resposta = true;
  	}

  return resposta;
}