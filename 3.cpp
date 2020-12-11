#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
mt19937_64 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rg(0,1e18);

ld p[130][130];
ld sp[130][130];
int V, DIM;

const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<ld> > a, vector<ld> & ans) {
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
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}


ld InvDist(int v, int w){ // calcula o inverso da distancia entre v e w;
	int m = v^w ;
	ld ans=0;
	while(m) ans+=(ld)(m&1), m>>=1;
	ans = 1/sqrt(ans);
	return ans;
}

void CreateP(){ // cria a função P(v,w) que retorna a probabilidade de ir pra w saindo de v.
	for(int i=0; i< V; i++){
		ld den=0;
		for(int j=0; j< V; j++){
			if(j==i) continue;
			den+=InvDist(i,j);
		}
		for(int j=0; j< V; j++){
			if(j!=i) p[i][j] = InvDist(i,j)/den;
			sp[i][j]= p[i][j] + (j>0 ? sp[i][j-1] : 0); // sp[i][j] guarda a soma p[i][0]+...+p[i][j], servirá para otimizar o código.
		}
	}
}

int onde(int u, ld rd){ // recebe um numero rd random e indica pra qual vertice ir. É feita uma busca binária.
	int i=0, f=V-1;
	while(i!=f){
		int mid=(i+f)/2;
		if(sp[u][mid]<rd) i=mid+1;
		else f=mid;
	}
	return i;
}


int main(){
	ios::sync_with_stdio(false);
  	cin.tie(0);
  	DIM=7;
	V=1<<DIM;
	CreateP();
	ll Soma=0;
	
	vector <vector<ld>> a;
	a.assign(V,vector<ld>(V+1,0));
	for(int i=0; i<V; i++){
		if(i==V-1) continue;
		for(int j=0; j<V; j++){
			if(j==V-1) continue;
			if(j==i) a[i][j]=1;
			else a[i][j]= (ld) -p[i][j];
		}
		a[i][V]=(ld) 1;
	}
	
	vector < ld > ans;
	gauss(a,ans);
	cout << "ESPERADO: " << ans[0] << endl;
	return 0;
	
	for(int i=1; i<=100000000; i++){
		int u=0;
		while(u!=V-1){
			ld rd = (ld) rg(mt_rand)/1e18;
			int v = onde(u,rd);
			Soma++;
			u=v;
		}
		if(i%1000000==0) cout << i/1000000 << ' '<< (double) Soma/i << endl;
	}

}
