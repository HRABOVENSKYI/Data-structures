#include <iostream>

using namespace std;

struct BstNode {
    int data;
    BstNode *left;
    BstNode *right;
};

BstNode *GetNewNode(int data) {
    auto *newNode = new BstNode();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BstNode *Insert(BstNode *root, int data) { //insert the data at appropriate position in the tree
    if (root == NULL) {
        root = GetNewNode(data);
        return root;
    } else if (data <= root->data) {
        root->left = Insert(root->left, data);
    } else {
        root->right = Insert(root->right, data);
    }
    return root;
}

bool Search(BstNode *root, int data) {
    if (root == NULL) return false;
    else if (root->data == data) return true;
    else if (data <= root->data) return Search(root->left, data);
    else return Search(root->right, data);
}

int FindMin(BstNode *root) {
    if (root == NULL) {
        cout << "Error: tree is empty" << endl;
        return -1;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

int FindMax(BstNode *root) {
    if (root == NULL) {
        cout << "Error: tree is empty" << endl;
        return -1;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}

int main() {
    BstNode *root = NULL; //creating an empty tree
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 8);
    root = Insert(root, 12);

    int number;
    cout << "Enter number to search" << endl;
    cin >> number;
    if (Search(root, number)) {
        cout << "Found" << endl;
    } else {
        cout << "Not found" << endl;
    }

    cout << "Min element is: " << FindMin(root) << endl;
    cout << "Max element is: " << FindMax(root) << endl;

    return 0;
}
