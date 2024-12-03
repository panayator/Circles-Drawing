#include <GL/glut.h>


void set8pixels(int xc, int yc, int x, int y, float pointSize)
{   // Draws 8 symmetric pixels of a circle with its center at (xc, yc). pointSize indicates the size of the pixel
    glPointSize(pointSize);
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - x, yc + y);
    glEnd();
}

class Circle
{
public:
    float centerX, centerY, radius, lineSize;
    Circle(float _centerX = 0.0, float _centerY = 0.0, float _radius = 10.0, float _lineSize = 1.0)
        : centerX(_centerX), centerY(_centerY), radius(_radius), lineSize(_lineSize) {}

    void draw() const;
};

void Circle::draw() const   // Draws the circle using Bresenham's algorithm for circle drawing
{
    glPointSize(lineSize);
    glColor3f(1.0, 0.0, 0.0);
    int x = 0;
    int y = static_cast<int>(radius);
    int e = -static_cast<int>(radius);

    while (x <= y)
    {
        set8pixels(static_cast<int>(centerX), static_cast<int>(centerY), x, y, lineSize);
        x = x + 1;
        e = e + 2 * x + 1;
        if (e >= 0)
        {
            y = y - 1;
            e = e - 2 * y + 2;
        }
    }
}

float windowWidth = 600.0;
float windowHeight = 600.0;
float mouseX = 0.0, mouseY = 0.0;
bool isMouseDown = false;
bool isFirstClick = false;

float minLineSize = 1.0;
float maxLineSize = 100.0; // OpenGl and/or system limitations do not visually allow higher lineSize for the circle than this
float currentLineSize = minLineSize;

float minRadius = 20.0;
float maxRadius = 410.0;
float currentRadius = minRadius;

enum key_state {NOTPUSHED, PUSHED} keyArray[127];   // Enumeration type (such as true/false) array to store the state (pushed or not) of keyboard keys
enum special_key_state {NOTPRESSED, PRESSED} specialKeyArray[127];  // Similar array to store the state (pushed or not) of special keys 

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);   // Essentially clears the window's contents, so that a fresh frame can be drawn
    glEnable(GL_POINT_SMOOTH);  // Enables antialiasing for point rendering, resulting in smoother and more rounded points when drawing.

    if (isFirstClick)   // If a left mouse button click is the first click, draw the circle, where mouseX = xc, mouseY = yc, currentRadius = r, currentLineSize = size
    {
        Circle circle(mouseX, mouseY, currentRadius, currentLineSize);
        circle.draw();
    }

    if (keyArray['w'] || keyArray['W']){    // Move circle upwards when 'w' or 'W' is pressed
        mouseY += 0.08;
    }
    if (keyArray['s'] || keyArray['S']){    // Move circle downwards when 's' or 'S' is pressed
        mouseY -= 0.08;
    }
    if (keyArray['d'] || keyArray['D']){    // Move circle to the right when 'd' or 'D' is pressed
        mouseX += 0.08;
    }
    if (keyArray['a'] || keyArray['A']){    // Move circle to the left when 'a' or 'A' is pressed
        mouseX -= 0.08;
    }
    if (specialKeyArray[GLUT_KEY_UP]){  // Increase line size when the up arrow key is pressed
        currentLineSize += 0.02;
        if (currentLineSize > maxLineSize)
            currentLineSize = maxLineSize;
    }
    if (specialKeyArray[GLUT_KEY_DOWN]){    // Decrease line size when the down arrow key is pressed
        currentLineSize -= 0.02;
        if (currentLineSize < minLineSize)
            currentLineSize = minLineSize;
    }
    if (specialKeyArray[GLUT_KEY_RIGHT]){   // Increase circle radius when the right arrow key is pressed
        currentRadius += 0.08;
        if (currentRadius > maxRadius)
            currentRadius = maxRadius;
    }
    if (specialKeyArray[GLUT_KEY_LEFT]){    // Decrease circle radius when the left arrow key is pressed
        currentRadius -= 0.08;
        if (currentRadius < minRadius)
            currentRadius = minRadius;
    }

    glutSwapBuffers();  // Swaps the front and back buffers of the current window when updating the window's contents, allowing for smooth animation and preventing flickering.
}

void KeyboardFunc(unsigned char key, int x, int y)  // Checks if a specified key is pressed and saves it as PUSHED in the keyArray
{
    if (key == 27){ // If the Esc key is pressed, close the program
        exit(0);
    } 
        
    if (key == 'W' || key == 'w'){ // W key
        keyArray['W'] = PUSHED;
        keyArray['w'] = PUSHED;
    }
    if (key == 'S' || key == 's'){ // S key
        keyArray['S'] = PUSHED;
        keyArray['s'] = PUSHED;
    }
    if (key == 'D' || key == 'd'){ // D key
        keyArray['D'] = PUSHED;
        keyArray['d'] = PUSHED;
    }
    if (key == 'A' || key == 'a'){ // A key
        keyArray['a'] = PUSHED;
        keyArray['a'] = PUSHED;
    }
}

void KeyboardUpFunc(unsigned char key, int x, int y)    // Checks if a specified key is no longer pushed and saves it as NOTPUSHED in the keyArray
{ 
    if (key == 'W' || key == 'w'){ // W key
        keyArray['W'] = NOTPUSHED;
        keyArray['w'] = NOTPUSHED;
    }
    if (key == 'S' || key == 's'){ // S key
        keyArray['S'] = NOTPUSHED;
        keyArray['s'] = NOTPUSHED;
    }
    if (key == 'D' || key == 'd'){ // D key
        keyArray['D'] = NOTPUSHED;
        keyArray['d'] = NOTPUSHED;
    }
    if (key == 'A' || key == 'a'){ // A key
        keyArray['A'] = NOTPUSHED;
        keyArray['a'] = NOTPUSHED;
    }
}

