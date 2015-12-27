#ifndef HELIOS_PRIMITIVE_H
#define HELIOS_PRIMITIVE_H

#include <vec3.h>

class Primitive {
protected:
    Vec3 position;

public:
    virtual ~Primitive() = default;
};

#endif //HELIOS_PRIMITIVE_H
