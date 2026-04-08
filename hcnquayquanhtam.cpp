#include <GL/glut.h>

static GLfloat spin = 0.0; /* góc quay hiện tại của hình chữ nhật */
int isSpinning = 0; /* Thêm cờ (flag) để theo dõi trạng thái xem có đang quay hay không */

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0); 
    glShadeModel (GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0); /* xoay một góc spin quanh trục z */ 
    glColor3f(1.0, 1.0, 1.0); /* thiết lập màu vẽ cho hcn (màu trắng) */ 
    glRectf(-25.0, -25.0, 25.0, 25.0); /* vẽ hcn, tâm mặc định ở (0,0) nên sẽ quay chuẩn quanh tâm */
    glPopMatrix();
    glutSwapBuffers();  /* thực hiện việc hoán đổi 2 buffer */
}

/* Hàm này thay thế cho spinDisplay cũ */
void timerFunc(int value)
{
    if (isSpinning) {
        spin = spin + 10.0;  /* xoay thêm 2 độ */ 
        if (spin > 360.0)
            spin = spin - 360.0;
        
        glutPostRedisplay();    /* yêu cầu vẽ lại */
        
        /* Gọi lại chính hàm này sau 16ms (~60 FPS), giúp tốc độ quay luôn đều */
        glutTimerFunc(16, timerFunc, 0); 
    }
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:  
            if (state == GLUT_DOWN && !isSpinning) {
                isSpinning = 1; /* Cập nhật trạng thái thành đang quay */
                glutTimerFunc(16, timerFunc, 0); /* Kích hoạt bộ đếm thời gian */
            }
            break;
        case GLUT_MIDDLE_BUTTON:    
        case GLUT_RIGHT_BUTTON: /* Bổ sung thêm chuột phải để bạn dễ bấm dừng hơn */
            if (state == GLUT_DOWN) {
                isSpinning = 0; /* Tắt trạng thái quay, timerFunc sẽ tự dừng */
            }
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);   
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100); 
    glutCreateWindow ("Spinning Rectangle Smoothly"); 
    init ();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); 
    glutMouseFunc(mouse); 
    
    glutMainLoop();
    return 0;
}