#include <iostream>
#include <fstream>
#include "ppm_image.h"


bool PpmImage::save(const std::string &file_name)
{

    std::ofstream file(file_name, std::ios::binary | std::ios::out);

    if(!file.is_open()) {
        std::cerr << "Could not open file " << file_name << " for writing!" << std::endl;
        return false;
    }

    /**
     * Write the .ppm file header.
     */
    file << "P6" << std::endl;
    file << width << " " << height << std::endl;
    file << max_color_value << std::endl;

    long total_pixels = width * height * 3;

    /**
     * Write the values to the file.
     */
    file.write(pixels, total_pixels);

    file.close();

    return true;
}
