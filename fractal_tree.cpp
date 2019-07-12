#include <GL/glut.h>
#include <iostream>

using namespace std;

float branch_scalar = 0.67;
volatile float angle = 45;
const int win_size = 900;
void branch(float len = 100) {
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex2d(0, 0);
  glVertex2d(0, -len);
  glEnd();
  glTranslatef(0, -len, 0);
  if (len > 1) {
    glPushMatrix();
    glRotatef(angle, 0, 0, 1);
    branch(len * branch_scalar);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-angle, 0, 0, 1);
    branch(len * branch_scalar);
    glPopMatrix();
  }
  glPopMatrix();
}
void reshape(int w, int h){
  glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
  //glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
  glLoadIdentity();             /* Reset project matrix. */
  glOrtho(0, w, 0, h, -1, 1);   /* Map abstract coords directly to window coords. */
  glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
  glTranslatef(0, -h, 0);       /* Shift origin up to upper-left corner. */
}
void update(){

  //angle++;
  glutPostRedisplay();
}
void draw()
{
  // clear out the window with black
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glPushMatrix();
  glScalef(2.0, 2.0, 0.0);
  glTranslatef(win_size/4, win_size/2, 0);
  branch();
  glPopMatrix();

  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
}
void mouseMove(int mx, int my){
  angle = win_size / 2.0 - mx/2.0;
}
void keyboard(unsigned char c, int x, int y){
  if(c == 27){
    exit(0);
  }
}
int main(int argc, char** argv){

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(win_size, win_size);
  glutInitWindowPosition(3000, 300);

  glutCreateWindow("Fractal Tree");
  glutDisplayFunc(draw);

  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  //glutMotionFunc(mouseMove);

  glutPassiveMotionFunc(mouseMove);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(update);

  glutMainLoop();
  return 0;
}
