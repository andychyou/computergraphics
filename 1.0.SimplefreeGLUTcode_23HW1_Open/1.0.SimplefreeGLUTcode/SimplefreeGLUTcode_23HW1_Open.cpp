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
int altpressed = 0;
int ctrlpressed = 0;
int f1pressed = 0;
int f2pressed = 0;
float clicked_v_glutx, clicked_v_gluty;
int vertex_clicked = 0;
int rightclick_x, rightclick_y;
float object_move_x = 0;
float object_move_y = 0;
float scale_move = 1;
int prev_x = 0;
float prev_x_glut = 0;
float prev_y_glut = 0;
int prev_exist = 0;

float my_object[7][2];
float my_object_center_x = 0;
float my_object_center_y = 0;
int my_n_object_points = 7;
float shear_move_x, shear_move_y;
int shear_right;

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

void draw_my_object() {
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < my_n_object_points; i++)
		glVertex2f(my_object[i][0], my_object[i][1]);
	glEnd();
	glPointSize(5.0f);

	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < my_n_object_points; i++) {
		glVertex2f(my_object[i][0], my_object[i][1]);
	}
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(my_object_center_x, my_object_center_y);
	glEnd();
	glPointSize(1.0f);
}

void display(void) {
	glClearColor(r, g, b, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);

	draw_axes();
	draw_line(px, py, qx, qy);
	draw_object();
	draw_my_object();
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

//일반적인 문자 버튼 외의 버튼들 ex. shift
void special(int key, int x, int y) {
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
		case GLUT_KEY_ALT_L:
			altpressed = 1;
			fprintf(stdout, "Left alt pressed\n");
			glutPostRedisplay();
			break;
		case GLUT_KEY_CTRL_L:
			ctrlpressed = 1;
			fprintf(stdout, "Left ctrl pressed\n");
			glutPostRedisplay();
			break;
		case GLUT_KEY_F1:
			f1pressed = 1;
			fprintf(stdout, "F1 pressed\n");
			glutPostRedisplay();
			break;
		case GLUT_KEY_F2:
			f2pressed = 1;
			fprintf(stdout, "F2 pressed\n");
			glutPostRedisplay();
			break;
	}
}

void upspecial(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_SHIFT_L:
		shiftpressed = 0;
		fprintf(stdout, "Left shift unpressed\n");
		glutPostRedisplay();
		break;
	case GLUT_KEY_ALT_L:
		altpressed = 0;
		object_move_x = object_move_y = 0;
		fprintf(stdout, "Left alt unpressed\n");
		glutPostRedisplay();
		break;
	case GLUT_KEY_CTRL_L:
		ctrlpressed = 0;
		scale_move = 1;
		fprintf(stdout, "Left alt unpressed\n");
		glutPostRedisplay();
		break;
	case GLUT_KEY_F1:
		f1pressed = 0;
		fprintf(stdout, "F1 unpressed\n");
		glutPostRedisplay();
		break;
	case GLUT_KEY_F2:
		f2pressed = 0;
		fprintf(stdout, "F2 unpressed\n");
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
	px = clicked_v_glutx;
	py = clicked_v_gluty;
}

void move_object(float after_glutx, float after_gluty) {
	object_center_x -= object_move_x;
	object_center_y -= object_move_y;
	for (int i = 0; i < n_object_points; i++) {
		object[i][0] -= object_move_x;
		object[i][1] -= object_move_y;
	}

	object_move_x = after_glutx - win_to_glut_x(rightclick_x) ;
	object_move_y = after_gluty - win_to_glut_y(rightclick_y) ;

	object_center_x += object_move_x;
	object_center_y += object_move_y;
	for (int i = 0; i < n_object_points; i++) {
		object[i][0] += object_move_x;
		object[i][1] += object_move_y;
	}
}

void scale_object() {
	float original_object_center_x, original_object_center_y;
	original_object_center_x = object_center_x;
	original_object_center_y = object_center_y;

	//원점으로 transpose
	object_center_x -= original_object_center_x;
	object_center_y -= original_object_center_y;
	for (int i = 0; i < n_object_points; i++) {
		object[i][0] -= original_object_center_x;
		object[i][1] -= original_object_center_y;
	}

	//scaling 적용
	for (int i = 0; i < n_object_points; i++) {
		object[i][0] = object[i][0] * scale_move;
		object[i][1] = object[i][1] * scale_move;
	}

	//원래 위치로 돌아감
	object_center_x += original_object_center_x;
	object_center_y += original_object_center_y;
	for (int i = 0; i < n_object_points; i++) {
		object[i][0] += original_object_center_x;
		object[i][1] += original_object_center_y;
	}
}

void shear_object_x() {
	float original_object_center_x, original_object_center_y;
	original_object_center_x = my_object_center_x;
	original_object_center_y = my_object_center_y;

	//원점으로 transpose
	my_object_center_x -= original_object_center_x;
	my_object_center_y -= original_object_center_y;
	for (int i = 0; i < my_n_object_points; i++) {
		my_object[i][0] -= original_object_center_x;
		my_object[i][1] -= original_object_center_y;
	}

	//shearing 적용
	my_object_center_x += shear_move_x * my_object_center_y;
	for (int i = 0; i < my_n_object_points; i++) {
		float x = my_object[i][0];
		float y = my_object[i][1];
		my_object[i][0] = my_object[i][0] + shear_move_x * y;
		//my_object[i][1] = my_object[i][1] + shear_move_y * x;
	}
	

	//원래 위치로 돌아감
	my_object_center_x += original_object_center_x;
	my_object_center_y += original_object_center_y;
	for (int i = 0; i < my_n_object_points; i++) {
		my_object[i][0] += original_object_center_x;
		my_object[i][1] += original_object_center_y;
	}
}

