#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y, float z, float rad, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->side = rad;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -rad,-rad,-rad, // triangle 1 : begin
        -rad,-rad, rad,
        -rad, rad, rad, // triangle 1 : end
        rad, rad,-rad, // triangle 2 : begin
        -rad,-rad,-rad,
        -rad, rad,-rad, // triangle 2 : end
        rad,-rad, rad,
        -rad,-rad,-rad,
        rad,-rad,-rad,
        rad, rad,-rad,
        rad,-rad,-rad,
        -rad,-rad,-rad,
        -rad,-rad,-rad,
        -rad, rad, rad,
        -rad, rad,-rad,
        rad,-rad, rad,
        -rad,-rad, rad,
        -rad,-rad,-rad,
        -rad, rad, rad,
        -rad,-rad, rad,
        rad,-rad, rad,
        rad, rad, rad,
        rad,-rad,-rad,
        rad, rad,-rad,
        rad,-rad,-rad,
        rad, rad, rad,
        rad,-rad, rad,
        rad, rad, rad,
        rad, rad,-rad,
        -rad, rad,-rad,
        rad, rad, rad,
        -rad, rad,-rad,
        -rad, rad, rad,
        rad, rad, rad,
        -rad, rad, rad,
        rad,-rad, rad
    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rock::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rock::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Rock::right()
{
    this->position.x += 0.5;
}
void Rock::left()
{
    this->position.x -= 0.5;
}

bounding_box_t Rock::bounding_box() {
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;
    float w = this->side;
    float h = this->side;
    float l = this->side;
    bounding_box_t bbox = { x,y,z,w,h,l};
    return bbox;
}
