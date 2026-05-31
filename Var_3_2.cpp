#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>  
#include <cstdlib> 
#include <ctime>   
#include <map>

using namespace std;

/**
 * @defgroup DataGeneration Генерация данных
 * @brief Структуры и функции для генерации массива сотрудников.
 * @{
 */

/**
 * @brief Структура, описывающая сотрудника.
 */
struct Employee {
    string name;       
    string job;        
    string department; 
    int salary;        
};



/**
 * @defgroup LinearSearch Линейный поиск
 * @brief Прямой перебор массива.
 * @{
 */

/**
 * @brief Функция линейного поиска по ключу (ФИО).
 * @param arr Ссылка на вектор сотрудников.
 * @param targetName Искомое ФИО.
 * @return Вектор найденных сотрудников (все вхождения).
 */
vector<Employee> linearSearch(const vector<Employee>& arr, string targetName) {
    vector<Employee> found; 
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].name == targetName) {
            found.push_back(arr[i]); 
        }
    }
    return found;
}
/** @} */


/**
 * @defgroup BST Бинарное дерево
 * @brief Реализация незбалансированного бинарного дерева поиска.
 * @{
 */

/**
 * @brief Узел бинарного дерева.
 */
struct BSTNode {
    string key;                 
    vector<Employee> records;   
    BSTNode* left;              
    BSTNode* right;             
};

/**
 * @brief Класс бинарного дерева поиска.
 */
class BST {
    BSTNode* root = nullptr; 

    /**
     * @brief Функция добавления узла (рекурсивная).
     * @param node Текущий узел дерева.
     * @param emp Данные сотрудника для добавления.
     * @return Указатель на добавленный узел или текущий узел.
     */
    BSTNode* addNode(BSTNode* node, Employee emp) {
        if (node == nullptr) {
            BSTNode* newNode = new BSTNode;
            newNode->key = emp.name;
            newNode->records.push_back(emp);
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }
        
        
        if (emp.name == node->key) {
            node->records.push_back(emp);
        } 
        
        else if (emp.name < node->key) {
            node->left = addNode(node->left, emp);
        } 
        else {
            node->right = addNode(node->right, emp);
        }
        return node;
    }

public:
    /**
     * @brief Вставка нового сотрудника.
     * @param emp Сотрудник.
     */
    void insert(Employee emp) { 
        root = addNode(root, emp); 
    }

    /**
     * @brief Поиск в дереве (простым циклом).
     * @param targetName Искомое ФИО.
     * @return Вектор найденных сотрудников с заданным ФИО.
     */
    vector<Employee> search(string targetName) {
        BSTNode* current = root; 
        
        while (current != nullptr) {
            if (targetName == current->key) return current->records; 
            if (targetName < current->key) current = current->left;  
            else current = current->right;                          
        }
        return {}; 
    }
};
/** @} */


/**
 * @defgroup RBT Красно черное дерево
 * @brief Реализация сбалансированного красно-черного дерева.
 * @{
 */

/**
 * @brief Узел красно-черного дерева.
 */
struct RBNode {
    string key;
    vector<Employee> records;
    bool isRed;     //true - красный, false - черный
    RBNode* left;
    RBNode* right;
    RBNode* parent; 
};

/**
 * @brief Класс красно-черного дерева.
 */
class RBTree {
    RBNode* NIL;  
    RBNode* root; 

    /**
     * @brief Поворот дерева влево.
     */
    void rotateLeft(RBNode* currentNode) {
        RBNode* rightChild = currentNode->right;
        currentNode->right = rightChild->left;
        if (rightChild->left != NIL) rightChild->left->parent = currentNode;
        rightChild->parent = currentNode->parent;
        if (currentNode->parent == NIL) root = rightChild;
        else if (currentNode == currentNode->parent->left) currentNode->parent->left = rightChild;
        else currentNode->parent->right = rightChild;
        rightChild->left = currentNode;
        currentNode->parent = rightChild;
    }

    /**
     * @brief Поворот дерева вправо.
     */
    void rotateRight(RBNode* currentNode) {
        RBNode* leftChild = currentNode->left;
        currentNode->left = leftChild->right;
        if (leftChild->right != NIL) leftChild->right->parent = currentNode;
        leftChild->parent = currentNode->parent;
        if (currentNode->parent == NIL) root = leftChild;
        else if (currentNode == currentNode->parent->right) currentNode->parent->right = leftChild;
        else currentNode->parent->left = leftChild;
        leftChild->right = currentNode;
        currentNode->parent = leftChild;
    }

