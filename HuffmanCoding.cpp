#include <iostream>
#include <queue>
using namespace std;

// A tree node struct
struct Node
{
    char value;
    unsigned characterFrequency;
    Node *leftSubNode;
    Node *rightSubNode;

    Node(char value, unsigned characterFrequency)
    {
        leftSubNode = NULL;
        rightSubNode = NULL;
        this->value = value;
        this->characterFrequency = characterFrequency;
    }
};

// Compare two nodes
struct nodeCompare
{
    bool operator()(Node *left, Node *right)
    {
        return (left->characterFrequency > right->characterFrequency);
    }
};

void printTree(struct Node *root, string encode)
{
    if (!root)
    {
        return;
    }
    if (root->value != 'X')
    {
        cout << encode << " ";
    }

    printTree(root->leftSubNode, encode + "0");
    printTree(root->rightSubNode, encode + "1");
}

int main()
{
    string s = "abcdef";
    int f[] = {5, 9, 12, 13, 16, 45};
    int size = s.length();

    struct Node *leftNode;
    struct Node *rightNode;
    struct Node *newNode;

    // Priority Queue to create a min heap
    priority_queue<Node *, vector<Node *>, nodeCompare > minHeap;

    // Create a leaf node for each unique character
    // and build a min heap of all leaf nodes
    for (int i = 0; i < size; i++)
    {
        minHeap.push(new Node(s[i], f[i]));
    }

    while (minHeap.size() > 1)
    {

        // Extract two nodes with the minimum
        // frequency from the min heap
        leftNode = minHeap.top();
        minHeap.pop();
        rightNode = minHeap.top();
        minHeap.pop();

        // Create a new internal node
        // X is used to distinguish internal
        // nodes without data
        newNode = new Node('X', leftNode->characterFrequency + rightNode->characterFrequency);

        newNode->leftSubNode = leftNode;
        newNode->rightSubNode = rightNode;

        minHeap.push(newNode);
    }

    printTree(minHeap.top(), "");
    cout << endl;
}