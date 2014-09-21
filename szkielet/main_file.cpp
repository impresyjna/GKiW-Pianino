#include <windows.h> 
#include "gl\glew.h"
#include "gl\glut.h"
#include "stdio.h" 
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "tga.h"
#include "tlo.h"
#include "klawisze.h"
#include "pianino.h"
#include "okno.h"
#include "stolek.h"
#include "obraz.h"
#include "Lamp_01.h"
#include <string>

using namespace std; 
using namespace glm; 

GLuint tapeta;
GLuint podloga; 
GLuint sufit;
GLuint drewno; 
GLuint obraz; 

TGAImg img; 

mat4 pianino; 
mat4 tlo; 
mat4 lampa; 

float obrot_biale[29];
float obrot_czarne[20];
float obrot_mloteczki[49]; 

bool podnoszenie=0;
bool opuszczanie=0;
bool podniesione=0;
float uchyl=0.0f;
int lastTime=0;
int klawisz=-1;
int klawisz_pom=-1;

void rysuj_z_tex(GLuint *uchwyt, float *ver, float *vertexture, int vercount) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,*uchwyt);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, ver);
	glTexCoordPointer( 2, GL_FLOAT, 0, vertexture);
	glDrawArrays( GL_QUADS, 0, vercount);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void rysuj_z_tex_trojkaty(GLuint *uchwyt, float *ver, float *vertexture, int vercount) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,*uchwyt);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, ver);
	glTexCoordPointer( 2, GL_FLOAT, 0, vertexture);
	glDrawArrays( GL_TRIANGLES, 0, vercount);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void rysuj_z_kolor(float *ver, float *vercolor, int vercount) {
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,ver);
	glColorPointer(3,GL_FLOAT,0,vercolor);
	glDrawArrays(GL_QUADS,0,vercount);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);	

}

