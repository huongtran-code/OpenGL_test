#include <GL/glut.h>

float rotBlue = 0.0f;   
float rotYellow = 0.0f; 
bool isRotBlue = false;
bool isRotYellow = false;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Nền đen
    glEnable(GL_DEPTH_TEST);          // Bật 3D
}

// Hàm vẽ khối hộp chữ nhật dài
void drawBox(float r, float g, float b) {
    glPushMatrix();
    glScalef(0.4f, 1.5f, 0.4f); // Co giãn lập phương thành hình hộp chữ nhật
    
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    
    glColor3f(0.0f, 0.0f, 0.0f); // Vẽ nét bao quanh cho đẹp
    glutWireCube(1.001);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Đặt camera nhìn từ hướng (3, 3, 5) để thấy rõ chiều không gian
    gluLookAt(3.0, 3.0, 5.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0);

    // --- KHỐI CHỮ NHẬT XANH (BÊN DƯỚI) ---
    glPushMatrix();
        if (isRotBlue) glRotatef(rotBlue, 0.0f, 0.0f, 1.0f); // a. Quay quanh trục Oz
        
        // Dịch chuyển để tâm khối nằm ở y=0.75 (đáy nằm ở y=0)
        glTranslatef(0.0f, 0.75f, 0.0f);
        drawBox(0.5f, 0.7f, 1.0f); 
    glPopMatrix();

    // --- KHỐI CHỮ NHẬT VÀNG (BÊN TRÊN) ---
    glPushMatrix();
        // O là điểm nối (y = 1.5). Di chuyển hệ tọa độ đến O
        glTranslatef(0.0f, 1.5f, 0.0f);
        
        // b. Quay quanh trục L (song song Oz, đi qua O)
        if (isRotYellow) glRotatef(rotYellow, 0.0f, 0.0f, 1.0f);
        
        // Sau khi quay tại O, dịch chuyển lên trên để vẽ khối vàng
        glTranslatef(0.0f, 0.75f, 0.0f);
        drawBox(1.0f, 0.9f, 0.3f);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
    if (isRotBlue) rotBlue += 2.0f;
    if (isRotYellow) rotYellow += 2.0f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q') isRotBlue = !isRotBlue;   // Nhấn q bật/tắt quay khối xanh
    if (key == 'r') isRotYellow = !isRotYellow; // Nhấn r bật/tắt quay khối vàng
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 800);
    glutCreateWindow("Bai 5: Robot Arm - Fixed");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}