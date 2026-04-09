#include <GL/glut.h>
#include <math.h>

float starRot = 0.0f;
float starScale = 1.0f;
int mode = 0; // 0: Đứng yên, 1: Quay quanh tâm, 2: Quay quanh đỉnh
bool isScaling = false;

// Hàm vẽ ngôi sao và vòng tròn bao quanh (Câu d)
void drawStarAndCircle(float radius) {
    const float PI = 3.14159f;

    // Vẽ hình tròn bao quanh
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * PI * i / 100;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    // Vẽ ngôi sao 5 cánh
    glColor3f(1.0f, 0.9f, 0.0f); // Màu vàng
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0); // Tâm
    for (int i = 0; i <= 10; i++) {
        float r = (i % 2 == 0) ? radius : radius * 0.4f;
        float angle = PI / 2 + i * 2.0f * PI / 10;
        glVertex2f(r * cos(angle), r * sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    
    // c. Thu nhỏ kích thước
    glScalef(starScale, starScale, 1.0f);

    if (mode == 2) {
        // b. Quay quanh một đỉnh (giả sử đỉnh trên cùng tại y = 0.3)
        glTranslatef(0.0f, 0.3f, 0.0f); 
        glRotatef(starRot, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, -0.3f, 0.0f);
    } else if (mode == 1) {
        // a. Quay quanh tâm
        glRotatef(starRot, 0.0f, 0.0f, 1.0f);
    }

    drawStarAndCircle(0.3f);
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value) {
    if (mode > 0) starRot += 2.0f;
    
    // Thu nhỏ đến khi còn một nửa (0.5) thì dừng
    if (isScaling && starScale > 0.5f) {
        starScale -= 0.01f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) mode = 1;
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') mode = 2; // Quay quanh đỉnh
    if (key == 'b') isScaling = true; // Thu nhỏ
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bai 2");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}