#include "main.h"
#include "sail.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z);
    glm::vec3 position,speed,acc;
    float rotation;
    Sail sail;
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
    void add_sail(float x, float y, float z);
    bounding_box_t bounding_box();
private:
    VAO *base;
    VAO *side;
    VAO *face;
    VAO *pole;
};

#endif // BOAT_H
