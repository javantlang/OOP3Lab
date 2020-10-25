#include <iostream>

using namespace std;

class Node {
public:
    Node* next;
    Node* prev;
    friend class List;
    Node()
    {
        prev = NULL;
        next = NULL;
    }
    virtual void getName()
    {
        cout << "Node\n";
    }
};

class Point2D : public Node {
public:
    int x;
    int y;
    Point2D()
    {
        cout << "Constructor Point2D\n";
        x = 0;
        y = 0;
    }
    void getName()
    {
        cout << "getName(Point2D)\n";
    }
};

class Point3D : public Node {
public:
    int x;
    int y;
    int z;
    Point3D()
    {
        std::cout << "Constructor Point3D\n";
        x = 0;
        y = 0;
        z = 0;
    }
    void getName()
    {
        cout << "getName(Point3D)\n";
    }
};

class Point4D : public Node {
public:
    int x;
    int y;
    int z;
    int l;
    Point4D()
    {
        std::cout << "Constructor Point4D\n";
        x = 0;
        y = 0;
        z = 0;
        l = 0;
    }
    void getName()
    {
        cout << "getName(Point4D)\n";
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

Node* List::Delete(Node* node)
{
    count--;
    Node* prevNode;
    Node* nextNode;
    prevNode = node->prev;
    nextNode = node->next;
    if (prevNode != NULL)
        prevNode->next = node->next;
    else
        //Присваивание корню следующий, после удаляемого, элемент
        root = nextNode;
    if (nextNode != NULL)
        nextNode->prev = node->prev;
    else
        //Присваивание конца предыдущего для удаляемого элемента
        tail = prevNode;
    delete node;
    //Возвращение предыдущего элемента
    if (prevNode != NULL)
        return prevNode;
    else
        //Возвращение корня, если предыдущего нет
        return root;
}

void List::Clear()
{
    Node* delRoot = root;
    if (delRoot == NULL) return;
    do
    {
        Node* delNode = delRoot;
        delRoot = delRoot->next;
        delete delNode;
    } while (delRoot != NULL);
    count = 0;
    root = NULL;
}

int main()
{
    std::cout << "Hello World!\n";
}