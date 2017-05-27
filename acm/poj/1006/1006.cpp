#include <iostream>
#include <cstdio>
#include <cstring>
#include <math.h>

using namespace std;


int main(int argc, char* argv) {
    int p;
    int e;
    int i;
    int d;
    int cnt = 0;
    while (cin >> p >> e >> i >>d) {
        if (p == -1 && e == -1 && i == -1 && d == -1) {
            break;
        }
        
        p -= d;
        e -= d;
        i -= d;
        int m,n,k;
        int ret = 0;
        for (m = 1; m <= 924; m++) {
            ret = 23 * m + p;
            if ((ret - e) % 28 == 0 && (ret-i) % 33 == 0) {
                break;  
            }
        }
        cout << "Case " << ++cnt << ": the next triple peak occurs in " << ret << " days." << endl;
    }

    return 0;
}
