#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

ld p[130][130];
ld sp[130][130];
int V, DIM;

const double EPS = 1e-9;

void gauss (vector < vector<ld> > a, vector<ld> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
}


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
			sp[i][j]= p[i][j] + (j>0 ? sp[i][j-1] : 0); // sp[i][j] guarda a soma p[i][0]+...+p[i][j], servir� para otimizar o c�digo.
		}
	}
}

void solve(int DIM, ld& Esperanca, ld& Esperanca_com_Restricao){ // retorna os dois resultados dada a dimens�o DIM.
	V = 1<<DIM;
	CreateP();
	ll Soma=0, Soma_Rest=0;
	vector<vector<ld>> cT;
	cT.assign(V,vector<ld>(V+1,0)); // os coeficientes para o sistema linear para achar T[u].
	
	for(int i=0; i<V; i++){ // cria o sistema linear para achar T[u]
		if(i==V-1) continue;
		for(int j=0; j<V; j++){
			if(j==V-1) continue;
			if(j==i) cT[i][j]=1;
			else cT[i][j] = (ld) -p[i][j];
		}
		if(i==V-2) cT[i][V]=p[i][V-1];
	}
	vector<ld>T; // vamos resolver o sistema linear e achar T[u]
	gauss(cT,T);
	
	vector<vector<ld>> cE, cER; //os coeficientes para o sistema linear para achar as esperan�as, cE guardar� o sistema sem restri��es e cER com restri��es.
	cE.assign(V,vector<ld>(V+1,0)); cER.assign(V,vector<ld>(V+1,0));
	
	for(int i=0; i<V; i++){
		if(i==V-1) continue;
		for(int j=0; j<V; j++){
			if(j==V-1) continue;
			if(i==j) cE[i][j]=1, cER[i][j]=1;
			else cE[i][j]=-p[i][j], cER[i][j]=-p[i][j];
		}
		cE[i][V]=1;
		cER[i][V]=T[i]/T[0];
	}
	vector <ld> ansE, ansER;
	gauss(cE, ansE); gauss(cER, ansER);
	Esperanca = ansE[0]; Esperanca_com_Restricao=ansER[0];
}


int main(){
	ios::sync_with_stdio(false);
  	cin.tie(0);
  	DIM=7;
	V=1<<DIM;
	CreateP();
	ll Soma=0, SomaR=0, iR=0;
	
	ld Esperanca_3, Esperanca_com_Restricao_3, Esperanca_7, Esperanca_com_Restricao_7;
	solve(3, Esperanca_3, Esperanca_com_Restricao_3); solve(7, Esperanca_7, Esperanca_com_Restricao_7);
	cout << "O numero esperado de passos para a formiga ir de (0,0,0) a (1,1,1) eh " << Esperanca_3 << endl;
	cout << "O numero esperado de passos para a formiga ir de (0,0,0) a (1,1,1) passando imediatamente antes por (1,1,0) eh " << Esperanca_com_Restricao_3 << endl;
	cout << "O numero esperado de passos para a formiga ir de (0,0,0,0,0,0,0) a (1,1,1,1,1,1,1) eh " << Esperanca_7 << endl;
	cout << "O numero esperado de passos para a formiga ir de (0,0,0,0,0,0,0) a (1,1,1,1,1,1,1) passando imediatamente antes por (1,1,1,1,1,1,0) eh " << Esperanca_com_Restricao_7 << endl;
	return 0; 
}
