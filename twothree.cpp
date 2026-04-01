#include <iostream>
using namespace std;

struct Node {
    int data[2], n;
    Node* child[3];

    Node(int val) {
        data[0] = val;
        n = 1;
        child[0] = child[1] = child[2] = NULL;
    }
};

class TwoThreeTree {
private:
    Node* root;

    Node* insert(Node* node, int val, int &upKey, Node* &newChild) {
        if (node == NULL) {
            newChild = NULL;
            return new Node(val);
        }

        if (node->child[0] == NULL) {
            // Leaf node
            if (node->n == 1) {
                if (val < node->data[0]) {
                    node->data[1] = node->data[0];
                    node->data[0] = val;
                } else {
                    node->data[1] = val;
                }
                node->n = 2;
                newChild = NULL;
                return NULL;
            } else {
                // Split leaf node
                int temp[3] = {node->data[0], node->data[1], val};

                for (int i = 0; i < 3; i++)
                    for (int j = i + 1; j < 3; j++)
                        if (temp[i] > temp[j])
                            swap(temp[i], temp[j]);

                node->data[0] = temp[0];
                node->n = 1;

                Node* newNode = new Node(temp[2]);
                upKey = temp[1];
                newChild = newNode;

                return node;
            }
        }

        int pos;
        if (val < node->data[0])
            pos = 0;
        else if (node->n == 1 || val < node->data[1])
            pos = 1;
        else
            pos = 2;

        int newKey;
        Node* child = insert(node->child[pos], val, newKey, newChild);

        if (child == NULL)
            return NULL;

        if (node->n == 1) {
            if (pos == 0) {
                node->child[2] = node->child[1];
                node->child[1] = newChild;
                node->data[1] = node->data[0];
                node->data[0] = newKey;
            } else if (pos == 1) {
                node->child[2] = newChild;
                node->data[1] = newKey;
            } else {
                node->child[1] = newChild;
                node->data[1] = newKey;
            }
            node->n = 2;
            newChild = NULL;
            return NULL;
        }

        // Split internal node
        int temp[3] = {node->data[0], node->data[1], newKey};
        Node* tempChild[4] = {node->child[0], node->child[1], node->child[2], newChild};
        int k = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (temp[i] > temp[j]) {
                    swap(temp[i], temp[j]);
                }
            }
        }

        node->data[0] = temp[0];
        node->n = 1;
        node->child[1] = tempChild[1];
        node->child[2] = NULL;

        Node* newNode = new Node(temp[2]);
        newNode->child[0] = tempChild[2];
        newNode->child[1] = tempChild[3];
        newNode->child[2] = NULL;

        upKey = temp[1];
        newChild = newNode;

        return node;
    }

    void display(Node* node, int level) {
        if (node != NULL) {
            for (int i = 0; i < level; i++)
                cout << "  ";
            for (int i = 0; i < node->n; i++)
                cout << node->data[i] << " ";
            cout << endl;

            for (int i = 0; i <= node->n; i++)
                if (node->child[i] != NULL)
                    display(node->child[i], level + 1);
        }
    }

public:
    TwoThreeTree() { root = NULL; }

    void insert(int val) {
        if (root == NULL) {
            root = new Node(val);
            return;
        }

        int upKey;
        Node* newChild;

        Node* newRoot = insert(root, val, upKey, newChild);

        if (newRoot != NULL && newChild != NULL) {
            Node* temp = new Node(upKey);
            temp->child[0] = root;
            temp->child[1] = newChild;
            root = temp;
        } else if (newRoot != NULL) {
            root = newRoot;
        }
    }

    void show() {
        display(root, 0);
    }
};

int main() {
    TwoThreeTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);

    cout << "2-3 Tree structure:\n";
    tree.show();

    return 0;
}