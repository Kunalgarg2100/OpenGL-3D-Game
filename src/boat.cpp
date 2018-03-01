#include "boat.h"
#include "main.h"
//#include "cannon.h"

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat base_vertex_buffer_data[] = {
        -1.0f, -1.0f, -2.0f,
        1.0f, -1.0f, -2.0f,
        -1.0f, -1.0f, 2.0f,

        -1.0f, -1.0f,2.0f,
        1.0f, -1.0f, 2.0f,
        1.0f, -1.0f, -2.0f
    };
    GLfloat side_vertex_buffer_data[] = {
        -1.0f, -1.0f, -2.0f,
        -1.0f, -1.0f, 2.0f,
        -2.0f, 1.0f, 3.0f,

        -1.0f, -1.0f, -2.0f,
        -2.0f, 1.0f, 3.0f,
        -2.0f, 1.0f, -3.0f,

        1.0f, -1.0f, -2.0f,
        1.0f, -1.0f, 2.0f,
        2.0f, 1.0f, 3.0f,

        1.0f, -1.0f, -2.0f,
        2.0f, 1.0f, 3.0f,
        2.0f, 1.0f, -3.0f,

    };
    GLfloat face_vertex_buffer_data[] = {
        -2.0f,   1.0f,-3.0f,
        -1.0f, -1.0f, -2.0f,
        0.0f, 2.0f,-4.0f,

        2.0f, 1.0f,-3.0f,
        1.0f,  -1.0f,-2.0f,
        0.0f, 2.0f,-4.0f,

        0.0f, 2.0f,-4.0f,
        -1.0f, -1.0f,-2.0f,
        1.0f, -1.0f,-2.0f,

         -2.0f, 1.0f, 3.0f,
        -1.0f,-1.0f, 2.0f,
        0.0f, 2.0f, 4.0f,

        2.0f, 1.0f,3.0f,
        1.0f,  -1.0f,2.0f,
        0.0f,  2.0f,4.0f,

        0.0f, 2.0f,4.0f,
        -1.0f,-1.0f, 2.0f,
        1.0f,-1.0f, 2.0f,

    };

    const double PI = 4 * atan(1);
    int ptr=0;
    GLfloat flag_vertex_buffer_data[7200];
        for(int i=0;i<800;i++){
            double angle = i * PI/400;
            for(int j=0;j<3;j++)
                flag_vertex_buffer_data[ptr++]=0.0f;
            for(int j=0;j<2;j++)
            {
                flag_vertex_buffer_data[ptr++]=0.2*cos(angle);
                flag_vertex_buffer_data[ptr++]=4.0f;
                flag_vertex_buffer_data[ptr++]=0.5f*sin(angle);
                angle = (i+1) * PI/400;
            }
        };
    //this->cannon = Cannon(x,y,z);
    this->base = create3DObject(GL_TRIANGLES, 2 * 3, base_vertex_buffer_data, COLOR_BLACK);
    this->side = create3DObject(GL_TRIANGLES, 4 * 3, side_vertex_buffer_data,COLOR_RED);
    this->face = create3DObject(GL_TRIANGLES, 6 * 3, face_vertex_buffer_data,COLOR_GREEN);
    this->flag = create3DObject(GL_TRIANGLES, 2400, flag_vertex_buffer_data,COLOR_BACKGROUND, GL_FILL);

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
    draw3DObject(this->flag);
    //draw3DObject(this->cannon.object);
    //cannon.draw(cannon);

}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Boat::right()
{
    this->position.x += 0.5;
}
void Boat::left()
{
    this->position.x -= 0.5;
}
void Boat::up()
{
    this->position.z += 0.5;
}
void Boat::down()
{
    this->position.z -= 0.5;
}
