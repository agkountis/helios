#include <iostream>
#include "vec3.h"

using namespace std;

int main() {

    Vec3 vec(2, 2, 2);

    Vec3 vec3 = vec + 2.0;

    cout << vec3.x << " " << vec3.y << " " << vec3.z << endl;

    return 0;
}