#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "./mylibs/sistemasyplanetas.h"

// CONSTANTES
const char SEPARADOR_ALUMNOS_TXT = ';';
const int MINIMO_PORCENTAJE_ACEPTADO = 70;

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

const long MAX = 100;

// CONSTANTES EXITOS

// CONSTANTES ERRORES
const int ERROR_CODIGO_ALUMNO_VACIO = -127;
const int ERROR_NO_EXISTE_SISTEMA_O_PLANETA = -126;
const int ALUMNO_NO_PROVIENE_SISTEMA = -125;
const int ALUMNO_NO_PROVIENE_PLANETA = -124;
const int ERROR_NO_PUEDE_PROVENIR_DE_PLANETA_Y_SISTEMA = -123;


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
	char fecha[TAMANIO_FECHA_ALUMNO_CURSO];	// Formato YYYYMMDD
	char descripcionCurso[TAMANIO_DESCRIPCION_ALUMNO_CURSO];
	unsigned int respuestasTendientesLuz;
	unsigned int respuestasTendientesOscuridad;
} RespuestasAlumnoPorCurso;

// FUNCIONES PEDIDAS
void consultarAlumno(char codigo[]);
void actualizarAlumnos(char nombreDeArchivoActualizaciones[]);

// FUNCIONES AUXILIARES TOP
void cargarVectorDesdeAlumnosTxt(Alumno alumnos[], long * tope, FILE * alumnosActualizados);
bool busquedaBinariaAlumnos(Alumno alumnos[], long tope, char codigoBuscado[], long * posicionFinal);

// FUNCIONES AUXILIARES MEDIUM
int hayErrorEnDatosAlumno(Alumno alumno);
int noExisteSistemaPlanetaDelAlumno(Alumno alumno);
void insertarAlumno(Alumno alumno, long posicion, Alumno alumnado[], long * tope);
void imprimirAlumnadoEnTxt(Alumno alumnado[], long tope, FILE * alumnosTxt);

// FUNCIONES AUXILIARES DOWN
void leerUnAlumnoTxt(Alumno * alumno, FILE * archivoAbierto);
void imprimirAlumno(Alumno alumno);
void imprimirAlumnoEnTxt(Alumno alumno, FILE	* archivo);
void cargarAtributoAlumnoTxt(char atributo[], FILE * archivoAbierto);
bool sistemaPlanetaEstaDentroDelMargen(long codigo);
Alumno constructorAlumno(char codigo[], char nombre[], char apellido[], char email[], long sistema, long planeta);
void copiarAlumno(Alumno * destino, Alumno origen);


// FUNCIONES TRUCHAS
void inicializarUnAlumno(Alumno * alumno);

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

	actualizarAlumnos("actualizaciones.txt");

	fclose(fp);
	return 0;
}

void actualizarAlumnos(char nombreDeArchivoActualizaciones[]) {
	bool seEncontro;
	Alumno alumnosActualizaciones[MAX], alumnado[MAX];
	long topeActualizaciones, topeAlumnado, posicionAlumnoBuscado;
	FILE * archivoActualizaciones = fopen(nombreDeArchivoActualizaciones, "r");
	FILE * archivoAlumnos = fopen(ALUMNOS_TXT, "r");

	cargarVectorDesdeAlumnosTxt(alumnosActualizaciones, &topeActualizaciones, archivoActualizaciones);
	cargarVectorDesdeAlumnosTxt(alumnado, &topeAlumnado, archivoAlumnos);
	fclose(archivoAlumnos);
	fclose(archivoActualizaciones);

	for (long i = 0; i < topeActualizaciones; i++) {
		seEncontro = busquedaBinariaAlumnos(alumnado, topeAlumnado, alumnosActualizaciones[i].codigo, &posicionAlumnoBuscado);
		if (seEncontro) {
			copiarAlumno(&alumnado[posicionAlumnoBuscado], alumnosActualizaciones[i]);
		} else {
			insertarAlumno(alumnosActualizaciones[i], posicionAlumnoBuscado, alumnado, &topeAlumnado);
		}
	}

	// Limpiar archivo
	archivoAlumnos = fopen(ALUMNOS_TXT, "w");
	fclose(archivoAlumnos);

	archivoAlumnos = fopen(ALUMNOS_TXT, "a");
	imprimirAlumnadoEnTxt(alumnado, topeAlumnado, archivoAlumnos);
	fclose(archivoAlumnos);
}



void insertarAlumno(Alumno alumno, long posicion, Alumno alumnado[], long * tope) {
	long i = *tope -1;
	for (i; i >= posicion; i--) {
		copiarAlumno(&alumnado[i+1], alumnado[i]);
	}
	copiarAlumno(&alumnado[i+1], alumno);
	(*tope)++;
}

