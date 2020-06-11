#include<bits/stdc++.h>
using namespace std;

class Node
{
public:
    string key;
    Node *left;
    Node *right;
    int height;
};


int max(int a, int b);


int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


int max(int a, int b)
{
    return (a > b)? a : b;
}


Node* newNode(string key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}


Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    return x;
}


Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;


    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


Node* insert(Node* node, string key)
{

    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;


    node->height = 1 + max(height(node->left),
                           height(node->right));


    int balance = getBalance(node);


    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


Node* minValueNode(Node* node)
{
    Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}
Node* deleteNode(Node* root, string key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {

        if ((root->left == NULL) ||
            (root->right == NULL)) {
            Node *temp = root->left ?
                         root->left :
                         root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp;
            free(temp);
        } else {
            Node *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }

    if (root == NULL)
        return root;

    // update depth
    root->height = 1 + max(height(root->left),
                          height(root->right));

    int balance = getBalance(root);


    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
    void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
void inorder(Node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}
void postorder(Node *root) {
    if (root == NULL)
        return;
    postorder(root ->left);
    postorder(root ->right);
    cout << root->key << " ";
}
// Driver Code
void print2DUtil(Node *root, int space)

{
    if (root == NULL)
        return;
    int COUNT = 5;
    space += COUNT;

    print2DUtil(root->right, space);


    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->key<<"\n";

    print2DUtil(root->left, space);
}

void print2D(Node *root)
{

    print2DUtil(root, 0);
}
int maxDepth(Node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}
Node *splay(Node *root, string key)
{
    if (root == NULL || root->key == key)
        return root;


    if (root->key > key)
    {
        if (root->left == NULL) return root;

        if (root->left->key > key)
        {
            root->left->left = splay(root->left->left, key);

            root = rightRotate(root);
        }
        else if (root->left->key < key) // Zig-Zag (Left Right)
        {
            root->left->right = splay(root->left->right, key);

            // Do first rotation for root->left
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL)? root: rightRotate(root);
    }
    else // Key lies in right subtree
    {
        if (root->right == NULL) return root;

        // Zag-Zig (Right Left)
        if (root->right->key > key)
        {
            root->right->left = splay(root->right->left, key);

            // Do first rotation for root->right
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        // Do second rotation for root
        return (root->right == NULL)? root: leftRotate(root);
    }
}


Node *search(Node *root, string key)
{
    return splay(root, key);
}



int main()
{
    Node *root = NULL;


    root = insert(root, "Abxdsa");
    root = insert(root, "aaaaa");
    root = insert(root, "abcasdas");
    root = insert(root, "bbbbb");
    root = insert(root, "asdsxcv");
    root = insert(root, "sadsdf");
    root = insert(root, "sadssdf");
    root = insert(root, "sadsssdf");
    root = insert(root, "sadssssdf");
    root = insert(root, "saghgdsdf");
    root = insert(root, "saddsdf");
    root = insert(root, "sadscvvdf");



    cout << "Preorder traversal of  "
            "AVL tree is :  \n";
    preOrder(root);
    cout << " " << endl;


    cout << "\nInorder traversal of  "
            "AVL tree is :  \n";
    inorder(root);

    cout << "\nPostorder traversal of  "
            "AVL tree is : \n";
    postorder(root);
    cout << " " << endl;

    cout << "\nHeight of tree is " << maxDepth(root);
    root = deleteNode(root, "aaaaa");
    print2D(root);

    root = search(root, "bbbbb");

    cout << " Traversal of the modified Splay tree is \n";
    preOrder(root);


    return 0;




}


