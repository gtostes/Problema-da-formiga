#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
mt19937_64 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rg(0,1e18);

ld p[130][130];
ld sp[130][130];
int V;

ld InvDist(int v, int w){ // calcula o inverso da distancia entre v e w;
	int m = v^w ;
	ld ans=0;
	while(m) ans+=(ld)(m&1), m>>=1;
	ans = 1/sqrt(ans);
	return ans;
}

void CreateP(){ // cria a fun��o P(v,w) que retorna a probabilidade de ir pra w saindo de v.
	for(int i=0; i< V; i++){
		ld den=0;
		for(int j=0; j< V; j++){
			if(j==i) continue;
			den+=InvDist(i,j);
		}
		for(int j=0; j< V; j++){
			if(j!=i) p[i][j] = InvDist(i,j)/den;
			sp[i][j]= p[i][j]; // sp[i][j] guarda a soma p[i][0]+...+p[i][j], servir� para otimizar o c�digo.
			if(j>0) sp[i][j]+=sp[i][j-1];
		}
	}
}

int onde(int u, ld rd){ // recebe um numero rd random entre 0 e 1 e indica pra qual vertice ir. � feita uma busca bin�ria.
	int i=0, f=V-1;
	while(i!=f){
		int mid=(i+f)/2;
		if(sp[u][mid]<rd) i=mid+1;
		else f=mid;
	}
	return i;
}

void Solve(int DIM, ld &Esperanca, ld& Esperanca_com_Restricao, ll it){ // retorna os valores das Esperan�as depois de um numero de itera��es it.
	V= 1<<DIM;
	ll Soma=0, SomaR=0, iR=0;
	CreateP();
	
	for(int i=1; i<=it; i++){
		int u=0;
		ll S=0;
		while(u!=V-1){
			ld rd= (ld) rg(mt_rand)/1e18;
			int v=onde(u,rd);
			S++; // guarda o numero de passos nessa iteracao.
			if(v==V-1 && u==V-2) iR++, SomaR+=S; // se esse caminho foi do tipo que passa em (1,..,1,0) imediatamente antes de (1,1,...,1) a gente guarda em SomaR e iR;
			u=v;
		}
		Soma+=S; // soma o numero de passos nesse ultimo caminho ao total
		if(i%100000==0) cout << i/100000 << endl; //s� pra marcar tempo
	}
	Esperanca = (ld) Soma/it; // retorna o valor esperado -> Soma do tamanho de todos os caminhos / Numero de caminhos
	Esperanca_com_Restricao = (ld) SomaR/iR; // valor esperado -> Soma do tamanho de todos caminhos com a restricao / Numero de caminhos com a restricao.
}

int main(){
	ios::sync_with_stdio(false);
  	cin.tie(0);
  	ld Esperanca_3, Esperanca_Rest_3, Esperanca_7, Esperanca_Rest_7;
  	int it3=100000000, it7=10000000;
  	Solve(3, Esperanca_3, Esperanca_Rest_3, it3);
  	Solve(7, Esperanca_7, Esperanca_Rest_7, it7);
  	cout << "a) O numero de passos esperado eh " << Esperanca_3 << endl;
  	cout << "b) O numero de passos esperado eh " << Esperanca_Rest_3 << endl;
  	cout << "c) O numero de passos esperado eh " << Esperanca_7 << endl;
  	cout << "d) O numero de passos esperado eh " << Esperanca_Rest_7 << endl;
}
