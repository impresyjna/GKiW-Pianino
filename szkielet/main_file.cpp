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
GLuint biale; 
GLuint czarne; 
GLuint lampka; 

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
int mloteczek=0;
int wcisniety=-1;

bool fullscreen=TRUE;

void rysuj_z_tex(GLuint *uchwyt, float *ver, float *vertexture, float *vernormals, int vercount) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,*uchwyt);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, ver);
	glTexCoordPointer( 2, GL_FLOAT, 0, vertexture);
	glNormalPointer(GL_FLOAT,0,vernormals);
	glDrawArrays( GL_QUADS, 0, vercount);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void rysuj_z_tex_trojkaty(GLuint *uchwyt, float *ver, float *vertexture, float *vernormals, int vercount) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,*uchwyt);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, ver);
	glTexCoordPointer( 2, GL_FLOAT, 0, vertexture);
	glNormalPointer(GL_FLOAT,0,vernormals);
	glDrawArrays( GL_TRIANGLES, 0, vercount);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
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
	rysuj_z_tex(&drewno,pudloVertices,pudlotexVertices,pudloVertices, pudloVertexCount);
	macierz_pokrywy(uchyl); //Argument to wartość typu float oznaczająca uchył pokrywy
	rysuj_z_tex(&drewno,movingpokrywaVertices, movingpokrywaTex, movingpokrywaVertices, movingpokrywaVertexCount);
	macierz_klawisza(obrot_biale[0], -1.38); 
	rysuj_z_tex(&biale, bialy_prostyVertices, bialy_prostyTex, bialy_prostyVertices, bialy_prostyVerCount);
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
				rysuj_z_tex(&biale, bialy_leftcutVertices, bialy_onesidecutTex, bialy_leftcutVertices, bialy_leftcutVerCount);
			}
			if(j==3 || j==6) rysuj_z_tex(&biale, bialy_rightcutVertices, bialy_onesidecutTex, bialy_rightcutVertices, bialy_rightcutVerCount);
			else rysuj_z_tex(&biale, bialy_twosidecutVertices, bialy_twosidecutTex, bialy_twosidecutVertices, bialy_twosidecutVerCount);
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
				rysuj_z_tex(&czarne, czarnyVertices, czarnyTex, czarnyVertices, czarnyVerCount);
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
		rysuj_z_tex(&podloga,podlogaVertices,podlogatexVertices,podlogaVertices, podlogaVertexCount); 
		rysuj_z_tex(&sufit,sufitVertices,sufittexVertices, sufitVertices, sufitVertexCount); 
		rysuj_z_tex(&tapeta,scianyVertices,scianytexVertices, scianyVertices, scianyVertexCount);

		/* Rysowanie pianina z klawiszami */ 
		rysuj_pianino(); 

		///* Rysowanie lampy oteksturowanej */
		macierz_draga(); 
		rysuj_z_tex_trojkaty(&lampka, Lamp_01Verts, Lamp_01TexCoords, Lamp_01Normals, Lamp_01NumVerts); 

		macierz_stolka();
		rysuj_z_tex(&drewno, stolekVertices, stolekTexCoord, stolekVertices, stolekVertexCount); 

		macierz_obrazu(); 
		rysuj_z_tex(&drewno, rama_oVertices, rama_oTexVertices, rama_oVertices, rama_oVertexCount); 
		rysuj_z_tex(&obraz, obrazVertices, obrazTexVertices, obrazVertices, obrazVertexCount); 
		float lightPos0[]={-2,0.7,-3,1};
		float lightDir0[]={-1,0,1,0}; 
		glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
		glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,lightDir0);

		float lightPos1[]={-5,0,4,0};
		float lightDir1[]={-2,0,-3,0};
		glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);
		glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,lightDir1);
	}
	else if(podniesione==1)
	{
		macierz_tla2(); 
		rysuj_z_tex(&drewno,podlogaVertices,podlogatexVertices, podlogaVertices, podlogaVertexCount); 
		rysuj_z_tex(&drewno,sufitVertices,sufittexVertices,sufitVertices, sufitVertexCount); 
		rysuj_z_tex(&drewno,scianyVertices,scianytexVertices,scianyVertices,scianyVertexCount);

		rysuj_struny(); 
		for(int i=0; i<49; i++)
		{
			glColor3ub(255-4*i, 255-2*i, 255);
			macierz_mloteczkow(-2.0+0.0855*i,-4.0, obrot_mloteczki[i]);

			glutSolidCube(1.0); 
		}
		float lightPos0[]={-2,0.7,-3,1};
		float lightDir0[]={-1,0,1,0}; 
		glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
		glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,lightDir0);

		float lightPos1[]={-5,0,4,0};
		float lightDir1[]={-2,0,-3,0};
		glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);
		glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,lightDir1);
		glColor3ub(255, 255, 255);
	}

	if((klawisz==-1)&&(klawisz_pom!=-1))
	{
		klawisz=klawisz_pom;
		klawisz_pom=-1;
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
					else if(obrot_biale[klawisz-49]>=6.0f)
					{
						if((klawisz-49)==wcisniety) wcisniety=-1;
						klawisz=-1;
					}
				}
				else if((klawisz>77)&&(klawisz<=97))
				{
					if(obrot_czarne[klawisz-78]<6.0f) obrot_czarne[klawisz-78]=obrot_czarne[klawisz-78]+1.0f;
					else if(obrot_czarne[klawisz-78]>=6.0f)
					{
						if((klawisz-49)==wcisniety) wcisniety=-1;
						klawisz=-1;
					}
				}
			}
		}
	}
	else if(podniesione==1)
	{
		int actTime=glutGet(GLUT_ELAPSED_TIME);
		int interval=actTime-lastTime;

		if(interval>50)
		{
			lastTime=actTime;

			if(klawisz!=-1)
			{
				if(klawisz<=28)
				{
					int kpom=klawisz;
					if(kpom==0) mloteczek=0;
					else
					{
						kpom=kpom-1;
						int kpom2=kpom/7;
						kpom=kpom%7;
						if(kpom<=3) mloteczek=kpom*2+(kpom2*12)+1;
						else if(kpom==4) mloteczek=7+(kpom2*12)+1;
						else mloteczek=kpom*2+(kpom2*12);
					}
					if(obrot_mloteczki[mloteczek]<30.0f) obrot_mloteczki[mloteczek]=obrot_mloteczki[mloteczek]+3.0f;
					else if(obrot_mloteczki[mloteczek]>=30.0f) klawisz=-1;
				}
				else if((klawisz>28)&&(klawisz<=48))
				{
					int kpom=klawisz-29;
					int kpom2=kpom/5;
					kpom=kpom%5;
					if(kpom<=2) mloteczek=kpom*2+2+(kpom2*12);
					else mloteczek=kpom*2+3+(kpom2*12);
					if(obrot_mloteczki[mloteczek]<30.0f) obrot_mloteczki[mloteczek]=obrot_mloteczki[mloteczek]+3.0f;
					else if(obrot_mloteczki[mloteczek]>=30.0f) klawisz=-1;
				}
				else if((klawisz>48)&&(klawisz<=77))
				{
					int kpom=klawisz-49;
					if(kpom==0) mloteczek=0;
					else
					{
						kpom=kpom-1;
						int kpom2=kpom/7;
						kpom=kpom%7;
						if(kpom<=3) mloteczek=kpom*2+(kpom2*12)+1;
						else if(kpom==4) mloteczek=7+(kpom2*12)+1;
						else mloteczek=kpom*2+(kpom2*12);
					}
					if(obrot_mloteczki[mloteczek]>0.0f) obrot_mloteczki[mloteczek]=obrot_mloteczki[mloteczek]-3.0f;
					else if(obrot_mloteczki[mloteczek]<=0.0f)
					{
						if((klawisz-49)==wcisniety) wcisniety=-1;
						klawisz=-1;
					}
				}
				else if((klawisz>77)&&(klawisz<=97))
				{
					int kpom=klawisz-78;
					int kpom2=kpom/5;
					kpom=kpom%5;
					if(kpom<=2) mloteczek=kpom*2+2+(kpom2*12);
					else mloteczek=kpom*2+3+(kpom2*12);
					if(obrot_mloteczki[mloteczek]>0.0f) obrot_mloteczki[mloteczek]=obrot_mloteczki[mloteczek]-3.0f;
					else if(obrot_mloteczki[mloteczek]<=0.0f)
					{
						if((klawisz-49)==wcisniety) wcisniety=-1;
						klawisz=-1;
					}
				}
			}
		}
	}

	glutPostRedisplay();
}

