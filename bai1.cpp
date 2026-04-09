#include <GL/glut.h>

float posX = -0.8f;      // Vị trí bắt đầu (cạnh trái)
float rotX = 0.0f;      // Góc quay quanh trục X
bool isRunning = false; // Trạng thái nhấn chuột

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    // Di chuyển ấm trà theo trục X
    glTranslatef(posX, 0.0f, 0.0f);
    // Quay quanh trục X (1.0f ở tham số thứ 2)
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    
    glColor3f(0.0f, 0.7f, 0.9f); // Màu xanh lơ
    glutWireTeapot(0.2);         // Vẽ ấm trà khung lưới
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value) {
    if (isRunning) {
        // a. Xoay quanh trục X
        rotX += 3.0f; 

        // b. Dịch chuyển từ trái sang phải, chạm mép (0.8) thì dừng
        if (posX < 0.8f) {
            posX += 0.01f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // Chạy 60 FPS
}

void mouse(int button, int state, int x, int y) {
    // Khi nhấn trái chuột
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isRunning = true;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bai 1");
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}