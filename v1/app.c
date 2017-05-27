#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "./mylibs/sistemasyplanetas.h"

// CONSTANTES
const char SEPARADOR_ALUMNOS_TXT = ';';

// CONSTANTES ARCHIVOS
const char ALUMNOS_TXT[] = "alumnos.txt";

// CONSTANTES TAMANIOS VECTORES
#define CORRECTOR_TAMANIO_VECTOR_A_STRING = 1
#define TAMANIO_CODIGO_ALUMNO 11
#define TAMANIO_NOMBRE_ALUMNO 21
#define TAMANIO_APELLIDO_ALUMNO 21
#define TAMANIO_EMAIL_ALUMNO 101
#define TAMANIO_FECHA_ALUMNO_CURSO 9
#define TAMANIO_DESCRIPCION_ALUMNO_CURSO 51
#define TAMANIO_CODIGO_SISTPLAN_STRING 20

// CONSTANTES EXITOS

// CONSTANTES ERRORES
const int ERROR_CODIGO_ALUMNO_VACIO = -127;
const int ERROR_NO_EXISTE_SISTEMA_O_PLANETA = -126;
const int ALUMNO_NO_PROVIENE_SISTEMA = -125;
const int ALUMNO_NO_PROVIENE_PLANETA = -124;


typedef struct alumno {
	char codigo[TAMANIO_CODIGO_ALUMNO];
	char nombre[TAMANIO_NOMBRE_ALUMNO];
	char apellido[TAMANIO_APELLIDO_ALUMNO];
	char email[TAMANIO_EMAIL_ALUMNO];
	long codigoSistemaOrigen;
	long codigoPlanetaOrigen;
} Alumno;

typedef struct respuestasAlumnoPorCurso {
	long codigoAlumno;
	// Formato YYYYMMDD
	char fecha[TAMANIO_FECHA_ALUMNO_CURSO];
	char descripcionCurso[TAMANIO_DESCRIPCION_ALUMNO_CURSO];
	unsigned int respuestasTendientesLuz;
	unsigned int respuestasTendientesOscuridad;
} RespuestasAlumnoPorCurso;

// FUNCIONES PEDIDAS


// FUNCIONES AUXILIARES
void leerUnAlumnoTxt(Alumno * alumno, FILE * archivoAbierto);
void imprimirAlumnoEnTxt(FILE	* archivo, Alumno alumno);
void inicializarUnAlumno(Alumno * alumno);
void imprimirAlumnoEnTxt(FILE	* archivo, Alumno alumno);
void mostrarAlumno(Alumno alumno);
void constructorAlumno(char codigo[], char nombre[], char apellido[], char email[], long sistema, long planeta);



// FUNCIONES TRUCHAS

int main(int argc, char const *argv[]) {
	FILE * fp, * fpSP;
	char dEnc;
	Alumno unAlumno;
	fp = fopen(ALUMNOS_TXT, "r");
/*
	inicializarUnAlumno(&unAlumno);
//	unAlumno.codigoSistemaOrigen = 2222;
	imprimirAlumnoEnTxt(fp, unAlumno);
*/
	leerUnAlumnoTxt(&unAlumno, fp);
	leerUnAlumnoTxt(&unAlumno, fp);

	mostrarAlumno(unAlumno);

	fclose(fp);
	return 0;
}

void leerArchivoActualizacionAlumnos(Alumno alumnos[], long * tope, FILE * alumnosActualizados) {
	char c;
	long i = 0;
	while(!feof(alumnosActualizados)) {
		leerUnAlumnoTxt(alumnos+i, alumnosActualizados;);
		if (!hayErrorEnDatosAlumno(alumno[i])) {
			i++;
		}
	}
	*tope = int;
}

bool hayErrorEnDatosAlumno(Alumno alumno) {
	return false;
}

