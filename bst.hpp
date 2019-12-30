/**
 * Binary Search Tree - Template
 *
 * Store values in a BST
 * Can use Inorder, Preorder and Postorder to traverse tree
 * Can use Add/Remove to modify tree
 * Rebalance creates a balanced tree
 *
 * @author Kyle Dukart
 * @date 1/25/19
 */

#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int nodeCounter = 0;
template<class T>
class BST {
  // display a sideways ascii representation of tree
  friend ostream &operator<<(ostream &os, const BST &bst) {
    bst.sideways(bst.rootPtr, 0, os);
    return os;
  }

 private:
  // Node for BST
  typedef struct node {
    T data;
    struct node *leftPtr;
    struct node *rightPtr;
  } Node;

  // root of the tree
  Node *rootPtr{nullptr};

  // Make a new BST Node
  Node *makeNode(const T &value) const {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->leftPtr = nullptr;
    newNode->rightPtr = nullptr;
    return newNode;
  }

  // helper function for displaying tree sideways, works recursively
  void sideways(Node *current, int level, ostream &os) const {
    static const string indents{"   "};
    if (current) {
      level++;
      sideways(current->rightPtr, level, os);

      // indent for readability, 4 spaces per depth level
      for (int i = level; i >= 0; i--)
        os << indents;

      // display information of object
      os << current->data << endl;
      sideways(current->leftPtr, level, os);
    }
  }

  // Additional private functions

  // recursively copies a tree, creating a new dynamically allocated tree
  // returning a new rootptr
  Node* copyTree(const Node* treePtr) const {
      Node *newTreePtr = nullptr;
      if (treePtr != nullptr) {
          newTreePtr = makeNode(treePtr->data);
          newTreePtr->leftPtr = copyTree(treePtr->leftPtr);
          newTreePtr->rightPtr = copyTree(treePtr->rightPtr);
      }
      return newTreePtr;
  }

  // recursively finds the height of a tree
  int getHeightHelper(Node* subTreePtr) const {
      if (subTreePtr == nullptr)
          return 0;
      else
          return 1 + max(getHeightHelper(subTreePtr->rightPtr), getHeightHelper(subTreePtr->leftPtr));  // NOLINT
  }

  // recursive inorder traversal applying the visit function
  static void inOrder(void visit(const T &item), Node* treePtr) {
      if (treePtr != nullptr) {
          inOrder(visit, treePtr->leftPtr);
          T nodeData = treePtr->data;
          visit(nodeData);
          inOrder(visit, treePtr->rightPtr);
      }
  }

  // recursive preorder traversal applying the visit function
  static void preOrder(void visit(const T &item), Node* treePtr) {
      if (treePtr != nullptr) {
          T nodeData = treePtr->data;
          visit(nodeData);
          preOrder(visit, treePtr->leftPtr);
          preOrder(visit, treePtr->rightPtr);
      }
  }

  // recursive postorder traversal applying the visit function
  static void postOrder(void visit(const T &item), Node* treePtr) {
      if (treePtr != nullptr) {
          postOrder(visit, treePtr->leftPtr);
          postOrder(visit, treePtr->rightPtr);
          T nodeData = treePtr->data;
          visit(nodeData);
      }
  }

  // recursively traverses both trees,
  // checking if their data and structure is equal
  // answer should be set to true before calling
  void equalityHelper(bool &answer, Node* firstTreePtr, Node* secondTreePtr) const { // NOLINT
      if (answer) {
          if (firstTreePtr == nullptr && secondTreePtr != nullptr) {
              answer = false;
              return;
          } else if (firstTreePtr != nullptr && secondTreePtr == nullptr) {
              answer = false;
              return;
          } else if (firstTreePtr != nullptr) {
              if (firstTreePtr->data != secondTreePtr->data) {
                  answer = false;
                  return;
              } else {
                  equalityHelper(answer, firstTreePtr->leftPtr, secondTreePtr->leftPtr);  // NOLINT
                  equalityHelper(answer, firstTreePtr->rightPtr, secondTreePtr->rightPtr);  // NOLINT
              }
          }
      }
    }

  // Recursively transverses the tree to add a node at the shortest height
  // subTreePtr points to the tree in which we will add the Node
  // newNodePtr points to the new Node
  Node* addHelper(Node* subTreePtr, Node* newNodePtr) {
      if (subTreePtr == nullptr) {
          return newNodePtr;
      } else {
          if (subTreePtr->data > newNodePtr->data) {
              subTreePtr->leftPtr = addHelper(subTreePtr->leftPtr, newNodePtr);
          } else {
              subTreePtr->rightPtr = addHelper(subTreePtr->rightPtr, newNodePtr);  // NOLINT
          }
          return subTreePtr;
      }
  }

  // recursively traverses the tree, deleting nodes postorder
  void clearHelper(Node* treePtr) {
      if (treePtr != nullptr) {
          clearHelper(treePtr->leftPtr);
          clearHelper(treePtr->rightPtr);
          delete treePtr;
      }
  }

  // recursively traverses the tree,
  // increments the node counter at each node
  void countNodes(Node* treePtr) const {
      if (treePtr != nullptr) {
          countNodes(treePtr->leftPtr);
          nodeCounter++;
          countNodes(treePtr->rightPtr);
      }
  }

  // recursively traverses the tree checking if each node's data is == item,
  // updating &answer if true
  void containsHelper(const T &item, Node* treePtr, bool &answer) const {  // NOLINT
      if (treePtr != nullptr && !answer) {
          if (treePtr->data == item) {
              answer = true;
          } else {
              containsHelper(item, treePtr->leftPtr, answer);
              containsHelper(item, treePtr->rightPtr, answer);
          }
      }
  }

