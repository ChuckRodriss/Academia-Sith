#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "./mylibs/sistemasyplanetas.h"

// CONSTANTES
const char SEPARADOR_ALUMNOS_TXT = ';';

// CONSTANTES ARCHIVOS
const char ALUMNOS_TXT[] = "alumnos.txt";
const char ACTUALIZACION_ALUMNOS_TXT[] = "alumnos.txt";


// CONSTANTES TAMANIOS VECTORES
#define CORRECTOR_TAMANIO_VECTOR_A_STRING = 1
#define TAMANIO_CODIGO_ALUMNO 11
#define TAMANIO_NOMBRE_ALUMNO 21
#define TAMANIO_APELLIDO_ALUMNO 21
#define TAMANIO_EMAIL_ALUMNO 101
#define TAMANIO_MAYOR_STRING_ALUMNO 101

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
Alumno constructorAlumno(char codigo[], char nombre[], char apellido[], char email[], long sistema, long planeta);
int hayErrorEnDatosAlumno(Alumno alumno);
void leerArchivoActualizacionAlumnos(Alumno alumnos[], long * tope, FILE * alumnosActualizados);
bool cargarAtributoAlumnoTxt(char atributo[], FILE * archivoAbierto);

/**
	*
	*
	*
	*
	*
*/
int main(int argc, char const *argv[]) {
	FILE * fp, * fpSP;
	char dEnc;
	Alumno unAlumno, vectorA[100];
	long tope;
	fp = fopen(ALUMNOS_TXT, "r");

	leerArchivoActualizacionAlumnos(vectorA, &tope, fp);
	for (long i = 0; i < tope; i++) {
		mostrarAlumno(vectorA[i]);
	}

	printf("%d\n", FOPEN_MAX );
	fclose(fp);
	return 0;
}

void leerArchivoActualizacionAlumnos(Alumno alumnos[], long * tope, FILE * alumnosActualizados) {
	char c;
	long i = 0;
	while(!feof(alumnosActualizados)) {
		leerUnAlumnoTxt(alumnos+i, alumnosActualizados);
		if (!hayErrorEnDatosAlumno(alumnos[i])) {
//			mostrarAlumno(alumnos[i]);
			i++;
		}
	}
	*tope = i;
}

int hayErrorEnDatosAlumno(Alumno alumno) {
	if (strcmp(alumno.codigo, "") == 0) return ERROR_CODIGO_ALUMNO_VACIO;

	return false;
}

void leerUnAlumnoTxt(Alumno * alumno, FILE * archivoAbierto) {
	int i;
	char atributo[TAMANIO_MAYOR_STRING_ALUMNO];

	// Controlo que el archivo no esté terminado
	if (!cargarAtributoAlumnoTxt(atributo, archivoAbierto)) {
		return;
	}
	strcpy(alumno->codigo, atributo);
	cargarAtributoAlumnoTxt(atributo, archivoAbierto);
	strcpy(alumno->nombre, atributo);
	cargarAtributoAlumnoTxt(atributo, archivoAbierto);
	strcpy(alumno->apellido, atributo);
	cargarAtributoAlumnoTxt(atributo, archivoAbierto);
	strcpy(alumno->email, atributo);
	// Leer Codigo Sistema
	cargarAtributoAlumnoTxt(atributo, archivoAbierto);
	alumno->codigoSistemaOrigen = (strcmp(atributo, "") == 0) ? ALUMNO_NO_PROVIENE_SISTEMA : atol(atributo);
	// Leer Codigo Planeta
	cargarAtributoAlumnoTxt(atributo, archivoAbierto);
	alumno->codigoPlanetaOrigen = (strcmp(atributo, "") == 0) ? ALUMNO_NO_PROVIENE_PLANETA : atol(atributo);
}

bool cargarAtributoAlumnoTxt(char atributo[], FILE * archivoAbierto) {
	int i = 0;
	char c;
	while ((c = fgetc(archivoAbierto)) != SEPARADOR_ALUMNOS_TXT && c != '\n') {
		// TERMINA EL ARCHIVO
		if (feof(archivoAbierto)) return false;
		atributo[i] = c;
		i++;
	}
	atributo[i] = '\0';
	return true;
}

void inicializarUnAlumno(Alumno * alumno) {
	*alumno = constructorAlumno("abc", "rodrigo", "mistogun", "sceptile@hotmail.com", ALUMNO_NO_PROVIENE_SISTEMA, 28);
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

Alumno constructorAlumno(char codigo[], char nombre[], char apellido[], char email[], long sistema, long planeta) {
	Alumno alumno;
	strcpy(alumno.codigo, codigo);
	strcpy(alumno.nombre, nombre);
	strcpy(alumno.apellido, apellido);
	strcpy(alumno.email, email);
	alumno.codigoSistemaOrigen = sistema;
	alumno.codigoPlanetaOrigen = planeta;
	return alumno;
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
