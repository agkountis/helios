#ifndef HELIOS_OBJECT_H
#define HELIOS_OBJECT_H

#include <ray.h>

class Object {
protected:
    Vec3 position;

public:

    Object() = default;

    Object(const Vec3 &position) : position(position)
    { }

    virtual void set_position(const Vec3 &position)
    {
        this->position = position;
    }


    virtual const Vec3 &get_position() const
    {
        return position;
    }

    virtual ~Object() = default;
};

#endif //HELIOS_OBJECT_H