    /**
     * @brief Восстановление баланса и цветов после вставки.
     * @param node Вставленный узел.
     */
    void fixInsert(RBNode* node) {
        while (node->parent->isRed) {
            RBNode* grandpa = node->parent->parent; 
            
            if (node->parent == grandpa->left) {
                RBNode* uncle = grandpa->right; 
                
                if (uncle->isRed) { 
                    node->parent->isRed = false;
                    uncle->isRed = false;
                    grandpa->isRed = true;
                    node = grandpa; 
                } else { 
                    if (node == node->parent->right) { 
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->isRed = false;
                    grandpa->isRed = true;
                    rotateRight(grandpa);
                }
            } else {
                RBNode* uncle = grandpa->left;
                
                if (uncle->isRed) {
                    node->parent->isRed = false;
                    uncle->isRed = false;
                    grandpa->isRed = true;
                    node = grandpa;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->isRed = false;
                    grandpa->isRed = true;
                    rotateLeft(grandpa);
                }
            }
        }
        root->isRed = false; 
    }

public:
    /**
     * @brief Конструктор красно-черного дерева.
     */
    RBTree() {
        NIL = new RBNode;
        NIL->isRed = false;
        NIL->left = nullptr;
        NIL->right = nullptr;
        NIL->parent = nullptr;
        root = NIL;
    }

    /**
     * @brief Вставка элемента в дерево.
     * @param emp Данные сотрудника.
     */
    void insert(Employee emp) {
        RBNode* current = root;
        // поиск места
        while (current != NIL) {
            if (emp.name == current->key) {
                current->records.push_back(emp);
                return;
            }
            if (emp.name < current->key) current = current->left;
            else current = current->right;
        }

        // новый красный узел
        RBNode* newNode = new RBNode;
        newNode->key = emp.name;
        newNode->records.push_back(emp);
        newNode->isRed = true;
        newNode->left = NIL;
        newNode->right = NIL;
        newNode->parent = NIL;

        // Привязка узла
        RBNode* parentNode = NIL;
        current = root;
        while (current != NIL) {
            parentNode = current;
            if (newNode->key < current->key) current = current->left;
            else current = current->right;
        }
        
        newNode->parent = parentNode;
        if (parentNode == NIL) root = newNode;
        else if (newNode->key < parentNode->key) parentNode->left = newNode;
        else parentNode->right = newNode;

        // Фикс
        fixInsert(newNode);
    }

    /**
     * @brief Поиск записей по ключу.
     * @param targetName Искомое ФИО.
     * @return Найденные записи.
     */
    vector<Employee> search(string targetName) {
        RBNode* current = root;
        while (current != NIL) {
            if (targetName == current->key) return current->records;
            if (targetName < current->key) current = current->left;
            else current = current->right;
        }
        return {};
    }
};
/** @} */


/**
 * @defgroup HashTable Хэш таблица
 * @brief Хэш-таблица с методом разрешения коллизий цепочками.
 * @{
 */

/**
 * @brief Класс Хэш-таблицы.
 */
class HashTable {
    vector<vector<Employee>> table; 
    int collisionsCount;            

    /**
     * @brief Хэш-функция для преобразования строки в индекс.
     * @param name Входная строка.
     * @return Индекс корзины.
     */
    int makeHash(string name) {
        long long sum = 0;
        for (int i = 0; i < name.length(); i++) {
            sum = (sum * 31) + name[i]; 
        }
        return sum % table.size(); 
    }

public:
    /**
     * @brief Инициализация хэш-таблицы заданного размера.
     * @param size Размер таблицы.
     */
    HashTable(int size) {
        table.resize(size);
        collisionsCount = 0;
    }

    /**
     * @brief Вставка элемента в хэш-таблицу с обработкой коллизий.
     * @param emp Данные сотрудника.
     */
    void insert(Employee emp) {
        int basketNumber = makeHash(emp.name);

        bool isBasketOccupied = !table[basketNumber].empty(); 
        bool isDifferentPerson = true;

        
        if (isBasketOccupied) {
            if (table[basketNumber][0].name == emp.name) {
                isDifferentPerson = false;
            }
        }

        
        if (isBasketOccupied && isDifferentPerson) {
            collisionsCount++;
        }

        
        table[basketNumber].push_back(emp);
    }

    /**
     * @brief Поиск элементов по ключу.
     * @param targetName Искомое ФИО.
     * @return Вектор найденных записей.
     */
    vector<Employee> search(string targetName) {
        vector<Employee> found;
        int basketNumber = makeHash(targetName); 
        
        
        for (int i = 0; i < table[basketNumber].size(); i++) {
            if (table[basketNumber][i].name == targetName) {
                found.push_back(table[basketNumber][i]);
            }
        }
        return found;
    }

