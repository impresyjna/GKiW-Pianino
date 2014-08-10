#include <windows.h> //Wymagane dla implementacji OpenGL w Visual Studio.
#include "gl\glew.h"
#include "gl\glut.h"
#include "stdio.h" //Przydatne do wypisywania komunikatów na konsoli
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "tga.h"
#include "cube.h"

GLuint tapeta;
GLuint podloga; 
GLuint sufit;
TGAImg tap; 
TGAImg pod; 
TGAImg suf; 


void displayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glm::mat4 M;
	//M=I;
	M=glm::mat4(1.0f); //m zawiera macierz jednostkow¹
	M=glm::rotate(M,-90.0f,glm::vec3(0.0f,0.0f,1.0f));
	M=glm::rotate(M,-90.0f,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::scale(M,glm::vec3(4.0f,4.0f,4.0f));

	glm::mat4 V=glm::lookAt(
		glm::vec3(3.0f, 0.0f,-4.0f),
		glm::vec3(0.0f,-0.3f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f));

	glm::mat4 P=glm::perspective(75.0f, 1.0f, 1.0f, 50.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	
		
	/*M=glm::mat4(1.0f);
	M=glm::rotate(M,-90.0f,glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 W=glm::scale(M, glm::vec3(5.0f,1.0f,2.0f)); */
	glLoadMatrixf(glm::value_ptr(V*M));

	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3,GL_FLOAT,0,cubeVertices);
		
	glDrawArrays(GL_QUADS,0,cubeVertexCount);
	glDisableClientState(GL_VERTEX_ARRAY);	
	glDisableClientState(GL_COLOR_ARRAY);

	/* Rysowanie sufitu */
	glBindTexture(GL_TEXTURE_2D,sufit);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, cubeVertices);
	glTexCoordPointer( 2, GL_FLOAT, 0, cubetexVertices);
	glDrawArrays( GL_QUADS, 0, cubeVertexCount);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	/* Rysowanie scian */
	/*glBindTexture(GL_TEXTURE_2D,tapeta);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, cubeVertices);
	glTexCoordPointer( 2, GL_FLOAT, 0, cubetexVertices);
	glDrawArrays( GL_QUADS, 0, cubeVertexCount);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
*/
	glutSwapBuffers();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Program OpenGL");        
	glutDisplayFunc(displayFrame);

	//Tutaj kod inicjujacy	
	glewInit();

	if (suf.Load("texture/sciana1.tga")==IMG_OK) {
	glGenTextures(1,&sufit); //Zainicjuj uchwyt tex
	glBindTexture(GL_TEXTURE_2D,sufit); //Przetwarzaj uchwyt tex
	if (suf.GetBPP()==24) //Obrazek 24bit
	 glTexImage2D(GL_TEXTURE_2D,0,3,suf.GetWidth(),suf.GetHeight(),0,
		GL_RGB,GL_UNSIGNED_BYTE,suf.GetImg());
	  else if (suf.GetBPP()==32) //Obrazek 32bit
	   glTexImage2D(GL_TEXTURE_2D,0,4,suf.GetWidth(),suf.GetHeight(),0,
		GL_RGBA,GL_UNSIGNED_BYTE,suf.GetImg());
	  else {
	   //Obrazek 16 albo 8 bit, takimi siê nie przejmujemy
	  }
	} else {
	 //b³¹d
	}

	if (pod.Load("texture/sciana2.tga")==IMG_OK) {
	glGenTextures(1,&podloga); //Zainicjuj uchwyt tex
	glBindTexture(GL_TEXTURE_2D,podloga); //Przetwarzaj uchwyt tex
	if (pod.GetBPP()==24) //Obrazek 24bit
	 glTexImage2D(GL_TEXTURE_2D,0,3,pod.GetWidth(),pod.GetHeight(),0,
		GL_RGB,GL_UNSIGNED_BYTE,pod.GetImg());
	  else if (pod.GetBPP()==32) //Obrazek 32bit
	   glTexImage2D(GL_TEXTURE_2D,0,4,pod.GetWidth(),pod.GetHeight(),0,
		GL_RGBA,GL_UNSIGNED_BYTE,pod.GetImg());
	  else {
	   //Obrazek 16 albo 8 bit, takimi siê nie przejmujemy
	  }
	} else {
	 //b³¹d
	}
	
	if (tap.Load("texture/deski.tga")==IMG_OK) {
	glGenTextures(1,&tapeta); //Zainicjuj uchwyt tex
	glBindTexture(GL_TEXTURE_2D,tapeta); //Przetwarzaj uchwyt tex
	if (tap.GetBPP()==24) //Obrazek 24bit
	 glTexImage2D(GL_TEXTURE_2D,0,3,tap.GetWidth(),tap.GetHeight(),0,
		GL_RGB,GL_UNSIGNED_BYTE,tap.GetImg());
	  else if (tap.GetBPP()==32) //Obrazek 32bit
	   glTexImage2D(GL_TEXTURE_2D,0,4,tap.GetWidth(),tap.GetHeight(),0,
		GL_RGBA,GL_UNSIGNED_BYTE,tap.GetImg());
	  else {
	   //Obrazek 16 albo 8 bit, takimi siê nie przejmujemy
	  }
	} else {
	 //b³¹d
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D); 

    glutMainLoop();	

	glDeleteTextures(1,&sufit);
	glDeleteTextures(1,&tapeta);
	glDeleteTextures(1,&podloga);

    return 0;
}