#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height; // výška uzlu

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// TODO 1: napište funkci, která spočítá balance faktor uzlu
int getBalance(Node* node) {
	if (node->left == nullptr && node->right == nullptr) return 0;
	if (node->left == nullptr) return -getHeight(node->right);
	if (node->right == nullptr) return getHeight(node->left);
	return getHeight(node->left) - getHeight(node->right);
}

// TODO 2: implementujte pravotočivou rotaci
Node* rightRotate(Node* y) {
    Node* x = y->left;
	Node* T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = 1 + max(getHeight(y->left), getHeight(y->right));
	x->height = 1 + max(getHeight(x->left), getHeight(x->right));
	return x;
}

// TODO 3: implementujte levotočivou rotaci
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = 1 + max(getHeight(x->left), getHeight(x->right));
	y->height = 1 + max(getHeight(y->left), getHeight(y->right));
	return y;
}

// Vložení do AVL stromu
Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // duplicity ignorujeme

    // TODO 4: přepočítejte výšku uzlu
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // TODO 5: získejte balance faktor a proveďte potřebné rotace
    int balance = getBalance(node);

    // Levý-levý případ
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Pravý-pravý případ
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Levý-pravý případ
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Pravý-levý případ
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// TODO 6: napište funkci pro spočítání počtu uzlů v podstromu
int countNodes(Node* root) {
	if (root->left == nullptr && root->right == nullptr) return 1;
	if (root->left == nullptr) return countNodes(root->right) + 1;
	if (root->right == nullptr) return countNodes(root->left) + 1;
	return countNodes(root->left) + countNodes(root->right) + 1;
}

// Výpis inorder
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Inorder průchod AVL stromem: ";
    inorder(root);
    cout << endl;

    cout << "Pocet uzlu ve stromu: " << countNodes(root) << endl;
    cout << "Vyska stromu (root): " << getHeight(root) << endl;
}