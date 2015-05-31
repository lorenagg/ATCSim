/*
 * weather.cpp
 *
 *  Created on: 31/5/2015
 *      Author: LorenaGutierrez
 */

#include "weather.h"

weather::weather() {
	// TODO Auto-generated constructor stub

}

weather::~weather() {
	// TODO Auto-generated destructor stub
}



//declaro las variables del circulo, que seran punto origen en x, y, y el radio, ademas otras dos variable que seran para hacer el calculo en x y el calculo en y

float ptox= 2, ptoy= 5, radio= 3, calx, caly;
void inicio(void)
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(0.0,0.0,0.0,0.0);
	gluOrtho2D(-20,20,-20,20);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);

	for(double i=0.0; i<10; i=i+0.09)
	{
		calx=radio*cos(i);
		caly=radio*sin(i);

		glVertex2f(calx,caly);
	}
	glEnd();


	glFlush();
}
