#include <iostream>
#include <string>
#include "locale.h"
using namespace std;

// ноды бинарного дерева
struct Node {
    string name;
    int height;
    Node* left;
    Node* right;
    Node* parent;
    Node(string key) : name(key), height(0), left(NULL), right(NULL), parent(NULL) {};
};

// проходим по всему дереву и в алфавитном порядке вставляем новый нод
void insert(Node* root, Node* node) {
    while (root) {
        if (node->name < root->name) {
            if (root->left) {
                root = root->left; // если нод (левый) занят, перемещаемся к нему и начинаем заново
                node->height++;
                cout << "/1/ ";
            }

            else {
                node->parent = root; // вствляем нод
                root->left = node;
                cout << node->parent->name << " " << node->height << " l\n";
                break;
            }
        }
        else if (node->name > root->name) {
            if (root->right) {
                root = root->right; // если нод (правый) занят, перемещаемся к нему и начинаем заново
                node->height++;
                cout << "/2/ ";
            }
            else {
                node->parent = root; // вствляем нод
                root->right = node;
                cout << node->parent->name << " " << node->height << " r\n";
                break;
            }
        }
    }
}
void inorderTraversal(Node* x) {
    if (x) { // пока есть нод
        inorderTraversal(x->left); // заходим в рекурсию до самого левого нода
        cout << x->name << " "; // выводим нод
        inorderTraversal(x->right); // заходим в рекурсию в правый
    }
    else return;
}
void symmetricalTraversal(Node* x) {
    if (x) { // пока есть нод
        cout << x->name << " "; // выводим текущий нод рекурсии
        symmetricalTraversal(x->left); // рекурсионно заходим в левый, выводим его и далее
        symmetricalTraversal(x->right); // рекурсионно заходим в правые оставшиеся
    }
    else return;
}
int treeHeight(Node* x) {
    int maxH = -1;
    int result;
    if (x) { // пока есть нод
        if (maxH < x->height)
            maxH = x->height;

        result = treeHeight(x->left); // рекурсионно заходим в левые
        if (maxH < result)
            maxH = result;

        result = treeHeight(x->right); // рекурсионно заходим в правые оставшиеся
        if (maxH < result)
            maxH = result;
    }
    return maxH;
}
int search(Node* x, string key) {
    int res = -1;
    int temp = -1;
    if (x) { // пока есть нод
        if (key == x->name)
            res = x->height;
        if ((temp = search(x->left, key)) != -1)
            res = temp; // рекурсионно заходим в левые
        if ((temp = search(x->right, key)) != -1)
            res = temp; // рекурсионно заходим в левые
    }
    return res;
}
//int search(Node* x, string key) {
//    int maxH = -1;
//    int result;
//    if (x) { // пока есть нод
//        if (key == x->name)
//            maxH = x->height;
//
//        result = search(x->left, key); // рекурсионно заходим в левые
//        if (result > -1)
//            maxH = result;
//
//        result = search(x->right, key); // рекурсионно заходим в правые оставшиеся
//        if (result > -1)
//            maxH = result;
//    }
//    return maxH;
//}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите количество имен в дереве: ";
    int n;
    Node* root = new Node("");
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Введите " << i + 1 << " имя: ";
        string town;
        cin >> town;
        insert(root, new Node(town));
    }

    cout << "Дерево было успешно построено.\n\n";
    cout << "Список доступных команд:\n"
        << "1 -> Вставка нового элемента\n"
        << "2 -> Прямой обход\n"
        << "3 -> Симметричный обход\n"
        << "4 -> Высота дерева\n"
        << "5 -> Нахождение длины пути от корня до заданного значения\n"
        << "Введите номер команды: ";

    int command;
    string node;
    string key;

    while (true) {
        cin >> command;
        switch (command)
        {
        case 1:
            cout << "Введите имя элемента: ";
            cin >> node;
            insert(root, new Node(node));
            cout << "Элемент был успешно вставлен!\n";
            break;
        case 2:
            cout << "Прямой обход:";
            inorderTraversal(root);
            cout << endl;
            break;
        case 3:
            cout << "Симметричный обход:";
            symmetricalTraversal(root);
            cout << endl;
            break;
        case 4:
            cout << "Высота текущего состояния дерева: ";
            cout << treeHeight(root) << endl;
            break;
        case 5:
            cout << "Введите имя элемента, до которого искать длину пути: ";
            cin >> key;
            cout << "Глубина элемента с именем - " << key << ": ";
            cout << search(root, key) << endl;
            break;
        default:
            cout << "Неизвестная команда, попоробуйте еще раз.\n";
            cin >> command;
            break;
        }
        cout << "Введите номер команды: ";
    }
}