#include "mountain.h"
using namespace std;
float height_map[200][200];

void design_map(int siz,float height,int type)
{

	float low = 0.1;
	if(type==3)
		low = 0.15;
	for(int i=0;i<=siz;i++)
	{
		height_map[i][siz] = height_map[i][0] = low  - (rand()%2)/10;
	}
	for(int i=0;i<=siz;i++)
	{
		height_map[siz][i] = height_map[0][i] = low - (rand()%10)/10;
	}	
	if(type==1)
		height_map[siz/2][siz/2]=height;
	else if(type==2)
		height_map[siz/2][siz/2]=1*height;

	if(type==1||type==2)
	{
		height_map[siz/4][siz/4]=height/3.0;
		height_map[siz/4][3*siz/4]=height/3.0;
		height_map[3*siz/4][siz/4]=height/3.0;
		height_map[3*siz/4][3*siz/4]=height/3.0;
	}
	int win_siz = siz;
	float randint=10.0;
	if(type==3)
		randint=15.0;
	while(win_siz>1)
	{
		for(int i=0;i<siz;i+=win_siz)
		{
			for(int j=0;j<siz;j+=win_siz)
			{
				// printf("i=%d j=%d win=%d\n",i,j,win_siz);
				float p1 = height_map[i][j];
				float p2 = height_map[i][j+win_siz];
				float p3 = height_map[i+win_siz][j];
				float p4 = height_map[i+win_siz][j+win_siz];
				
				if(height_map[i+win_siz/2][j+win_siz/2]==0.0)
				{
					height_map[i+win_siz/2][j+win_siz/2] = (p1+p2+p3+p4)/4 + float(rand()%4)/randint;
				}		
				float p5 = height_map[i+win_siz/2][j+win_siz/2];
				if(height_map[i][j+win_siz/2]==0)
					height_map[i][j+win_siz/2] = (p1+p2+p5)/3.0 + float(rand()%2)/randint;
				
				if(height_map[i+win_siz/2][j]==0)	
					height_map[i+win_siz/2][j] = (p1+p5+p3)/3.0+float(rand()%2)/randint;
				
				if(height_map[i+win_siz/2][j+win_siz]==0)	
					height_map[i+win_siz/2][j+win_siz] = (p2+p4+p5)/3.0+float(rand()%2)/randint ;
				
				if(height_map[i+win_siz][j+win_siz/2]==0)
					height_map[i+win_siz][j+win_siz/2] = (p3+p4+p5)/3.0+float(rand()%2)/randint ;
			}
		}
		win_siz/=2;
	}
	if(type==2)
	{
		for(int i= 0;i<siz/8;i++)
		{
			for(int j=0;j<siz/8;j++)
			{
				height_map[siz/2+i][siz/2+j]=height/4.0;
				height_map[siz/2-i][siz/2+j]=height/4.0;
				height_map[siz/2+i][siz/2-j]=height/4.0;
				height_map[siz/2-i][siz/2-j]=height/4.0;

			}
		}
	}	

}

Mountain::Mountain(glm::vec3 pos, int siz,int type,float bloc)
{
	GLfloat vertex_buffer_data[siz*siz*18];
	GLfloat vertex_color_data[siz*siz*18];
	this->siz = siz;
	this->type = type;
	this->position = pos;
	int n = 4;
	this->rotationx = 0;
	this->rotationy = 0;
	this->rotationz = 0;
	if(type==1||type==3)
		design_map(siz,3.0,type);
	else
		design_map(siz,4.0,type);
		
    float xarr1[5];
    float yarr1[5];
	float angle = float(2.0*3.14)/float(n);
	float rotation[3][3] = {(float)cos(angle),(float)-sin(angle),0.0,(float)sin(angle),(float)cos(angle),0.0,0.0,0.0,1.0};
	float block = bloc;
	this->block = block;
    xarr1[0]=-block*cos(angle/2);
	yarr1[0]=block*sin(angle/2);
	for(int i=1;i<n;i++)
	{
		float x =rotation[0][0]*xarr1[i-1] + rotation[0][1]*yarr1[i-1];
		float y =rotation[1][0]*xarr1[i-1] + rotation[1][1]*yarr1[i-1];
		xarr1[i] = x;
		yarr1[i] = y;
	}
	float cur_x = 0.0;
	float cur_y = 0.0;
	int row_siz = siz;
	int col_siz = siz;
	for(int row=0;row<row_siz;row++)
	{	
		cur_y = -block*row*sqrt(2);
		for(int col=0;col<col_siz;col++)
		{	
			cur_x = block*col*sqrt(2); 
			for(int i=0;i<2;i++)
			{
				float s1,s2,s3;
				if(i==0)
				{
					s1 = height_map[row][col];
					s2 = height_map[row+1][col];
					s3 = height_map[row+1][col+1];
				}
				if(i==1)
				{
					s1 = height_map[row+1][col+1];
					s2 = height_map[row][col+1];
					s3 = height_map[row][col];
				}
				
				vertex_buffer_data[9*(i+(row*col_siz+col)*2)] = xarr1[2*i]+cur_x;
				vertex_buffer_data[9*(i+(row*col_siz+col)*2)+1] =s1;
				vertex_buffer_data[9*(i+(row*col_siz+col)*2)+2] = yarr1[2*i]+cur_y;

				vertex_buffer_data[9*(i+(row*col_siz+col)*2)+3] = xarr1[(2*i+1)%n]+cur_x;
				vertex_buffer_data[9*(i+(row*col_siz+col)*2)+4] = s2;
				vertex_buffer_data[9*(i+(row*col_siz+col)*2)+5] = yarr1[(2*i+1)%n]+cur_y;

				vertex_buffer_data[9*(i+(row*col_siz+col)*2)+6] = xarr1[(2*i+2)%n]+cur_x;
				vertex_buffer_data[9*(i+(row*col_siz+col)*2)+7] = s3;
				vertex_buffer_data[9*(i+(row*col_siz+col)*2)+8] = yarr1[(2*i+2)%n]+cur_y;

				if(type!=2){
					vertex_color_data[9*(i+(row*col_siz+col)*2)]   = 0.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+1] = s1/3.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+2] = 0.2;

					vertex_color_data[9*(i+(row*col_siz+col)*2)+3] = 0.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+4] = s2/3.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+5] = 0.2;

					vertex_color_data[9*(i+(row*col_siz+col)*2)+6] = 0.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+7] = s3/3.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+8] = 0.2;
				}	
				else
				{
					vertex_color_data[9*(i+(row*col_siz+col)*2)]   = 1-s1/3.0;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+1] = 0.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+2] = 0.2;

					vertex_color_data[9*(i+(row*col_siz+col)*2)+3] = 1-s2/3.0;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+4] = 0.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+5] = 0.2;

					vertex_color_data[9*(i+(row*col_siz+col)*2)+6] = 1-s3/3.0;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+7] = 0.2;
					vertex_color_data[9*(i+(row*col_siz+col)*2)+8] = 0.2;
				}
				
				//volcano 1-s/3.0,0.2,0.2				
				
			}
		}
	}
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
			height_map[i][j]=0.0;
	this->object = create3DObject(GL_TRIANGLES,row_siz*col_siz*2*3, vertex_buffer_data,vertex_color_data, GL_FILL);
}

void Mountain::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	 glm::mat4 rotatex    = glm::rotate((float) (this->rotationx), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz), glm::vec3(0, 0, 1));
    glm::mat4 rotate     =rotatex*rotatey*rotatez;
	Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}