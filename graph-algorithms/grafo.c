/*
 * grafo.c
 *
 *  Created on: 27/09/2013
 *      Author: eccard
 */
// Felipe Lugão Eccard
// Rodrigo Magalhães Rodovalho
#include <stdio.h>
#include <stdlib.h>

#define INFINITY 0x3f3f3f3f
#define NODOS 1000

int distancia[NODOS];
int prof[4];

typedef struct lista
{
	int vertice;
	float custo;

	struct lista *prox;
}lista;
typedef struct ligacao{
	int origem;
	int destino;
	float custo;

	struct ligacao *prox;
}ligacao;

// para mexer no bellmanford
typedef struct lig{
	int origem;
	int destino;
	float custo;
}lig;

// estrutura para o algoritmo de dijkastra
typedef struct vetcontrol{
	float custochegada;
	int origem;
	int mark;
}vetcontrol;

lista* insere(lista *l,int v,float c)
{
	lista* p=(lista*)malloc(sizeof(lista));

	p->vertice=v;
	p->custo=c;
	p->prox=l;
	l=p;
	return l;
}
ligacao* inserelig(ligacao *lig,int origem,int destino,float custo){
	ligacao *l=(ligacao*)malloc(sizeof(ligacao));
	l->origem=origem;
	l->destino=destino;
	l->custo=custo;
	l->prox=lig;

	lig=l;
	return lig;
}
// inserir aresta no grafo
void inserirGrafo(lista **G,int v1,int v2,float c)
{
	G[v1]=insere(G[v1],v2,c);
//	G[v2]=insere(G[v2],v1,c);
}
//void inserirGrafo(lista **G,int v1,int v2,float c)
//{
//	lista* p = G[v1];
//	int control=0;
//	while(p!=NULL){
//		if(p->vertice==v2){
//			if(p->custo==0){
//				p->custo=c;
//				control=1;
//			}
//		}
//		p=p->prox;
//	}
//	if(control==0){
//		G[v1]=insere(G[v1],v2,c);
//		G[v2] = insere(G[v2],v1,0);
//	}
//
//}
void imprime(lista *l)
{
	lista *p=l;
	while(p!=NULL)
	{
		printf("[ %d , %g]", p->vertice,p->custo);
		p=p->prox;
	}
}
// imprimir o grafo
void imprimegrafo(lista **G, int numvertices)
{
	int i;

	for (i=0;i<numvertices;i++)
	{
		printf("\n Vertice %d :-->",i);
		imprime(G[i]);
	}
}

// ler um grafo de um arquivo
lista **import(FILE *f,int *ver,int *totalarestas)
{
	int vert,arest,i;

	fscanf(f,"%d",&vert);
	fscanf(f,"%d",&arest);

	*ver=vert;
	*totalarestas=arest;
	lista **G=(lista**)malloc(vert*sizeof(lista*));

	for (i=0;i<vert;i++)
		G[i]=NULL;

	for (i=0;i<arest;i++)
	{
		int v1,v2;
		float c;
		fscanf(f,"%d %d %f",&v1,&v2,&c);
		//      printf(" v1: %d v2: %d c: %f\n",v1,v2,c);
		inserirGrafo(G,v1,v2,c);
	}

	return G;
}
// 2 inserir nova aresta no grafo
void insearest(lista **G)
{
	int v1,v2;
	float c;

	printf(" Digite qual aresta deseja inserir no gravo. exe: 1,2  é aresta 1 ---- 2 ");
	scanf(" %d,%d",&v1,&v2);
	printf(" Digite o custo ");
	scanf(" %f",&c);

	inserirGrafo(G,v1,v2,c);
}


// exite para o camihos....
int existeca (int *vet,int pos, int vertice)
{
	int i;

	for (i=0;i<pos;i++)
	{
		if (vet[i]==vertice)
			return 1;
	}
	return 0;
}

void imprimecaminhos(int *vet,int pos,int destino, lista **G)
{
	int i;
	if (vet[pos-1]==destino)
	{
		printf("\n");
		for (i=0;i<pos;i++)
		{
			printf("%i ",vet[i]);
		}
	}
	else
	{
		lista *p=G[vet[pos-1]];
		while (p!=NULL)
		{
			if (!existeca(vet,pos,p->vertice))
			{
				vet[pos]=p->vertice;
				imprimecaminhos(vet,pos+1,destino,G);
			}
			p=p->prox;
		}
	}
}

