#include <iostream>
#include <queue>

using namespace std;

struct Node {
    char data;
    Node *left;
    Node *right;
};

//function to insert nodes in a binary search tree
Node *Insert(Node *root, char data) {
    if (root == NULL) {
        root = new Node();
        root->data = data;
        root->left = root->right = NULL;
    }
    else if (data <= root->data) root->left = Insert(root->left, data);
    else root->right = Insert(root->right, data);
    return root;
}

//function to print nodes in a binary tree in Level order
void LevelOrder(Node *root) {
    if (root == NULL) return;
    queue<Node *> Q;
    Q.push(root);
    //while there is at least one discovered node
    while (!Q.empty()) {
        Node *current = Q.front();
        Q.pop(); //removing the element at front
        cout << current->data << " ";
        if (current->left != NULL) Q.push(current->left);
        if (current->right != NULL) Q.push(current->right);
    }
}

int main() {
    Node *root = NULL;
    root = Insert(root, 'M');
    root = Insert(root, 'B');
    root = Insert(root, 'Q');
    root = Insert(root, 'Z');
    root = Insert(root, 'A');
    root = Insert(root, 'C');

    cout << "Print nodes in level order: ";
    LevelOrder(root);
    cout << endl;

    return 0;
}