//Początek obsługi klawiatury:
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=28;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=27;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=26;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=25;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=24;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=23;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=22;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=21;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=21;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=20;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=19;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=18;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=17;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=16;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=15;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=14;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=14;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=13;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=12;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=11;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=10;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=9;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=8;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=7;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=7;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=6;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=5;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=4;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=3;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=2;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=1;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=0;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=29;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=30;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=31;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=32;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=33;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=34;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=35;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=36;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=37;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=38;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=39;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=40;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=41;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=42;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=43;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=44;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=45;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=46;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=47;
					wcisniety=klawisz;
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
			if((klawisz==-1)&&(wcisniety==-1))
			{
				if(klawisz_pom==-1)
				{
					klawisz=48;
					wcisniety=klawisz;
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
			else if(klawisz_pom==-1) klawisz_pom=77;
			break;
		}
	case '2': 
		{
			if(klawisz==-1) klawisz=76;
			else if(klawisz_pom==-1) klawisz_pom=76;
			break;
		}
	case '3': 
		{
			if(klawisz==-1) klawisz=75;
			else if(klawisz_pom==-1) klawisz_pom=75;
			break;
		}
	case '4': 
		{
			if(klawisz==-1) klawisz=74;
			else if(klawisz_pom==-1) klawisz_pom=74;
			break;
		}
	case '5': 
		{
			if(klawisz==-1) klawisz=73;
			else if(klawisz_pom==-1) klawisz_pom=73;
			break;
		}
	case '6': 
		{
			if(klawisz==-1) klawisz=72;
			else if(klawisz_pom==-1) klawisz_pom=72;
			break;
		}
	case '7': 
		{
			if(klawisz==-1) klawisz=71;
			else if(klawisz_pom==-1) klawisz_pom=71;
			break;
		}
	case '8': 
		{
			if(klawisz==-1) klawisz=70;
			else if(klawisz_pom==-1) klawisz_pom=70;
			break;
		}
	case 'q': 
		{
			if(klawisz==-1) klawisz=70;
			else if(klawisz_pom==-1) klawisz_pom=70;
			break;
		}
	case 'w': 
		{
			if(klawisz==-1) klawisz=69;
			else if(klawisz_pom==-1) klawisz_pom=69;
			break;
		}
	case 'e': 
		{
			if(klawisz==-1) klawisz=68;
			else if(klawisz_pom==-1) klawisz_pom=68;
			break;
		}
	case 'r': 
		{
			if(klawisz==-1) klawisz=67;
			else if(klawisz_pom==-1) klawisz_pom=67;
			break;
		}
	case 't': 
		{
			if(klawisz==-1) klawisz=66;
			else if(klawisz_pom==-1) klawisz_pom=66;
			break;
		}
	case 'y': 
		{
			if(klawisz==-1) klawisz=65;
			else if(klawisz_pom==-1) klawisz_pom=65;
			break;
		}
	case 'u': 
		{
			if(klawisz==-1) klawisz=64;
			else if(klawisz_pom==-1) klawisz_pom=64;
			break;
		}
	case 'i': 
		{
			if(klawisz==-1) klawisz=63;
			else if(klawisz_pom==-1) klawisz_pom=63;
			break;
		}
	case 'a': 
		{
			if(klawisz==-1) klawisz=63;
			else if(klawisz_pom==-1) klawisz_pom=63;
			break;
		}
	case 's': 
		{
			if(klawisz==-1) klawisz=62;
			else if(klawisz_pom==-1) klawisz_pom=62;
			break;
		}
	case 'd': 
		{
			if(klawisz==-1) klawisz=61;
			else if(klawisz_pom==-1) klawisz_pom=61;
			break;
		}
	case 'f': 
		{
			if(klawisz==-1) klawisz=60;
			else if(klawisz_pom==-1) klawisz_pom=60;
			break;
		}
	case 'g': 
		{
			if(klawisz==-1) klawisz=59;
			else if(klawisz_pom==-1) klawisz_pom=59;
			break;
		}
	case 'h': 
		{
			if(klawisz==-1) klawisz=58;
			else if(klawisz_pom==-1) klawisz_pom=58;
			break;
		}
	case 'j': 
		{
			if(klawisz==-1) klawisz=57;
			else if(klawisz_pom==-1) klawisz_pom=57;
			break;
		}
	case 'k': 
		{
			if(klawisz==-1) klawisz=56;
			else if(klawisz_pom==-1) klawisz_pom=56;
			break;
		}
	case 'z': 
		{
			if(klawisz==-1) klawisz=56;
			else if(klawisz_pom==-1) klawisz_pom=56;
			break;
		}
	case 'x': 
		{
			if(klawisz==-1) klawisz=55;
			else if(klawisz_pom==-1) klawisz_pom=55;
			break;
		}
	case 'c': 
		{
			if(klawisz==-1) klawisz=54;
			else if(klawisz_pom==-1) klawisz_pom=54;
			break;
		}
	case 'v': 
		{
			if(klawisz==-1) klawisz=53;
			else if(klawisz_pom==-1) klawisz_pom=53;
			break;
		}
	case 'b': 
		{
			if(klawisz==-1) klawisz=52;
			else if(klawisz_pom==-1) klawisz_pom=52;
			break;
		}
	case 'n': 
		{
			if(klawisz==-1) klawisz=51;
			else if(klawisz_pom==-1) klawisz_pom=51;
			break;
		}
	case 'm': 
		{
			if(klawisz==-1) klawisz=50;
			else if(klawisz_pom==-1) klawisz_pom=50;
			break;
		}
	case ',': 
		{
			if(klawisz==-1) klawisz=49;
			else if(klawisz_pom==-1) klawisz_pom=49;
			break;
		}
	case 'N': 
		{
			if(klawisz==-1) klawisz=78;
			else if(klawisz_pom==-1) klawisz_pom=78;
			break;
		}
	case 'B': 
		{
			if(klawisz==-1) klawisz=79;
			else if(klawisz_pom==-1) klawisz_pom=79;
			break;
		}
	case 'V': 
		{
			if(klawisz==-1) klawisz=80;
			else if(klawisz_pom==-1) klawisz_pom=80;
			break;
		}
	case 'X': 
		{
			if(klawisz==-1) klawisz=81;
			else if(klawisz_pom==-1) klawisz_pom=81;
			break;
		}
	case 'Z': 
		{
			if(klawisz==-1) klawisz=82;
			else if(klawisz_pom==-1) klawisz_pom=82;
			break;
		}
	case 'H': 
		{
			if(klawisz==-1) klawisz=83;
			else if(klawisz_pom==-1) klawisz_pom=83;
			break;
		}
	case 'G': 
		{
			if(klawisz==-1) klawisz=84;
			else if(klawisz_pom==-1) klawisz_pom=84;
			break;
		}
	case 'F': 
		{
			if(klawisz==-1) klawisz=85;
			else if(klawisz_pom==-1) klawisz_pom=85;
			break;
		}
	case 'S': 
		{
			if(klawisz==-1) klawisz=86;
			else if(klawisz_pom==-1) klawisz_pom=86;
			break;
		}
	case 'A': 
		{
			if(klawisz==-1) klawisz=87;
			else if(klawisz_pom==-1) klawisz_pom=87;
			break;
		}
	case 'Y': 
		{
			if(klawisz==-1) klawisz=88;
			else if(klawisz_pom==-1) klawisz_pom=88;
			break;
		}
	case 'T': 
		{
			if(klawisz==-1) klawisz=89;
			else if(klawisz_pom==-1) klawisz_pom=89;
			break;
		}
	case 'R': 
		{
			if(klawisz==-1) klawisz=90;
			else if(klawisz_pom==-1) klawisz_pom=90;
			break;
		}
	case 'W': 
		{
			if(klawisz==-1) klawisz=91;
			else if(klawisz_pom==-1) klawisz_pom=91;
			break;
		}
	case 'Q': 
		{
			if(klawisz==-1) klawisz=92;
			else if(klawisz_pom==-1) klawisz_pom=92;
			break;
		}
	case '^': 
		{
			if(klawisz==-1) klawisz=93;
			else if(klawisz_pom==-1) klawisz_pom=93;
			break;
		}
	case '%': 
		{
			if(klawisz==-1) klawisz=94;
			else if(klawisz_pom==-1) klawisz_pom=94;
			break;
		}
	case '$': 
		{
			if(klawisz==-1) klawisz=95;
			else if(klawisz_pom==-1) klawisz_pom=95;
			break;
		}
	case '@': 
		{
			if(klawisz==-1) klawisz=96;
			else if(klawisz_pom==-1) klawisz_pom=96;
			break;
		}
	case '!': 
		{
			if(klawisz==-1) klawisz=97;
			else if(klawisz_pom==-1) klawisz_pom=97;
			break;
		}
	}
}
//Koniec obsługi klawiatury

