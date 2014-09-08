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
#include <string>

using namespace std; 
using namespace glm; 

GLuint tapeta;
GLuint podloga; 
GLuint sufit;
GLuint drewno; 

TGAImg img; 

mat4 pianino; 
mat4 tlo; 
mat4 lampa; 

float obrot_biale[29];
float obrot_czarne[20];

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

void macierz_podstawka() {
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
	M=translate(M,vec3(0.1f, 0.2f, -0.3f));
	M=scale(M,vec3(0.07f, 0.07f, 0.07f));
	lampa=M; 
	glLoadMatrixf(value_ptr(V*M));
};

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
	M=translate(M,vec3(0.1f, 0.2f, -0.15f));
	M=rotate(M, 90.f,vec3(1.0f, 0.0f, 0.0f)); 
	M=scale(M,vec3(0.03f, 0.35f, 0.03f)); 
	glLoadMatrixf(value_ptr(V*M));
};

void macierz_abazuru(float z) {
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
	M=translate(M,vec3(0.1f, 0.2f, z));
	M=scale(M,vec3(0.07f, 0.07f, 0.07f)); 
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

void rysuj_pianino(){
	macierz_pianina();
	rysuj_z_tex(&drewno,pudloVertices,pudlotexVertices,pudloVertexCount);
	macierz_pokrywy(0.0f); //Argument to wartość typu float oznaczająca uchył pokrywy
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
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<7; j++)
		{
			float x;
			x=-1.305+0.085*ktory;
			macierz_black(obrot_czarne[ktory], x);
			ktory++;
			if(j!=3 && j!=6) rysuj_z_kolor(czarnyVertices, czarnyColors, czarnyVerCount);
		}
	}
}

void rysuj_lampe(){
	macierz_podstawka();
	glutSolidTorus(0.2, 0.4, 10, 20);
	macierz_draga();
	glutSolidTorus(0.2, 0.3, 10, 20); 
	macierz_abazuru(0.0f); 
	glutSolidTorus(0.2, 0.4, 10, 20);
	macierz_abazuru(0.02f);
	glutSolidTorus(0.2, 0.35, 10, 20);
	macierz_abazuru(0.04f);
	glutSolidTorus(0.2, 0.30, 10, 20);
	macierz_abazuru(0.06f);
	glutSolidTorus(0.2, 0.25, 10, 20);
	macierz_abazuru(0.08f);
	glutSolidTorus(0.2, 0.2, 10, 20);
}

void displayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Rysowanie podlogi,sufitu i scian */
	macierz_tla(); 
	rysuj_z_tex(&podloga,podlogaVertices,podlogatexVertices,podlogaVertexCount); 
	rysuj_z_tex(&sufit,sufitVertices,sufittexVertices,sufitVertexCount); 
	rysuj_z_tex(&tapeta,scianyVertices,scianytexVertices,scianyVertexCount);

	/* Rysowanie pianina z klawiszami */ 
	rysuj_pianino(); 

	/* Rysowanie lampy oteksturowanej */
	rysuj_lampe();

	macierz_stolka();
	rysuj_z_tex(&drewno, stolekVertices, stolekTexCoord, stolekVertexCount); 

	glutSwapBuffers();
}


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
	glutDisplayFunc(displayFrame);

	//Tutaj kod inicjujacy	
	glewInit();

	glEnable(GL_DEPTH_TEST);
	/*Wczytywanie wszystkich tekstur */
	wczytaj_teksture(&tapeta, "texture/sciana2.tga"); 
	wczytaj_teksture(&podloga, "texture/deski.tga"); 
	wczytaj_teksture(&sufit, "texture/sufit1.tga"); 
	wczytaj_teksture(&drewno, "texture/drewno1.tga");

	for(int i=0; i<29; i++)
	{
		obrot_biale[i]=6.0; 
	}

	for(int i=0; i<20; i++)
	{
		obrot_czarne[i]=6.0; 
	}

	obrot_biale[3]=1.0; 
	/*polecam wartości od 6.0 do 1.0 żeby nacisnac bo bez swiatla wyglada to znosnie, pewnie potem bedzie troche lepiej i troche mniej ale to juz latwo dopracowac */


	glutMainLoop();	

	glDeleteTextures(1,&sufit);
	glDeleteTextures(1,&tapeta);
	glDeleteTextures(1,&podloga);

	return 0;
}