void copiarAlumno(Alumno * destino, Alumno origen) {
	*destino = origen;
}


void consultarAlumno(char codigo[]) {
	FILE * alumnosTxt = fopen(ALUMNOS_TXT, "r");
	Alumno alumnos[MAX];
	long tope, posicionCodigoBuscado;
	bool seEncontro;

	cargarVectorDesdeAlumnosTxt(alumnos, &tope, alumnosTxt);
	seEncontro = busquedaBinariaAlumnos(alumnos, tope, codigo, &posicionCodigoBuscado);
	if (seEncontro) {
		imprimirAlumno(alumnos[posicionCodigoBuscado]);
	} else {
		printf("%s\n", "El codigo no pertenece a ningun alumno.");
	}

	fclose(alumnosTxt);
}


bool busquedaBinariaAlumnos(Alumno alumnos[], long tope, char codigoBuscado[], long * posicionCodigoBuscado) {
	char codigoActual[TAMANIO_CODIGO_ALUMNO];
	long inicio = 0, fin = tope-1, centro;
	long correctorPosicionFinal = 0;

	while (inicio <= fin) {
		centro = (inicio + fin) / 2;
		strcpy(codigoActual, alumnos[centro].codigo);

		if (strcmp(codigoActual, codigoBuscado) < 0) {
			inicio = centro + 1;
			correctorPosicionFinal = 1;
		} else if (strcmp(codigoActual, codigoBuscado) > 0) {
			fin = centro - 1;
			correctorPosicionFinal = 0;
		} else if (strcmp(codigoActual, codigoBuscado) == 0) {
			*posicionCodigoBuscado = centro;
			return true;
		}
	}
	*posicionCodigoBuscado = centro + correctorPosicionFinal;
	return false;
}

void cargarVectorDesdeAlumnosTxt(Alumno alumnos[], long * tope, FILE * archivoAlumnosTxt) {
	char c;
	long i = 0;
	while((c = fgetc(archivoAlumnosTxt)) != EOF) {
		ungetc(c, archivoAlumnosTxt);
		leerUnAlumnoTxt(alumnos+i, archivoAlumnosTxt);
		if (!hayErrorEnDatosAlumno(alumnos[i])) {
			i++;
		}
	}
	*tope = i;
}

int hayErrorEnDatosAlumno(Alumno alumno) {
	int error;
	// Codigo vacio
	if (strcmp(alumno.codigo, "") == 0) return ERROR_CODIGO_ALUMNO_VACIO;
	// Planeta no existente
	if ((error = noExisteSistemaPlanetaDelAlumno(alumno))) return error;
	return false;
}

int noExisteSistemaPlanetaDelAlumno(Alumno alumno) {
	if (sistemaPlanetaEstaDentroDelMargen(alumno.codigoSistemaOrigen)) {
		if (sistemaPlanetaEstaDentroDelMargen(alumno.codigoPlanetaOrigen)) {
			return ERROR_NO_PUEDE_PROVENIR_DE_PLANETA_Y_SISTEMA;
		}
	} else {
		if (!sistemaPlanetaEstaDentroDelMargen(alumno.codigoPlanetaOrigen)) {
			return ERROR_NO_EXISTE_SISTEMA_O_PLANETA;
		}
	}
	return false;
}

bool sistemaPlanetaEstaDentroDelMargen(long codigo) {
	return codigo >= 1 && codigo <= consultarCantidadSistemasPlanetas();
}

void leerUnAlumnoTxt(Alumno * alumno, FILE * archivoAbierto) {
	int i;
	char atributo[TAMANIO_MAYOR_STRING_ALUMNO];

	// Controlo que el archivo no esté terminado
	cargarAtributoAlumnoTxt(atributo, archivoAbierto);
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

void cargarAtributoAlumnoTxt(char atributo[], FILE * archivoAbierto) {
	int i = 0;
	char c;
	while ((c = fgetc(archivoAbierto)) != SEPARADOR_ALUMNOS_TXT && c != '\n') {
		atributo[i] = c;
		i++;
	}
	atributo[i] = '\0';
}

void inicializarUnAlumno(Alumno * alumno) {
	*alumno = constructorAlumno("abc", "rodrigo", "mistogun", "sceptile@hotmail.com", ALUMNO_NO_PROVIENE_SISTEMA, 28);
}

void imprimirAlumnoEnTxt(Alumno alumno, FILE	* archivo) {
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

void imprimirAlumnadoEnTxt(Alumno alumnado[], long tope, FILE * alumnosTxtAbierto) {
	for (long i = 0; i < tope; i++) {
		imprimirAlumnoEnTxt(alumnado[i], alumnosTxtAbierto);
	}
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

void imprimirAlumno(Alumno alumno) {
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
