#include "sail.h"
#include "main.h"

Sail::Sail(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->acc = glm::vec3(0, 0, 0);

    GLfloat flag_vertex_buffer_data[] = {
        0.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 2.5f,
        0.0f, 0.0f, 0.0f,

    };
    this->flag = create3DObject(GL_TRIANGLES, 3, flag_vertex_buffer_data,COLOR_BROWN);
}

void Sail::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->flag);
}

void Sail::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sail::tick() {
    //this->rotation += 5;
    this->position += this->speed;
    //this->speed += this->acc;
    if(this->speed.x > 0.5)
        this->speed.x -= 0.5;
    else if(this->speed.x < -0.5)
        this->speed.x += 0.5;
    else
        this->speed.x = 0;
    if(this->speed.z > 0.5)
        this->speed.z -= 0.5;
    else if(this->speed.z < -0.5)
        this->speed.z += 0.5;
    else
        this->speed.z = 0;
    if(this->speed.y > 0.5)
        this->speed.y -= 0.5;
    else if(this->speed.y < -0.5)
        this->speed.y += 0.5;
    else
        this->speed.y = 0;
    if(this->position.y < 4.1)
    {
       this->speed.y = 0;
        if(this->position.y <= 4)
      {
           this->position.y = 4;
       }
    }
    if(this->position.y > 4 && this->speed.y == 0)
    {
        this->speed.y -= 0.5;
    }
}

void Sail::jump()
{
    if(this->position.y <= 4.1)
        this->speed.y = 4;
}

void Sail::forward()
{
    this->speed = glm::vec3(-0.5*sin(this->rotation*PI/180.0),0,-0.5*cos(this->rotation*PI/180.0));
    /*this->position.z -= 0.5*cos(this->rotation*PI/180.0);
    this->position.x -= 0.5*sin(this->rotation*PI/180.0);*/
}

void Sail::backward()
{
    this->speed = glm::vec3(0.5*sin(this->rotation*PI/180.0),0,0.5*cos(this->rotation*PI/180.0));
    /*this->position.z += 0.5*cos(this->rotation*PI/180.0);
    this->position.x += 0.5*sin(this->rotation*PI/180.0);*/
}

void Sail::left()
{
    this->rotation += 0.5;
}

void Sail::right()
{
    this->rotation -= 0.5;
}
