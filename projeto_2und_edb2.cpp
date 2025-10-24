#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int key;
    Node *left, *right, *parent;
    int height;
    bool color; // true = vermelho, false = preto

    Node(int k) {
        key = k;
        left = right = parent = nullptr;
        height = 1;
        color = true;
    }
};

// ---------------------------- AVL ----------------------------
class AVLTree {
private:
    Node* root;

    int height(Node* n) { return n ? n->height : 0; }

    int getBalance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key) return rotateRight(node);
        if (balance < -1 && key > node->right->key) return rotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;
        if (key < root->key) root->left = deleteNode(root->left, key);
        else if (key > root->key) root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        if (!root) return root;
        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    void print(Node* root, string indent = "", bool last = true) {
        if (root) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << root->key << endl;
            print(root->left, indent, false);
            print(root->right, indent, true);
        }
    }

    bool search(Node* root, int key) {
        if (!root) return false;
        if (root->key == key) return true;
        return key < root->key ? search(root->left, key) : search(root->right, key);
    }

public:
    AVLTree() { root = nullptr; }
    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = deleteNode(root, key); }
    void print() { print(root); }
    bool search(int key) { return search(root, key); }
};

// ---------------------------- RUBRO-NEGRA ----------------------------
class RBTree {
private:
    Node* root;
    Node* TNULL;

    void initializeNULLNode(Node* node, Node* parent) {
        node->key = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = false;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            this->root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            this->root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* k) {
        Node* u;
        while (k->parent->color == true) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == true) {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u->color == true) {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
                break;
        }
        root->color = false;
    }

    void fixDelete(Node* x) {
        Node* s;
        while (x != root && x->color == false) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == true) {
                    s->color = false;
                    x->parent->color = true;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == false && s->right->color == false) {
                    s->color = true;
                    x = x->parent;
                } else {
                    if (s->right->color == false) {
                        s->left->color = false;
                        s->color = true;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->right->color = false;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == true) {
                    s->color = false;
                    x->parent->color = true;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == false && s->left->color == false) {
                    s->color = true;
                    x = x->parent;
                } else {
                    if (s->left->color == false) {
                        s->right->color = false;
                        s->color = true;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->left->color = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = false;
    }

    void rbTransplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    Node* minimum(Node* node) {
        while (node->left != TNULL)
            node = node->left;
        return node;
    }

    void deleteNodeHelper(Node* node, int key) {
        Node* z = TNULL;
        Node* x, *y;
        while (node != TNULL) {
            if (node->key == key)
                z = node;
            if (node->key <= key)
                node = node->right;
            else
                node = node->left;
        }
        if (z == TNULL) return;
        y = z;
        bool y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == false)
            fixDelete(x);
    }

    void printHelper(Node* root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            string sColor = root->color ? "Vermelho" : "Preto";
            cout << root->key << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    Node* searchTreeHelper(Node* node, int key) {
        if (node == TNULL || key == node->key)
            return node;
        if (key < node->key)
            return searchTreeHelper(node->left, key);
        return searchTreeHelper(node->right, key);
    }

public:
    RBTree() {
        TNULL = new Node(0);
        TNULL->color = false;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void insert(int key) {
        Node* node = new Node(key);
        node->parent = nullptr;
        node->key = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = true;
        Node* y = nullptr;
        Node* x = this->root;
        while (x != TNULL) {
            y = x;
            if (node->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        node->parent = y;
        if (y == nullptr)
            root = node;
        else if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
        if (node->parent == nullptr) {
            node->color = false;
            return;
        }
        if (node->parent->parent == nullptr)
            return;
        fixInsert(node);
    }

    void remove(int key) { deleteNodeHelper(this->root, key); }

    void print() { printHelper(this->root, "", true); }

    bool search(int key) {
        Node* res = searchTreeHelper(this->root, key);
        return res != TNULL;
    }
};

// ---------------------------- MAIN ----------------------------
int main() {
    int tipo;
    cout << "Escolha o tipo de arvore:\n1 - AVL\n2 - Rubro-Negra\n";
    cin >> tipo;

    if (tipo == 1) {
        AVLTree avl;
        int op, valor;
        do {
            cout << "\n1-Inserir\n2-Remover\n3-Buscar\n4-Imprimir\n0-Sair\n";
            cin >> op;
            if (op == 1) { cin >> valor; avl.insert(valor); }
            else if (op == 2) { cin >> valor; avl.remove(valor); }
            else if (op == 3) { cin >> valor; cout << (avl.search(valor) ? "Encontrado\n" : "Nao encontrado\n"); }
            else if (op == 4) { avl.print(); }
        } while (op != 0);
    } 
    else if (tipo == 2) {
        RBTree rb;
        int op, valor;
        do {
            cout << "\n1-Inserir\n2-Remover\n3-Buscar\n4-Imprimir\n0-Sair\n";
            cin >> op;
            if (op == 1) { cin >> valor; rb.insert(valor); }
            else if (op == 2) { cin >> valor; rb.remove(valor); }
            else if (op == 3) { cin >> valor; cout << (rb.search(valor) ? "Encontrado\n" : "Nao encontrado\n"); }
            else if (op == 4) { rb.print(); }
        } while (op != 0);
    }
}
