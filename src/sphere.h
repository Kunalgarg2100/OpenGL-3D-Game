#include "main.h"

#ifndef SPHERE_H
#define SPHERE_H


class Sphere {
public:
    Sphere() {}
    Sphere(float x, float y, float z, float radius,color_t color);
    glm::vec3 position, end1, end2,speed,end3,end4;
    float rotation,radius, norm_speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void left();
    void right();
    void down();
    void up();
    bounding_box_t bounding_box();

private:
    VAO *object;

};

#endif // BOAT_H
