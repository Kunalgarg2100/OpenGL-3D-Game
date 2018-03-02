#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotation_y = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->acc = glm::vec3(0, 0, 0);
    height = 2;
    radius = 0.25;
    int p = 0;
    int l = 0;
    static GLfloat cannon_vertex_buffer_data[10010];
    int i = 0, flag = 0;
    float change = 1;
    for(float theta = 0;theta < 361.0; theta += change, flag++){
        cannon_vertex_buffer_data[i++] = position.x - radius*cos(theta * PI / 180.0);
        cannon_vertex_buffer_data[i++] = position.y -2- radius*sin(theta * PI / 180.0)+p;
        cannon_vertex_buffer_data[i++] = position.z + height/2-5+l;

        cannon_vertex_buffer_data[i++] = position.x  - radius*cos(theta * PI / 180.0);
        cannon_vertex_buffer_data[i++] = position.y -2-radius*sin(theta * PI / 180.0)+p;
        cannon_vertex_buffer_data[i++] = position.z -height/2-5+l;

        if(flag % 2 == 0){
            cannon_vertex_buffer_data[i++] = position.x  - radius*cos((theta + change) * PI / 180.0);
            cannon_vertex_buffer_data[i++] = position.y-2- radius*sin((theta + change) * PI / 180.0)+p;
            cannon_vertex_buffer_data[i++] = position.z -5-height/2+l;
        }
        else{
            cannon_vertex_buffer_data[i++] = position.x  - radius*cos((theta - change) * PI / 180.0);
            cannon_vertex_buffer_data[i++] = position.y -2- radius*sin((theta - change) * PI / 180.0)+p;
            cannon_vertex_buffer_data[i++] = position.z + height/2-5+l;
            theta -= change;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, i/3, cannon_vertex_buffer_data,COLOR_RED);


}

void Cannon::draw(glm::mat4 VP,float x, float y, float z) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,1, 0));

    //glm::mat4 rotate1    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(1,0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate  = rotate * glm::translate(glm::vec3(-x, -y, -z));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
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

void Cannon::jump()
{
    if(this->position.y <= 4.1)
            this->speed.y = 4;
}

void Cannon::forward()
{
    this->speed = glm::vec3(-0.5*sin(this->rotation*PI/180.0),0,-0.5*cos(this->rotation*PI/180.0));
    /*this->position.z -= 0.5*cos(this->rotation*PI/180.0);
    this->position.x -= 0.5*sin(this->rotation*PI/180.0);*/
}
void Cannon::backward()
{
    this->speed = glm::vec3(0.5*sin(this->rotation*PI/180.0),0,0.5*cos(this->rotation*PI/180.0));
    /*this->position.z += 0.5*cos(this->rotation*PI/180.0);
    this->position.x += 0.5*sin(this->rotation*PI/180.0);*/
}