void SpecialFunc(int key, int x, int y) // Checks if a specified special key is pressed and saves it as PUSHED in the specialKeyArray
{
    
    if (key == GLUT_KEY_UP) // Arrow Up
    {
        specialKeyArray[GLUT_KEY_UP] = PRESSED;
    }
    else if (key == GLUT_KEY_DOWN) // Arrow Down
    {
        specialKeyArray[GLUT_KEY_DOWN] = PRESSED;
    }
    else if (key == GLUT_KEY_RIGHT) // Arrow Right
    {
        specialKeyArray[GLUT_KEY_RIGHT] = PRESSED;
    }
    else if (key == GLUT_KEY_LEFT) // Arrow Left
    {
        specialKeyArray[GLUT_KEY_LEFT] = PRESSED;
    }
}

void SpecialUpFunc(int key, int x, int y){  // Checks if a specified special key is no longer pushed and saves it as NOTPUSHED in the specialKeyArray
    
    if (key == GLUT_KEY_UP) // Arrow Up
    {
        specialKeyArray[GLUT_KEY_UP] = NOTPRESSED;
    }
    else if (key == GLUT_KEY_DOWN) // Arrow Down
    {
        specialKeyArray[GLUT_KEY_DOWN] = NOTPRESSED;
    }
    else if (key == GLUT_KEY_RIGHT) // Arrow Right
    {
        specialKeyArray[GLUT_KEY_RIGHT] = NOTPRESSED;
    }
    else if (key == GLUT_KEY_LEFT) // Arrow Left
    {
        specialKeyArray[GLUT_KEY_LEFT] = NOTPRESSED;
    }
}

void MousePressed(int button, int state, int x, int y)  // Checks if the left mouse button is pressed
{
    isMouseDown = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN); // Sets isMouseDown to listen for when the left mouse button is pressed
    if (isMouseDown && !isFirstClick)   // If the mouse click isn't the first click it then becomes the first click (so that the circle is drawn)
    {
        isFirstClick = true;
    }
}

void MouseMove(int x, int y)    // Moves the circle according to the movement of the mouse only while the left mouse button is pressed
{
    if (isMouseDown)
    {
        mouseX = x - windowWidth / 2;
        mouseY = windowHeight / 2 - y;
    }
}

void context_menu(int option)   // Pop up menu that displays all movement/adjustment options for the circle
{
    switch(option)
    {
        case 1: mouseY += 5.0; glutPostRedisplay(); break;
        case 2: mouseY -= 5.0; glutPostRedisplay(); break;
        case 3: mouseX += 5.0; glutPostRedisplay(); break;
        case 4: mouseX -= 5.0; glutPostRedisplay(); break;
        case 5: currentLineSize += 1.0;
        if (currentLineSize > maxLineSize)
            currentLineSize = maxLineSize;
        glutPostRedisplay(); break;
        case 6: currentLineSize -= 1.0;
        if (currentLineSize < minLineSize)
            currentLineSize = minLineSize;
        glutPostRedisplay(); break;
        case 7: currentRadius += 4.0;
        if (currentRadius > maxRadius)
            currentRadius = maxRadius;
        glutPostRedisplay(); break;
        case 8: currentRadius -= 4.0;
        if (currentRadius < minRadius)
            currentRadius = minRadius;
        glutPostRedisplay(); break;
        
        case 9: exit(0); break;
    }
}

void idle(){    // Redisplay the circle if no other event is happening (idle state)
    glutPostRedisplay();
}

void Initialize()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2, -200.0, 200.0); // Specifies the coordinate system to be used for rendering, defining the left, right, bottom, and top limits of the viewing frustum
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);  // Initializes the GLUT library 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // Sets the display mode to double buffering and RGB color
    glutInitWindowSize(windowWidth, windowHeight);  // Specifies the initial window size
    glutInitWindowPosition(100, 200);   // Specifies the initial window position
    glutCreateWindow("Circles Draw");   //Specifies the window's title
    glutDisplayFunc(Draw);
    glutMouseFunc(MousePressed);
    glutMotionFunc(MouseMove);
    glutKeyboardFunc(KeyboardFunc);
    glutKeyboardUpFunc(KeyboardUpFunc);
    glutSpecialFunc(SpecialFunc);
    glutSpecialUpFunc(SpecialUpFunc);
    Initialize();
    glutCreateMenu(context_menu);
    glutAddMenuEntry("Move Circle Up (W key)", 1);
    glutAddMenuEntry("Move Circle Down (S key)", 2);
    glutAddMenuEntry("Move Circle Right (D key)", 3);
    glutAddMenuEntry("Move Circle Left (A key)", 4);
	glutAddMenuEntry("Increase size (Arrow Up)", 5);
    glutAddMenuEntry("Decrease size (Arrow Down)", 6);
    glutAddMenuEntry("Increase radius (Arrow Right)", 7);
    glutAddMenuEntry("Decrease radius (Arrow Left)", 8);
    glutAddMenuEntry("Close (Esc)", 9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);  // Attaches the menu to the right mouse button
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
