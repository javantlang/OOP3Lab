#include <iostream>
#include <time.h>
#include <ctime>

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
        cout << "Node";
    }
    virtual ~Node()
    {
        cout << "Destructor Node\n";
        this->next = NULL;
        this->prev = NULL;
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
    ~Point2D()
    {
        cout << "Destructor Point2D\n";
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
    ~Point3D()
    {
        cout << "Destructor Point3D\n";
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
    ~Point4D()
    {
        cout << "Destructor Point4D\n";
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
        root = NULL;
        current = root;
        tail = root;
    }
    int getCount() { return count; };
    bool isEmpty() { return root == NULL; };
    void first() { current = root; }
    void last() { current = tail; };
    void next() { current = current->next; }
    void prev() { current = current->prev; }
    void Clear();
    int getPos(Node*);
    Node* getNodePos(int);
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

int List::getPos(Node* node)
{
    Node* posNode = root;
    int pos = 0;
    while (posNode != node)
    {
        posNode = posNode->next;
        ++pos;
    }
    return pos;
}

Node* List::getNodePos(int n)
{
    if (n > count) return NULL;
    current = root;
    while (n != 0)
    {
        current = current->next;
        --n;
    }
    return current;
}

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
    cout << "Добавление на позицию " << getPos(curPos) + 1 << "\n";
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
    cout << "Delete Node "; node->getName();
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

void randActions(int n, List* actionList)
{
    cout << "\nRANDOM ACTIONS\n";
    while (n != 0)
    {
        int x = rand();
        int amount = actionList->getCount();
        if (x % 5 == 0)
            actionList->Add(new Point2D, actionList->getNodePos(rand() % amount));
        if (x % 5 == 1)
            actionList->Add(new Point3D, actionList->getNodePos(rand() % amount));
        if (x % 5 == 2)
            actionList->Add(new Point4D, actionList->getNodePos(rand() % amount));
        if (x % 5 == 3)
            if (!actionList->isEmpty())
                actionList->Delete(actionList->getNodePos(rand() % amount));
        if (x % 5 == 4)
            if (!actionList->isEmpty())
                actionList->getNodePos(rand() % amount)->getName();
        --n;
    }
}

int main()
{
    setlocale(0, "");
    srand(time(0));
    List* list = new List;
    for (int i = 0; i < 6; ++i)
    {
        int x = rand();
        if (x % 3 == 0)
            list->Add(new Point2D);
        if (x % 3 == 1)
            list->Add(new Point3D);
        if (x % 3 == 2)
            list->Add(new Point4D);
    }
    cout << "Вывод с конца до начала списка\n";
    for (list->last(); !list->eol(); list->prev())
    {
        list->getObject()->getName();
    }
    cout << "\nВывод с начала до конца списка\n";
    for (list->first(); !list->eol(); list->next())
    {
        list->getObject()->getName();
    }
    randActions(12, list);
    cout << "\nВывод с начала до конца списка\n";
    for (list->first(); !list->eol(); list->next())
    {
        list->getObject()->getName();
    }
    list->Clear();
    cout << "Время работы программы " << clock()/1000.0 << " секунды";
    return 0;
}