#include "boat.h"
#include "main.h"
#include "sail.h"
#include "cannon.h"

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->speed = glm::vec3(0, 0, 0);
    this->acc = glm::vec3(0, 0, 0);
    this->norm_speed = 0.5;
    this->rotation = 0;
    iswind = false;

    GLfloat base_vertex_buffer_data[] = {
        -1.01f, -1.01f, -2.01f,
        1.01f, -1.01f, -2.01f,
        -1.01f, -1.01f, 2.01f,

        -1.01f, -1.01f,2.01f,
        1.01f, -1.01f, 2.01f,
        1.01f, -1.01f, -2.01f
    };
    GLfloat side_vertex_buffer_data[] = {
        -1.01f, -1.01f, -2.01f,
        -1.01f, -1.01f, 2.01f,
        -2.01f, 1.01f, 3.01f,

        -1.01f, -1.01f, -2.01f,
        -2.01f, 1.01f, 3.01f,
        -2.01f, 1.01f, -3.01f,

        1.01f, -1.01f, -2.01f,
        1.01f, -1.01f, 2.01f,
        2.01f, 1.01f, 3.01f,

        1.01f, -1.01f, -2.01f,
        2.01f, 1.01f, 3.01f,
        2.01f, 1.01f, -3.01f,

    };
    GLfloat face_vertex_buffer_data[] = {
        -2.01f,   1.01f,-3.01f,
        -1.01f, -1.01f, -2.01f,
        0.01f, 2.01f,-4.01f,

        2.01f, 1.01f,-3.01f,
        1.01f,  -1.01f,-2.01f,
        0.01f, 2.01f,-4.01f,

        0.01f, 2.01f,-4.01f,
        -1.01f, -1.01f,-2.01f,
        1.01f, -1.01f,-2.01f,

        -2.01f, 1.01f, 3.01f,
        -1.01f,-1.01f, 2.01f,
        0.01f, 2.01f, 4.01f,

        2.01f, 1.01f,3.01f,
        1.01f,  -1.01f,2.01f,
        0.01f,  2.01f,4.01f,

        0.01f, 2.01f,4.01f,
        -1.01f,-1.01f, 2.01f,
        1.01f,-1.01f, 2.01f,

    };

    int ptr=0;
    GLfloat pole_vertex_buffer_data[7200];
    for(int i=0;i<800;i++){
        double angle = i * M_PI/400;
        for(int j=0;j<3;j++)
            pole_vertex_buffer_data[ptr++]=0.01f;
        for(int j=0;j<2;j++)
        {
            pole_vertex_buffer_data[ptr++]=0.3f*cos(angle);
            pole_vertex_buffer_data[ptr++]=5.0f;
            pole_vertex_buffer_data[ptr++]=0.3f*sin(angle);
            angle = (i+1) * PI/400;
        }
    };

    this->base = create3DObject(GL_TRIANGLES, 2 * 3, base_vertex_buffer_data, COLOR_BROWN);
    this->side = create3DObject(GL_TRIANGLES, 4 * 3, side_vertex_buffer_data,COLOR_RED);
    this->face = create3DObject(GL_TRIANGLES, 6 * 3, face_vertex_buffer_data,{204, 204, 0});
    this->pole = create3DObject(GL_TRIANGLES, 2400, pole_vertex_buffer_data,COLOR_BACKGROUND, GL_FILL);
    sail = Sail(x,y,z);
    cannon = Cannon(x,y,z,COLOR_RED);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->side);
    draw3DObject(this->face);
    draw3DObject(this->pole);
    sail.draw(VP);
    cannon.draw(VP);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->position += this->speed;
    if(iswind){
    this->speed.x = 0.2*cos(windir* M_PI / 180.0f);
    this->speed.z = 0.2*sin(windir* M_PI / 180.0f);
    }
    else{
    //this->speed += this->acc;
    if(this->speed.x > this->norm_speed)
        this->speed.x -= this->norm_speed;
    else if(this->speed.x < -this->norm_speed)
        this->speed.x += this->norm_speed;
    else
        this->speed.x = 0;
    if(this->speed.z > this->norm_speed)
        this->speed.z -= this->norm_speed;
    else if(this->speed.z < -this->norm_speed)
        this->speed.z += this->norm_speed;
    else
        this->speed.z = 0;
    }
    if(this->speed.y > this->norm_speed)
        this->speed.y -= this->norm_speed;
    else if(this->speed.y < -this->norm_speed)
        this->speed.y += this->norm_speed;
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
        this->speed.y -= this->norm_speed;
    }
    sail.tick(iswind,windir);
    cannon.tick(iswind,windir);
}

void Boat::jump()
{
    if(this->position.y <= 4.1)
        this->speed.y = 4;
    sail.jump();
    cannon.jump();
}

void Boat::forward()
{
    if(!iswind){
    this->speed = glm::vec3(-this->norm_speed*sin(this->rotation*PI/180.0),0,-this->norm_speed*cos(this->rotation*PI/180.0));
    sail.forward(this->rotation);
    cannon.forward();
    }
}

void Boat::backward()
{
    if(!iswind){
    this->speed = glm::vec3(this->norm_speed*sin(this->rotation*PI/180.0),0,this->norm_speed*cos(this->rotation*PI/180.0));
    sail.backward(this->rotation);
    cannon.backward();
    }
}

void Boat::left()
{
    this->rotation += this->norm_speed;
    sail.left(this->rotation);
    cannon.left();
}

void Boat::right()
{
    this->rotation -= this->norm_speed;
    sail.right(this->rotation);
    cannon.right();
}

void Boat::set_speed(float a){
    this->norm_speed = a;
    sail.set_speed(a);
    cannon.set_speed(a);
}

bounding_box_t Boat::bounding_box() {
    float w,h,l;
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;
    w = 4,h=3,l=8;
    bounding_box_t bbox = { x,y,z,w,h,l};
    return bbox;
}
