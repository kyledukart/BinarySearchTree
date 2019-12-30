/**
 * Testing BST - Binary Search Tree functions
 *
 * @author Yusuf Pisan, edited by Kyle Dukart
 * @date 19 Jan 2019
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include <string>

#include "bst.hpp"

using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor {
 public:
  TreeVisitor() = delete;

  // insert output to SS rather than cout, so we can test it
  static stringstream SS;

  static string GetSS() {
    return SS.str();
  }

  static void ResetSS() {
    SS.str(string());
  }
  // instead of cout, insert item into a string stream
  static void visitor(const string &item) {
    SS << item;
  }

  // instead of cout, insert item into a string stream
  static void visitor(const int &item) {
    SS << item;
  }
};

// initialize the static variable
stringstream TreeVisitor::SS;

void testBSTConstructors() {
  cout << "\n\n* Testing 0 param constructor, ==, !=, IsEmpty, and XTraverse"
       << endl;
  BST<string> b1;
  BST<string> b2;
  BST<string> b3;
  // == and != for empty trees
  assert(b1 == b2 && (!(b1 != b2)));
  b1.Add("c");
  b2.Add("c");
  b3.Add("b");
  // == and !- for 1-node trees b1, b2, b3
  assert(b1 == b2 && (!(b1 != b2)));
  assert(b1 != b3 && (!(b1 == b3)));

  b1.Add("a");
  b1.Add("f");
  b1.Add("g");
  b1.Add("x");
  b2.Add("a");
  b2.Add("f");
  b2.Add("g");
  b2.Add("x");
  // == for 5-node trees b1, b2
  assert(b1 == b2 && (!(b1 != b2)));

  BST<string> b4(b3);
  // copy constructor for 1-node trees b3, b4
  assert(b3 == b4 && (!(b3 != b4)));

  BST<string> b5(b1);
  // copy constructor for 5-node trees b1, b5
  assert(b1 == b5 && (!(b5 != b1)));

  BST<string> b7("b");
  // 1-param constructor for 1-node trees b3, b7
  assert(b3 == b7 && (!(b3 != b7)));

  cout << "b1 is: " << endl;
  cout << b1 << endl;

  TreeVisitor::ResetSS();
  b1.InorderTraverse(TreeVisitor::visitor);
  string result = "acfgx";
  assert(TreeVisitor::GetSS() == result);

  TreeVisitor::ResetSS();
  b1.PreorderTraverse(TreeVisitor::visitor);
  result = "cafgx";
  assert(TreeVisitor::GetSS() == result);

  TreeVisitor::ResetSS();
  b1.PostorderTraverse(TreeVisitor::visitor);
  result = "axgfc";
  assert(TreeVisitor::GetSS() == result);

  cout << "Done testBSTConstructors" << endl;
}

void test_scratchpad() {
    cout << "Starting test_scratchpad" << endl;
    BST<int> b1;
    BST<int> b2(20);
    BST<int> b3;
    assert(b1.IsEmpty());
    assert(!b2.IsEmpty());
    assert(b1.getHeight() == 0);
    assert(b2.getHeight() == 1);
    b1.Add(20);
    b3.Add(20);
    assert(b1 == b2);
    assert(b2 == b3);
    b1.Add(40);
    assert(b1 != b2);
    b1.Add(41);
    b1.Add(42);
    b1.Add(43);
    b2.Add(43);
    b2.Add(42);
    b2.Add(41);
    b2.Add(40);
    b1.Rebalance();
    b2.Rebalance();
    assert(b1.getHeight() == b2.getHeight());
    cout << "Ending test_scratchpad" << endl;
}

void test_nodeCount() {
    cout << "Starting test_nodeCount" << endl;
    BST<int> b1;
    BST<int> b2(10);
    BST<int> b3(20);
    assert(b1.IsEmpty());
    assert(!b2.IsEmpty());
    assert(!b3.IsEmpty());
    b2.Clear();
    assert(b2.IsEmpty());
    assert(b1.getHeight() == 0);
    assert(b3.getHeight() == 1);
    b3.Add(10);
    b3.Add(40);
    b3.Add(50);
    assert(b3.getHeight() == 3);
//    assert(b1.NumberOfNodes() == 0);
//    assert(b3.NumberOfNodes() == 4);
    cout << "Ending test_nodeCount" << endl;
}

void test_addRemoveContains() {
    cout << "Starting test_addRemoveContains" << endl;
    BST<int> b1;
    BST<int> b2(10);
    BST<int> b3(20);
    assert(b2.Contains(10));
    assert(b3.Contains(20));
    assert(!b2.Contains(-10));
    assert(!b3.Contains(10));
    b1.Add(10);
    b1.Add(50);
    b1.Add(30);
    b1.Add(40);
    b1.Add(20);
    b1.Add(60);
    b1.Add(5);
    b1.Add(80);
    b1.Remove(20);  // delete leaf
    b1.Remove(60);  // delete node with 1 child
    b1.Add(45);
    b1.Remove(50);  // delete node with 2 children
    b1.Remove(10);  // delete root
    TreeVisitor::ResetSS();
    b1.InorderTraverse(TreeVisitor::visitor);
    string result = "530404580";
    assert(TreeVisitor::GetSS() == result);

    cout << "Ending test_addRemoveContains" << endl;
}

void treeQuiz() {

}

void testBSTAll() {
  //testBSTConstructors();
  //test_scratchpad();
  //test_nodeCount();
  //test_addRemoveContains();
  treeQuiz();
}
