#include "main.h"
#include"sphere.h"
#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y,float z, float side, int u,int num,color_t color1,color_t color2,color_t color3);
    glm::vec3 position;
    float rotation;
    color_t color;
    int num;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int shootcnt,reqcnt;
    double speed;
    double side;
    Sphere head;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *pole;
};

#endif // BALL_H
