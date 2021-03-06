#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y,float z, float side,float rad1, bool flag, color_t color);
    glm::vec3 position;
    float rotation;
    color_t color;
    void draw(glm::mat4 VP);
    bool flag;
    void set_position(float x, float y);
    void tick();
    double speed;
    void left();
    void right();
    double side;
    float rad1;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;

};

#endif // BALL_H