void leerUnAlumnoTxt(Alumno * alumno, FILE * archivoAbierto) {
	int i;
	char c, codigo[TAMANIO_CODIGO_SISTPLAN_STRING];

	// Leer Codigo
	i = 0;
	while ((c = fgetc(archivoAbierto)) != SEPARADOR_ALUMNOS_TXT) {
		alumno->codigo[i] = c;
		i++;
	}
	alumno->codigo[i] = '\0';
	// Leer Nombre
	i = 0;
	while ((c = fgetc(archivoAbierto)) != SEPARADOR_ALUMNOS_TXT) {
		alumno->nombre[i] = c;
		i++;
	}
	alumno->nombre[i] = '\0';
	// Leer Apellido
	i = 0;
	while ((c = fgetc(archivoAbierto)) != SEPARADOR_ALUMNOS_TXT) {
		alumno->apellido[i] = c;
		i++;
	}
	alumno->apellido[i] = '\0';
	// Leer Email
	i = 0;
	while ((c = fgetc(archivoAbierto)) != SEPARADOR_ALUMNOS_TXT) {
		alumno->email[i] = c;
		i++;
	}
	alumno->email[i] = '\0';
	// Leer Codigo Sistema
	i = 0;
	while ((c = fgetc(archivoAbierto)) != SEPARADOR_ALUMNOS_TXT) {
		codigo[i] = c;
		i++;
	}
	codigo[i] = '\0';
	alumno->codigoSistemaOrigen = (strcmp(codigo, "") == 0) ? ALUMNO_NO_PROVIENE_SISTEMA : atol(codigo);
	// Leer Codigo Planeta
	i = 0;
	while ((c = fgetc(archivoAbierto)) != '\n') {
		codigo[i] = c;
		i++;
	}
	codigo[i] = '\0';
	alumno->codigoPlanetaOrigen = (strcmp(codigo, "") == 0) ? ALUMNO_NO_PROVIENE_PLANETA : atol(codigo);
}

void inicializarUnAlumno(Alumno * alumno) {
	strcpy(alumno->codigo, "abc");
	strcpy(alumno->nombre, "rodrigo");
	strcpy(alumno->apellido, "mistogun");
	strcpy(alumno->email, "sceptile@hotmail.com");
	alumno->codigoSistemaOrigen = ALUMNO_NO_PROVIENE_SISTEMA;
	alumno->codigoPlanetaOrigen = 28;
}

void imprimirAlumnoEnTxt(FILE	* archivo, Alumno alumno) {
	fprintf(archivo, "%s", alumno.codigo);
	fprintf(archivo, "%c", SEPARADOR_ALUMNOS_TXT);
	fprintf(archivo, "%s", alumno.nombre);
	fprintf(archivo, "%c", SEPARADOR_ALUMNOS_TXT);
	fprintf(archivo, "%s", alumno.apellido);
	fprintf(archivo, "%c", SEPARADOR_ALUMNOS_TXT);
	fprintf(archivo, "%s", alumno.email);
	fprintf(archivo, "%c", SEPARADOR_ALUMNOS_TXT);
	fprintf(archivo, "%ld", alumno.codigoSistemaOrigen);
	fprintf(archivo, "%c", SEPARADOR_ALUMNOS_TXT);
	fprintf(archivo, "%ld", alumno.codigoPlanetaOrigen);
	fprintf(archivo, "\n");
}

void constructorAlumno(char codigo[], char nombre[], char apellido[], char email[], long sistema, long planeta) {
	strcpy(alumno->codigo, codigo);
	strcpy(alumno->nombre, nombre);
	strcpy(alumno->apellido, apellido);
	strcpy(alumno->email, email);
	alumno->codigoSistemaOrigen = sistema;
	alumno->codigoPlanetaOrigen = planeta;
}

void mostrarAlumno(Alumno alumno) {
	printf("%s", alumno.codigo);
	printf("%c", SEPARADOR_ALUMNOS_TXT);
	printf("%s", alumno.nombre);
	printf("%c", SEPARADOR_ALUMNOS_TXT);
	printf("%s", alumno.apellido);
	printf("%c", SEPARADOR_ALUMNOS_TXT);
	printf("%s", alumno.email);
	printf("%c", SEPARADOR_ALUMNOS_TXT);
	printf("%ld", alumno.codigoSistemaOrigen);
	printf("%c", SEPARADOR_ALUMNOS_TXT);
	printf("%ld", alumno.codigoPlanetaOrigen);
	printf("\n");
}
