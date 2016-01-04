#include <iostream>
#include <image.h>

int main(int argc, char **argv)
{

    Image *image = new Image(2048, 2048);

    if(!image->save("foo.ppm")) {
        std::cerr << "Failed to write to file." << std::endl;
        exit(1);
    }

    return 0;
}