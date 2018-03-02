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
    void set_position(float x, float y, float z);
    void tick();
    void left();
    void right();
    void down();
    void jump();
    void forward();
    void backward();
    void up();
    VAO *flag;
};

#endif // SAIL_H