int verificacaminho(int *vet,int pos,int destino, lista **G,int *valida)
{
	if (vet[pos-1]==destino){
		*valida = 1;
		return 0;
	}
	else
	{
		lista *p=G[vet[pos-1]];
		while (p!=NULL)
		{
			if (!existeca(vet,pos,p->vertice))
			{
				vet[pos]=p->vertice;
				verificacaminho(vet,pos+1,destino,G,valida);
			}
			p=p->prox;
		}
	}
}



int VerificaConexo(int *vet,lista**G,int tam,int *valida){
	int i,j;
	for(i=0;i<tam;i++){
		for(j=i;j<tam;j++){
			*valida = 0;
			if(i!=j){
				verificacaminho(vet,1,j,G,valida);
				if(*valida==0){
					return 0;
				}

			}
		}
	}

	return 1;
}

ligacao arestaminima(lista **grafo,int vertices){
	int i;
	float min=200000;
	ligacao lig;

	for (i=0;i<vertices;i++)
	{
		lista *p=grafo[i];
		while(p!=NULL)
		{
			if (p->custo<min){

				lig.origem=i;
				lig.destino= p->vertice;
				lig.custo=p->custo;

				min=p->custo;
			}

			p=p->prox;
		}
	}
	return lig;
}
int taprim(int *vet,int vert,int procura){
	int i;
	for (i=0;i<vert;i++)
		if (vet[i]==procura)
			return 1;

	return 0;
}
float custo2ver(lista **grafo,int ver1,int ver2){

	lista *l;
	l=grafo[ver1];

	while(l!=NULL){
		if(l->vertice==ver2)
			return l->custo;
		l=l->prox;
	}
	return 0;

}

// prim implementation
void algoritprim(lista **grafo,int totalvertices){
	int *prim;
	int i;
	int cont=0;

	float total=0;

	prim = (int*)malloc(totalvertices*sizeof(int));

	for (i=0;i<totalvertices;i++)
		prim[i]=-1;


	prim[0]=0;
	cont++;

	lista *p;
	p=grafo[0];
	float min=20000;
	while(p!=NULL){
		if(p->custo<min){
			min=p->custo;
			prim[cont]=p->vertice;
		}
		p=p->prox;
	}
	cont++;
	printf("\n (%d %d) |custo: %g",prim[0],prim[1],custo2ver(grafo,prim[0],prim[1]));
	total+=custo2ver(grafo,prim[0],prim[1]);

	lista * r;
	int vertice_origem=0;
	int vertice_destino=0;
	while(cont<totalvertices){
		min=200000;
		for (i=0;i<cont;i++){
			//			printf("\n ------------------------------grafo %d:",prim[i]);
			r=grafo[prim[i]];
			while(r!=NULL)
			{
				//                	printf("\n zzzzz %g", r->custo);
				if ((r->custo<min) && (!taprim(prim,cont,r->vertice))){
					vertice_origem=prim[i];//i;
					//                    	printf("  %d  %d",i,r->vertice);
					vertice_destino=r->vertice;
					min=r->custo;
					prim[cont]=r->vertice;
				}
				r=r->prox;
			}

		}

		printf("\n (%d %d) |custo: %g ",vertice_origem,vertice_destino,custo2ver(grafo,vertice_origem,vertice_destino));
		//		,custo2ver(grafo,vertice_origem,vertice_destino));
		cont++;
		total+=custo2ver(grafo,vertice_origem,vertice_destino);


	}
	printf("\n Custo mínimo : %g \n",total);
	//	for (i=0;i<totalvertices;i++)
	//	printf(" --- %d",prim[i]);
}
// pegar o vertice de custo minimo nao analizado
int dijkastraaux(vetcontrol *vetc,int totalvertices){
	int i;
	int verticemincusto;
	int min=30000;
	for (i=0;i<totalvertices;i++){
		if (vetc[i].custochegada<min && vetc[i].mark==0){
			min=vetc[i].custochegada;
			verticemincusto=i;
		}
	}
	return verticemincusto;
}
void auxdijkastra(vetcontrol *vetc,int origem,int destino){
	if (destino!=origem){
		destino=vetc[destino].origem;
		auxdijkastra(vetc,origem,destino);
		printf(" %d",destino);
	}
}

