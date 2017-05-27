#include <iostream>
#include <cstdio>
#include <cstring>


using namespace std;

const int F_LEN = 20;
const int R_LEN = 26 * F_LEN;



void print(int *fi, int len, int pos){
    int fi_begin = 0;
    int all = len > pos ? len : pos;
    bool not_begin = true;
    int j = 0;
    int i = 0;
    for (i = 0; i < all; i++) {
        if (not_begin) {
            if (fi[i] == 0){
                if (i < pos) {
                    fi_begin++;
                }
                continue;
            } else {
                not_begin = false;
            }
        } else {
            if (i == pos) {
                j = i;
            }
            if (i >= len) {
                fi[i] == 0;
            }
        }
    }
    if (all == pos) {
        cout << ".";
    }
    for (i = all-1; i>=fi_begin; i--){
        if (j == i+1) {
            cout << ".";
        } 
        cout << fi[i];
    }
    cout << endl;
}

void calc(int *fi, int fi_len, int n, int pos) {
    int i = 0;
    int j = 0;
    int k = 0;

    int tmp[R_LEN];
    int tmp_r[R_LEN];
    memset(tmp, 0, sizeof(int) * R_LEN);
    memset(tmp_r, 0, sizeof(int) * R_LEN);
    for (i = 0; i < fi_len; i++) {
        tmp[i] = fi[i];
    }
    int tmp_len = fi_len;
    if (n > 1) {
        for (k = 1; k < n; k++) {
            int last_pos = 0;
            for (i = 0; i < fi_len; i++) {
                int this_pos;
                for (j = 0; j < tmp_len; j++) {
                    int tmp_ij = tmp[j] * fi[i];
                    int npos = i + j;
                    this_pos = npos;
                    int p = 0;
                    tmp_r[npos] += tmp_ij;
                    while (tmp_r[npos+p] > 9) {
                        int tmp_join = tmp_r[npos+p] / 10;
                        tmp_r[npos+p] %= 10;
                        tmp_r[npos+p+1] += tmp_join;
                        p++;
                        this_pos = npos+p;
                    }
                }
                if (this_pos > last_pos) {
                    last_pos = this_pos;
                }
            }
            tmp_len = last_pos + 1;
            for (i = 0; i < tmp_len; i++) {
                tmp[i] = tmp_r[i];
            }
            memset(tmp_r, 0, sizeof(int) * R_LEN);
        }
        print(tmp, tmp_len, pos);
    } else {
        print(tmp, tmp_len, pos);
    }
}

int main(int argc, char* argv) {
    char f[F_LEN];
    int fi[F_LEN];
    memset(f,0,sizeof(f));
    int n;
    double lf;
    while (scanf("%s %d", f, &n)!=EOF) {
        int i = 0;
        int c = 0;
        int pos = 0;
        int len = 0;
        bool begin = false;
        while(f[i] != 0) {
            if (f[i] == '.') {
                begin = true;
            } else {
                if(begin) {
                    pos++;
                }
                len++;
                c = c * 10 + (f[i] - 48);
            }
            i++;
        }
        if (n == 0) {
            cout << 1 << endl;
        } else if (n > 0) {
            if (c == 0) {
                cout << 0 << endl;
            } else {
                memset(fi,0,sizeof(int) * F_LEN);
                i = 0;
                while (c != 0) {
                    int tmp = c % 10;
                    fi[i++] = tmp;
                    c /= 10;
                }
                calc(fi, i, n, pos*n);
            }
        }
        memset(f,0,sizeof(f));
    }
    return 0;
}
