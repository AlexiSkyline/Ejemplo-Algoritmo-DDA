#include <conio.h>
#include <windows.h>
#include <GL\glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

// ? Definimos las variables para usar el argoritmi DDA
int x_1, y_1, x_2, y_2, Pasos, dy, dx;
double Pendiente;

// Todo: Display, función que crea la imagen
// * Descripcion geométrica de la imagen que se va a usar
void Display() { // * Contiene el algoritmo
	// ? Delta
	dy = y_2 - y_1;
	dx = x_2 - x_1;
	
	//? Pendientes de la recta
	Pendiente = ( dy * 1.0 ) / ( dx * 1.0 );
	
	//? Numero de pasos
	Pasos = max( dy, dx );
	
	glClear( GL_COLOR_BUFFER_BIT ); // * Función para el color de la ventana
	glColor3f( 1, 1, 1 ); // * Establece color de objetos
	glLoadIdentity();
	
	// Todo: Definimos las Propiedades el Plano Cartesiano
	glLineWidth( 5.0 );
	glColor3f( 1, 0, 0 ); // * Color de la Ejes de las "X y Y"
	glBegin( GL_LINES );
		glVertex2d( -20, 0 ); // * Primera Línea
		glVertex2d( 20, 0 );
		glVertex2d( 0, 20 ); // * Segunda Línea
		glVertex2d( 0, -20 );
	glEnd();
	
	// TODO: Definimos las propiedades de las Lineas que forman los cuadrados
	glLineWidth( 2.0 );
	glColor3f( 0.90, 0.90, 0.90 ); // *  Color de los lineas de los cuadrados
	glBegin( GL_LINES );
		// * Líneas Horizontales
		for( int j = 21; j > -20; j-- ) {
			glVertex2f( -20, j + 0.5 );
			glVertex2f( 20, j + 0.5 );
		}
		
		// * Líneas Verticales
		for( int j = 21; j > -20; j-- ) {
			glVertex2f( j + 0.5, -20 );
			glVertex2f( j + 0.5, 20 );
		}
		
	glEnd();
	
	// Todo: Dibujasmos las lineas de las (X y Y) y definimos El punto 0.0
	glPointSize( 18 ); // * Se define el tamaño del píxel
	glBegin( GL_POINTS );
		glColor3f( 1.0, 1.0, 1.0 );
		glVertex3f( 0.0f, 0.0f, 0.0f ); // * El origen
		glColor3f( 0.90, 0.90, 0.90 ); //* Colores de las linea
		
		double xi = x_1 * 1.0;
		double yi = y_1 * 1.0;
		
		if( Pendiente < 1 ) {
			for( int k = 0; k < Pasos + 1; k++ ) {
				glVertex2d( xi, round( yi )); // * Función de punto en OpenGL
				xi++;
				yi = yi + Pendiente;
			}
		} else {
			for( int k = 0; k < Pasos + 1; k++ ) {
				glVertex2d( round( xi ), yi );
				yi++;
				xi = xi + 1.0/Pendiente;
			}
		}
	glEnd();
	
	// Todo: Gráfica de línea
	glColor3f( 0, 0, 1 ); // * Color de objeto
	glLineWidth( GL_LINES );  // * Ancho de la línea
		glVertex2d( x_1 * 1.0, y_1 * 1.0 );
		glVertex2d( x_2 * 1.0, y_2 * 1.0 );
	glEnd();
	
	glFlush(); // * Procesa todas las subrutinas de OpenGL
}

void Init() {
	glClearColor( 0.30, 0.30, 0.30, 0 ); // * Color de la pantalla en color negro
}

// TODO: Definir el sistema de coordenadas para la ventana de visualización
void reshape( int width, int height ) {
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION ); // * Tipo de proyección
	glLoadIdentity(); // * Asignar la matriz identidad como matriz de proyecto
	glOrtho( -20, 20, -20, 20, -1, 1 );
	/*
		* Objeto definidos dentro de este rangom se mosyrar en la pantalla
	*/
	glMatrixMode( GL_MODELVIEW );
}

// Todo: Función principal
int main( int argc, char *argv[] ) {
	// * Leer los puntos iniciales y finales de la recta a graficar
	cout<<"Ingrese X1:"; cin >> x_1;
	cout<<"Ingrese Y1:"; cin >> y_1;
	cout<<"Ingrese X2:"; cin >> x_2;
	cout<<"Ingrese Y2:"; cin >> y_2;
	
	glutInit( &argc, argv ); //* Realizar Inicialización del Glut
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ); // * Número de buffer | Color RGB
	glutInitWindowSize( 800, 800 ); // * Establece la altura y el archi de la pantalla
	glutCreateWindow( "Algoritmo DDA" ); //* Crea y le pasamos el nombre de la Pestaña
	Init(); // * Ejecuta el procedimiento de inicialización
	glutDisplayFunc( Display ); // * Asigna la imagen a la ventana de visualizacion
	/*
		*Especifica qué va a contener la ventana de visualización
		*Envia los gráficos a la ventana de visualización
	*/
	glutReshapeFunc( reshape ); // * Cambia de tamaño de la ventana actual
	glutMainLoop(); // * Mandamos a llamar la función de las ventanas que se hayan creado
	/* 
		* Muestra los gráficos iniciales y los pone en un bucle infinito
		* Muestra todo y espera
	*/

	return 0;
}