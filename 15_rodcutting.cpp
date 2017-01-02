#include <iostream>
#include <climits>
#include <iomanip>

using namespace std;

int cut_rod_bruteforce(int p[], int n) {
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i=1; i<=n; ++i) {
	q = max(q, p[i]+cut_rod_bruteforce(p, n-i));
    }
    return q;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int my_max(int a, int b) {
    if (b>a) return b;
    else return a;
}

int cut_rod_memoized_aux(int p[], int n, int r[]) {
    if (r[n] >= 0) return r[n];
    int q;
    if (n == 0) {
	q = 0;
    } else {
	q = INT_MIN;
	for (int i=1; i<=n; ++i) {
	    q = my_max(q, p[i] + cut_rod_memoized_aux(p, n-i, r));
	}
    }
    r[n] = q;
    return q;
}

int cut_rod_memoized(int p[], int n) {
    int r[n+1];
    for (int i=0; i<=n; ++i) {
	r[i] = INT_MIN;
    }
    return cut_rod_memoized_aux(p, n, r);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

int cut_rod_bottomup(int p[], int n) {
    int r[n+1];
    r[0] = 0;
    for (int j=1; j<=n; ++j) {
	int q = INT_MIN;
	for (int i=1; i<=j; ++i) {
	    q = my_max(q, p[i]+r[j-i]);
	}
	r[j] = q;
    }
    return r[n];
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int cut_rod_bottomup_extended(int p[], int n) {
    int r[n+1];
    int s[n+1];
    r[0] = 0;
    s[0] = 0;
    for (int j=1; j<=n; ++j) {
	int q = INT_MIN;
	for (int i=1; i<=j; ++i) {
	    if (p[i]+r[j-i] > q) {
		q = p[i] + r[j-i];
		s[j] = i;
	    }
	}
	r[j]=q;
    }
    // //s-printer-temp for n=10:
    // if (n == 10) {
    // 	for (int i=0; i<=10; ++i) {
    // 	    cout << endl << "* "<< setw(2) << i << "  " << setw(2) << s[i] << " *";
    // 	}
    // 	cout << endl;
    // }
    return r[n];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int cut_rod_memoized_extended_aux(int p[], int n, int r[], int s[]) {
    if (r[n] >= 0) return r[n];
    int q;
    if (n == 0) {
        q = 0;
	s[n] = 0;
    } else {
        q = INT_MIN;
        for (int j=1; j<=n; ++j) {
	    if (p[j] + cut_rod_memoized_extended_aux(p, n-j, r, s) > q) {
		q = p[j] + cut_rod_memoized_extended_aux(p, n-j, r, s);
		s[n] = j;
	    }
        }
    }
    r[n] = q;
    return q;
}

int cut_rod_memoized_extended(int p[], int n) {
    int r[n+1];
    int s[n+1];
    
    for (int i=0; i<=n; ++i) {
        r[i] = INT_MIN;
	s[i] = INT_MIN;
    }
    //return cut_rod_memoized_extended_aux(p, n, r, s);

    int ret =cut_rod_memoized_extended_aux(p, n, r, s);
    
    // //s-printer-temp for n=10:
    // if (n == 10) {
    //     for (int i=0; i<=10; ++i) {
    //         cout << endl << "* "<< setw(2) << i << "  " << setw(2) << s[i] << " *";
    //     }
    //     cout << endl;
    // }
    return ret;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30, '0', '0','0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };
    for (int i=1; i<=10; ++i) {
	cout << setw(2) << cut_rod_bruteforce(p, i) << " ";
    }
    cout << endl;

    for (int i=1; i<=40; ++i) {
        cout << setw(2) << cut_rod_memoized(p, i) << " ";
    }
    cout << endl;

    for (int i=1; i<=40; ++i) {
        cout << setw(2) << cut_rod_bottomup(p, i) << " ";
    }
    cout << endl;
    
    for (int i=1; i<=40; ++i) {
        cout << setw(2) << cut_rod_bottomup_extended(p, i) << " ";
    }
    cout << endl;

    for (int i=1; i<=40; ++i) {
        cout << setw(2) << cut_rod_memoized_extended(p, i) << " ";
    }
    cout << endl;
    
    return 0;
}
