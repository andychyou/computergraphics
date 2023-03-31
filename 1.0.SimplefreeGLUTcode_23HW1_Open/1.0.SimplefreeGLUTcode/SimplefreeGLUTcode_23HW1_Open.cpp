#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define TO_RADIAN		0.017453292519943296 

int rightbuttonpressed = 0;
int leftbuttonpressed = 0, center_selected = 0;

float r, g, b; // Background color
float px, py, qx, qy; // Line (px, py) --> (qx, qy)
int n_object_points = 6;
float object[6][2], object_center_x, object_center_y;
float rotation_angle_in_degree;
int window_width, window_height;


float clicked_x_glut, clicked_y_glut;

float move_angle = 0;
int shiftpressed = 0;
float clicked_v_glutx, clicked_v_gluty;
int vertex_clicked = 0;

void draw_axes() {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.975f, 0.025f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.975f, -0.025f);
	glVertex2f(1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.025f, 0.975f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(-0.025f, 0.975f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
	glLineWidth(1.0f);

	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glPointSize(1.0f);
}
void draw_line(float px, float py, float qx, float qy) {
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(px, py); 
	glVertex2f(qx, qy);
	glEnd();
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(px, py);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(qx, qy);
	glEnd();
	glPointSize(1.0f);
}

void draw_object(void) {
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < 6; i++)
		glVertex2f(object[i][0], object[i][1]);
	glEnd();
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 6; i++)
		glVertex2f(object[i][0], object[i][1]);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(object_center_x, object_center_y);
	glEnd();
	glPointSize(1.0f);
}

void display(void) {
	glClearColor(r, g, b, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);

	draw_axes();
	draw_line(px, py, qx, qy);
	draw_object();
	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		r = 1.0f; g = b = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 'g':
		g = 1.0f; r = b = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 'b':
		b = 1.0f; r = g = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 's':
		r = 250.0f / 255.0f, g = 128.0f / 255.0f, b = 114.0f / 255.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 'q':
		glutLeaveMainLoop();
		break;

	}
	
}

//�Ϲ����� ���� ��ư ���� ��ư�� ex. shift
void special(int key, int x, int y) {
	printf("special key : %c\n", key);
	switch (key) {
		case GLUT_KEY_LEFT:
			r -= 0.1f;
			if (r < 0.0f) r = 0.0f;
			fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			r += 0.1f;
			if (r > 1.0f) r = 1.0f;
			fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			g -= 0.1f;
			if (g < 0.0f) g = 0.0f;
			fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			g += 0.1f;
			if (g > 1.0f) g = 1.0f;
			fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
			glutPostRedisplay();
			break;
		case GLUT_KEY_SHIFT_L:
			shiftpressed = 1;
			fprintf(stdout, "Left shift pressed\n");
			
			glutPostRedisplay();
			break;
	}
}

void upspecial(int key, int x, int y) {
	switch (key){
	case GLUT_KEY_SHIFT_L:
		shiftpressed = 0;
		fprintf(stdout, "Left shift unpressed\n");

		glutPostRedisplay();
		break;
	}
}

float win_to_glut_x(int x) {
	float a = ((x - window_width / 2.0f) / 250.0f);
	return a;
}

float win_to_glut_y(int y) {
	float a = ((window_height / 2.0f  - y)/ 250.0f);
	return a;
}


void rotate_line_up() {
	
	float b_px, b_py, b_qx, b_qy, t_x, t_y, length;
	length = sqrt(pow((px - qx), 2.0) + pow((qx - qy), 2.0));
	b_px = px;
	b_py = py;
	b_qx = qx;
	b_qy = qy;
	//px, py = 0;
	t_x = -b_px;
	t_y = -b_py;
	b_qx += t_x;
	b_qy += t_y;

	move_angle = 0.05;
	qx = b_qx * cos(move_angle) - b_qy * sin(move_angle);
	qy = b_qx * sin(move_angle) + b_qy * cos(move_angle);
	qx -= t_x;
	qy -= t_y;
	glutPostRedisplay();

}

void rotate_line_down() {

	float b_px, b_py, b_qx, b_qy, t_x, t_y, length;
	length = sqrt(pow((px - qx), 2.0) + pow((qx - qy), 2.0));
	b_px = px;
	b_py = py;
	b_qx = qx;
	b_qy = qy;
	//px, py = 0;
	t_x = -b_px;
	t_y = -b_py;
	b_qx += t_x;
	b_qy += t_y;

	move_angle = -0.05;
	qx = b_qx * cos(move_angle) - b_qy * sin(move_angle);
	qy = b_qx * sin(move_angle) + b_qy * cos(move_angle);
	qx -= t_x;
	qy -= t_y;
	glutPostRedisplay();

}

void move_vertex(float after_glutx, float after_gluty) {
	clicked_v_glutx = after_glutx;
	clicked_v_gluty = after_gluty;
	qx = clicked_v_glutx;
	qy = clicked_v_gluty;
}


