#include "building.h"
#include "main.h"

Building::Building(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -5.0f,-5.0f,-2.0f, // triangle 1 : begin
        -5.0f,-5.0f, 2.0f,
        -5.0f, 5.0f, 2.0f, // triangle 1 : end
        5.0f, 5.0f,-2.0f, // triangle 2 : begin
        -5.0f,-5.0f,-2.0f,
        -5.0f, 5.0f,-2.0f, // triangle 2 : end
        5.0f,-5.0f, 2.0f,
        -5.0f,-5.0f,-2.0f,
        5.0f,-5.0f,-2.0f,
        5.0f, 5.0f,-2.0f,
        5.0f,-5.0f,-2.0f,
        -5.0f,-5.0f,-2.0f,
        -5.0f,-5.0f,-2.0f,
        -5.0f, 5.0f, 2.0f,
        -5.0f, 5.0f,-2.0f,
        5.0f,-5.0f, 2.0f,
        -5.0f,-5.0f, 2.0f,
        -5.0f,-5.0f,-2.0f,
        -5.0f, 5.0f, 2.0f,
        -5.0f,-5.0f, 2.0f,
        5.0f,-5.0f, 2.0f,
        5.0f, 5.0f, 2.0f,
        5.0f,-5.0f,-2.0f,
        5.0f, 5.0f,-2.0f,
        5.0f,-5.0f,-2.0f,
        5.0f, 5.0f, 2.0f,
        5.0f,-5.0f, 2.0f,
        5.0f, 5.0f, 2.0f,
        5.0f, 5.0f,-2.0f,
        -5.0f, 5.0f,-2.0f,
        5.0f, 5.0f, 2.0f,
        -5.0f, 5.0f,-2.0f,
        -5.0f, 5.0f, 2.0f
    };
    static const GLfloat vertex_buffer_data1[] =
    {
        5.0f, 5.0f, 2.0f,
        -5.0f, 5.0f, 2.0f,
        5.0f,-5.0f, 2.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 11*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_GREEN, GL_FILL);
}

void Building::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(5.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Building::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Building::tick() {
   // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Building::right()
{
    //this->position.x += 0.5;
}
void Building::left()
{
    //this->position.x -= 0.5;
}
