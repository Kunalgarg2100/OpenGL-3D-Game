#include "sphere.h"
#include "main.h"

Sphere::Sphere(float x, float y, float z, float radius,color_t color){
    this->position = glm::vec3(x, y, z);
    this->radius = radius;
    this->rotation = 0;
    this->norm_speed = 0.01;
    GLfloat base_vertex_buffer_data[15001];
    int ptr = 0;
    for(float alpha = 0;alpha < 181.0; alpha+=1){

        float c_radius = radius * sin(alpha * M_PI / 180.0);
        float d_radius = radius * sin((alpha+1) * M_PI / 180.0);

        int flag = 0;
        for(float theta = 0;theta < 361.0; theta += 100){
            end1 = glm::vec3(c_radius*cos(theta * M_PI / 180.0) , radius*cos(alpha * M_PI / 180.0), c_radius*sin(theta * M_PI / 180.0));
            end2 = glm::vec3(d_radius*cos(theta * M_PI / 180.0) , radius*cos((alpha+1)*M_PI/180.0), d_radius*sin(theta * M_PI / 180.0));
            end3 = glm::vec3(c_radius*cos((theta + 100) * M_PI / 180.0) , radius*cos(alpha * M_PI / 180.0), c_radius*sin((theta + 100) * M_PI / 180.0));
            end4 = glm::vec3(d_radius*cos((theta - 100) * M_PI / 180.0) , radius*cos((alpha+1)*M_PI/180.0), d_radius*sin((theta - 100) * M_PI / 180.0));
            base_vertex_buffer_data[ptr++] = end1.x;
            base_vertex_buffer_data[ptr++] = end1.y;
            base_vertex_buffer_data[ptr++] = end1.z;

            base_vertex_buffer_data[ptr++] = end2.x;
            base_vertex_buffer_data[ptr++] = end2.y;
            base_vertex_buffer_data[ptr++] = end2.z;

            if(flag % 2 != 0)
            {
                base_vertex_buffer_data[ptr++] = end3.x;
                base_vertex_buffer_data[ptr++] = end3.y;
                base_vertex_buffer_data[ptr++] = end3.z;
            }
            else
            {
                base_vertex_buffer_data[ptr++] = end4.x;
                base_vertex_buffer_data[ptr++] = end4.y;
                base_vertex_buffer_data[ptr++] = end4.z;
                theta -= 100;
            }
            flag++;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, ptr/3, base_vertex_buffer_data,color);
}

void Sphere::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sphere::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sphere::tick() {
    this->position += this->speed;
    if(this->speed.y > -1){
        this->speed.y -= 0.02;
    }
    /* Setting limits for speed in x and y direction */
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

bounding_box_t Sphere::bounding_box() {
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;
    float w = this->radius;
    float h = this->radius;
    float l = this->radius;
    bounding_box_t bbox = { x,y,z,w,h,l};
    return bbox;
}
