#include <GL/glut.h>

float sphereRot = 0.0f;
bool isRotating = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Đặt camera nhìn từ trên xuống và hơi chéo để thấy rõ khối 3D
    gluLookAt(1.5, 1.5, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // --- VẼ CỘT HÌNH CHỮ NHẬT ---
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        // Đặt cột thấp xuống để phần đỉnh nằm gần gốc tọa độ hoặc giữa màn hình
        glTranslatef(0.0f, -0.5f, 0.0f); 
        glScalef(0.3f, 1.2f, 0.3f); // Cột cao 1.2 đơn vị
        glutWireCube(1.0); 
    glPopMatrix();

    // --- VẼ QUẢ CẦU ---
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        
        // TÁCH QUẢ CẦU RA:
        // Cột cao 1.2, tâm tại -0.5 => Đỉnh cột đang ở: -0.5 + (1.2 / 2) = 0.1
        // Vậy ta phải đưa quả cầu lên ít nhất là 0.1 + bán kính quả cầu (0.3) = 0.4
        glTranslatef(0.0f, 0.4f, 0.0f); 
        
        if (isRotating) glRotatef(sphereRot, 0.0f, 1.0f, 0.0f);
        
        glutWireSphere(0.3, 20, 20); // Bán kính 0.3
    glPopMatrix();

    glutSwapBuffers();
}

// Các hàm timer, mouse, reshape giữ nguyên như bài trước...
void timer(int value) {
    if (isRotating) sphereRot += 2.0f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) isRotating = !isRotating;
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 700);
    glutCreateWindow("Fix: Sphere on top");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}