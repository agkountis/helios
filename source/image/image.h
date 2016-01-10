#ifndef HELIOS_IMAGE_H
#define HELIOS_IMAGE_H

#include <string>
#include <vector>

class Image {
private:
    unsigned int width;
    unsigned int height;

    std::vector<float *> pixels;
    int current_write_index = 0;

    bool save_as_ppm(const std::string &file_name);

    bool save_auto_detect(const std::string &file_name);

public:
    Image(unsigned int width, unsigned int height) : width(width), height(height)
    { }

    enum ImageFormat {
        IMG_FMT_PPM,
        IMG_FMT_AUTO_DETECT
    };

    unsigned int get_width() const;

    unsigned int get_height() const;

    void write_pixel(float r, float g, float b);

    void tone_map_pixel(float *r, float *g, float *b);

    bool save(const std::string &file_name, ImageFormat image_format = IMG_FMT_AUTO_DETECT);
};

#endif //HELIOS_IMAGE_H
