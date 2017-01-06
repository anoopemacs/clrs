// longest common subsequence
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int lcs_bruteforce(int x[], int m, int y[], int n) { // [1,m], [1,n]
    // returns the length of lcs
    if(m==0 || n==0) return 0;
    if(x[m]==y[n]) return lcs_bruteforce(x, m-1, y, n-1) + 1;
    return max(lcs_bruteforce(x, m-1, y, n), lcs_bruteforce(x, m, y, n-1));
}

int lcs_bottomup(int x[], int m, int y[], int n, int b[][7], int c[][7]) {
    for (int i=1; i<=m; ++i) c[i][0] = 0;
    for (int j=0; j<=n; ++j) c[0][j] = 0;
    for (int i=1; i<=m; ++i) {
	for (int j=1; j<=n; ++j) {
	    if(x[i]==y[j]) {
		c[i][j] = c[i-1][j-1]+1;
		b[i][j] = 'N';
	    } else if (c[i-1][j] >= c[i][j-1]) {
		c[i][j] = c[i-1][j];
		b[i][j] = '|';
	    } else {
		c[i][j] = c[i][j-1];
		b[i][j] = '-';
	    }
	}
    }
}

void print_lcs(int b[][7], int x[], int i, int j) {
    if (i==0 || j==0) return;
    if (b[i][j]=='N') {
	print_lcs(b, x, i-1, j-1);
	printf("%c ", x[i]);
    } else if (b[i][j]=='|') {
	print_lcs(b, x, i-1, j);
    } else {
	print_lcs(b, x, i, j-1);
    }
}

int main() {
    int x[] = {'h', 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
    int y[] = {'h', 'B', 'D', 'C', 'A', 'B', 'A' };
    int Nx = sizeof(x)/sizeof(x[0]);
    int Ny = sizeof(y)/sizeof(y[0]);
    cout << lcs_bruteforce(x, Nx-1, y, Ny-1) << endl;

    int b[8][7];
    int c[8][7];
    lcs_bottomup(x, Nx-1, y, Ny-1, b, c);
    print_lcs(b, x, Nx-1, Ny-1);
    
    return 0;
}





