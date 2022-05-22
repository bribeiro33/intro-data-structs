#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.h"
#include "processing.h"
#include "Matrix_test_helpers.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;

TEST(test_1x2_energy_mat){
    Image* img = new Image; 
    Image* img_correct = new Image; 
    //Image* correct = new Image;

    // string input = "P3 2 3\t255 16 5 123\n43\n\n43 9 \n13\n 12 255 \n0 213 76 \n45 209 \n5 33 255 0 \n";
    // std::istringstream ss_input(input);
    Image_init(img, 1, 2);
    Pixel color = {45, 255, 76};
    Image_fill(img, color);
    Image_init(img_correct, 1, 2);
    Image_fill(img_correct, color);

    Pixel color2 = {33, 65, 106};
    Image_set_pixel(img, 0, 0, color2);

    Matrix* energy = new Matrix; 
    compute_energy_matrix(img, energy); 
    Matrix* energy_correct = new Matrix; 
    Matrix_init(energy_correct, 1, 2);
    *Matrix_at(energy_correct, 0, 0) = 0;
    *Matrix_at(energy_correct, 1, 0) = 0;
    ASSERT_TRUE(Matrix_equal(energy,energy_correct));

    // Compute the cost matrix
    Matrix* cost = new Matrix;
    compute_vertical_cost_matrix(energy, cost);
    ASSERT_TRUE(Matrix_equal(cost, energy_correct));
    // Find the minimal cost seam

    int *seam = new int[Matrix_height(cost)]; 
    find_minimal_vertical_seam(cost, seam);
    int seam_correct [1] = {0};
    ASSERT_TRUE(array_equal(seam, seam_correct, 1));
    
    // Remove the minimal cost seam
    Image* img_c = new Image; 
    Image_init(img, 1, 1);
    Image_fill(img_c, color2);
    seam_carve(img, 1, 1);
    Image_equal(img, img_c);

    delete energy; 
    delete img_correct; 
     delete img_c; 
    delete energy_correct; 
    delete cost; 
    delete[] seam; 
    delete img; 
    //delete correct; 
}

TEST_MAIN()