#include "main.h"
#include "sail.h"
#include "cannon.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z);
    glm::vec3 position,speed,acc;
    float rotation;
    Sail sail;
    Cannon cannon;
    void draw(glm::mat4 VP);
    float height;
    float radius;
    double windir;
    float canx,cany,canz;
    void set_position(float x, float y, float z);
    void tick();
    void left();
    void right();
    void jump();
    void forward();
    void backward();
    bool iswind;
    void blow_wind();
    bounding_box_t bounding_box();
private:
    VAO *base;
    VAO *side;
    VAO *face;
    VAO *pole;
};

#endif // BOAT_H
