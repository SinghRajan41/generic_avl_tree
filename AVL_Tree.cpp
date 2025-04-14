#include <bits/stdc++.h>
#define ll long long int
#define all(x) x.begin(), x.end()
using namespace std;
template<class Y>
class node{
    public:
    Y val;
    int height;
    node *left, *right;
    node(Y val){
        this->val = val;
        left = right = NULL;
        height = 1;
    }
};
template<class X>
class avl_tree{
    node<X> *root;
    vector<X> arr;

    //recursive function to calculate height of the tree
    int height_rec(node<X> *root){
        if(root == NULL){
            return 0;
        }else{
            int left,right;
            left = height(root->left);
            right = height(root->right);
            return 1 + max(left, right);
        }
    }
    int height(node<X> *cur_node){
        if(cur_node == NULL){
            return 0;
        }else{
            return cur_node->height;
        }
    }
    void recal_height(node<X> *cur_node){
        if(cur_node == NULL){
            return;
        }else{
            cur_node->height = 1 + max(height(cur_node->left), height(cur_node->right));
        }
    }
    node<X> * left_rotate(node<X> *root){
        node<X> *a,*b,*c;
        a = root;
        b = a->right;
        c = b->left;
        b->left = a;
        a->right = c;
        recal_height(a);
        recal_height(b);
        return b;
    }
    node<X> * right_rotate(node<X> *root){
        node<X> *a,*b,*c;
        a = root;
        b = a->left;
        c = b->right;
        b->right = a;
        a->left = c;
        recal_height(a);
        recal_height(b);
        return b;
    }
    node<X> * do_height_balance(node<X> *root){
        if(root == NULL){
            return NULL;
        }
        int bf = balance(root);
        //RR - root right heavy, right child is right heavy
        if(bf > 1 && balance(root->right) >= 0){
            return left_rotate(root);
        }
        //LL - root is left heavy and left child is left heavy
        if(bf < -1 && balance(root->left) <= 0){
            return right_rotate(root);
        }
        //RL - root is right heavy and right child is left heavy
        if(bf > 1 && balance(root->right) <= 0){
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }
        //LR - root is left heavy and left child is right heavy
        if(bf < -1 && balance(root->left) >= 0){
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
        return root;
    }
    node<X> * _insert(node<X> *cur_node,int val){
        if(cur_node == NULL){
            return new node(val);
        }else{
            if(val < cur_node->val){
                cur_node->left = _insert(cur_node->left, val);
            }else{
                cur_node->right = _insert(cur_node->right, val);
            }
            recal_height(cur_node);
            return cur_node = do_height_balance(cur_node);
        }
    }
    node<X> * _remove(node<X> *root, int val){
        if(root == NULL)
            return NULL;
        if(val > root->val)
            root->right = _remove(root->right, val);
        else if(val < root->val)
            root->left = _remove(root->left, val);
        else{
            if(root->left == NULL){
                node<X> *temp = root->right;
                delete root;
                return temp;
            }
            else if(root->right == NULL){
                node<X> *temp = root->left;
                delete root;
                return temp;
            }else{
                node<X> *pred = root->left;
                while(pred->right != NULL){
                    pred = pred->right;
                }
                root->val = pred->val;
                root->left = _remove(root->left, val);
                recal_height(root->left);
            }
        }
        recal_height(root);
        return root = do_height_balance(root);
    }
    void _inorder(node<X> *cur_node){
        if(cur_node == NULL){
            return;
        }else{
            _inorder(cur_node->left);
            arr.push_back(cur_node->val);
            _inorder(cur_node->right);
        }
    }
    int balance(node<X> *root){
        if(root == NULL){
            return 0;
        }else{
            return height(root->right) - height(root->left);
        }
    }
    void _check_balance(node<X> *root){
        if(root == NULL){
            return;
        }
        int bf = balance(root);
        if(bf < -1 || bf > 1){
            cout<<bf<<" ";
        }
        if(height_rec(root) != height(root)){
            cout<<"HEIGHT ERROR "<<height_rec(root)<<" "<<height(root)<<"\n";
        }
        _check_balance(root->left);
        _check_balance(root->right);
    }
    bool _search(node<X> *root, X val){
        if(root == NULL){
            return false;
        }
        if(root->val == val){
            return true;
        }else{
            if(val < root->val){
                return _search(root->left, val);
            }else{
                return _search(root->right, val);
            }
        }
    }
    public:
    avl_tree(){
        root = NULL;
    }
    bool search(X val){
        return _search(root, val);
    }
    void insert(int val){
        root = _insert(root, val);
    }
    void remove(int val){
        root = _remove(root, val);
    }
    vector<int> inorder(){
        arr.clear();
        _inorder(root);
        return arr;
    }
    void check_balance(){
        _check_balance(root);
    }
};
template<class X>
void random_insertions(avl_tree<X> &tree, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int val = rand() % 10000000; // Random value between 0 and 999
        cout << "Inserting " << val << endl;
        tree.insert(val);

    }
}

template<class X>
void random_deletions(avl_tree<X> &tree, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int val = rand() % 10000000;
        cout << "Removing " << val << endl;
        tree.remove(val);
    }
}
void stress_test()
{
    avl_tree<int> tree;
    srand(time(0)); // Initialize random seed
    random_insertions(tree, 200000);
    cout << "INSERTION DONE\n";
    random_deletions(tree, 100000);
    cout<<"DELETIONS DONE\n";
    vector<int> arr = tree.inorder();
    if(is_sorted(arr.begin(), arr.end())){
        cout<<"INORDER IS SORTED\n";
    }else{
        cout<<"INORDER IS NOT SORTED\n";
    }
    tree.check_balance();
}
int main(int argc, char *argv[])
{
    stress_test();
    return 0;
}