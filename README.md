# generic_avl_tree
Implementation for a generic height balanced binary search tree (AVL Tree)
This repository contains a C++ implementation of an AVL Tree, a self-balancing binary search tree. The AVL Tree ensures that the heights of the left and right subtrees of any node differ by at most one, providing logarithmic time complexity for operations such as insertion, deletion, and search.

**Features**

    Self-balancing: The AVL Tree automatically balances itself using rotations (left and right) to maintain efficient performance during insertions and deletions.
    
    Insertion & Deletion: Supports insertion and deletion of nodes, while maintaining the balance of the tree.
    
    In-order Traversal: Performs an in-order traversal to get the sorted order of elements stored in the tree.
    
    Search: Efficiently searches for a specific element in the tree.
    
    Stress Testing: Includes a stress test function to simulate random insertions and deletions to check the tree's behavior.

**Data Structures**

    Node: A node in the AVL Tree contains:
    
    A value (val).
    
    Pointers to the left and right child nodes (left and right).
    
    An integer height to keep track of the tree's balance.
    
    AVL Tree: The tree is implemented as a class with the following public methods:
    
    insert(int val): Inserts a new value into the tree.
    
    remove(int val): Removes a value from the tree.
    
    search(X val): Searches for a specific value in the tree.
    
    inorder(): Returns the sorted list of elements in the tree.
    
    check_balance(): Prints any balance factor issues or height mismatches in the tree.
