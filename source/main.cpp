#include <iostream>
#include <ppm_image.h>

int main(int argc, char **argv)
{

    Image *image = new PpmImage(2048, 2048);

    if(!image->save("test.ppm")) {
        std::cerr << "Failed to write to file" << std::endl;
        exit(1);
    }

    return 0;
}