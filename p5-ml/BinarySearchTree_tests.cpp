// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>
#include <string>
using namespace std;


void helper_print(BinarySearchTree<int> tree) {
    cout << "cout << tree.to_string()" << endl;
    cout << tree.to_string() << endl << endl;

    cout << "cout << tree" << endl << "(uses iterators)" << endl;
    cout << tree << endl << endl;
}
void helper_preorder_print(BinarySearchTree<int> tree, string correct_string){
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    assert(oss_preorder.str() == correct_string);
}
void helper_inorder_print(BinarySearchTree<int> tree, string correct_string){
    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    assert(oss_inorder.str() == correct_string);
}


TEST(basic_tree) {
  BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  helper_print(tree);

  std::string correct = "5 3 7 ";
  helper_preorder_print(tree, correct);

  correct = "3 5 7 ";
  helper_inorder_print(tree, correct);
}

TEST(empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_TRUE(tree.size() == 0);
    ASSERT_TRUE(tree.height() == 0);
    //unisgned add u after
    BinarySearchTree<int> tree_copy = tree; //might need to do something with pointers to 
    //                                          check copy->copy constructor
    ASSERT_TRUE(tree_copy.find(1) == tree_copy.end());
    ASSERT_TRUE(tree_copy.min_element() == tree_copy.end());
    ASSERT_TRUE(tree_copy.max_element() == tree_copy.end());
    ASSERT_TRUE(tree_copy.min_greater_than(5) == tree_copy.end());

    ASSERT_TRUE(tree_copy.check_sorting_invariant());
    
    helper_print(tree_copy);

    std::string correct = "";
    helper_preorder_print(tree_copy, correct);
    helper_inorder_print(tree_copy, correct);
}

TEST(all_left_tree){
    BinarySearchTree<int> tree;
    tree.insert(110);
    tree.insert(15);
    tree.insert(14);
    tree.insert(3);
    tree.insert(-6);
    ASSERT_FALSE(tree.empty());
    ASSERT_TRUE(tree.size() == 5);
    ASSERT_TRUE(tree.height() == 5);
    BinarySearchTree<int> tree_copy = tree; //might need to do something with pointers to 
    //                                          check copy->copy constructor
    ASSERT_TRUE(tree_copy.find(1) == tree_copy.end());
    ASSERT_TRUE(*tree_copy.find(-6) == -6);
    ASSERT_TRUE(*tree_copy.find(110) == 110);
    ASSERT_TRUE(*tree_copy.find(14) == 14);
    
    ASSERT_TRUE(*tree_copy.min_element() == -6);
    ASSERT_TRUE(*tree_copy.max_element() == 110);
    ASSERT_TRUE(tree_copy.min_greater_than(110) == tree_copy.end());
    ASSERT_TRUE(*tree_copy.min_greater_than(109) == 110);
    ASSERT_TRUE(*tree_copy.min_greater_than(14) == 15);
    ASSERT_TRUE(*tree_copy.min_greater_than(-6) == 3);
    ASSERT_TRUE(*tree_copy.min_greater_than(-20) == -6);

    ASSERT_TRUE(tree_copy.check_sorting_invariant());
    
    helper_print(tree_copy);
    std::string correct = "110 15 14 3 -6 ";
    helper_preorder_print(tree_copy, correct);
    correct = "-6 3 14 15 110 ";
    helper_inorder_print(tree_copy, correct);
}

TEST(all_right_tree){
    BinarySearchTree<int> tree;
    tree.insert(-1);
    tree.insert(0);
    tree.insert(2);
    tree.insert(35);
    ASSERT_FALSE(tree.empty());
    ASSERT_TRUE(tree.size() == 4);
    ASSERT_TRUE(tree.height() == 4);

    BinarySearchTree<int> tree_copy = tree;
    ASSERT_TRUE(tree_copy.find(1) == tree_copy.end());
    ASSERT_TRUE(*tree_copy.find(-1) == -1);
    ASSERT_TRUE(*tree_copy.find(35) == 35);
    ASSERT_TRUE(*tree_copy.find(0) == 0);
    
    ASSERT_TRUE(*tree_copy.min_element() == -1);
    ASSERT_TRUE(*tree_copy.max_element() == 35);
    ASSERT_TRUE(tree_copy.min_greater_than(35) == tree_copy.end());
    ASSERT_TRUE(*tree_copy.min_greater_than(34) == 35);
    ASSERT_TRUE(*tree_copy.min_greater_than(0) == 2);
    ASSERT_TRUE(*tree_copy.min_greater_than(-1) == 0);
    ASSERT_TRUE(*tree_copy.min_greater_than(-2) == -1);

    ASSERT_TRUE(tree_copy.check_sorting_invariant());
    
    helper_print(tree_copy);
    std::string correct = "-1 0 2 35 ";
    helper_preorder_print(tree_copy, correct);
    helper_inorder_print(tree_copy, correct);
}

TEST(balanced_tree){
    BinarySearchTree<int> tree;
    tree.insert(11); 
    tree.insert(7); 
    tree.insert(12); 
    tree.insert(1187); 
    tree.insert(-2);
    tree.insert(9);
    tree.insert(8);
    tree.insert(10);
    ASSERT_FALSE(tree.empty());
    ASSERT_TRUE(tree.size() == 8);
    ASSERT_TRUE(tree.height() == 4);

    BinarySearchTree<int> tree_copy = tree;
    ASSERT_TRUE(tree_copy.find(1) == tree_copy.end());
    ASSERT_TRUE(*tree_copy.find(-2) == -2);
    ASSERT_TRUE(*tree_copy.find(1187) == 1187);
    ASSERT_TRUE(*tree_copy.find(8) == 8);

    ASSERT_TRUE(*tree_copy.min_element() == -2);
    ASSERT_TRUE(*tree_copy.max_element() == 1187);
    ASSERT_TRUE(*tree_copy.min_greater_than(7) == 8);
    ASSERT_TRUE(*tree_copy.min_greater_than(6) == 7);
    ASSERT_TRUE(tree_copy.min_greater_than(1187) == tree_copy.end());
    ASSERT_TRUE(*tree_copy.min_greater_than(12) == 1187);
    ASSERT_TRUE(*tree_copy.min_greater_than(65) == 1187);

    ASSERT_TRUE(tree_copy.check_sorting_invariant());

    helper_print(tree_copy);
    std::string correct = "11 7 -2 9 8 10 12 1187 ";
    helper_preorder_print(tree_copy, correct);
    correct = "-2 7 8 9 10 11 12 1187 ";
    helper_inorder_print(tree_copy, correct);
}

TEST(false_invariant){
    BinarySearchTree<int> tree;
    tree.insert(1); 
    tree.insert(0);
    *tree.begin() = 2; 
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(false_complex_invariant){
    BinarySearchTree<int> tree;
    tree.insert(1); 
    tree.insert(0);
    *tree.begin() = 2; 
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST_MAIN()
