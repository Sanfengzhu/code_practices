#include <iostream>
#include <cstdio>
#include <cstring>


using namespace std;

int main(int argc, char* argv) {
    int cnt = 0;
    double s;
    double ret = 0;
    while (cin >> s) {
        ret += s;
        cnt++;
        if (cnt == 12) {
            ret /= 12.0;
            break;
        }
    }
    cout << "$" << ret << endl;
    return 0;
}
