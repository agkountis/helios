#include <mat4.h>
#include <stdio.h>
#include <iostream>
#include <image.h>

int main(int argc, char **argv)
{

    Image image(10, 10);

    if(!image.save_as_ppm("test.ppm")) {
        std::cerr << "Failed to write to file" << std::endl;
        exit(1);
    }

    return 0;
}