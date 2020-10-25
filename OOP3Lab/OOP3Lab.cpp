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
    //Начало списка
    Node* root;
    //Конец списка
    Node* tail;
    //Текущий узел
    Node* current;
    //Счётчик
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
    void Clear();
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

template <class T>
Node* List::Add(T* point)
{
    Node* newObj = point;
    Node* nextNode;
    count++;
    //Создаём новый корень, если его нет
    if (root == NULL)
    {
        newObj->next = NULL;
        newObj->prev = NULL;
        root = newObj;
        tail = root;
    }
    //Создаём новый узел, который становится корнем
    else
    {
        newObj->next = root;
        root->prev = newObj;
        newObj->prev = NULL;
        root = newObj;
    }
    return newObj;
}

template <class T>
Node* List::Add(T* point, Node* curPos)
{
    Node* newObj = point;
    Node* nextNode;
    count++;
    nextNode = curPos->next;
    curPos->next = newObj;
    newObj->next = nextNode;
    newObj->prev = curPos;
    if (nextNode != NULL)
        nextNode->prev = newObj;
    else
        tail = newObj;//Добавляемый элемент является последним
    return newObj;
}

int main()
{
    std::cout << "Hello World!\n";
}