void macierz_tla() {
	mat4 M;

	M=mat4(1.0f); //m zawiera macierz jednostkow¹(I)
	M=rotate(M,-90.0f, vec3(0.0f,0.0f,1.0f));
	M=rotate(M,-90.0f, vec3(0.0f,1.0f,0.0f));
	M=scale(M, vec3(10.0f,15.0f,15.0f));

	tlo=M; 

	mat4 V=lookAt(
		vec3(0.0f, 0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(130.0f, 1.0f, 1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(V*M));
};

void macierz_tla2() {
	mat4 M;

	M=mat4(1.0f); //m zawiera macierz jednostkow¹(I)
	M=rotate(M,-90.0f, vec3(0.0f,0.0f,1.0f));
	M=rotate(M,-90.0f, vec3(0.0f,1.0f,0.0f));
	M=scale(M, vec3(10.0f,30.0f,30.0f));

	tlo=M; 

	mat4 V=lookAt(
		vec3(0.0f, 0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(130.0f, 1.0f, 1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(V*M));
};

void macierz_pianina() {
	mat4 M;
	mat4 V=glm::lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(100.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=mat4(1.0f);
	M=rotate(M,-45.0f, vec3(0.0f,1.0f,0.0f));
	M=translate(M, vec3(-2.4f,-1.0f,-1.5f));
	M=scale(M,vec3(0.5f, 0.8f, 0.5f));
	pianino=M; 
	glLoadMatrixf(value_ptr(V*M));
}

void macierz_strun(float grubosc, float x) {
	mat4 M;
	mat4 V=glm::lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(100.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=mat4(1.0f);
	//M=rotate(M,-30.0f, vec3(0.0f,1.0f,0.0f));
	M=translate(M, vec3(x,0.0f,-1.0f));
	M=scale(M,vec3(grubosc, 9.0f, grubosc));
	glLoadMatrixf(value_ptr(V*M));
}

void macierz_mloteczkow(float x, float z, float obrot){
	mat4 M;
	mat4 V=glm::lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(130.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=mat4(1.0f);
	M=translate(M, vec3(0.0f, 0.0f, z)); 
	M=translate(M, vec3(x, 0.0f, 0.0f)); 
	M=scale(M, vec3(0.07f, 1.0f, 0.07f)); 
	M=rotate(M, obrot, vec3(1.0f, 0.0f, 0.0f)); 
	glLoadMatrixf(value_ptr(V*M));
}

void macierz_pokrywy(float uchyl) {
	mat4 M;
	mat4 V=lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(100.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=mat4(1.0f);
	M=translate(M,vec3(-0.65f, -0.113f,-2.75f));
	M=rotate(M,-45.0f,vec3(0.0f,1.0f,0.0f));
	M=rotate(M,uchyl,vec3(1.0f,0.0f,0.0f));
	M=scale(M,vec3(0.5f, 0.8f, 0.5f));
	glLoadMatrixf(value_ptr(V*M));
}

void macierz_klawisza(float uchyl,float x) {
	mat4 M;
	mat4 V=lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(100.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=pianino;
	M=translate(M,vec3(0.0f, 0.0f, -0.9f));
	M=translate(M,vec3(0.0f, 0.2f, 0.0f));
	M=translate(M,vec3(x, 0.0f, 0.0f));
	M=rotate(M,4.0f, vec3(0.0f, 1.0f, 0.0f));
	M=rotate(M,uchyl, vec3(1.0f, 0.0f, 0.0f));
	M=scale(M,vec3(0.13f, 0.1f, 0.25f));
	glLoadMatrixf(value_ptr(V*M));
}

void macierz_black(float uchyl, float x){
	mat4 M;
	mat4 V=lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(100.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=pianino;
	M=translate(M,vec3(0.0f, 0.0f, -0.9f));
	M=translate(M,vec3(0.0f, 0.25f, 0.0f));
	M=translate(M,vec3(x, 0.0f, 0.0f));
	M=rotate(M,4.0f, vec3(0.0f, 1.0f, 0.0f));
	M=rotate(M,uchyl, vec3(1.0f, 0.0f, 0.0f));
	M=scale(M,vec3(0.1f, 0.07f, 0.25f));
	glLoadMatrixf(value_ptr(V*M));
}

void macierz_draga() {
	mat4 M;
	mat4 V=lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(100.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=tlo;
	
	M=translate(M,vec3(0.0f, 0.15f, -0.15f));
	M=scale(M,vec3(0.25f, 0.25f, 0.4f)); 
	
	glLoadMatrixf(value_ptr(V*M));
};

void macierz_stolka() {
	mat4 M;
	mat4 V=lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(100.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=pianino;
	M=translate(M,vec3(0.0f, 0.0f, -1.3f));
	M=translate(M,vec3(0.0f, -0.5f, 0.0f));
	//M=translate(M, vec3(1.0f, 0.0f, 0.0f)); 
	//M=rotate(M,4.0f, vec3(0.0f, 1.0f, 0.0f));
	M=scale(M,vec3(1.0f, 0.6f, 0.2f));
	glLoadMatrixf(value_ptr(V*M));
}

void macierz_obrazu(){
	mat4 M;
	mat4 V=lookAt(
		vec3(0.0f,0.0f,-5.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f));

	mat4 P=perspective(100.0f, 1.0f,1.0f, 50.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);


	M=tlo;
	M=translate(M,vec3(0.0f, 0.0f, 0.07f));
	M=scale(M,vec3(0.05f, 0.05f, 0.07f));
	M=rotate(M, 90.0f, vec3(0.0f, 1.0f, 0.0f)); 
	glLoadMatrixf(value_ptr(V*M));
}

void rysuj_pianino(){
	macierz_pianina();
	rysuj_z_tex(&drewno,pudloVertices,pudlotexVertices,pudloVertexCount);
	macierz_pokrywy(uchyl); //Argument to wartość typu float oznaczająca uchył pokrywy
	rysuj_z_tex(&drewno,movingpokrywaVertices, movingpokrywaTex, movingpokrywaVertexCount);
	macierz_klawisza(obrot_biale[0], -1.38); 
	rysuj_z_kolor(bialy_prostyVertices, bialy_prostyColors, bialy_prostyVerCount);
	int ktory=1; 
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<7; j++)
		{
			float x; 
			x=-1.40+0.085*ktory;
			macierz_klawisza(obrot_biale[ktory], x);
			ktory++;
			if(j==0 || j==4) {
				rysuj_z_kolor(bialy_leftcutVertices, bialy_onesidecutColors, bialy_leftcutVerCount);
			}
			if(j==3 || j==6) rysuj_z_kolor(bialy_rightcutVertices, bialy_onesidecutColors, bialy_rightcutVerCount);
			else rysuj_z_kolor(bialy_twosidecutVertices, bialy_twosidecutColors, bialy_twosidecutVerCount);
		}
	}

	ktory=0;
	int kolejny=0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<7; j++)
		{
			float x;
			x=-1.305+0.085*ktory;
			macierz_black(obrot_czarne[kolejny], x);
			ktory++;
			if(j!=3 && j!=6)
			{
				rysuj_z_kolor(czarnyVertices, czarnyColors, czarnyVerCount);
				kolejny++;
			}
		}
	}
	if((klawisz==-1)&&(klawisz_pom!=-1))
	{
		klawisz=klawisz_pom;
		klawisz_pom=-1;
	}
}

void rysuj_struny()
{
		glDisable(GL_TEXTURE_2D);
		glColor3ub(255, 255, 255); 
		for(int i=0; i<49; i++)
		{
			macierz_strun(0.005+0.0005*i, -4.37+0.187*i);
			glutSolidCube(1.0); 
		}
}

void displayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(podniesione==0)
	{
		/* Rysowanie podlogi,sufitu i scian */
		macierz_tla(); 
		rysuj_z_tex(&podloga,podlogaVertices,podlogatexVertices,podlogaVertexCount); 
		rysuj_z_tex(&sufit,sufitVertices,sufittexVertices,sufitVertexCount); 
		rysuj_z_tex(&tapeta,scianyVertices,scianytexVertices,scianyVertexCount);

		/* Rysowanie pianina z klawiszami */ 
		rysuj_pianino(); 

		///* Rysowanie lampy oteksturowanej */
		//rysuj_lampe();
		macierz_draga(); 
		rysuj_z_tex_trojkaty(&sufit, Lamp_01Verts, Lamp_01TexCoords, Lamp_01NumVerts); 

		macierz_stolka();
		rysuj_z_tex(&drewno, stolekVertices, stolekTexCoord, stolekVertexCount); 

		macierz_obrazu(); 
		rysuj_z_tex(&drewno, rama_oVertices, rama_oTexVertices, rama_oVertexCount); 
		rysuj_z_tex(&obraz, obrazVertices, obrazTexVertices, obrazVertexCount); 
		float lightPos[]={10, 10, 10, 1.0};
		glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	}
	else if(podniesione==1)
	{
		macierz_tla2(); 
		rysuj_z_tex(&drewno,podlogaVertices,podlogatexVertices,podlogaVertexCount); 
		rysuj_z_tex(&drewno,sufitVertices,sufittexVertices,sufitVertexCount); 
		rysuj_z_tex(&drewno,scianyVertices,scianytexVertices,scianyVertexCount);

		rysuj_struny(); 
		for(int i=0; i<49; i++)
		{
			glColor3ub(255-4*i, 255-2*i, 255);
			macierz_mloteczkow(-2.0+0.0855*i,-4.0, obrot_mloteczki[i]);

			glutSolidCube(1.0); 
		}
	}
	glutSwapBuffers();
}

void nextFrame(void)
{
	if(podniesione==0)
	{
		int actTime=glutGet(GLUT_ELAPSED_TIME);
		int interval=actTime-lastTime;


		if(interval>50)
		{
			lastTime=actTime;
			if((podnoszenie==1)&&(podniesione==0)&&(uchyl<90.0f))
			{
				uchyl=uchyl+1.0f;
			}
			if((podnoszenie==1)&&(uchyl>=90.0f))
			{
				podnoszenie=0;
				podniesione=1;
			}
			if((opuszczanie==1)&&(uchyl>0.0f))
			{
				uchyl=uchyl-1.0f;
			}
			if((opuszczanie==1)&&(uchyl<=0.0f))
			{
				opuszczanie=0;
			}
			if(klawisz!=-1)
			{
				if(klawisz<=28)
				{
					if(obrot_biale[klawisz]>1.0f) obrot_biale[klawisz]=obrot_biale[klawisz]-1.0f;
					else if(obrot_biale[klawisz]<=1.0f) klawisz=-1;
				}
				else if((klawisz>28)&&(klawisz<=48))
				{
					if(obrot_czarne[klawisz-29]>1.0f) obrot_czarne[klawisz-29]=obrot_czarne[klawisz-29]-1.0f;
					else if(obrot_czarne[klawisz-29]<=1.0f) klawisz=-1;
				}
				else if((klawisz>48)&&(klawisz<=77))
				{
					if(obrot_biale[klawisz-49]<6.0f) obrot_biale[klawisz-49]=obrot_biale[klawisz-49]+1.0f;
					else if(obrot_biale[klawisz-49]>=6.0f) klawisz=-1;
				}
				else if((klawisz>77)&&(klawisz<=97))
				{
					if(obrot_czarne[klawisz-78]<6.0f) obrot_czarne[klawisz-78]=obrot_czarne[klawisz-78]+1.0f;
					else if(obrot_czarne[klawisz-78]>=6.0f) klawisz=-1;
				}
			}
		}
	}
	else if(podniesione==1)
	{
		//Kod animacji w srodku
	}

	glutPostRedisplay();
}

//Początek poligonu klawiatury:
void keyFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
	case '`':
		{
			if((podniesione==0)&&(podnoszenie==0)&&(opuszczanie==0))
			{
				podnoszenie=1;
				PlaySound("sound/skrzyp.wav", NULL, SND_FILENAME|SND_ASYNC);
			}
			else if((podniesione==1)&&(opuszczanie==0)&&(podnoszenie==0))
			{
				podniesione=0;
				opuszczanie=1;
				PlaySound("sound/skrzyp.wav", NULL, SND_FILENAME|SND_ASYNC);
			}
			break;
		}
	case '1':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=28;
					PlaySound("sound/01.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '2':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=27;
					PlaySound("sound/02.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '3':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=26;
					PlaySound("sound/03.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '4':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=25;
					PlaySound("sound/04.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '5':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=24;
					PlaySound("sound/05.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '6':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=23;
					PlaySound("sound/06.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '7':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=22;
					PlaySound("sound/07.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '8':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=21;
					PlaySound("sound/11.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'q':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=21;
					PlaySound("sound/11.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'w':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=20;
					PlaySound("sound/12.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'e':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=19;
					PlaySound("sound/13.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'r':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=18;
					PlaySound("sound/14.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 't':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=17;
					PlaySound("sound/15.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'y':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=16;
					PlaySound("sound/16.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'u':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=15;
					PlaySound("sound/17.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'i':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=14;
					PlaySound("sound/21.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'a':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=14;
					PlaySound("sound/21.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 's':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=13;
					PlaySound("sound/22.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'd':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=12;
					PlaySound("sound/23.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'f':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=11;
					PlaySound("sound/24.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'g':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=10;
					PlaySound("sound/25.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'h':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=9;
					PlaySound("sound/26.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'j':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=8;
					PlaySound("sound/27.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'k':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=7;
					PlaySound("sound/31.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'z':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=7;
					PlaySound("sound/31.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'x':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=6;
					PlaySound("sound/32.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'c':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=5;
					PlaySound("sound/33.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'v':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=4;
					PlaySound("sound/34.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'b':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=3;
					PlaySound("sound/35.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'n':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=2;
					PlaySound("sound/36.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'm':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=1;
					PlaySound("sound/37.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case ',':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=0;
					PlaySound("sound/38.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'N':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=29;
					PlaySound("sound/60.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'B':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=30;
					PlaySound("sound/59.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'V':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=31;
					PlaySound("sound/58.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'X':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=32;
					PlaySound("sound/57.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'Z':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=33;
					PlaySound("sound/56.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'H':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=34;
					PlaySound("sound/55.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'G':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=35;
					PlaySound("sound/54.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'F':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=36;
					PlaySound("sound/53.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'S':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=37;
					PlaySound("sound/52.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'A':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=38;
					PlaySound("sound/51.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'Y':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=39;
					PlaySound("sound/50.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'T':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=40;
					PlaySound("sound/49.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'R':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=41;
					PlaySound("sound/48.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'W':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=42;
					PlaySound("sound/47.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case 'Q':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=43;
					PlaySound("sound/46.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '^':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=44;
					PlaySound("sound/45.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '%':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=45;
					PlaySound("sound/44.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '$':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=46;
					PlaySound("sound/43.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '@':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=47;
					PlaySound("sound/42.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	case '!':
		{
			if(klawisz==-1)
			{
				if(klawisz_pom==-1)
				{
					klawisz=48;
					PlaySound("sound/41.wav", NULL, SND_FILENAME|SND_ASYNC);
				}
				else
				{
					klawisz=klawisz_pom;
					klawisz_pom=-1;
				}
			}
			break;
		}
	}
} 

void keyUpFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
	case '1': 
		{
			if(klawisz==-1) klawisz=77;
			else klawisz_pom=77;
			break;
		}
	case '2': 
		{
			if(klawisz==-1) klawisz=76;
			else klawisz_pom=76;
			break;
		}
	case '3': 
		{
			if(klawisz==-1) klawisz=75;
			else klawisz_pom=75;
			break;
		}
	case '4': 
		{
			if(klawisz==-1) klawisz=74;
			else klawisz_pom=74;
			break;
		}
	case '5': 
		{
			if(klawisz==-1) klawisz=73;
			else klawisz_pom=73;
			break;
		}
	case '6': 
		{
			if(klawisz==-1) klawisz=72;
			else klawisz_pom=72;
			break;
		}
	case '7': 
		{
			if(klawisz==-1) klawisz=71;
			else klawisz_pom=71;
			break;
		}
	case '8': 
		{
			if(klawisz==-1) klawisz=70;
			else klawisz_pom=70;
			break;
		}
	case 'q': 
		{
			if(klawisz==-1) klawisz=70;
			else klawisz_pom=70;
			break;
		}
	case 'w': 
		{
			if(klawisz==-1) klawisz=69;
			else klawisz_pom=69;
			break;
		}
	case 'e': 
		{
			if(klawisz==-1) klawisz=68;
			else klawisz_pom=68;
			break;
		}
	case 'r': 
		{
			if(klawisz==-1) klawisz=67;
			else klawisz_pom=67;
			break;
		}
	case 't': 
		{
			if(klawisz==-1) klawisz=66;
			else klawisz_pom=66;
			break;
		}
	case 'y': 
		{
			if(klawisz==-1) klawisz=65;
			else klawisz_pom=65;
			break;
		}
	case 'u': 
		{
			if(klawisz==-1) klawisz=64;
			else klawisz_pom=64;
			break;
		}
	case 'i': 
		{
			if(klawisz==-1) klawisz=63;
			else klawisz_pom=63;
			break;
		}
	case 'a': 
		{
			if(klawisz==-1) klawisz=63;
			else klawisz_pom=63;
			break;
		}
	case 's': 
		{
			if(klawisz==-1) klawisz=62;
			else klawisz_pom=62;
			break;
		}
	case 'd': 
		{
			if(klawisz==-1) klawisz=61;
			else klawisz_pom=61;
			break;
		}
	case 'f': 
		{
			if(klawisz==-1) klawisz=60;
			else klawisz_pom=60;
			break;
		}
	case 'g': 
		{
			if(klawisz==-1) klawisz=59;
			else klawisz_pom=59;
			break;
		}
	case 'h': 
		{
			if(klawisz==-1) klawisz=58;
			else klawisz_pom=58;
			break;
		}
	case 'j': 
		{
			if(klawisz==-1) klawisz=57;
			else klawisz_pom=57;
			break;
		}
	case 'k': 
		{
			if(klawisz==-1) klawisz=56;
			else klawisz_pom=56;
			break;
		}
	case 'z': 
		{
			if(klawisz==-1) klawisz=56;
			else klawisz_pom=56;
			break;
		}
	case 'x': 
		{
			if(klawisz==-1) klawisz=55;
			else klawisz_pom=55;
			break;
		}
	case 'c': 
		{
			if(klawisz==-1) klawisz=54;
			else klawisz_pom=54;
			break;
		}
	case 'v': 
		{
			if(klawisz==-1) klawisz=53;
			else klawisz_pom=53;
			break;
		}
	case 'b': 
		{
			if(klawisz==-1) klawisz=52;
			else klawisz_pom=52;
			break;
		}
	case 'n': 
		{
			if(klawisz==-1) klawisz=51;
			else klawisz_pom=51;
			break;
		}
	case 'm': 
		{
			if(klawisz==-1) klawisz=50;
			else klawisz_pom=50;
			break;
		}
	case ',': 
		{
			if(klawisz==-1) klawisz=49;
			else klawisz_pom=49;
			break;
		}
	case 'N': 
		{
			if(klawisz==-1) klawisz=78;
			else klawisz_pom=78;
			break;
		}
	case 'B': 
		{
			if(klawisz==-1) klawisz=79;
			else klawisz_pom=79;
			break;
		}
	case 'V': 
		{
			if(klawisz==-1) klawisz=80;
			else klawisz_pom=80;
			break;
		}
	case 'X': 
		{
			if(klawisz==-1) klawisz=81;
			else klawisz_pom=81;
			break;
		}
	case 'Z': 
		{
			if(klawisz==-1) klawisz=82;
			else klawisz_pom=82;
			break;
		}
	case 'H': 
		{
			if(klawisz==-1) klawisz=83;
			else klawisz_pom=83;
			break;
		}
	case 'G': 
		{
			if(klawisz==-1) klawisz=84;
			else klawisz_pom=84;
			break;
		}
	case 'F': 
		{
			if(klawisz==-1) klawisz=85;
			else klawisz_pom=85;
			break;
		}
	case 'S': 
		{
			if(klawisz==-1) klawisz=86;
			else klawisz_pom=86;
			break;
		}
	case 'A': 
		{
			if(klawisz==-1) klawisz=87;
			else klawisz_pom=87;
			break;
		}
	case 'Y': 
		{
			if(klawisz==-1) klawisz=88;
			else klawisz_pom=88;
			break;
		}
	case 'T': 
		{
			if(klawisz==-1) klawisz=89;
			else klawisz_pom=89;
			break;
		}
	case 'R': 
		{
			if(klawisz==-1) klawisz=90;
			else klawisz_pom=90;
			break;
		}
	case 'W': 
		{
			if(klawisz==-1) klawisz=91;
			else klawisz_pom=91;
			break;
		}
	case 'Q': 
		{
			if(klawisz==-1) klawisz=92;
			else klawisz_pom=92;
			break;
		}
	case '^': 
		{
			if(klawisz==-1) klawisz=93;
			else klawisz_pom=93;
			break;
		}
	case '%': 
		{
			if(klawisz==-1) klawisz=94;
			else klawisz_pom=94;
			break;
		}
	case '$': 
		{
			if(klawisz==-1) klawisz=95;
			else klawisz_pom=95;
			break;
		}
	case '@': 
		{
			if(klawisz==-1) klawisz=96;
			else klawisz_pom=96;
			break;
		}
	case '!': 
		{
			if(klawisz==-1) klawisz=97;
			else klawisz_pom=97;
			break;
		}
	}
}
//Koniec poligonu klawiatury

void wczytaj_teksture(GLuint *uchwyt, char *plik){
	if (img.Load(plik)==IMG_OK) {
		glGenTextures(1,&*uchwyt); //Zainicjuj uchwyt tex
		glBindTexture(GL_TEXTURE_2D,*uchwyt); //Przetwarzaj uchwyt tex
		if (img.GetBPP()==24) //Obrazek 24bit
			glTexImage2D(GL_TEXTURE_2D,0,3,img.GetWidth(),img.GetHeight(),0,
			GL_RGB,GL_UNSIGNED_BYTE,img.GetImg());
		else if (img.GetBPP()==32) //Obrazek 32bit
			glTexImage2D(GL_TEXTURE_2D,0,4,img.GetWidth(),img.GetHeight(),0,
			GL_RGBA,GL_UNSIGNED_BYTE,img.GetImg());
		else {
			//Obrazek 16 albo 8 bit, takimi siê nie przejmujemy
		}
	} else {

	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_TEXTURE_2D); 
};

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Program OpenGL");        
	glutKeyboardFunc(keyFunc);
	glutKeyboardUpFunc(keyUpFunc);
	glutDisplayFunc(displayFrame);
	glutIdleFunc(nextFrame);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	//Tutaj kod inicjujacy	
	glewInit();

	glEnable(GL_DEPTH_TEST);
	
	/*Wczytywanie wszystkich tekstur */
	wczytaj_teksture(&tapeta, "texture/sciana2.tga"); 
	wczytaj_teksture(&podloga, "texture/deski.tga"); 
	wczytaj_teksture(&sufit, "texture/sufit1.tga"); 
	wczytaj_teksture(&drewno, "texture/drewno1.tga");
	wczytaj_teksture(&obraz, "texture/obraz.tga"); 

	for(int i=0; i<29; i++)
	{
		obrot_biale[i]=6.0; 
	}

	for(int i=0; i<20; i++)
	{
		obrot_czarne[i]=6.0; 
	}

	for(int i=0; i<49; i++)
	{
		obrot_mloteczki[i]=0.0; //Asia przypomina, obrót młoteczka to tak mniej więcej od 0.0 do 30.0 przynajniej tak wybadałam
	}
	/* Inne parametry nie ulegają zmianie */ 

	
	glutMainLoop();	

	glDeleteTextures(1,&sufit);
	glDeleteTextures(1,&tapeta);
	glDeleteTextures(1,&podloga);
	glDeleteTextures(1,&drewno); 
	glDeleteTextures(1,&obraz); 

	return 0;
}
