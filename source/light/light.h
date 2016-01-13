#ifndef HELIOS_LIGHT_H
#define HELIOS_LIGHT_H

#include <object.h>

class Light : public Object {
private:
    Vec3 color;

public:
    Light() = default;

    Light(const Vec3 &position, const Vec3 &color) : Object(position), color(color)
    { }

    void set_color(const Vec3 &color)
    {
        this->color = color;
    }

    const Vec3 &get_color() const
    {
        return color;
    }
};

#endif //HELIOS_LIGHT_H