  // recursively fills a dynamic array with the tree's values
  void fillArray(T* arrayPtr, Node* treePtr) const {
      if (treePtr != nullptr) {
          arrayPtr[nodeCounter] = treePtr->data;
          nodeCounter--;
          fillArray(arrayPtr, treePtr->leftPtr);
          fillArray(arrayPtr, treePtr->rightPtr);
      }
  }

  // recursively searches tree for a node an deletes it,
  // keeping BST structure intact
  void deleteNode(Node* treePtr, Node* parentPtr, T value, bool &answer) {  // NOLINT
      if (treePtr == nullptr) {
          answer = false;
          return;
      } else if (value < treePtr->data) {
          deleteNode(treePtr->leftPtr, treePtr, value, answer);
      } else if (value > treePtr->data) {
          deleteNode(treePtr->rightPtr, treePtr, value, answer);
      } else if (value == treePtr->data) {  // value has been found at treePtr
          if (treePtr->leftPtr == nullptr && treePtr->rightPtr == nullptr) {
              // node with 0 children
              if (parentPtr != nullptr && parentPtr->leftPtr == treePtr) {
                  parentPtr->leftPtr = nullptr;
              } else if (parentPtr != nullptr && parentPtr->rightPtr == treePtr) {  // NOLINT
                  parentPtr->rightPtr = nullptr;
              }
              delete treePtr;
              answer = true;
          } else if (treePtr->leftPtr == nullptr) {
              // node with only right child
              if (parentPtr != nullptr && parentPtr->leftPtr == treePtr) {
                  parentPtr->leftPtr = treePtr->rightPtr;
              } else if (parentPtr != nullptr) {
                  parentPtr->rightPtr = treePtr->rightPtr;
              }
              delete treePtr;
              answer = true;
          } else if (treePtr->rightPtr == nullptr) {
              // node with only left child
              if (parentPtr != nullptr && parentPtr->leftPtr == treePtr) {
                  parentPtr->leftPtr = treePtr->leftPtr;
              } else if (parentPtr != nullptr) {
                  parentPtr->rightPtr = treePtr->leftPtr;
              }
              delete treePtr;
              answer = true;
          } else {
              // node with 2 children
              T minValue;
              minValue = smallestNode(treePtr->rightPtr);
              treePtr->data = minValue;
              deleteNode(treePtr->rightPtr, treePtr, minValue, answer);
          }
      }
  }

  // recursively finds the minimum value in a given tree
  T smallestNode(Node* treePtr) {
      if (treePtr->leftPtr == nullptr)
          return treePtr->data;
      else
          return smallestNode(treePtr->leftPtr);
  }

 public:
  // constructor, empty tree
  BST() : rootPtr(nullptr) {
  }

  // constructor, tree with root
  explicit BST(const T &rootItem) {
    rootPtr = makeNode(rootItem);
  }

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (i.e. rebalance)
  BST(const T arr[], int n) {
      rootPtr = nullptr;
      for (int i = 0; i < n; i++) {
        Add(arr[i]);
      }
  }

  // copy constructor
  BST(const BST<T> &bst) {
    rootPtr = copyTree(bst.rootPtr);
  }

  // destructor
  virtual ~BST() {
    Clear();
  }

  // true if no nodes in BST
  bool IsEmpty() const {
    return (rootPtr == nullptr);
  }

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int getHeight() const {
    return getHeightHelper(rootPtr);
  }

  // number of nodes in BST
  int NumberOfNodes() const {
    nodeCounter = 0;
    countNodes(rootPtr);
    return nodeCounter;
  }
  // add a new item, return true if successful
  bool Add(const T &item) {
    if (Contains(item)) {
        return false;
    } else {
        Node* newNodePtr = makeNode(item);
        rootPtr = addHelper(rootPtr, newNodePtr);
    }
    return true;
  }

  // remove item, return true if successful
  bool Remove(const T &item) {
    bool answer = false;
    deleteNode(rootPtr, nullptr, item, answer);
    return answer;
  }

  // true if item is in BST
  bool Contains(const T &item) const {
      bool answer = false;
      containsHelper(item, rootPtr, answer);
      return answer;
  }

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void InorderTraverse(void visit(const T &item)) const {
    inOrder(visit, rootPtr);
  }

  // preorder traversal: root-left-right
  void PreorderTraverse(void visit(const T &item)) const {
    preOrder(visit, rootPtr);
  }

  // postorder traversal: left-right-root
  void PostorderTraverse(void visit(const T &item)) const {
    postOrder(visit, rootPtr);
  }

  // create dynamic array, copy all the items to the array
  // and then read the array to re-create this tree from scratch
  // so that resulting tree should be balanced
  void Rebalance() {
      T* tempArray;
      nodeCounter = 0;
      int tempCounter = nodeCounter = NumberOfNodes();
      tempArray = new T[nodeCounter];
      fillArray(tempArray, rootPtr);
      Clear();
      for (int i = 0; i < tempCounter; i++) {
          Add(tempArray[i]);
      }
      delete[] tempArray;
  }

  // delete all nodes in tree
  void Clear() {
      clearHelper(rootPtr);
      rootPtr = nullptr;
  }

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BST<T> &other) const {
      bool answer = true;
      equalityHelper(answer, rootPtr, other.rootPtr);
      return answer;
  }

  // not == to each other
  bool operator!=(const BST<T> &other) const {
    return !(*this == other);
  }
};

#endif  // BST_HPP
