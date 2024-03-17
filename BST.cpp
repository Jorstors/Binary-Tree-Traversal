#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Tree
{
    private:
        struct Node
        {
            int data = -1;
            Node *parent = nullptr;
            Node *left = nullptr;
            Node *right = nullptr;

            Node() {}
            Node(int data) : data(data) {}
        };

        Node *root = nullptr;

    // recursively searches tree tructure
    // for data input's sorted position
        void addLeafPrivate(int data, Node *n)
        {
            if (data < n->data)
            {
                if (n->left != nullptr)
                    addLeafPrivate(data, n->left);
                else
                    n->left = new Node(data);
            }
            else if (data > n->data)
            {
                if (n->right != nullptr)
                    addLeafPrivate(data, n->right);
                else
                    n->right = new Node(data);
            }
        }

        void PrintIOPrivate(Node* n)
        {
            //if tree is not made
            if (root == nullptr)
            {
                cout << "Tree not made." << endl;
                return;
            }

            if (n->left != nullptr) //left
                PrintIOPrivate(n->left);
            
            cout << n->data << ", "; //root
            
            if (n->right != nullptr) //right
                PrintIOPrivate(n->right);

            //recursion goes out of scope and releases from stack (returns to parent)
        }

        void PrintPrePrivate(Node *n)
        {
            // if tree is not made
            if (root == nullptr)
            {
                cout << "Tree not made." << endl;
                return;
            }

            cout << n->data << ", "; // root

            if (n->left != nullptr) // left
                PrintPrePrivate(n->left);

            if (n->right != nullptr) // right
                PrintPrePrivate(n->right);

            // recursion goes out of scope and releases from stack (returns to parent)
        }

        void PrintPostPrivate(Node *n)
        {
            // if tree is not made
            if (root == nullptr)
            {
                cout << "Tree not made." << endl;
                return;
            }

            if (n->left != nullptr) // left
                PrintPostPrivate(n->left);


            if (n->right != nullptr) // right
                PrintPostPrivate(n->right);

            cout << n->data << ", "; // root

            // recursion goes out of scope and releases from stack (returns to parent)
        }
    

    public:
        Tree() {}
        Tree(vector<int> intVector) 
        { 
            sort(intVector.begin(), intVector.end());
            root = new Node(intVector[intVector.size() / 2]); // middle of sorted vector
            intVector.erase(intVector.begin() + intVector.size() / 2); // remove middle
            for_each(intVector.begin(), intVector.end(), [this](int data) { addLeaf(data); }); 
        }

        //to-private function--for recursion
        void addLeaf(int data)
        { 
            if (root == nullptr)
                root = new Node(data);
            else
                addLeafPrivate(data, root); 
        }

        void PrintIO() // inorder recursive
        { PrintIOPrivate(root); }
        void PrintPre() // preorder recursive
        { PrintPrePrivate(root); }
        void PrintPost() // postorder recursive
        { PrintPostPrivate(root); }

        void PrintLevels() // level order iterative
        {
            if (root == nullptr)
            {
                cout << "Tree not made." << endl;
                return;
            }
            vector<vector<int>> levels; // for data use other than cout
            queue<Node*> q; 
            q.push(root);
            while(!q.empty())
            {
                vector<int> level;
                for(int i = 0; i < q.size(); i++)
                {
                    Node *n = q.front();
                    q.pop();
                    if(n->left != nullptr) { q.push(n->left); }
                    if(n->right != nullptr) { q.push(n->right); }
                    level.push_back(n->data);
                }
                levels.push_back(level);
                for (int n : level)
                    cout << n << ", ";
            }
        }
};
int main(void)
{
    vector<vector<int>> testCases = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {5, 1, 9, 4, 8, 2, 6, 3, 7, 0},
        {7, 2, 9, 4, 2, 6, 3, 7, 5, 4},
        {5},
        {10, 5},
        {20, 35, 15, 10, 40, 25, 5, 30, 2, 8, 12, 18, 22, 28, 32, 38, 45},
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

    for(vector<int> intVector : testCases)
    {
        Tree tree(intVector);
        static int count = 1;
        cout << "=================================================" << endl;
        cout << "Test Case: { "; 
        for (int n : intVector) cout << n << ", ";
        cout << "}" << endl << endl;

        cout << "In Order:   ";
        tree.PrintIO();
        cout << endl;

        cout << "Pre Order:  ";
        tree.PrintPre();
        cout << endl;

        cout << "Post Order: ";
        tree.PrintPost();
        cout << endl;

        cout << "Levels:     ";
        tree.PrintLevels();
        cout << endl;
        cout << "=================================================" << endl;
        count++;
    }

    return 0;
}