void dijkastra(lista ** gr, int origem,int destino,int totalvertices){

	vetcontrol *vetc;

	vetc = (vetcontrol*)malloc(totalvertices*sizeof(vetcontrol));
	int i;
	lista *p;
	float custo;
	int verta;
	for (i=0;i<totalvertices;i++){
		vetc[i].custochegada=30000000;
		vetc[i].origem=i;
		vetc[i].mark=0;
	}

	vetc[origem].custochegada=0;
	vetc[origem].origem=origem;

	verta=origem;

	while(verta!=destino){
		//		pegar a lista do vertice de menor custo atual
		custo=0;
		verta=dijkastraaux(vetc,totalvertices);
		p=gr[verta];

		vetc[verta].mark=1;

		while(p!=NULL){

			//printf("\n--- : %d",p->vertice);
			custo= vetc[verta].custochegada+ p->custo;
			if (custo<vetc[p->vertice].custochegada ){
				vetc[p->vertice].custochegada=custo;
				vetc[p->vertice].origem=verta;
				//printf("\n -------custo: %g",custo);
			}
			p=p->prox;
		}

	}
	printf("custo total: %g \ncaminho: ",vetc[destino].custochegada);

	auxdijkastra(vetc,origem,destino);
	printf(" %d",destino);
	/*
	int r;
	r=destino;
	while(r!=origem){
		printf(" %d",r );
		r=vetc[r].origem;
	}
	printf(" %d",r );
	 */
}
// profundidade
void ImprimeProfundidade(lista **G,int no,int *vet,int *i){
	//   printf("%d ",no);
	prof[*i]=no;
	vet[no] = 1;
	lista *p;
	p=G[no];
	while(p!=NULL){
		if(vet[p->vertice]==0){
			*i=*i+1;
			ImprimeProfundidade(G,p->vertice,vet,i);
		}
		p=p->prox;
	}
}

// bellmanford
void bfp(lista ** gr, int origem,int destino,int totalvertices){

	vetcontrol *vetc;

	vetc = (vetcontrol*)malloc(totalvertices*sizeof(vetcontrol));
	int i;
	lista *p;
	float custo;
	int verta;
	int *vet;
	vet = (int*)malloc(totalvertices*sizeof(int));
	for(i=0;i<totalvertices;i++){
		vet[i] = 0;
	}
	//	int prof[totalvertices];
	int lugar=0;
	ImprimeProfundidade(gr,origem,vet,&lugar);

	for (i=0;i<totalvertices;i++){
		printf(" %d \n",prof[i]);
	}

	for (i=0;i<totalvertices;i++){
		vetc[i].custochegada=30000000;
		vetc[i].origem=i;
		vetc[i].mark=0;
	}

	vetc[origem].custochegada=0;
	vetc[origem].origem=origem;

	verta=origem;

	while(verta!=destino){
		//		pegar a lista do vertice de menor custo atual
		custo=0;
		//verta=dijkastraaux(vetc,totalvertices);
		p=gr[verta];

		vetc[verta].mark=1;

		while(p!=NULL){

			//printf("\n--- : %d",p->vertice);
			custo= vetc[verta].custochegada+ p->custo;
			if (custo<vetc[p->vertice].custochegada ){
				vetc[p->vertice].custochegada=custo;
				vetc[p->vertice].origem=verta;
				//printf("\n -------custo: %g",custo);
			}
			p=p->prox;
		}

	}
	printf("custo total: %g \ncaminho: ",vetc[destino].custochegada);

	auxdijkastra(vetc,origem,destino);
	printf(" %d",destino);
	/*
	int r;
	r=destino;
	while(r!=origem){
		printf(" %d",r );
		r=vetc[r].origem;
	}
	printf(" %d",r );
	 */
}
void BellmanFord(lig arestas[], int totalaresta, int totalvertice, int origem,int destino) {
	int i,j,trocou;
	for (i = 0; i < totalvertice; i++) {
		distancia[i] = INFINITY;
	}
	distancia[origem]=0;
	for (i = 0; i < totalvertice; i++) {
		trocou = 0;
		for (j = 0; j < totalaresta; j++) {
			if (distancia[arestas[j].destino] > distancia[arestas[j].origem] + arestas[j].custo) {
				distancia[arestas[j].destino] = distancia[arestas[j].origem] + arestas[j].custo;
				trocou=1;
			}
		}
		// se nenhuma iteração teve efeito, futuras iterações estão dispensadas
		if (trocou==0) break;
	}
	// usado somente para detectar ciclos negativos (dispensável)
	for (i = 0; i < totalaresta; i++) {
		if (distancia[arestas[i].destino] > distancia[arestas[i].origem] + arestas[i].custo) {
			printf("Ciclo negativo de pesos de arestas detectado");
			break;
		}
	}
//	for (i = 0; i < totalvertice; i++) {
//		printf("A distancia mais curta entre os nodos %d e %d eh %d\n",origem,i,distancia[i]);
//	}

	printf("A distancia mais curta entre os nodos %d e %d eh %d\n",origem,destino,distancia[destino]);


}


