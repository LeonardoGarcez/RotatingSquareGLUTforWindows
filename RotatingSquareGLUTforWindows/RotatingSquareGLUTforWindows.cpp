// RotatingSquareGLUTforWindows.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "Angel.h"

float theta = 0.0;
float thetaLoc = 0.0;

void init(void) {
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glewExperimental = GL_TRUE;
  glewInit();

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  //  Load shaders and initialize attribute buffers
  GLuint program = InitShader("vshader21.glsl", "fshader21.glsl");
  glUseProgram(program);

  

  vec2 vertices[4] = {
      vec2(  0,  1 ),
      vec2(  1,  0 ),
      vec2( -1,  0 ),
      vec2(  0, -1 )
  };

  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Associate out shader variables with our data buffer
  GLuint vPosition = glGetAttribLocation(program, "vPosition");
  glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(vPosition);

  thetaLoc = glGetUniformLocation(program, "theta");
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  theta += 0.1;
  glUniform1f(thetaLoc, theta);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glFlush();
}

void idle() {
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 033: // saindo com ESC
      exit(EXIT_SUCCESS);
      break;
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(512, 512);

  glutIdleFunc(idle);

  glutCreateWindow("MAC5744 - Aula 1 - Rotating Square");

  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}
