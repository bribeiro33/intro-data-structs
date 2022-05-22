// Project UID af1f95f547e44c8ea88730dfb185559d
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_matrix_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);

  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 5);

  Matrix_fill(mat, 0);

  int *ptr = Matrix_at(mat, 2, 3);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
  ASSERT_EQUAL(*ptr, 0);
  *ptr = 42;

  const int *cptr = Matrix_at(mat, 2, 3);
  ASSERT_EQUAL(*cptr, 42);

  Matrix_fill_border(mat, 2);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 2);

  ASSERT_EQUAL(Matrix_max(mat), 42);

  delete mat;
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

// helper func
// checks that pointer is pointing to correct row, col, 
// and has right value (row() and col())
bool helper_ptr_test(Matrix *mat, int* ptr, int* row_col, int value){
  // row, col, value are the expected 
  bool pass = Matrix_row(mat, ptr) == row_col[0] && 
              Matrix_column(mat, ptr) == row_col[1] &&
              *ptr == value;
  return pass; 
}

// helper func
// checks that pointer is pointing to correct row, col,
// and has right value (row() and col())
bool helper_const_ptr_test(Matrix *mat, const int* ptr,
                             int* row_col, int value){
  // row, col, value are the expected 
  bool pass = Matrix_row(mat, ptr) == row_col[0] && 
              Matrix_column(mat, ptr) == row_col[1] &&
              *ptr == value;
  return pass; 
}

// helper struct?
// struct to make inputting expected values of the four corners easier 
struct ExpectedValues{
  int top_left;
  int top_right; 
  int bottom_left;
  int bottom_right; 
};

// helper func
// checks all four corners are pointing to the right place
bool helper_corner_test(Matrix *mat, ExpectedValues *val) {
  int max_row = Matrix_height(mat) - 1;
  int max_col = Matrix_width(mat) - 1;

  // checking top left corner, set to -1
  int *top_left = Matrix_at(mat, 0, 0);
  *top_left = val->top_left; 
  int row_col [2] = {0,0};
  assert(helper_ptr_test(mat, top_left, row_col, val->top_left));

  // checking top right corner, set to 13
  int *top_right = Matrix_at(mat, 0, max_col);
  *top_right = val->top_right; 
  int row_col2 [2] = {0,max_col};
  assert(helper_ptr_test(mat, top_right, row_col2, val->top_right));

  // checking bottom left corner, set to 0
  int *bottom_left = Matrix_at(mat, max_row, 0);
  *bottom_left = val->bottom_left; 
  int row_col3 [2] = {max_row, 0};
  assert(helper_ptr_test(mat, bottom_left, row_col3, val->bottom_left));

  // checking bottom right corner, set to 256
  int *bottom_right = Matrix_at(mat, max_row, max_col);
  *bottom_right = val->bottom_right; 
  int row_col4 [2] = {max_row, max_col};
  assert(helper_ptr_test(mat, bottom_right, row_col4, val->bottom_right));
  return true; 
}

// helper func
// checks all four corners are pointing to the right place
// checks const at()
bool helper_corner_const_test(Matrix *mat, ExpectedValues *val) {
  int max_row = Matrix_height(mat) - 1;
  int max_col = Matrix_width(mat) - 1;

  // checking top left corner, set to -1
  const int *top_left = Matrix_at(mat, 0, 0);
  int row_col [2] = {0, 0};
  assert(helper_const_ptr_test(mat, top_left, row_col, val->top_left));

  // checking top right corner, set to 13
  int *top_right = Matrix_at(mat, 0, max_col);
  int row_col2 [2] = {0, max_col};
  assert(helper_const_ptr_test(mat, top_right, row_col2, val->top_right));

  // checking bottom left corner, set to 0
  int *bottom_left = Matrix_at(mat, max_row, 0); 
  int row_col3 [2] = {max_row, 0};
  assert(helper_const_ptr_test(mat, bottom_left, row_col3, val->bottom_left));

  // checking bottom right corner, set to 256
  int *bottom_right = Matrix_at(mat, max_row, max_col); 
  int row_col4 [2] = {max_row, max_col};
  assert(helper_const_ptr_test(mat, bottom_right, row_col4, val->bottom_right));
  return true; 
}

