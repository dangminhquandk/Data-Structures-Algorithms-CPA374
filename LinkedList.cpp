#include <iostream>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node *next;

        // Khởi tạo một Node
        Node (T value) : data(value), next(nullptr) {}
    };

    Node *head = nullptr; // Quản lý đầu DSLK
    Node *tail = nullptr; // Quản lý cuối DSLK
    size_t size = 0;

public: 
    // Khởi tạo DSLK
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Giải phóng bộ nhớ khi huỷ đối tượng
    ~LinkedList(){
        clear();
    }

    // 1. Insertion
    void push_front (T val) {
        Node *newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        }else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void push_back(T val) {
        Node *newNode = new Node(val);
        if (empty()) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insert_at(int index, T val) {
        if (index < 0 || index > static_cast<int>(size)) throw std::out_of_range("Index out of bounds");
        if (index == 0) {
            push_front(val);
            return;
        }
        if (index == static_cast<int>(size)) {
            push_back(val);
            return;
        }
        Node *newNode = new Node(val);
        Node *current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    // 2. Deletion
    void pop_front() {
        if (empty()) return;
        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
        if (empty()) tail = nullptr;
    }

    void pop_back() {
        if (empty()) return;
        if (head == tail) {
            pop_front();
            return;
        }
        
        Node *current = head;
        while (current->next != tail) current = current->next;
        delete tail;
        tail = current;
        tail->next = nullptr;
        size--;
    }

    void remove_value (T val) {
        if (empty()) return;
        if (head->data == val) {
            pop_front();
            return;
        }
        Node *current = head;
        while (current->next != nullptr && current->next->data != val) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node *temp = current->next;
            if (temp == tail) tail = current;
            current->next = current->next->next;
            delete temp;
            size--;
        }
    }

    void clear() {
        while (!empty()) pop_front();
    }

    // 3. Utilities
    bool empty() const {
        return size == 0;
    }

    size_t get_size() const {
        return size;
    }

    bool search(T val) const {
        Node *current = head;
        while (current != nullptr) {
            if (current->data == val) return true;
            current = current->next;
        }
        return false;
    }

    void display() {
        Node *current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "NULL\n";
    }
};

int main() {
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(5);
    list.pop_front();
    //....

    list.display();
    list.remove_value(15);

    list.display();
    return 0;
}