#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Queue {
private:
    struct Data {
        int heso;
        int bac;

        Data(int _heso, int _bac) : heso(_heso), bac(_bac) {}
    };
    struct Node {
        Data val;
        Node *next;

        Node (int _heso, int _bac) : val(_heso, _bac), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() {
        clear();
    }

    void clear() {
        if (!empty()) pop_front();
    }

    bool empty() const {
        return size == 0;
    }

    void pop_front() {
        if (empty()) return;

        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    void push_back(int heso, int bac) {
        if (empty()) {
            head = tail = new Node(heso, bac);
            size++;
            return;
        }
        
        Node *current = head;
        while (current != nullptr) {
            if (current->val.bac == bac) {
                current->val.heso += heso;
                return;
            }
            current = current->next;
        }

        Node *newNode = new Node(heso, bac);
        tail->next = newNode;
        tail = newNode;
        size++;
    }

    void sortDescending() {
        if (!head) return;
        for (Node *i = head; i->next != nullptr; i = i->next) {
            for (Node *j = i->next; j != nullptr; j = j->next) {
                if (i->val.bac < j->val.bac) {
                    swap(i->val, j->val);
                }
            }
        }
    }

    void display() {
        Node *current = head;
        while(current != nullptr) {
            cout << current->val.heso << "x^" << current->val.bac << " ";
            if (current != tail) cout << "+ ";
            current = current->next;
        }
        cout << '\n';
        return;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    if (fopen("data.inp", "r")) {
        freopen("data.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    }

    Queue list;
    int bac, heso;
    string poly;
    while (getline(cin, poly)) {
        stringstream ss(poly);
        string temp;

        while (getline(ss, temp, '+')) {
            char x, hat;

            stringstream rr(temp);
            rr >> heso >> x >> hat >> bac;
            list.push_back(heso, bac);
        }
    }

    list.sortDescending();

    list.display();
    return 0;
}