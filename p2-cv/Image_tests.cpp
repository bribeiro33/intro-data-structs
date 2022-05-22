// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

//3x2 where its filled with the same color and then the corners are changed 
// innit1, print, set_pixel, get_pixel, fill
TEST(test_print_simple_3x2) {
  Image *img = new Image; 

  Image_init(img, 3, 2);
  Pixel pix_fill = {25, 25, 25};
  Image_fill(img, pix_fill);
  
  const Pixel color1 = {255, 66, 58};
  const Pixel color2 = {32, 255, 143};
  const Pixel color3 = {0, 0, 255};
  const Pixel color4 = {255, 255, 255};

  ASSERT_EQUAL(Image_width(img), 3);
  ASSERT_EQUAL(Image_height(img), 2);
  Image_set_pixel(img, 0, 0, color1);
  Image_set_pixel(img, 0, 2, color2);
  Image_set_pixel(img, 1, 0, color3);
  Image_set_pixel(img, 1, 2, color4);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), pix_fill));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), color1));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 2), color2));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 0), color3));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 2), color4));

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n3 2\n255\n";
  correct << "255 66 58 25 25 25 32 255 143 \n";
  correct << "0 0 255 25 25 25 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; 
}

//1x1 img with 
TEST(test_print_1x1) {
  Image *img = new Image; 

  Image_init(img, 1, 1);
  ASSERT_EQUAL(Image_width(img), 1);
  ASSERT_EQUAL(Image_height(img), 1);

  Pixel pix_fill = {0, 0, 0};
  Image_fill(img, pix_fill);
  
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), pix_fill));
  const Pixel white = {255, 255, 255};
  Image_set_pixel(img, 0, 0, white);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), white));

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; 
}

//2x3 innit test
//innit2, width, height, get_pixel, set_pixel, print
TEST(test_innit_simple_2x3){
  Image *img = new Image;

  string input = "P3 2 3\t255 16 5 123\n43\n\n43 9 \n13\n"
                 "12 255 \n0 213 76 \n45 209 \n5 33 255 0 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);
  ASSERT_EQUAL(Image_width(img), 2);
  ASSERT_EQUAL(Image_height(img), 3);

  Pixel top_left = {16, 5, 123};
  Pixel top_right = {43, 43, 9};
  Pixel bottom_left = {45, 209, 5};
  Pixel bottom_right = {33, 255, 0}; 
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), top_left));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), top_right));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), bottom_left));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 1), bottom_right));

  //setting pixels to the next corner, clockwise
  Image_set_pixel(img, 0, 0, top_right);
  Image_set_pixel(img, 0, 1, bottom_left);
  Image_set_pixel(img, 2, 0, bottom_right);
  Image_set_pixel(img, 2, 1, top_left);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), top_right));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), bottom_left));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), bottom_right));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 1), top_left));

  string output_correct = "P3\n2 3\n255\n43 43 9 45 209 5 "
            "\n13 12 255 0 213 76 \n33 255 0 16 5 123 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);
  
  delete img;
}

//2x3 innit test
//innit2, width, height, get_pixel, set_pixel, print
TEST(test_innit_1x1){
  Image *img = new Image;

  string input = "P3 1 1 255 102 0 204";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);
  ASSERT_EQUAL(Image_width(img), 1);
  ASSERT_EQUAL(Image_height(img), 1);

  Pixel pixel = {102, 0, 204};
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), pixel));

  Pixel pixel2 = {51, 255, 255};
  Image_set_pixel(img, 0, 0, pixel2);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), pixel2));
  
  string output_correct = "P3\n1 1\n255\n51 255 255 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);

  Image_fill(img, pixel);
  string output_correct2 = "P3\n1 1\n255\n102 0 204 \n";
  std::ostringstream ss_output2;
  Image_print(img, ss_output2);
  actual = ss_output2.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct2);


  
  delete img;
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
