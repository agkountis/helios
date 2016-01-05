#include "image.h"
#include <fstream>
#include <iostream>


/* Static functions */

static std::string extract_file_extension(const std::string &file_name)
{
    long dot_idx = -1;

    dot_idx = file_name.find_last_of('.');

    if(dot_idx < 0) {
        std::cerr << "ERROR: Fine name has no extension! "
                "Could auto-detect the image file format."
                " Please provide a supported file format extension." << std::endl;
        return "";
    }

    return file_name.substr((unsigned long)dot_idx);
}

/* ------------------------------------------------------------------*/

/* Private Functions */

bool Image::save_as_ppm(const std::string &file_name)
{
    std::ofstream file(file_name, std::ios::binary | std::ios::out);

    if(!file.is_open()) {
        std::cerr << "Could not open file " << file_name << " for writing!" << std::endl;
        return false;
    }

    static const int max_color_value = 255;

    /**
     * Write the .ppm file header.
     */
    file << "P6" << std::endl;
    file << width << " " << height << std::endl;
    file << max_color_value << std::endl;

    /**
     * Write the values to the file.
     */
    for(int i = 0 ; i < width * height * 3; i += 3) {

        float *r = &pixels[i];
        float *g = &pixels[i + 1];
        float *b = &pixels[i + 2];

        tone_map(r, g, b);

        int int_rgb[3] = { (int)(*r * 255.0), (int)(*g * 255.0), (int)(*b * 255.0) };

        file.write((const char*)&int_rgb[0], 3 * sizeof(int));
    }

    file.close();

    return true;
}


bool Image::save_auto_detect(const std::string &file_name)
{
    std::string extension = extract_file_extension(file_name);

    if(extension.compare(".ppm") == 0) {
        return save_as_ppm(file_name);
    }

    std::cerr << "ERROR: Unrecognized file format! Please provide a supported file format extension." << std::endl;
    return false;
}

void Image::tone_map(float *r, float *g, float *b)
{
    *r = *r / *r + 1.0f;
    *g = *g / *g + 1.0f;
    *b = *b / *b + 1.0f;
}

/* ---------------------------------------------------------------------- */

unsigned int Image::get_width() const
{
    return width;
}

unsigned int Image::get_height() const
{
    return height;
}


bool Image::save(const std::string &file_name, ImageFormat image_format)
{
    if(file_name.size() == 0) {
        std::cerr << "ERROR: Image file name cannot be an empty string! Please provide a valid file name." << std::endl;
        return false;
    }

    switch (image_format) {
        case IMG_FMT_PPM:
            return save_as_ppm(file_name);
        case IMG_FMT_AUTO_DETECT:
            return save_auto_detect(file_name);
    }

    std::cerr << "ERROR: Could not detect the image file format!" << std::endl;
    return false;
}
