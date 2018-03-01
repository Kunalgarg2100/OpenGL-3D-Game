#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    glm::vec3 position;
    float rotation,height,radius,rotation_y;
    void draw(glm::mat4 VP,float x, float y, float z);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    void left();
    void right();
    void down();
    void up();
    void move_up();
    void move_dwn();
    VAO *object;
};

#endif // BOAT_H
