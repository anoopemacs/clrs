#include <iostream>
#include <climits>

using namespace std;

int my_max(int a, int b, int c) {
    int r = (a>b)? a:b;
    if(c>r) r=c;
    return r;
}

int maximum_subarray_sum(int change[], int b, int e) {
    if(b==e) return change[b];
    int n=e-b+1;
    int mid = b-1+n/2;

    int max_left_sum=INT_MIN;
    int temp_left_sum=0;
    for(int i=mid; i>=b; --i) {
	temp_left_sum += change[i];
	if(temp_left_sum > max_left_sum) max_left_sum = temp_left_sum;
    }

    int max_right_sum=INT_MIN;
    int temp_right_sum=0;
    for(int i=mid+1; i<=e; ++i) {
	temp_right_sum += change[i];
	if(temp_right_sum > max_right_sum) max_right_sum = temp_right_sum;
    }
    
    return my_max(max_left_sum + max_right_sum, maximum_subarray_sum(change, b, b-1+n/2), maximum_subarray_sum(change, b+n/2, e));
}

int main() {
    int price[] = {100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97};
    //price at end of each day 0,1...N
    
    int N = sizeof(price)/sizeof(price[0]) - 1;
    int change[N+1];
    for (int i=1; i<=N; ++i) {
	change[i] = price[i]-price[i-1];
    }
    for (int i=1; i<=N; ++i) {
	cout << change[i] << "  ";
    }
    cout << endl;
    // change[i] is profit for buying at begin of day i and selling at end of day i
    cout << maximum_subarray_sum(change, 1, N) << endl;
    
    return 0;
}
