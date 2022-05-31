# containers

## Resources
### Iterators
- Articles and reference pages            
    [C++ Reference](https://www.cplusplus.com/reference/iterator/)
    
    [C++ Iterators](https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterators.html)
    
    [Defining C++ Iterators](https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html)

- Article series
    
    [Introduction to Iterators in C++ - GeeksforGeeks](https://www.geeksforgeeks.org/introduction-iterators-c/)

- Videos
    
    [ITERATORS in C++](https://www.youtube.com/watch?v=SgcHcbQ0RCQ&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=93)

#### Allocator
- general
    
    [std::allocator](https://en.cppreference.com/w/cpp/memory/allocator)

    [What is an Allocator?](https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed)

    [std::allocator() in C++ with Examples - GeeksforGeeks](https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/)

- rebind
    
    [allocator::rebind](https://www.ibm.com/docs/en/zos/2.2.0?topic=classes-allocatorrebind)

    [what does (template) rebind do?](https://stackoverflow.com/questions/14148756/what-does-template-rebind-do)
            
#### Keywords and other
- Explicit    
    
    [What does the explicit keyword mean?](https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean)

- friend

    [Friend class and function in C++ - GeeksforGeeks](https://www.geeksforgeeks.org/friend-class-function-cpp/)

    [C++ Template Classes and Friend Function Details](https://web.mst.edu/~nmjxv3/articles/templates.html)

- lvalue and rvalue

    [std::move and the Move Assignment Operator in C++](https://www.youtube.com/watch?v=OWNeCTd7yQE)

    [lvalues and rvalues in C++](https://www.youtube.com/watch?v=fbYknr-HPYE)

    [Introduction](https://www.artima.com/articles/a-brief-introduction-to-rvalue-references)

#### Red Black Tree
        
[Red/Black Tree Visualizer](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

- Overview

    [5.16 Red Black tree | Introduction to Red Black trees | Data structure](https://www.youtube.com/watch?v=3RQtq7PDHog)

- Insertion and rotation

    [5.17 Red Black Tree Insertion](https://www.youtube.com/watch?v=qA02XWRTBdw)

    [10.1 AVL Tree - Insertion and Rotations](https://youtu.be/jDM6_TnYIqE?t=1059)

- Erasing

    [5.10 Binary Search Trees (BST) - Insertion and Deletion Explained](https://www.youtube.com/watch?v=cySVml6e_Fc)

    Deletion in Binary search Tree

    [5.18 Red Black Tree deletion | Data structure](https://www.youtube.com/watch?v=w5cvkTXY0vQ)

    [Deletion in Red-Black (RB) Tree](https://medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea)

- Traversing the tree

    [How to print the nodes of a binary tree in sorted order](https://www.educative.io/edpresso/how-to-print-the-nodes-of-a-binary-tree-in-sorted-order)
            
## Notes on the Red Black Tree (RBT)
### **RBT rules**
- It is a self balancing BST
- Every node is either black or red
- Root is always ***black***
- Every leaf node which is ***null*** (the last children which have no values) is ***black***
- If a node is ***red*** its children **must** be ***black*** (no successive red nodes)
- ***Every path from a node to any of it's descendant null nodes must the have same number of black nodes***

### **Insertion**
#### Cases
1. If tree is empty create new node as root node with color ***black***
2. If tree is not empty, create new node with color ***red***
3. If parent of new node is ***black*** then exit
4. If parent of new node is ***red*** then check the color of parent's sibling of new node
    1. If color is ***black*** or ***null*** then do suitable rotation and recolor
    2. If color is ***red*** then recolor, and check if parent's parent of new node is not root node then recolor it and recheck (if there is a red red conflict)

### **Erasing**
#### In a simple ***BST***
##### Cases
- **0 child =** simply delete the node
- **1 child =** replace the node with its child then delete the leaf node
- **2 children**
    1. ***In-order predecessor =***  we replace the node with its **largest element** in the **left side** of the node, then we delete it
    2. ***In-order successor =***  we replace the node with its **smallest element** from the **right side** of the node, then we delete it
#### In RBT
##### Cases
- General rules
    - We only delete ***leaf nodes*** we don’t delete ***internal nodes*** (if its an internal node we apply one of the cases of the *BST* deletion)
    - When **replacing** nodes we don’t change the *color* we only change its *value*

- If the node is ***red*** just *delete* it (the leaf node)

- If the node is ***black***, then check if:
    - the *sibling* is ***red***
        1. the *sibling* becomes ***black*** and the *parent* becomes ***red***
        2. ***single rotation*** (left left or right right rotation), toward the node’s direction (if the node is ***left*** (in relation to its parent), then ***right right rotation*** is applied and vice-versa)
            1. swap *colors* of *parent* and *sibling*
            2. Rotate to the *node’s direction*
            3. recheck the sibling again
    - The *sibling* is ***black*** (or **null**), and both the sibling’s children are black (or **null**),  the sibling becomes red (if its not **null**)
        - if the parent is ***red***, then it becomes black
        - if the parent is ***black*** and its not ***root*** recheck the sibling of the ***parent*** (because it is the one with the ***Double-Black*** problem)
    - the *sibling* is ***black***, and one of its children is ***red***
        - the ***red*** child is close to the ***Double-Black*** node
            1. swap the *sibling* and *its child* ***color*** (the *sibling* becomes ***red***, and *its child* becomes ***black***)
            2. the sibling will ***rotate* to the opposite** direction of the node (right or left rotation)
            3. recheck the sibling again (the next case is always performed here)
        - the ***red*** child is far from the ***Double-Black*** node
            1. the **red** child becomes **black**
            2. swap the node’s (the ***Double-Black***) *parent* and *sibling* ***colors***
            3. the node’s parent will ***rotate* towards** the node’s direction (the sibling will be in the middle)
