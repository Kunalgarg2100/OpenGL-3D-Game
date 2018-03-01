#include "main.h"
#include "cannon.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    Cannon cannon;
    void draw(glm::mat4 VP);
    float height;
    float radius;
    float canx,cany,canz;
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    void left();
    void right();
    void down();
    void up();
private:
    VAO *base;
    VAO *side;
    VAO *face;
    VAO *flag;
};

#endif // BOAT_H