int prevx, prevy;
void mousepress(int button, int state, int x, int y) {

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		leftbuttonpressed = 1;

		//���� �� glut ��ǥ ���
		fprintf(stdout, "*** The left mouse button was pressed at (%d, %d).\n", x, y);
		
		clicked_x_glut = win_to_glut_x(x);
		clicked_y_glut = win_to_glut_y(y);
		printf("Clicked glut coordinate %lf %lf\n", clicked_x_glut, clicked_y_glut);
		
		

		if (shiftpressed) {
			if ((fabs(clicked_x_glut - qx) < 0.01) && (fabs(clicked_y_glut - qy) < 0.01)) {
				printf("line clicked\n");
				vertex_clicked = 1;
				clicked_v_glutx = qx;
				clicked_v_gluty = qy;
			}
			for (int i = 0; i < n_object_points; i++) {
				printf("%lf\n", object[i][0]);
				if (fabs(clicked_x_glut - object[i][0]) < 0.01 && fabs(clicked_y_glut - object[i][1]) < 0.01) {
					printf("ok");
					break;
				}
			}
		}

	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		leftbuttonpressed = 0;
		vertex_clicked = 0;
	}
		
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
		rightbuttonpressed = 1;
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP))
		rightbuttonpressed = 0;

	// (d)
	else if (button == 3) {
		fprintf(stdout, "*** Up wheel mouse button was pressed.\n");
		rotate_line_up();
	}
	else if (button == 4) {
		fprintf(stdout, "*** Down wheel mouse button was pressed.\n");
		rotate_line_down();
	}


	

}


void mousemove(int x, int y) {
	
	float moveto_glutx, moveto_gluty;
	moveto_glutx = win_to_glut_x(x);
	moveto_gluty = win_to_glut_y(y);
	printf("mouse move to %d %d\n", x, x);
	if (vertex_clicked) {
		move_vertex(moveto_glutx, moveto_gluty);
	}
	glutPostRedisplay();
}
	
void reshape(int width, int height) {
	// DO NOT MODIFY THIS FUNCTION!!!
	window_width = width, window_height = height;
	glViewport(0.0f, 0.0f, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-window_width / 500.0f, window_width / 500.0f,  -window_height / 500.0f, window_height / 500.0f, -1.0f, 1.0f);

	glutPostRedisplay();
}


void close(void) {
	fprintf(stdout, "\n^^^ The control is at the close callback function now.\n\n");
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutSpecialUpFunc(upspecial);
	glutMouseFunc(mousepress);
	glutMotionFunc(mousemove);
	//glutMotionFunc���콺 ��ư(�޿�,�����Ʒ� �� ���콺 ��� ��ư)�� ������ �巡�׽� mousemove ȣ��. �Ű����� x,y���ڴ� window ��ǥ
	glutReshapeFunc(reshape);
 	glutCloseFunc(close);
}

void initialize_renderer(void) {
	register_callbacks();
	r = 250.0f / 255.0f, g = 128.0f / 255.0f, b = 114.0f / 255.0f; // Background color = Salmon
	//px,py�� �����߽�
	px = -0.75f, py = 0.20f, qx = -0.25f, qy = 0.20f;
	rotation_angle_in_degree = 1.0f; // 1 degree
	
	float sq_cx = 0.55f, sq_cy = -0.45f, sq_side = 0.25f;
	object[0][0] = sq_cx + sq_side;
	object[0][1] = sq_cy + sq_side;
	object[1][0] = sq_cx + 0.5 * sq_side;
	object[1][1] = sq_cy + 1.5 * sq_side;
	object[2][0] = sq_cx - sq_side;
	object[2][1] = sq_cy + sq_side;
	object[3][0] = sq_cx - sq_side;
	object[3][1] = sq_cy - sq_side;
	object[4][0] = sq_cx - 0.5 * sq_side;
	object[4][1] = sq_cy - 0.5 * sq_side;
	object[5][0] = sq_cx + sq_side;
	object[5][1] = sq_cy - sq_side;
	object_center_x = object_center_y = 0.0f;
	for (int i = 0; i < n_object_points; i++) {
		object_center_x += object[i][0];
		object_center_y += object[i][1];
	}
	object_center_x /= n_object_points;
	object_center_y /= n_object_points;
}

void initialize_glew(void) {
	GLenum error;

	glewExperimental = TRUE;
	error = glewInit();
	if (error != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}
	fprintf(stdout, "*********************************************************\n");
	fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "*********************************************************\n\n");
}

void greetings(char *program_name, char messages[][256], int n_message_lines) {
	fprintf(stdout, "**************************************************************\n\n");
	fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);
	fprintf(stdout, "    This program was coded for CSE4170 students\n");
	fprintf(stdout, "      of Dept. of Comp. Sci. & Eng., Sogang University.\n\n");

	for (int i = 0; i < n_message_lines; i++)
		fprintf(stdout, "%s\n", messages[i]);
	fprintf(stdout, "\n**************************************************************\n\n");

	initialize_glew();
}








#define N_MESSAGE_LINES 4
void main(int argc, char *argv[]) {
	char program_name[64] = "Sogang CSE4170 Simple 2D Transformations";
	char messages[N_MESSAGE_LINES][256] = {
		"    - Keys used: 'r', 'g', 'b', 's', 'q'",
		"    - Special keys used: LEFT, RIGHT, UP, DOWN",
		"    - Mouse used: SHIFT/L-click and move, ALT/R-click and move, CTRL/R-click and move",
		"    - Wheel used: up and down scroll"
		"    - Other operations: window size change"
	};

	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // <-- Be sure to use this profile for this example code!
 //	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize(750, 750);
	glutInitWindowPosition(500, 200);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

   // glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_EXIT); // default
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutMainLoop();
	fprintf(stdout, "^^^ The control is at the end of main function now.\n\n");
}