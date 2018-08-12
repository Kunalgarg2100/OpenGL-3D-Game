#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z,color_t color);
    glm::vec3 position,speed,acc;
    float rotation,height,radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(bool iswind,double angle);
    void left();
    void right();
    void down();
    float norm_speed;
    void up();
    void move_up();
    void move_dwn();
    void forward();
    void backward();
    void jump();
    void set_speed(float a);
    VAO *object;
};

#endif // BOAT_H
