#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *head;

void Insert(int x) { //insert the integer at the beginning of the list
    Node *temp = new Node();
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

void Delete(int n) { //delete a node at position n
    Node *temp1 = head;
    if (n == 1) {
        head = temp1->next; //head now points to second node
        delete temp1;
        return;
    }
    for (int i = 0; i < n - 2; i++) {
        temp1 = temp1->next; //temp1 points to (n - 1)th position
    }
    Node *temp2 = temp1->next; //nth node
    temp1->next = temp2->next; //(n + 1)th node
    delete temp2; //delete temp2
}

void Reverse() {
    Node *current, *prev, *next;
    current = head;
    prev = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

int main() {
    head = NULL; //empty list
    Insert(2);
    Insert(4);
    Insert(6);
    Insert(5);
    Print();
    Reverse();
    Print();
    int n;
    cout << "Enter a position of element to delete: " << endl;
    cin >> n;
    Delete(n);
    Print();

    return 0;
}
