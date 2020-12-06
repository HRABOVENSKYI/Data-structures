#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    string surname;
    string name;
    string group;
    int dateOfBirth;
    int rating;
    Node *left;
    Node *right;
};

vector<Node *> k;

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

Node *Delete(Node *root, int rating) {
    if (root == NULL) return root;
    else if (rating < root->rating) root->left = Delete(root->left, rating);
    else if (rating > root->rating) root->right = Delete(root->right, rating);
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
            root->name = temp->name;
            root->surname = temp->surname;
            root->group = temp->group;
            root->dateOfBirth = temp->dateOfBirth;
            root->rating = temp->rating;
            root->right = Delete(root->right, temp->rating);
        }
    }
    return root;
}

void GroupStudents(Node *root, string group) {
    if (root == NULL) return;
    GroupStudents(root->left, group);
    if (root->group == group) {
        k.push_back(root);
    }
    GroupStudents(root->right, group);
}

//function to print nodes, where rating >= 75, in a binary tree inorder
void InorderBestStudents(Node *root, int min) {
    if (root == NULL) return;
    InorderBestStudents(root->left, min);
    if (root->rating >= min) {
        cout << "Student: " << root->name << " " << root->surname << endl;
        cout << "Group: " << root->group << endl;
        cout << "Date of birth: " << root->dateOfBirth << endl;
        cout << "Rating: " << root->rating << endl;
        cout << endl;
    }
    InorderBestStudents(root->right, min);
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

    //create binary tree, sorted by rating
    root = InsertByRating(root, "Hemsworth", "Chris", "IoT-11", 1983, 88);
    root = InsertByRating(root, "Downey", "Robert", "IoT-12", 1965, 78);
    root = InsertByRating(root, "Johansson", "Scarlett", "IoT-13", 1984, 86);
    root = InsertByRating(root, "Ruffalo", "Mark", "IoT-12", 1967, 70);
    root = InsertByRating(root, "Holland", "Tom", "IoT-11", 1996, 92);
    root = InsertByRating(root, "Elizabeth", "Olsen", "IoT-13", 1989, 98);
    root = InsertByRating(root, "Evans", "Chris", "IoT-11", 1981, 54);

    cout << "=========================================" << endl;
    cout << "Print nodes in inorder, sorted by rating:\n" << endl;
    Inorder(root);
    cout << endl;

    GroupStudents(root, "IoT-12"); //create a vector of pointers to students from one group
    for (int i = 0; i < k.size(); i++) {
        root = Delete(root, k[i]->rating); //delete every student from this group
    }
    cout << "=========================================" << endl;
    cout << "Print nodes in inorder, sorted by rating after deletion:\n" << endl;
    Inorder(root);
    cout << endl;

    cout << "=========================================" << endl;
    cout << "Print best students, sorted by rating:\n" << endl;
    InorderBestStudents(root, 74);
    cout << endl;

    cout << "=========================================" << endl;
    cout << "Traversal in level order:\n" << endl;
    LevelOrderTraversal(root);
    cout << endl;

    return 0;
}
