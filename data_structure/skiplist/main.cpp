#include <iostream>

struct node_t {
    int data;
    node_t *next;
};
typedef node_t Node;

class SkipList
{
private:
    Node* top;
    Node* tail;
    int len;
public:
    SkipList():len(0){
        top = new Node();
        tail = new Node();
        top->data = 0;
        tail->data = 0;
        tail->next = NULL;
        top->next = tail;
    }
    ~SkipList(){
        delete top;
        delete tail;
    }

    bool empty() const {
        return len > 0 ? false : true;
    }

    int length() const {
        return len;
    }

    bool push(const int data){
        return insert(0, data);
    }

    bool pop() {
        return remove(0);
    }

    bool append(const int data){
        return insert(len, data);
    }

    bool insert(const int index, const int data){
        if (index < 0 || index > len) {
            return false;
        }else{
            int now_pos = 0;
            Node* now = top;
            while(now_pos!=index){
                now = now->next;
                now_pos++;
            }
            Node* new_node = new Node();
            new_node->data = data;
            new_node->next = now->next;
            now->next = new_node;
            len++;
            return true;
        }            
    }

    int find(const int data) const {
        Node * now = top->next;
        int pos = 0;
        while(now->next!=NULL){
            if(data == now->data){
                return pos;
            }
            pos++;
            now = now->next;
        }
        return -1;
    }

    bool remove(const int index) {
       if (index < 0 || index >= len) {
           return false;
       } else {
           int now_pos = -1;
           Node * now = top;
           while (now_pos != index - 1) {
               now = now->next;
               now_pos ++;
           }
           Node* rem_node = now->next;
           now->next = now->next->next;
           delete rem_node;
           len --;
           return true;
       } 
    }

    void clean() {
        Node * now = top->next;
        while(now->next!=NULL){
            Node* rem_node = now->next;
            now->next = now->next->next;
            delete rem_node;
        }
        len = 0;
    }

    void print() const {
        Node * now = top->next;
        std::cout << "[size=" << len << "] ";
        while(now->next!=NULL){
            std::cout << now->data << " ";
            now = now->next;
        }
        std::cout << std::endl;
    }
};

int main(int argc, char *argv[])
{
    SkipList s;
    s.insert(0,12);
    s.insert(0,13);
    s.insert(0,14);
    s.remove(2);
    s.insert(0,15);
    s.append(16);
    s.print();
    std::cout << s.find(123) << std::endl;
    std::cout << s.find(16) << std::endl;
    s.clean();
    s.print();
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);
    s.print();
    s.pop();
    s.pop();
    s.print();
    return 0;
}
