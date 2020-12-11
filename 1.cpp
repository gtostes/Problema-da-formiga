#include<bits/stdc++.h>
#define ll long long
using namespace std;

mt19937_64 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<int> rg(0,15);

vector < int > prox[10];

struct pt{
	int x,y,z;
	pt (int x=0, int y=0, int z=0) : x(x), y(y), z(z) {};
	int dis(pt m){
		int u =  (x-m.x)*(x-m.x) + (y-m.y)*(y-m.y) + (z-m.z)*(z-m.z);
		if(u==1) return 3;
		if(u==2) return 2;
		if(u==3) return 1;
		return 0;
	}
};

int main(){
	ios::sync_with_stdio(false);
  	cin.tie(0);
  	vector < pt > pontos;
  	for(int i=0; i<=1; i++){
  		for(int j=0; j<=1; j++){
  			for(int k=0; k<=1; k++){
  				pontos.push_back(pt(i,j,k));
			}
		}
	}
	
  	for(int i=0; i<8; i++){
  		for(int j=0; j<8; j++){
  			int u = pontos[i].dis(pontos[j]);
  			for(int k=0; k<u; k++) prox[i].push_back(j);
		}
	}
	
	ll sp=0;
	ll tot=0;
	for(int i=1; i<=100000000; i++){
		int u=0;
		ll p=0;
		while(u!=7){
			int nxt = rg(mt_rand);
			p++;
			if(u==6 && prox[u][nxt]==7) sp+=p, tot++;
			u = prox[u][nxt];
		}
	//	sp+=p;
		if(i%1000000==0) cout << (double) sp/tot << endl;
//		if(i%1000000==0) cout << (double) tot/i << endl;
	}
}
