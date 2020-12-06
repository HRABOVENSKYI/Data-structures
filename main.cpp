#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
};

//function to insert nodes in a binary search tree
Node *Insert(Node *root, int data) {
    if (root == NULL) {
        root = new Node();
        root->data = data;
        root->left = root->right = NULL;
    } else if (data <= root->data) root->left = Insert(root->left, data);
    else root->right = Insert(root->right, data);
    return root;
}

Node *FindMin(Node *root) {
    if (root == NULL) {
        cout << "Error: tree is empty" << endl;
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node *FindMax(Node *root) {
    if (root == NULL) {
        cout << "Error: tree is empty" << endl;
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

//function to visit nodes in a binary tree inorder
void Inorder(Node *root) {
    if (root == NULL) return;
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}

Node *Delete(Node *root, int data) {
    if (root == NULL) return root;
    else if (data < root->data) root->left = Delete(root->left, data);
    else if (data > root->data) root->right = Delete(root->right, data);
    else { //Found this data
        //case 1: No child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }

            //case 2: One child
        else if (root->left == NULL) {
            Node *temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == NULL) {
            Node *temp = root;
            root = root->left;
            delete temp;
        }

            //case 3: 2 children
        else {
            Node *temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

int main() {
    /* Creating an example tree
                  5
                 / \
                3   10
               / \   \
              1   4   11
    */
    Node *root = NULL;
    root = Insert(root, 5);
    root = Insert(root, 10);
    root = Insert(root, 3);
    root = Insert(root, 4);
    root = Insert(root, 1);
    root = Insert(root, 11);

    cout << "Print nodes in inorder before deletion: ";
    Inorder(root);
    cout << endl;

    //delete node with any value
    root = Delete(root, 5);

    cout << "Print nodes in inorder after deletion: ";
    Inorder(root);
    cout << endl;

    return 0;
}
