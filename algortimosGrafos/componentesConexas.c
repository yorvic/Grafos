/* Yorvic Godoy
Descripcion:ComponentesConexas */
/*========================<Bibliotecas>=========================*/
#include <stdio.h>
/*========================< Constantes >========================*/
#define	N	50
#define	MAX_MATRIZ	100
#define	INF			9999
/*===========================< Tipos >==========================*/
typedef int vertice;
typedef int _vertices[N];
typedef float  _matriz [MAX_MATRIZ][MAX_MATRIZ];

typedef struct{
	vertice v;
	vertice w;
}_arco;

typedef struct {
	int n;
	_vertices v;
}_conjVertices;

typedef struct {
	int n;
	_arco conjA[N];
}_conjuntoArcos;
/*========================< Prototipos >========================*/
void componentesConexas(_matriz a,int n,_conjVertices c[],int *p);
int buscarCom (vertice v,_conjVertices c[],int nConj);			//Busca a que componenteConexa pertenece v,retorna pos
/*=<ProTotipos de Conjuntos de tipo Vertijes>=*/
int  iguales (_conjVertices a,_conjVertices b);
int pertenece (_conjVertices a,vertice v);
int subConj (_conjVertices a,_conjVertices b);
void insertarEnConj (_conjVertices *a,vertice v);
void diferencia (_conjVertices a,_conjVertices b,_conjVertices *c);
void unircjto(_conjVertices A, _conjVertices B, _conjVertices *C);
/*========================<Funcion Main>========================*/
int main(){
	/* IMPORTANTE LOS INDICES EMPIEZAN DESDE 1 */
	_matriz m;	//Matriz de Ady
	int n;		//Cantidad de Vertices
	_conjVertices c[N];		//Conj de Vertices donde se almacenará los vertices de cada componente conexa
	int p;		//Cantidad de Componentes Conexas
	int i,j;
	/* Matriz de Prueba */
	n=4;
	m[1][2]=m[2][1]=3;
	m[3][4]=m[4][3]=10;
	componentesConexas(m,n,c,&p);
	/* Mostrar el Resultado por pantalla */
	printf("\nNumero de Componentes Conexas: P=%d\n",p);
	for( i=1 ; i<=n; i++ ){
		if(c[i].n){
			printf("\nComponente #%d : {",i);
			for( j=1 ; j<=c[i].n ; j++ )
				printf("%d,",c[i].v[j]);
			printf("}");
		}
	}
	return 0;
}
/*========================<ComponentesConexas>========================*/
void componentesConexas(_matriz a,int n,_conjVertices c[],int *p){
	int h;
	int i,j;
	_arco arco;
	_arco arregArco[N];
	int nArcos;

	//Inicializa c
	for( i=1 ; i<=n ; i++ ){
		c[i].n=1;
		c[i].v[1]=i;
	}

	*p=n;
	//VECTOR DE ARCOS
	nArcos=0;
	for( i=1 ; i<=n ; i++ ){
		for( j=i+1 ; j<=n ; j++ ){
			if( a[i][j] ){
				nArcos++;
				arregArco[nArcos].v=i;
				arregArco[nArcos].w=j;
			}
		}
	}
	h=0;
	while(nArcos){
		h++;
		arco.v=arregArco[h].v;
		arco.w=arregArco[h].w;
		i=buscarCom(arco.v,c,n);
		j=buscarCom(arco.w,c,n);
		nArcos--;
		if(i!=j){
			unircjto(c[i],c[j],&c[i]);
			c[j].n=0;
			*p=*p-1;
		}
	}
}
/*========================<Insertar en Conj>========================*/
void insertarEnConj (_conjVertices *a,vertice v){
	int n;
	if(!pertenece(*a,v)){
		n=a->n+1;
		a->n=n;
		a->v[n]=v;
	}
}
/*========================<pertenece>========================*/
int pertenece (_conjVertices a,vertice v){
	int i=1,band=0;
	while(!band && i<=a.n){
		if( v==a.v[i] )
			band=1;
		i++;
	}
	return band;
}
/*========================<diferencia>========================*/
void diferencia (_conjVertices a,_conjVertices b,_conjVertices *c){
	int i;
	c->n=0;
	for( i=1 ; i<=a.n ; i++ )
		if( !pertenece(b,a.v[i]) )
			insertarEnConj(c,a.v[i]);
}
/*========================<VerticeMenorCosto>========================*/
vertice MenorCosto (_conjVertices z,float costo[]){
	int i,aux,costV=INF+1;
	int aux2;
	for( i=1 ; i<=z.n ; i++ ){
		aux=z.v[i];
		if( costo[aux]<=costV ){
			costV=costo[aux];
			aux2=aux;
		}
	}
	return aux2;
}
/*========================<igualesConj>========================*/
int  iguales (_conjVertices a,_conjVertices b){
	return (a.n==b.n && subConj(a,b));
}
/*========================<subConj>========================*/
int subConj (_conjVertices a,_conjVertices b){
	int i,band=1;
	for( i=1 ; i<=a.n ; i++ )
		if( !pertenece(b,a.v[i]) )
			band=0;
	return  band;
}
/*========================<Union de Conjuntos>========================*/
void unircjto(_conjVertices A, _conjVertices B, _conjVertices *C){
	int i;
	*C = A;
	for (i = 1; i <= B.n; i++)
		if (!pertenece(A, B.v[i]))
			insertarEnConj(C, B.v[i]);
}
/*========================<BuscarCompoVer>========================*/
int buscarCom (vertice v,_conjVertices c[],int nConj){
	int i,j,aux;

	for( i=1 ; i<=nConj; i++ )
		for( j=1 ; j<=c[i].n ; j++ )
			if( v==c[i].v[j] )
				aux=i;
	return aux;
}