void wczytaj_teksture(GLuint *uchwyt, char *plik, float amb[], float dif[], float spec[], float shin){
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
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shin);
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
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	float amb[] = {0.05,0.05,0.05,1};
	float dif[] = {0.8,0.8,0.8,1};
	float spec[] = {0.05,0.05,0.05,1};

	glLightfv(GL_LIGHT1,GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1,GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT1,GL_SPECULAR, spec);
	glLightfv(GL_LIGHT1, GL_EMISSION, dif); 

	//Tutaj kod inicjujacy	
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	/*Wczytywanie wszystkich tekstur */
	

	wczytaj_teksture(&tapeta, "texture/sciana2.tga", tapeta_amb, tapeta_dif, tapeta_spec, 50); 
	wczytaj_teksture(&podloga, "texture/deski.tga", podloga_amb, podloga_dif, podloga_spec, 50); 
	wczytaj_teksture(&sufit, "texture/sufit1.tga", sufit_amb, sufit_dif, sufit_spec, 50); 
	wczytaj_teksture(&drewno, "texture/drewno1.tga", drewno_amb, drewno_dif, drewno_spec, 20);
	wczytaj_teksture(&obraz, "texture/obraz.tga", obraz_amb, obraz_dif, obraz_spec, 60); 
	wczytaj_teksture(&biale, "texture/biale.tga", biale_amb, biale_dif, biale_spec, 11.264); 
	wczytaj_teksture(&czarne, "texture/czarne.tga", czarne_amb, czarne_dif, czarne_spec, 32); 
	wczytaj_teksture(&lampka, "texture/lampka.tga", sufit_amb, sufit_dif, sufit_spec, 50); 

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
