#include <GL/glut.h>

float rotSelf = 0.0f;   
float rotOrbit = 0.0f;  
int mode = 0;           

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST); // Quan trọng để vẽ 3D
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Đặt Camera nhìn vào gốc tọa độ
    gluLookAt(0.0, 2.0, 5.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);

    // --- KHỐI CẦU 2 (Đỏ - Cố định bên phải) ---
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(0.6f, 0.0f, 0.0f); 
        glutWireSphere(0.4, 20, 20);
    glPopMatrix();

    // --- KHỐI CẦU 1 (Xanh lá) ---
    glPushMatrix();
        if (mode == 2) {
            // b. Quay quanh khối cầu 2
            glTranslatef(0.6f, 0.0f, 0.0f); // Tịnh tiến đến tâm cầu 2
            glRotatef(rotOrbit, 0.0f, 1.0f, 0.0f); // Quay hệ tọa độ
            glTranslatef(-1.2f, 0.0f, 0.0f); // Đẩy cầu 1 ra xa tâm quay
        } else {
            // Vị trí mặc định bên trái
            glTranslatef(-0.6f, 0.0f, 0.0f);
        }

        if (mode == 1) {
            // a. Quay quanh trục x chính nó
            glRotatef(rotSelf, 1.0f, 0.0f, 0.0f);
        }

        glColor3f(0.0f, 1.0f, 0.0f);
        glutWireSphere(0.4, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
}

// HÀM NÀY GIÚP VẬT THỂ KHÔNG BỊ MẤT KHI THAY ĐỔI KÍCH THƯỚC CỬA SỔ
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Tạo không gian quan sát 3D
    gluPerspective(45.0, aspect, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
    if (mode == 1) rotSelf += 2.0f;
    if (mode == 2) rotOrbit += 2.0f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') mode = 1; // Nhấn 'a' để quay quanh trục X
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) mode = 2; // Chuột trái để quay quanh nhau
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bai 4: Two Spheres - Fixed Display");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // Đăng ký hàm reshape
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}