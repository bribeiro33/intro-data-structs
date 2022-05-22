// Project UID af1f95f547e44c8ea88730dfb185559d
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstring>
#include "Matrix.h"
#include "Image.h"

//helper func
//returns pointer to specific rgb channel
// rgb==0 is red, rgb==1 is green, rgb==2 is blue
Matrix* channel_ptr(Image *img, char rgb){
  assert(rgb == 'r' || rgb == 'g' || rgb == 'b');
  
  if (rgb == 'r'){ return &(img->red_channel); }
  else if (rgb == 'g'){ return &(img->green_channel); }
  return &(img->blue_channel);
}

//helper func
//returns pointer to specific rgb channel
// rgb==0 is red, rgb==1 is green, rgb==2 is blue
const Matrix* channel_ptr(const Image *img, char rgb){
  assert(rgb == 'r' || rgb == 'g' || rgb == 'b');
  
  if (rgb == 'r'){ return &(img->red_channel); }
  else if (rgb == 'g'){ return &(img->green_channel); }
  return &(img->blue_channel);
}

//helper func 
//for innit function - takes input and create a pointer to the pixel
//that was just created
Pixel* Pixel_create (std::istream& is, Pixel* p){
  std::string input = "";
  for (int i = 0; i < 3; i++){
    is >> input;
    if (i%3 == 0){
      p->r = stoi(input);
    }
    else if (i%3 == 1){
      p->g = stoi(input); 
    }
    else if (i%3 == 2){
      p->b = stoi(input); 
    }
  }
  return p; 
}

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);
  img->width = width; 
  img->height = height; 
  Matrix_init(channel_ptr(img, 'r'), width, height);
  Matrix_init(channel_ptr(img, 'g'), width, height);
  Matrix_init(channel_ptr(img, 'b'), width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {  
  while (!is.get()){
    std::cout << "open failed" << std::endl; 
  }

  std::string input = ""; 
  
  // p3, width/height, 255
  for (int i = 0; i < 4; i++){
    is >> input; 
    if (i == 1){
      img->width = stoi(input); 
    }
    else if (i == 2){
      img->height = stoi(input);
      int height = img->height;
      int width = img->width; 
      Matrix_init(channel_ptr(img, 'r'), width, height);
      Matrix_init(channel_ptr(img, 'g'), width, height);
      Matrix_init(channel_ptr(img, 'b'), width, height);
    }
  }
  // filling in the pixel values
  Pixel p = {0,0,0};
  Pixel* p_ptr = &p;
  for (int row = 0; row < Image_height(img); ++row){
    for (int col = 0; col < Image_width(img); ++col){
      p_ptr = Pixel_create(is, p_ptr); 
      Image_set_pixel(img, row, col, p);
    }
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {

  os << "P3\n" ; 
  os << Image_width(img) << " " << Image_height(img) << "\n"; 
  os << "255\n"; 
  
  for (int row = 0; row < Image_height(img); ++row){
    for (int col = 0; col < Image_width(img); ++col){
      Pixel current_pix = Image_get_pixel(img, row, col);
      os << current_pix.r << " " << current_pix.g << " " << current_pix.b << " ";
    }
    os << "\n";
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width; 
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img->height; 
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));

  const int *red = Matrix_at(channel_ptr(img, 'r'), row, column);
  const int *green = Matrix_at(channel_ptr(img, 'g'), row, column);
  const int *blue = Matrix_at(channel_ptr(img, 'b'), row, column);

  Pixel p = {*red, *green, *blue};
  return p;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  
  *Matrix_at(channel_ptr(img, 'r'), row, column) = color.r; 
  *Matrix_at(channel_ptr(img, 'g'), row, column) = color.g; 
  *Matrix_at(channel_ptr(img, 'b'), row, column) = color.b; 
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  for (int row = 0; row < Image_height(img); ++row){
    for (int col = 0; col < Image_width(img); ++col){
      Image_set_pixel(img, row, col, color);
    }
  }
}
