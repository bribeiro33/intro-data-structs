// Project UID af1f95f547e44c8ea88730dfb185559ds
#include <string>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  assert(0 < width && width <= MAX_MATRIX_HEIGHT);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  mat->width = width; 
  mat->height = height; 
  //mat->data[width * height] = {0};
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  int width = Matrix_width(mat);
   os << width << " " << Matrix_height(mat) << std::endl; 
  const int SIZE = width * Matrix_height(mat); 
  for (int i = 0; i < SIZE; i++){
    os << mat->data[i] << " ";
    int col = i % width;
    if (col == width - 1){
      os << "\n"; 
    }
  }
 }

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width; 
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height; 
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  int row = 0;
  int index = ptr - mat->data;
  if (index != 0){
    row = index/Matrix_width(mat); 
  }
  return row;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  int index = ptr - mat->data; 
  int col = index % Matrix_width(mat); 
  return col; 
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  // row * width + col = index
  int index = row * Matrix_width(mat) + column; 

  int* ptr = mat->data + index; 

  return ptr; 
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  int index = (row * Matrix_width(mat)) + column; 

  const int* ptr = mat->data + index;

  return ptr; 
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  for (int row = 0; row < Matrix_height(mat); row++){
    for (int col = 0; col < Matrix_width(mat); col++){
        *Matrix_at(mat, row, col) = value; 
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  //  Highest index size in matrix 
  int matrix_size = Matrix_height(mat)*Matrix_width(mat);  
  int* end = mat->data + matrix_size; 
  
  for (int* current_ptr = mat->data; current_ptr < end; current_ptr++){
    
      int mat_row = Matrix_row(mat, current_ptr);
      int mat_height = Matrix_height(mat); 
      int mat_col = Matrix_column(mat, current_ptr);
      int mat_width = Matrix_width(mat);

      if (mat_row == 0 || mat_row == (mat_height - 1) ||
           mat_col == 0 || mat_col == (mat_width - 1)){
        *current_ptr = value; 
      }
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int max = *Matrix_at(mat, 0, 0);
  int matrix_size = Matrix_height(mat)*Matrix_width(mat);  
  
  for (int i = 1; i < matrix_size; i++){
    if (max < mat->data[i]){
      max = mat->data[i];
    }
  }

  return max; 
}

//helper func
//returns a pointer to the minimum value in the specified range
//used in column_of_min_val and min_val_in_row
const int* helper_ptr_to_min_val(const Matrix* mat, int row, 
                            int column_start, int column_end){
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  const int* min = Matrix_at(mat, row, column_end - 1);
  for (int col = column_end - 1; col >= column_start; col--){
    if (*Matrix_at(mat, row, col) <= *min){
      min = Matrix_at(mat, row, col);
    }
  }
  return min; 
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, 
                                        int row, int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  const int* min_ptr = helper_ptr_to_min_val(mat, row, column_start, column_end);
  int min_col = Matrix_column(mat, min_ptr);

  return min_col;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
// column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row, 
                            int column_start, int column_end) {
  
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int min_value = *helper_ptr_to_min_val(mat, row, column_start, column_end);
  
  return min_value; 
}



