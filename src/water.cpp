#include "water.h"
#include "main.h"

Water::Water(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->acc = 0.02;
    int ptr=0;
    GLfloat vertex_buffer_data[72000];
    for(float k=0;k<1;k+=0.1){
        for(int i=0;i<800;i++){
            double angle = i * PI/400;
            vertex_buffer_data[ptr++]=0.0f;
            vertex_buffer_data[ptr++]= k;
            vertex_buffer_data[ptr++]= 0.0f;
            for(int j=0;j<2;j++)
            {
                vertex_buffer_data[ptr++]=1000 * cos(angle);
                vertex_buffer_data[ptr++]=k;
                vertex_buffer_data[ptr++]=1000 * sin(angle);
                angle = (i+1) * PI/400;
            }
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 24000, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *=  glm::translate(position);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Water::tick(){
    if(this->position.y > 1)
        this->acc = -0.02;
    else if (this->position.y < 0)
        this->acc = 0.02;
    this->position.y += this->acc;
}
