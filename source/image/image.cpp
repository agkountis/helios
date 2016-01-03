#include <fstream>
#include <iostream>
#include "image.h"


bool Image::save_as_ppm(std::string file_name)
{

    std::ofstream file(file_name, std::ios::binary | std::ios::out);

    if(!file.is_open()) {
        std::cerr << "Could not open file " << file_name << " for writing!" << std::endl;
        return false;
    }

    /**
     * Write the .ppm file header.
     */
    file << "P6";
    file << "\n";
    file << width << " " << height;
    file << "\n";
    file << 255; //maximum color range
    file << "\n";

    /**
     * Enter random values for testing.
     */
    for(int i = 0 ; i < height * height ; i++) {
        pixels.push_back(128);
    }

    file.write((char *)pixels[0], width * height);

    file.close();

    return true;
}
