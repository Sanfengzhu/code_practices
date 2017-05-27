#include <iostream>
#include <cstdio>
#include <cstring>
#include <math.h>

using namespace std;

/**
 * 2
 * 1.0 1.0
 * 25.0 0.0
 **/
/**
 * Property 1: This property will begin eroding in year 1.
 * Property 2: This property will begin eroding in year 20.
 * END OF OUTPUT.
 **/

int main(int argc, char* argv) {
    int cnt;
    int c = 0;
    cin >> cnt;
    while (cnt-- != 0) {
        double x;
        double y;
        cin >> x >> y;
        double ret = (x * x + y * y) * 3.1415926 / 100.0;
        double r = ceil(ret);
        cout << "Property " << ++c << ": This property will begin eroding in year " << r << "." << endl;
    }
    cout << "END OF OUTPUT." << endl;
    return 0;
}
