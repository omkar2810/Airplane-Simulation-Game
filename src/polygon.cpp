#include "main.h"
#include "polygon.h"

Polygon::Polygon(int n, int part,color_t color,glm::vec3 scale,glm::vec3 position, float ang)
{
	this->color = color;
	this->scale = scale;
	this->position = position;
	this->angle = ang;
	float angle = float(2.0*3.14)/float(n);
	float rotation[3][3] = {(float)cos(angle),(float)-sin(angle),0.0,(float)sin(angle),(float)cos(angle),0.0,0.0,0.0,1.0};
	float xarr[n];
	float yarr[n];
	xarr[0]=0.0;
	yarr[0]=1.0;
    GLfloat vertex_buffer_data[500];
	for(int i=1;i<n;i++)
	{
		float x =rotation[0][0]*xarr[i-1] + rotation[0][1]*yarr[i-1];
		float y =rotation[1][0]*xarr[i-1] + rotation[1][1]*yarr[i-1];
		xarr[i] = x;
		yarr[i] = y;
	}
		
	for(int i=0;i<n/part;i++)
	{
		// if(n==500)
		// 	printf("%d\n",i);
		vertex_buffer_data[9*i] = 0.0;
		vertex_buffer_data[9*i+1] = 0.0;
		vertex_buffer_data[9*i+2] = 0.0;

		vertex_buffer_data[9*i+3] = xarr[i];
		vertex_buffer_data[9*i+4] = yarr[i];
		vertex_buffer_data[9*i+5] = 0.0;

		vertex_buffer_data[9*i+6] = xarr[(i+1)%n];
		vertex_buffer_data[9*i+7] = yarr[(i+1)%n];
		vertex_buffer_data[9*i+8] = 0.0;

	}

	this->object = create3DObject(GL_TRIANGLES,3*n/part, vertex_buffer_data, color, GL_FILL);
}

void Polygon::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(this->scale);
	glm::vec3 axis(0,0,1);
	glm::mat4 rotation = glm::rotate(this->angle,axis);
    
    Matrices.model *= (translate*scale*rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Polygon::tick(float x, float y)
{
	this->position.x += x;
	this->position.y += y;
}
