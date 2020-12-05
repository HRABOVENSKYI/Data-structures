#include <iostream>
#include <queue>

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

int FindHeight(BstNode *root) {
    if (root == NULL) return -1;
    return max(FindHeight(root->left), FindHeight(root->right)) + 1;
}

void LevelOrderTraversal(BstNode *root) {
    if (root == NULL) return;
    queue<BstNode *> Q;
    Q.push(root);
    //while there is at least one discovered node
    while (!Q.empty()) {
        BstNode *current = Q.front();
        cout << current->data << " ";
        if (current->left != NULL) Q.push(current->left);
        if (current->right != NULL) Q.push(current->right);
        Q.pop(); //removing the element at front
    }
}

int main() {
    BstNode *root = NULL; //creating an empty tree
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 8);
    root = Insert(root, 12);
    root = Insert(root, 6);
    root = Insert(root, 32);

    cout << "Min element is: " << FindMin(root) << endl;
    cout << "Max element is: " << FindMax(root) << endl;

    cout << "Height of the tree is " << FindHeight(root) << endl;

    cout << "Traversal in level order: ";
    LevelOrderTraversal(root);
    cout << endl;

    int number;
    cout << "Enter number to search" << endl;
    cin >> number;
    if (Search(root, number)) {
        cout << "Found" << endl;
    } else {
        cout << "Not found" << endl;
    }

    return 0;
}