//helper func
//tests min_in_row_col and min_in_row
//Matrix_width/2 must be >0
bool helper_min_value_test(const Matrix *mat, int* expected){
  assert(Matrix_width(mat)/2 > 0);
 
  //all of 1st row
  int min_in_row_column = Matrix_column_of_min_value_in_row(mat, 0, 0, Matrix_width(mat));
  assert(min_in_row_column == expected[0]); 
  int min_in_row_value = Matrix_min_value_in_row(mat, 0, 0, Matrix_width(mat));
  assert(min_in_row_value == expected[1]); 
 
  //all of last row
  min_in_row_column = Matrix_column_of_min_value_in_row(mat, Matrix_height(mat) - 1,
                                                         0, Matrix_width(mat));
  assert(min_in_row_column == expected[2]);
  min_in_row_value = Matrix_min_value_in_row(mat, Matrix_height(mat) - 1,
                                               0, Matrix_width(mat));
  assert(min_in_row_value == expected[3]);  
  
  //first half of 1st row
  min_in_row_column = Matrix_column_of_min_value_in_row(mat, 0, 0, Matrix_width(mat)/2);
  assert(min_in_row_column == expected[4]); 
  min_in_row_value = Matrix_min_value_in_row(mat, 0, 0, Matrix_width(mat)/2);
  assert(min_in_row_value == expected[5]);  
  
  //back half of last row
  min_in_row_column = Matrix_column_of_min_value_in_row(mat, Matrix_height(mat) - 1,
                       Matrix_width(mat)/2, Matrix_width(mat));
  assert(min_in_row_column == expected[6]);
  min_in_row_value = Matrix_min_value_in_row(mat, Matrix_height(mat) - 1,
                                 Matrix_width(mat)/2, Matrix_width(mat));
  assert(min_in_row_value == expected[7]); 

  return true;
}

//helper func
//tests Matrix_fill_border
bool tester_fill_border(Matrix* mat, int value){
  Matrix_fill_border(mat, value);

  //row check
  for (int i = 0; i < Matrix_width(mat); i++){
    assert(*Matrix_at(mat, 0, i) == value);
    assert(*Matrix_at(mat, Matrix_height(mat)-1, i) == value);
  }

  //columns check
  for (int i = 0; i < Matrix_height(mat); i++){
    assert(*Matrix_at(mat, i, 0) == value);
    assert(*Matrix_at(mat, i, Matrix_width(mat)-1) == value);
  }

  return true;
}

// 4x4 matrix
// filled with -3
// change values of four corners  
// tested fill(neg), width, height, at (const and not)
//(just corners), max(simple), fill border, print
TEST(test_matrix_even){
  Matrix *mat = new Matrix;
  ExpectedValues val = {-1, 13, 0, 256};
  Matrix_init(mat, 4, 4);
  ASSERT_EQUAL(Matrix_width(mat), 4);
  ASSERT_EQUAL(Matrix_height(mat), 4);
  Matrix_fill(mat, -3);
  
  ASSERT_TRUE(helper_corner_test(mat, &val));
  ASSERT_TRUE(helper_corner_const_test(mat, &val));


  ASSERT_EQUAL(Matrix_max(mat), 256);

  int expected [8] = {1, -3, 1, -3, 1, -3, 2, -3};
  ASSERT_TRUE(helper_min_value_test(mat, expected));

  ASSERT_TRUE(tester_fill_border(mat, 155));

  ostringstream expected_output;
  expected_output << "4 4\n"
                  << "155 155 155 155 \n"
                  << "155 -3 -3 155 \n"
                  << "155 -3 -3 155 \n"
                  << "155 155 155 155 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected_output.str(), actual.str());
 
  delete mat; 
}

// 3x5 matrix
// filled with 0
// change values of four corners  
// tested fill(0), width, height, at (const and not), max(simple), fill border
TEST(test_matrix_odd){
  Matrix *mat = new Matrix;
  ExpectedValues val = {6, 0, 333, -85};
  Matrix_init(mat, 5, 3);
  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 3);
  Matrix_fill(mat, 5);
  
  ASSERT_TRUE(helper_corner_test(mat, &val));
  ASSERT_TRUE(helper_corner_const_test(mat, &val));

  ASSERT_EQUAL(Matrix_max(mat), 333);

  int expected [8] = {4, 0, 4, -85, 1, 5, 4, -85};
  ASSERT_TRUE(helper_min_value_test(mat, expected));

  ostringstream expected_output;
  expected_output << "5 3\n"
                  << "6 5 5 5 0 \n"
                  << "5 5 5 5 5 \n"
                  << "333 5 5 5 -85 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected_output.str(), actual.str());

  ASSERT_TRUE(tester_fill_border(mat, 0));

  delete mat; 
}

// 1x1 matrix
// filled with -6
// change values of four corners  
// tested fill, width, height, at (const and not), max(neg), fill border
TEST(test_matrix_single){
  Matrix *mat = new Matrix;
  ExpectedValues val = {-6, -6, -6, -6};
  Matrix_init(mat, 1, 1);
  ASSERT_EQUAL(Matrix_width(mat), 1);
  ASSERT_EQUAL(Matrix_height(mat), 1);
  Matrix_fill(mat, -6);
  
  ASSERT_TRUE(helper_corner_test(mat, &val));
  ASSERT_TRUE(helper_corner_const_test(mat, &val));

  ASSERT_EQUAL(Matrix_max(mat), -6);
  
  int min_in_row_column = Matrix_column_of_min_value_in_row(mat, 0, 0, 1);
  ASSERT_EQUAL(min_in_row_column, 0); 
  int min_in_row_value = Matrix_min_value_in_row(mat, 0, 0, 1);
  ASSERT_EQUAL(min_in_row_value, -6); 

  ASSERT_TRUE(tester_fill_border(mat, -7));

  ostringstream expected;
  expected << "1 1\n"
           << "-7 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat; 
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
