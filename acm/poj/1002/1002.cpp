#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct di{
    int num;
    int cnt;
    struct di* next;
};

const int MAX_NUM = 19999999;
const int FOR_MOD = 10000000;

int main(int argc, const char *argv[]){
    int cnt = 0;
    char num[300];
    int map[26] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,-1,7,7,8,8,8,9,9,9,-1};
    scanf("%d", &cnt);
    
    di *b,*e;
    b = (struct di*)malloc(sizeof(struct di));
    e = (struct di*)malloc(sizeof(struct di));
    b->num = -1;
    b->cnt = 0;
    b->next = e;
    e->num = MAX_NUM;
    e->cnt = 0;
    e->next = NULL;

    while (cnt--) {
        scanf("%s",num);
        int i = 0;
        int num_i = 1;
        while ( num[i] != 0) {
            if (num[i] >= 48 && num[i] < 58){
                num_i = num_i * 10 + (num[i] - 48);
            } else if (num[i] > 64 && num[i] < 91) {
                if ( num[i] != 'Q' && num[i] != 'Z') {
                    num_i = num_i * 10 + map[num[i] - 65];
                }
            }
            i++;
        }
        di *s = b;
        while(s->next!=NULL) {
            if(s->num == num_i){
                s->cnt++;
                break;
            }else if(s->num < num_i && s->next->num > num_i){
                di *new_node;
                new_node = (struct di*)malloc(sizeof(struct di));
                new_node->num = num_i;
                new_node->cnt = 1;
                new_node->next = s->next;
                s->next = new_node;
                break;
            }
            s = s->next;
        }
    }
    di *first = b;
    bool has_print = false;
    while(first->next!=NULL){
        if ( first->cnt > 1) {
            printf("%03d-%04d %d\n", (first->num / 10000) % 1000 , first->num % 10000, first->cnt);
            has_print = true;
        }
        first = first->next;
    }
    if (!has_print) {
        cout << "No duplicates." << endl;
    }
    return 0;
}