    /**
     * @brief Возвращает число зафиксированных коллизий.
     * @return Число коллизий.
     */
    int getCollisions() { return collisionsCount; }
};
/** @} */

/**
 * @brief Функция генерации случайных данных сотрудников.
 * @param count Количество генерируемых записей.
 * @return Вектор сгенерированных сотрудников.
 */
vector<Employee> generateData(int count) {
    string surnames[] = {"Ivanov", "Petrov", "Sidorov", "Smirnov", "Volkov", "Kozlov", "Lebedev", "Egorov", "Nikitin", "Popov"};
    string names[] = {"I.", "P.", "S.", "A.", "V.", "K.", "L.", "E.", "N.", "M."};
    string patrs[] = {"I.", "P.", "S.", "A.", "V.", "K.", "L.", "E.", "N.", "M."};
    string posts[] = {"Accountant", "Analyst", "Manager", "Director", "Clerk"};
    string depts[] = {"IT", "HR", "Finance", "Sales", "Marketing"};

    vector<Employee> data;
    for (int i = 0; i < count; i++) {
        Employee emp;
        emp.name = surnames[rand() % 10] + " " + names[rand() % 10] + patrs[rand() % 10];
        emp.job = posts[rand() % 5];
        emp.department = depts[rand() % 5];
        emp.salary = 30000 + (rand() % 170000); 
        data.push_back(emp);
    }
    return data;
}
/** @} */


/**
 * @defgroup MainFunction Главная функция
 * @brief Главная функция и проведение тестов.
 * @{
 */


/**
 * @brief Точка входа в программу.
 * Выполняет тестирование различных методов поиска данных.
 * @return 0 при успешном завершении.
 */
int main() {
    system("chcp 65001 > nul"); // Русский язык в консоли
    srand(time(0)); 

    int testSizes[] = {100, 1000, 5000, 10000, 50000, 100000, 250000, 500000, 750000, 1000000};
    int numberOfTests = 10;

    ofstream file("results.csv");
    file << "Size,Linear_us,BST_us,RBT_us,Hash_us,Multimap_us,Collisions\n";

    

    for (int step = 0; step < numberOfTests; step++) {
        int N = testSizes[step]; 
        vector<Employee> myData = generateData(N);

        BST simpleTree;
        RBTree redBlackTree;
        HashTable hashTable(N); 
        multimap<string, Employee> cppMap; 

        
        for (int i = 0; i < N; i++) {
            simpleTree.insert(myData[i]);
            redBlackTree.insert(myData[i]);
            hashTable.insert(myData[i]);
            cppMap.insert({myData[i].name, myData[i]});
        }

        
        vector<string> namesToSearch;
        for (int i = 0; i < 100; i++) {
            namesToSearch.push_back(myData[rand() % N].name);
        }

        long long dummyCounter = 0; 

        // 1
        auto timeStart = chrono::steady_clock::now();
        for (int i = 0; i < 100; i++) dummyCounter += linearSearch(myData, namesToSearch[i]).size();
        auto timeEnd = chrono::steady_clock::now();
        int timeLinear = chrono::duration_cast<chrono::microseconds>(timeEnd - timeStart).count();

        // 2
        timeStart = chrono::steady_clock::now();
        for (int i = 0; i < 100; i++) dummyCounter += simpleTree.search(namesToSearch[i]).size();
        timeEnd = chrono::steady_clock::now();
        int timeBST = chrono::duration_cast<chrono::microseconds>(timeEnd - timeStart).count();

        // 3
        timeStart = chrono::steady_clock::now();
        for (int i = 0; i < 100; i++) dummyCounter += redBlackTree.search(namesToSearch[i]).size();
        timeEnd = chrono::steady_clock::now();
        int timeRBT = chrono::duration_cast<chrono::microseconds>(timeEnd - timeStart).count();

        // 4
        timeStart = chrono::steady_clock::now();
        for (int i = 0; i < 100; i++) dummyCounter += hashTable.search(namesToSearch[i]).size();
        timeEnd = chrono::steady_clock::now();
        int timeHash = chrono::duration_cast<chrono::microseconds>(timeEnd - timeStart).count();

        // 5
        timeStart = chrono::steady_clock::now();
        for (int i = 0; i < 100; i++) {
            auto range = cppMap.equal_range(namesToSearch[i]);
            for (auto it = range.first; it != range.second; ++it) dummyCounter++;
        }
        timeEnd = chrono::steady_clock::now();
        int timeMap = chrono::duration_cast<chrono::microseconds>(timeEnd - timeStart).count();

       
        cout << "N=" << N 
             << "\t Lin=" << timeLinear << " us"
             << "\t BST=" << timeBST << " us"
             << "\t RBT=" << timeRBT << " us"
             << "\t HT="  << timeHash << " us"
             << "\t MM="  << timeMap << " us\n";

        
        file << N << "," << timeLinear << "," << timeBST << "," << timeRBT << "," 
             << timeHash << "," << timeMap << "," << hashTable.getCollisions() << "\n";
    }

    file.close();
    system("pause"); 
    return 0;
}
/** @} */
