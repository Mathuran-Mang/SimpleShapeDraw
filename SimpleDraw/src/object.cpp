/*
 * Description: implementation of object.hpp
 * Author: HBF
 * Version: 2021-08-24
 */
#include <string>
#include <iostream>

using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "object.hpp"
#include <iostream>

void insert(LIST *list, SHAPE *object) {
	if (object == NULL) return;

	NODE *p = (NODE*) malloc(sizeof(NODE));
	p->object = object;
	p->prev = NULL;
	p->next = NULL;

	if (list->start == NULL) {
		list->start = p;
		list->end = p;
	} else {
		list->end->next = p;
		p->prev = list->end;
		list->end = p;
	}
}

void deleteNode(LIST *list, NODE **selectp) {
// ...
}

void clearList(LIST *list) {
// ...
}

void drawShape(SHAPE *object) {
	if (object->type == RECTANGLE) {  // rectangle

		  // draw filled rectangle
			glColor3f(object->fr, object->fg, object->fb);
			glBegin(GL_QUADS);
			glVertex2i(object->x1, object->y1);
			glVertex2i(object->x1, object->y2);
			glVertex2i(object->x2, object->y2);
			glVertex2i(object->x2, object->y1);
			glEnd();

			// stroke outline of rectangle
			glColor3f(object->sr, object->sg, object->sb);
			glLineWidth(object->swidth);
			glBegin(GL_LINE_LOOP);
			glVertex2i(object->x1, object->y1);
			glVertex2i(object->x1, object->y2);
			glVertex2i(object->x2, object->y2);
			glVertex2i(object->x2, object->y1);
			glEnd();

	} else if (object->type == CIRCLE) {  // circle
		glColor3f(object->fr, object->fg, object->fb);

		circleMidpoint(object->x1, object->y1, object->x2, object->y2);
		glColor3f(object->sr, object->sg, object->sb);
		glLineWidth(object->swidth);
		circleMidpointFill(object->x1, object->y1, object->x2, object->y2);
	}
}

void drawShapeHighLight(SHAPE *object) {
	object->sr = 1.0;
	object->sg = 1.0;
	std::cout << "static constructor\n";


}

void drawList(LIST *list) {
	NODE *p = list->start;
	while (p) {
		drawShape(p->object);
		p = p->next;
	}
}

void setPixel(GLint x, GLint y) {
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// draw points on line of circle
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x,
		const GLint& y) {
	setPixel(xc + x, yc + y); setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y); setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x); setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x); setPixel(xc - y, yc - x);

// ...
}

// draw circle main function
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2) {
	GLint r = sqrt(pow((x1 - x2),2) + pow((y1-y2), 2));
	GLint p = 1 - r; // Initial value of midpoint parameter.
	/* Plot the initial point in each circle quadrant. */
	x2 = 0, y2 = r;
	circlePlotPointsFill(x1, y1, x2, y2);
	while (x2 < y2) {
	x2++;
	if (p < 0) p += 2 * x2 + 1;
	else { y2--; p += 2 * (x2 - y2) + 1; }
	circlePlotPointsFill(x1, y1, x2, y2);
	}}

void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y) {
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2i(x1 - x, y1 + y); glVertex2i(x1 + x, y1 + y);
	glVertex2i(x1 - x, y1 - y); glVertex2i(x1 + x, y1 - y);
	glVertex2i(x1 - y, y1 + x); glVertex2i(x1 + y, y1 + x);
	glVertex2i(x1 - y, y1 - x); glVertex2i(x1 + y, y1 - x);
	glEnd();}


void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2) {
	GLint r = sqrt(pow((x1 - x2),2) + pow((y1-y2), 2));
	GLint p = 1 - r; // Initial value of midpoint parameter.
	/* Plot the initial point in each circle quadrant. */
	x2 = 0, y2 = r;
	circlePlotPoints(x1, y1, x2, y2);
	while (x2 < y2) {
	x2++;
	if (p < 0) p += 2 * x2 + 1;
	else { y2--; p += 2 * (x2 - y2) + 1; }
	circlePlotPoints(x1, y1, x2, y2);
	}}
