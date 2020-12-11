#include<bits/stdc++.h>
#define ll long long
using namespace std;
const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
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
//	ios::sync_with_stdio(false);
//  	cin.tie(0);
  	vector < pt > pontos;
  	for(int i=0; i<=1; i++){
  		for(int j=0; j<=1; j++){
  			for(int k=0; k<=1; k++){
  				pontos.push_back(pt(i,j,k));
			}
		}
	}
	vector <vector<double>> a;
	a.assign(8,vector<double>(9,0));
	for(int i=0; i<8; i++){
		if(i==7) continue;
		for(int j=0; j<8; j++){
			if(j==7) continue;
			if(j==i) a[i][j]=1;
			else a[i][j]= (double) -pontos[i].dis(pontos[j])/16;
		}
		if(i==6) a[i][8]=(double) pontos[i].dis(pontos[7])/16;
	//	for(int j=0; j<9; j++) printf("%5.3lf ", a[i][j]);
	}
	
	vector < double > ans, ansE;
	gauss(a,ans);
	for(auto x: ans) cout << x << ' ';
	cout << endl;

	vector <vector<double>> b;
	b.assign(8,vector<double>(9,0));

	for(int i=0; i<8; i++){
		if(i==7) continue;
		for(int j=0; j<8; j++){
			if(j==7) continue;
			if(i==j) b[i][j]=1;
			else{
				b[i][j] = (double) -pontos[i].dis(pontos[j])/16;
			}
		}
		b[i][8]=ans[i]/ans[0];
		for(int j=0; j<9; j++) printf("%5.3lf ", b[i][j]);
		cout << endl;
	}
	gauss(b,ansE);
	for(auto x: ansE) cout << x << ' ';
	cout << endl;
}