void shear_object_y() {
	float original_object_center_x, original_object_center_y;
	original_object_center_x = my_object_center_x;
	original_object_center_y = my_object_center_y;

	//원점으로 transpose
	my_object_center_x -= original_object_center_x;
	my_object_center_y -= original_object_center_y;
	for (int i = 0; i < my_n_object_points; i++) {
		my_object[i][0] -= original_object_center_x;
		my_object[i][1] -= original_object_center_y;
	}

	//shearing 적용
	my_object_center_y += shear_move_y * my_object_center_x;

	for (int i = 0; i < my_n_object_points; i++) {
		float x = my_object[i][0];
		float y = my_object[i][1];
		//my_object[i][0] = my_object[i][0] + shear_move_x * y;
		my_object[i][1] = my_object[i][1] + shear_move_y * x;
	}


	//원래 위치로 돌아감
	my_object_center_x += original_object_center_x;
	my_object_center_y += original_object_center_y;
	for (int i = 0; i < my_n_object_points; i++) {
		my_object[i][0] += original_object_center_x;
		my_object[i][1] += original_object_center_y;
	}
}


void mousepress(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		leftbuttonpressed = 1;

		//누른 곳 glut 좌표 계산
		fprintf(stdout, "*** The left mouse button was pressed at (%d, %d).\n", x, y);
		
		clicked_x_glut = win_to_glut_x(x);
		clicked_y_glut = win_to_glut_y(y);
		printf("Clicked glut coordinate %lf %lf\n", clicked_x_glut, clicked_y_glut);
		
		//다갹형 흰점 눌렀는지 확인
		for (int i = 0; i < n_object_points; i++) {
			printf("%lf\n", object[i][0]);
			if (fabs(clicked_x_glut - object[i][0]) < 0.01 && fabs(clicked_y_glut - object[i][1]) < 0.01) {
				printf("ok");
				break;
			}
		}

		if (shiftpressed) {
			//선분의 파란점
			if ((fabs(clicked_x_glut - px) < 0.04) && (fabs(clicked_y_glut - py) < 0.04)) {
				printf("line blue vertex clicked\n");
				vertex_clicked = 1;
				clicked_v_glutx = px;
				clicked_v_gluty = py;
			}
			
		}

	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		leftbuttonpressed = 0;
		vertex_clicked = 0;
	}
		
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		rightbuttonpressed = 1;
		rightclick_x = x;
		rightclick_y = y;
		prev_x_glut = win_to_glut_x(rightclick_x);
		prev_y_glut = win_to_glut_y(rightclick_y);
	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) {
		rightbuttonpressed = 0;
		

	}

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

	//printf("mouse move to %lf %lf\n", win_to_glut_x(x), prev_x_glut);

	if (vertex_clicked) {
		move_vertex(moveto_glutx, moveto_gluty);
	}
	else if (altpressed) {
		move_object(moveto_glutx, moveto_gluty);
	}
	else if (ctrlpressed) {
		printf("\n\n\n %lf -> %lf\n", prev_x_glut, moveto_glutx);
		printf("\n\n\n %lf", moveto_glutx - prev_x_glut);
		scale_move = 1 + moveto_glutx - prev_x_glut;
	
		prev_x_glut = moveto_glutx;

		printf("\n\nthis is scale move %lf\n\n", scale_move);
		printf("scale : %lf\n", scale_move);
		scale_object();
	}
	else if (f1pressed) {
		shear_move_x = moveto_glutx - prev_x_glut;
		printf("prev : %lf next : %lf\n", prev_x_glut, moveto_glutx);

		prev_x_glut = moveto_glutx;
		shear_object_x();
	}
	else if (f2pressed) {
		shear_move_y = moveto_gluty - prev_y_glut;
		printf("prev : %lf next : %lf\n", prev_y_glut, moveto_gluty);

		prev_y_glut = moveto_gluty;
		shear_object_y();
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
	//glutMotionFunc마우스 버튼(왼오,휠위아래 등 마우스 모든 버튼)을 누르고 드래그시 mousemove 호출. 매개변수 x,y인자는 window 좌표
	glutReshapeFunc(reshape);
 	glutCloseFunc(close);
}

void initialize_renderer(void) {
	register_callbacks();
	r = 250.0f / 255.0f, g = 128.0f / 255.0f, b = 114.0f / 255.0f; // Background color = Salmon
	//px,py가 무게중심
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


	float my_object_x_offset, my_object_y_offset;
	my_object_x_offset = 0.4f;
	my_object_y_offset = 0.4f;

	my_object[0][0] = 0.0f;
	my_object[0][1] = 0.0f;
	my_object[1][0] = 0.0f;
	my_object[1][1] = 0.2f;
	my_object[5][0] = 0.5f;
	my_object[5][1] = -0.1f;
	my_object[6][0] = 0.5f;
	my_object[6][1] = 0.0f;
	my_object[2][0] = 0.5f;
	my_object[2][1] = 0.2f;
	my_object[3][0] = 0.5f;
	my_object[3][1] = 0.3f;
	my_object[4][0] = 0.6f;
	my_object[4][1] = 0.1f;
	for (int i = 0; i < my_n_object_points; i++) {
		my_object[i][0] += my_object_x_offset;
		my_object[i][1] += my_object_y_offset;
	}
	for (int i = 0; i < my_n_object_points; i++) {

		my_object_center_x += my_object[i][0];
		my_object_center_y += my_object[i][1];

	}

	my_object_center_x /= my_n_object_points;
	my_object_center_y /= my_n_object_points;


	
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