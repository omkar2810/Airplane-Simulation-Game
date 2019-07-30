#include "water.h"
using namespace std;
float height_map1[500][500];
GLfloat vertex_buffer_data1[256*256*18];
GLfloat vertex_color_data1[256*256*18];
void design_map1(int siz,float height)
{
	for(int i=0;i<=siz;i++)
	{
		height_map1[i][siz] = height_map1[i][0] = 0.1;
	}
	for(int i=0;i<=siz;i++)
	{
		height_map1[siz][i] = height_map1[0][i] = 0.1;
	}	

	int win_siz = siz;
	while(win_siz>1)
	{
		for(int i=0;i<siz;i+=win_siz)
		{
			for(int j=0;j<siz;j+=win_siz)
			{
				// printf("i=%d j=%d win=%d\n",i,j,win_siz);
				float p1 = height_map1[i][j];
				float p2 = height_map1[i][j+win_siz];
				float p3 = height_map1[i+win_siz][j];
				float p4 = height_map1[i+win_siz][j+win_siz];
				
				if(height_map1[i+win_siz/2][j+win_siz/2]==0.0)
				{
					height_map1[i+win_siz/2][j+win_siz/2] = (p1+p2+p3+p4)/4 + float(rand()%2)/10.0;
				}		
				float p5 = height_map1[i+win_siz/2][j+win_siz/2];
				if(height_map1[i][j+win_siz/2]==0)
					height_map1[i][j+win_siz/2] = (p1+p2+p5)/3.0 + float(rand()%2)/10.0;
				
				if(height_map1[i+win_siz/2][j]==0)	
					height_map1[i+win_siz/2][j] = (p1+p5+p3)/3.0+float(rand()%2)/10.0;
				
				if(height_map1[i+win_siz/2][j+win_siz]==0)	
					height_map1[i+win_siz/2][j+win_siz] = (p2+p4+p5)/3.0+float(rand()%2)/10.0 ;
				
				if(height_map1[i+win_siz][j+win_siz/2]==0)
					height_map1[i+win_siz][j+win_siz/2] = (p3+p4+p5)/3.0+float(rand()%2)/10.0 ;
			}
		}
		win_siz/=2;
	}

}

Water::Water(glm::vec3 pos, int siz,int type,float blk)
{
	this->position = pos;
	int n = 4;
	this->rotationx = 0;
	this->rotationy = 0;
	this->rotationz = 0;
	design_map1(siz,3.0);
    float xarr1[5];
    float yarr1[5];
	float angle = float(2.0*3.14)/float(n);
	float rotation[3][3] = {(float)cos(angle),(float)-sin(angle),0.0,(float)sin(angle),(float)cos(angle),0.0,0.0,0.0,1.0};
	float block = blk;
    
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
		cur_y = -(float)block*(float)row;
		for(int col=0;col<col_siz;col++)
		{	
			cur_x = (float)block*(float)col;

			// std::	<<cur_x<<" "<<cur_y<<std::endl; 
			for(int i=0;i<2;i++)
			{
				float s1,s2,s3;
				if(i==0)
				{
					s1 = height_map1[row][col];
					s2 = height_map1[row+1][col];
					s3 = height_map1[row+1][col+1];
				}
				if(i==1)
				{
					s1 = height_map1[row+1][col+1];
					s2 = height_map1[row][col+1];
					s3 = height_map1[row][col];
				}
				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)] = xarr1[2*i]+cur_x;
				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)+1] = s1;
				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)+2] = yarr1[2*i]+cur_y;

				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)+3] = xarr1[(2*i+1)%n]+cur_x;
				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)+4] = s2;
				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)+5] = yarr1[(2*i+1)%n]+cur_y;

				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)+6] = xarr1[(2*i+2)%n]+cur_x;
				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)+7] = s3;
				vertex_buffer_data1[9*(i+(row*col_siz+col)*2)+8] = yarr1[(2*i+2)%n]+cur_y;


				// vertex_color_data1[9*(i+(row*col_siz+col)*2)]   = 0.2;
				// vertex_color_data1[9*(i+(row*col_siz+col)*2)+1] = 0.2;
				// vertex_color_data1[9*(i+(row*col_siz+col)*2)+2] = 1.0 - s1/2.0;

				// vertex_color_data1[9*(i+(row*col_siz+col)*2)+3] = 0.2f;
				// vertex_color_data1[9*(i+(row*col_siz+col)*2)+4] = 0.2f;
				// vertex_color_data1[9*(i+(row*col_siz+col)*2)+5] = 1.0-s2/2.0;

				// vertex_color_data1[9*(i+(row*col_siz+col)*2)+6] = 0.0f;
				// vertex_color_data1[9*(i+(row*col_siz+col)*2)+7] = 0.0f;
				// vertex_color_data1[9*(i+(row*col_siz+col)*2)+8] = 1.0-s3/2.0;

				if(type==1)
				{
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+1] = rgb(0) + rgb(30)*((s1-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)]   = rgb(0) + rgb(144)*((s1-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+2] = rgb(205) + rgb(50)*((s1-0.1)/0.5);

					vertex_color_data1[9*(i+(row*col_siz+col)*2)+3] = rgb(0) + rgb(30)*((s2-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+4] = rgb(0) + rgb(144)*((s2-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+5] = rgb(205) + rgb(50)*((s2-0.1)/0.5);

					vertex_color_data1[9*(i+(row*col_siz+col)*2)+6] = rgb(0) + rgb(30)*((s3-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+7] = rgb(0) + rgb(144)*((s3-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+8] = rgb(205) + rgb(50)*((s3-0.1)/0.5);
				}
				else
				{
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+1] = rgb(107) + rgb(20)*((s1-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)]   = rgb(142) + rgb(113)*((s1-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+2] = rgb(32) - rgb(32)*((s1-0.1)/0.5);

					vertex_color_data1[9*(i+(row*col_siz+col)*2)+3] = rgb(107) + rgb(20)*((s2-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+4] = rgb(142) + rgb(113)*((s2-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+5] = rgb(32) - rgb(32)*((s2-0.1)/0.5);

					vertex_color_data1[9*(i+(row*col_siz+col)*2)+6] = rgb(107) + rgb(20)*((s3-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+7] = rgb(142) + rgb(113)*((s3-0.1)/0.5);
					vertex_color_data1[9*(i+(row*col_siz+col)*2)+8] = rgb(32) - rgb(32)*((s3-0.1)/0.5);
				}
					
				
			}
		}
	}
	
	this->object = create3DObject(GL_TRIANGLES,row_siz*col_siz*2*3, vertex_buffer_data1,vertex_color_data1, GL_FILL);
}

void Water::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	 glm::mat4 rotatex    = glm::rotate((float) (this->rotationx), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz), glm::vec3(0, 0, 1));
    glm::mat4 rotate     =rotatex*rotatey*rotatez;
	glm::mat4 scale = glm::scale(glm::vec3(5.0,5.0,5.0));
	Matrices.model *= (translate*rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}