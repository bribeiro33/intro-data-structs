// Project UID af1f95f547e44c8ea88730dfb185559d
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"

using namespace std; 

int main(int argc, char* argv[]){
    
    if (argc < 4 || argc > 5){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" << 
        "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1; 
    }

    string filename = argv[1];
    ifstream fin; 
    fin.open(filename);
    if (!fin.is_open()){
        cout << "Error opening file: " << filename << endl;
        return 1; 
    }

    Image* img = new Image;
    Image_init(img, fin);
    
    int desired_width = atoi(argv[3]);
    int desired_height = Image_height(img);

    if (argc == 5){
        desired_height = atoi(argv[4]);
    }

    if (desired_width <= 0 || desired_width > Image_width(img)){
         cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" << 
        "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1; 
    }
    if (desired_height <= 0 || desired_height > Image_height(img)){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1; 
    }

    seam_carve(img, desired_width, desired_height);
    
    string result_file = argv[2];
    ofstream fout;
    fout.open(result_file); 
    if (!fout.is_open()){
        cout << "Error opening file: " << result_file << endl;
        return 1; 
    }
    
    Image_print(img, fout);

    
    fin.close();
    fout.close();
    delete img; 

    return 0;
}