// fluxo maximo
void fluxomaximo(int *vet,int pos,int destino, lista **G)
{
	int i;
	if (vet[pos-1]==destino)
	{
		printf("\n");
		for (i=0;i<pos;i++)
		{
			printf("%i ",vet[i]);
		}
	}
	else
	{
		lista *p=G[vet[pos-1]];
		while (p!=NULL)
		{
			if (!existeca(vet,pos,p->vertice))
			{
				vet[pos]=p->vertice;
				imprimecaminhos(vet,pos+1,destino,G);
			}
			p=p->prox;
		}
	}
}

int main ()
{
	lista **gr;
	FILE *arq;
	int *vet3;
	//char nome_arq[]="entrada2.txt";
	char nome_arq[21];
	int op,ver,totalaresta;
	int ori,dest;
	int i;

	do
	{
		printf("\n\n MENU \n");
		printf(" 1 para ler um grafo de um arquivo \n");
		printf(" 2 imprimir o grafo \n");
		printf(" 3 para inserir uma nova aresta no gravo\n");
		printf(" 4 Imprimir todos o caminho entre determinada origem e destino\n");
		printf(" 5 Verificar se existe caminho entre determinada origem e destino \n");
		printf(" 6 Verificar se o grafo é conexo \n");
		printf(" 7 para obter a arvore geradora minima (algoritmo de prim) sair \n");
		printf(" 8 para obter o caminho de custo minimo entre vertices(algoritmo de dijkstra \n");
		printf(" 9 bfp\n");
		scanf(" %d",&op);

		switch (op)
		{
		case 1 :
		{
			//			printf("Digite o nome do arquivo a ser aberto\n");
			//			scanf(" %20[^\n]",nome_arq);
			//			arq = fopen(nome_arq,"rt");
			arq = fopen("grafobf3.txt","rt");
			if(arq != NULL)
			{
				gr = import(arq,&ver,&totalaresta);
				printf("Arvore importada com sucesso\n");
			}


			else
				printf("Erro na abertura do arquivo\n");
		}
		break;
		case 2:
			imprimegrafo(gr,ver);
			break;
		case 3:
			insearest(gr);
			break;
		case 4:
			printf(" Digite o vetice de origem e de destino. exe: 1,3 ");
			scanf("%d,%d",&ori,&dest);
			int *vet=(int*)malloc(ver*sizeof(int));
			for (i=0;i<ver;i++)
				vet[i]=-1;
			vet[0]=ori;
			imprimecaminhos(vet,1,dest,gr);
			break;
		case 5:
			printf(" Digite o vetice de origem e de destino. exe: 1,3 ");
			scanf("%d,%d",&ori,&dest);
			int *vet2=(int*)malloc(ver*sizeof(int));
			int valida;
			valida = 0;
			for(i=0;i<ver;i++)
				vet2[i]=-1;
			vet2[0]=ori;
			//printf("%d",verificacaminho(vet2,1,dest,gr));
			verificacaminho(vet2,1,dest,gr,&valida);
			printf("%d\n",valida);
			if(valida>0){
				printf("Existe Caminho \n");
			}
			else{
				printf("Não existe Caminho \n");//			arq = fopen(nome_arq,"rt");
			}
			break;
		case 6:
			vet3=(int*)malloc(ver*sizeof(int));
			for (i=0;i<ver;i++)
				vet3[i]=-1;
			vet3[0]=0;
			int valida2 = 0;
			if(VerificaConexo(vet3,gr,ver,&valida2)){
				printf("Grafo Conexo");
			}
			else{
				printf("Grafo Desconexo");
			}
			break;
		case 7:
			algoritprim(gr,ver);
			break;
		case 8:
			printf(" Digite o vetice de origem e de destino. exe: 1,3 ");
			scanf("%d,%d",&ori,&dest);
			dijkastra(gr,ori,dest,ver);
			break;
		case 9:{
			//			lig Arestas[10] = {{0, 1, 5},  {0,2, 8}, {0,3, -4}, {1,0, -2},
			//					{2, 1, -3}, {2,3, 9}, {3,1, 7}, {3,4, 2},
			//					{4,0, 6}, {4,2, 7}};
			// BellmanFord(Estrutura, arestas, vertices,origem);
			lista *p;
			lig Arestas[totalaresta];
			int count=0;
			int i;
			for (i=0;i<ver;i++){
				p=gr[i];
				while(p!=NULL){
					Arestas[count].origem=i;
					Arestas[count].destino=p->vertice;
					Arestas[count].custo=p->custo;
					count++;
					p=p->prox;
				}
			}
			BellmanFord(Arestas, totalaresta, ver, 0,5);

		}
		break;
		}
	}while(op!=10);
	return 0;
}


