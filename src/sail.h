#include "main.h"

#ifndef Sail_H
#define Sail_H


class Sail {
public:
    Sail() {}
    Sail(float x, float y, float z);
    glm::vec3 position,speed,acc;
    float rotation;
    void draw(glm::mat4 VP);
    float height;
    float radius;
    float canx,cany,canz;
    float norm_speed;
    void set_position(float x, float y, float z);
    void tick(bool iswind,double angle);
    void left(float x);
    void right(float x);
    void down();
    void jump();
    void forward(float x);
    void backward(float x);
    void up();
    void set_speed(float a);
    VAO *flag;
};

#endif // SAIL_H
