#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *head;

void Insert(int x) {
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->data = x;
    temp->next = head;
    head = temp;
}

void Print() {
    Node *temp = head;
    cout << "List is: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n";
}

int main() {
    head = NULL;
    cout << "How many nubers to insert?" << endl;
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter the number: " << endl;
        cin >> x;
        Insert(x);
        Print();
    }
    return 0;
}
