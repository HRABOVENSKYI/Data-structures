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
    } else if (data <= root->data) root->left = Insert(root->left, data);
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

//function to print nodes in a binary tree preorder
void Preorder(Node *root) {
    if (root == NULL) return;
    cout << root->data << " ";
    Preorder(root->left);
    Preorder(root->right);
}

//function to print nodes in a binary tree inorder
void Inorder(Node *root) {
    if (root == NULL) return;
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}

//function to print nodes in a binary tree postorder
void Postorder(Node *root) {
    if (root == NULL) return;
    Postorder(root->left);
    Postorder(root->right);
    cout << root->data << " ";
}

bool IsSubtreeLesser(Node *root, int value) {
    if (root == NULL) return true;
    if (root->data <= value
    && IsSubtreeLesser(root->left, value)
    && IsSubtreeLesser(root->right, value))
        return true;
    else
        return false;
}

bool IsSubtreeGreater(Node *root, int value) {
    if (root == NULL) return true;
    if (root->data > value
        && IsSubtreeGreater(root->left, value)
        && IsSubtreeGreater(root->right, value))
        return true;
    else
        return false;
}

bool IsBinarySearchTree(Node *root) {
    if (root == NULL) return true;
    if (IsSubtreeLesser(root->left, root->data)
    && IsSubtreeGreater(root->right, root->data)
    && IsBinarySearchTree(root->left)
    && IsBinarySearchTree(root->right))
        return true;
    else
        return false;
}

int main() {
    /* Creating an example tree
                  7
                 / \
                4   9
               / \
              1   6
               \
                4
    */

    Node *root = NULL;
    root = Insert(root, '7');
    root = Insert(root, '4');
    root = Insert(root, '9');
    root = Insert(root, '1');
    root = Insert(root, '6');
    root = Insert(root, '4');

    cout << "Print nodes in level order: ";
    LevelOrder(root);
    cout << endl;

    cout << "Print nodes in preorder: ";
    Preorder(root);
    cout << endl;

    cout << "Print nodes in inorder: ";
    Inorder(root);
    cout << endl;

    cout << "Print nodes in postorder: ";
    Postorder(root);
    cout << endl;

    if (IsBinarySearchTree(root))
        cout << "Is binary search tree" << endl;
    else
        cout << "Isn't binary search tree";

    return 0;
}
