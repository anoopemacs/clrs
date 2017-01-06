#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int matrix_chain_order_bruteforce(int p[], int b, int e) { //[b,e]
    if(b==e) return 0;
    int ret = INT_MAX;
    for (int k=b; k<=e-1; ++k) {
        ret = min(ret, matrix_chain_order_bruteforce(p, b, k) + matrix_chain_order_bruteforce(p, k+1, e) + p[b-1]*p[k]*p[e]);
    }
    return ret;
}

const int N=7;

int matrix_chain_order_bottomup(int p[], int m[][N], int s[][N], int n) {
    for(int i=1; i<=n; ++i)
	m[i][i] = 0;
    
    for(int l=2; l<=n; ++l) { // l is the chain length of matrices to be multiplied
	for(int i=1; i<=n-l+1; ++i) { // i is begin of chain, last chain of this loop is [i, n] hence n-i+1 >= l
	    int j = i+l-1; // j is end of chain
	    m[i][j] = INT_MAX;
	    int q;
	    for(int k=i; k<=j-1; ++k) {// k is the cut index i<=k<j
		q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
		if (q<m[i][j]) {
		    m[i][j] = q;
		    s[i][j] = k;
		}
	    }
	}
    }
    return m[1][6];
}

void print_optimal_parens(int s[][N], int i, int j) {
    if (i==j)
	cout << "A" << i << " ";
    else {
	cout << "(";
	print_optimal_parens(s, i, s[i][j]);
	print_optimal_parens(s, s[i][j]+1, j);
	cout << ")";
    }
}

int matrix_chain_order_topdown_aux(int p[], int m2[][N], int s2[][N], int i, int j) {
    if (m2[i][j] < INT_MAX )
	return m2[i][j];
    if (i==j)
	m2[i][j] = 0;
    else {
	int q;
	for(int k=i; k<=j-1; ++k) {
	    q = matrix_chain_order_topdown_aux(p, m2, s2,  i, k) +
                matrix_chain_order_topdown_aux(p, m2, s2, k+1, j) +
		p[i-1]*p[k]*p[j];
	    if(q<m2[i][j]) {
		m2[i][j]=q;
		s2[i][j]=k;
	    }
        }
    }
    return m2[i][j];     
}

int matrix_chain_order_topdown(int p[], int m2[][N], int s2[][N], int n) {
    for(int i=1; i<=n; ++i)
	for(int j=1; j<=n; ++j)
	    m2[i][j]=INT_MAX;
    return matrix_chain_order_topdown_aux(p, m2, s2, 1, 6);
}

int main() {
    int p[] = {30, 35, 15, 5, 10, 20, 25}; //fig 15.5
    int n = sizeof(p)/sizeof(p[0]) - 1;
    cout << matrix_chain_order_bruteforce(p, 1, n) << " bruteforce" << endl;

    // int m[n+1][n+1];
    // int s[n+1][n+1];

    int m[7][7];
    int s[7][7];
    cout << matrix_chain_order_bottomup(p, m, s, n) << " bottomup" << endl;
    print_optimal_parens(s, 1, 6);
    cout << endl;
    
    int m2[7][7];    
    int s2[7][7];
    cout << matrix_chain_order_topdown(p, m2, s2, n) << " topdown" << endl;
    print_optimal_parens(s2, 1, 6);
    cout << endl;
    
    return 0;
}
