#include <iostream>

using namespace std;

class Node {
public:
    Node* next;
    Node* prev;
    Node()
    {
        prev = NULL;
        next = NULL;
    }
    friend class List;
    virtual void getName()
    {
        cout << "Node\n";
    }
};

class List {
    Node* root;
    Node* tail;
    Node* current;
    int count = 0;
public:
    List() {
        cout << "constructor List\n";
        current = NULL;
        root = NULL;
        tail = root;
    }
    int getCount() { return count; };
    bool isEmpty() { return root == NULL; };
    void first() { current = root; }
    void last() { current = tail; };
    void next() { current = current->next; }
    void prev() { current = current->prev; }
    Node* getObject() { return current; }
    bool eol() { return current == NULL; }
    template <class T>
    //Добавление элемента в начало списка
    Node* Add(T*);
    template <class T>
    //Добавление элемента после передаваемого указателя на элемент
    Node* Add(T*, Node*);
    Node* Delete(Node*);
};

int main()
{
    std::cout << "Hello World!\n";
}