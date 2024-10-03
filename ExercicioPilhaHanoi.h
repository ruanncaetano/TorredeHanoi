// tad
#define max 100
#define MAX_DISCOS 10
struct TpPilha
{
	int topo[max],base[max];
	int pilha[max]; // valores que vão representar os discos	
};
 void incializar(TpPilha &p,int qntd)
 {
 	int qntdPilha = max/qntd;
 	int i;
 	for(i=0;i<qntdPilha;i++)
 	{
 		p.base[i]= i* qntdPilha;
 		p.topo[i]= p.base[i] -1;
 	}
 }
 char vazia(TpPilha p,int np)
 {
 	return  p.topo[np] < p.base[np]; // vardade vazia
 }
 char cheia(TpPilha p, int np)
 {
 	return p.topo[np]+1 == p.base[np+1]; // p.base[np+1] estava sendo a proxima base
	 // o topo +1 e chegar na proxima base então esta cheia 
 }
 
 int elemTopo(TpPilha p,int np)
 {
 	return p.pilha[p.topo[np]];
 }
 
 void push(TpPilha &p,int np, int elem)
 {
 	p.pilha[++p.topo[np]]=elem;
 }
 int pop(TpPilha &p,int np)
 {
 	return p.pilha[p.topo[np]--];
 }
 
void imprimir(TpPilha p,int np)
{
	while(!vazia(p,np))
	{
		printf("%d", pop(p,np));
	}
}

