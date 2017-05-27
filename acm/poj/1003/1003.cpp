#include <iostream>
#include <cstdio>
#include <cstring>


using namespace std;

int main(int argc, char* argv) {
    double s;
    while (cin >> s) {
        if (s == 0.00) {
            break;
        }
        int i = 2;
        double now_s = 0;
        while ( now_s < s) {
            now_s += 1 / (i * 1.0);
            i += 1;
        }
        cout << i - 2  << " card(s)" << endl;
    }
    return 0;
}
