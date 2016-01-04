#include <iostream>
#include <fstream>
#include "ppm_image.h"


bool PpmImage::save(std::string file_name)
{

    std::ofstream file(file_name, std::ios::binary | std::ios::out);

    if(!file.is_open()) {
        std::cerr << "Could not open file " << file_name << " for writing!" << std::endl;
        return false;
    }

    /**
     * Write the .ppm file header.
     */
    file << "P6\n";
    file << width << " " << height << "\n";
    file << max_color_value << "\n";

    long total_pixels = width * height * 3;

    /**
     * Write the values to the file.
     */
    file.write(pixels, total_pixels);

    file.close();

    return true;
}
