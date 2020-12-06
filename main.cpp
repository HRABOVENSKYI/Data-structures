#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> k;

struct Node {
    string surname;
    string name;
    string group;
    int dateOfBirth;
    int rating;
    Node *left;
    Node *right;
};

Node *InsertByRating(Node *root, string surname, string name, string group, int dateOfBirth, int rating) {
    if (root == NULL) {
        root = new Node();
        root->surname = surname;
        root->name = name;
        root->group = group;
        root->dateOfBirth = dateOfBirth;
        root->rating = rating;
        root->left = root->right = NULL;
    } else if (rating <= root->rating)
        root->left = InsertByRating(root->left, surname, name, group, dateOfBirth, rating);
    else
        root->right = InsertByRating(root->right, surname, name, group, dateOfBirth, rating);
    return root;
}

//function to print nodes in a binary tree inorder
void Inorder(Node *root) {
    if (root == NULL) return;
    Inorder(root->left);
    cout << "Student: " << root->name << " " << root->surname << endl;
    cout << "Group: " << root->group << endl;
    cout << "Date of birth: " << root->dateOfBirth << endl;
    cout << "Rating: " << root->rating << endl;
    cout << endl;
    Inorder(root->right);
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

void deleteDeepest(Node *root, Node *d_node) {
    queue<Node *> q;
    q.push(root);

    // Do level order traversal until last node
    Node *temp;
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        if (temp == d_node) {
            temp = NULL;
            delete (d_node);
            return;
        }
        if (temp->right) {
            if (temp->right == d_node) {
                temp->right = NULL;
                delete (d_node);
                return;
            } else
                q.push(temp->right);
        }

        if (temp->left) {
            if (temp->left == d_node) {
                temp->left = NULL;
                delete (d_node);
                return;
            } else
                q.push(temp->left);
        }
    }
}

// function to delete element in binary tree
Node *DeleteByGroup(Node *root, string group) {
    if (root == NULL)
        return NULL;

    if (root->left == NULL && root->right == NULL) {
        if (root->group == group)
            return NULL;
        else
            return root;
    }

    queue<Node *> q;
    q.push(root);

    Node *temp;
    Node *key_node = NULL;

    // Do level order traversal to find deepest
    // node(temp) and node to be deleted (key_node)
    while (!q.empty()) {
        temp = q.front();
        q.pop();

        if (temp->group == group)
            key_node = temp;

        if (temp->left)
            q.push(temp->left);

        if (temp->right)
            q.push(temp->right);
    }

    if (key_node != NULL) {
        string x = temp->group;
        deleteDeepest(root, temp);
        key_node->group = x;
    }
    return root;
}

void NumOfGroupStudents(Node *root, string group) {
    if (root == NULL) return;
    NumOfGroupStudents(root->left, group);
    if (root->group == group) {
        k.push_back(1);
    }
    NumOfGroupStudents(root->right, group);
}

//function to print nodes, where rating >= 75, in a binary tree inorder
void InorderBestStudens(Node *root, int min) {
    if (root == NULL) return;
    InorderBestStudens(root->left, min);
    if (root->rating >= min) {
        cout << "Student: " << root->name << " " << root->surname << endl;
        cout << "Group: " << root->group << endl;
        cout << "Date of birth: " << root->dateOfBirth << endl;
        cout << "Rating: " << root->rating << endl;
        cout << endl;
    }
    InorderBestStudens(root->right, min);
}

void LevelOrderTraversal(Node *root) {
    if (root == NULL) return;
    queue<Node *> Q;
    Q.push(root);
    //while there is at least one discovered node
    while (!Q.empty()) {
        Node *current = Q.front();
        cout << "Student: " << current->name << " " << current->surname << endl;
        cout << "Group: " << current->group << endl;
        cout << "Date of birth: " << current->dateOfBirth << endl;
        cout << "Rating: " << current->rating << endl;
        cout << endl;
        if (current->left != NULL) Q.push(current->left);
        if (current->right != NULL) Q.push(current->right);
        Q.pop(); //removing the element at front
    }
}

int main() {
    //creating an empty tree
    Node *root = NULL;

    root = InsertByRating(root, "Hemsworth", "Chris", "IoT-11", 1983, 78);
    root = InsertByRating(root, "Downey", "Robert", "IoT-12", 1965, 86);
    root = InsertByRating(root, "Johansson", "Scarlett", "IoT-13", 1984, 70);
    root = InsertByRating(root, "Ruffalo", "Mark", "IoT-12", 1967, 92);
    root = InsertByRating(root, "Holland", "Tom", "IoT-11", 1996, 98);
    root = InsertByRating(root, "Elizabeth", "Olsen", "IoT-13", 1989, 88);
    root = InsertByRating(root, "Evans", "Chris", "IoT-11", 1981, 54);

    cout << "=========================================" << endl;
    cout << "Print nodes in inorder, sorted by rating:\n" << endl;
    Inorder(root);
    cout << endl;

    NumOfGroupStudents(root, "IoT-11");
    for (int i = 0; i < k.size(); i++) {
        root = DeleteByGroup(root, "IoT-11");
    }
    cout << "=========================================" << endl;
    cout << "Print nodes in inorder, sorted by rating" << endl;
    cout << "after deleting students of IoT-11:\n" << endl;
    Inorder(root);
    cout << endl;

    cout << "=========================================" << endl;
    cout << "Print best students, sorted by rating:\n" << endl;
    InorderBestStudens(root, 74);
    cout << endl;

    cout << "=========================================" << endl;
    cout << "Traversal in level order:\n" << endl;
    LevelOrderTraversal(root);
    cout << endl;

    return 0;
}
