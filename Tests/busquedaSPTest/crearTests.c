#include<stdio.h>
#include<string.h>

// CONSTANTES
const char SISTEMA = 'S';
const char PLANETA = 'P';
const char SEPARADOR_ALUMNOS_TXT = ';';
const long INICIALIZAR_CONTADOR = 0;

// CONSTANTES ARCHIVOS
const char ALUMNOS_TXT[] = "alumnos.txt";
const char CONTADOR_SISTPLAN_TXT[] = "contadorsistplan.txt";
const char SISTEMAS_PLANETAS_DAT[] = "sistyplan.dat";

// CONSTANTES TAMANIOS VECTORES
#define CORRECTOR_TAMANIO_VECTOR_A_STRING = 1
#define TAMANIO_DESCRIPCION_SISTPLAN 51
#define TAMANIO_CODIGO_ALUMNO 11
#define TAMANIO_NOMBRE_ALUMNO 21
#define TAMANIO_APELLIDO_ALUMNO 21
#define TAMANIO_EMAIL_ALUMNO 101
#define TAMANIO_FECHA_ALUMNO_CURSO 9
#define TAMANIO_DESCRIPCION_ALUMNO_CURSO 51

// CONSTANTES EXITOS
const int AGREGADO_CORRECTAMENTE = 127;

// CONSTANTES ERRORES
const int ERROR_DESCRIPCION_VACIA = -128;
const int ERROR_CODIGO_ALUMNO_VACIO = -127;
const int ERROR_NO_EXISTE_SISTEMA_O_PLANETA = -126;


typedef struct sistemaPlaneta {
	long codigo;
	char descripcion[TAMANIO_DESCRIPCION_SISTPLAN];
	char tipo;
} SistemaPlaneta;

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
int agregarSistema(char descripcion[]);
int agregarPlaneta(char descripcion[]);
void consultarSistemasYPlanetas();


// FUNCIONES AUXILIARES
void imprimirUnSistemaPlaneta(SistemaPlaneta sistemaPlaneta);
int agregarSistemaOPlaneta(char descripcion[], char tipo);
void imprimirAlumnoEnTxt(FILE	* archivo, Alumno alumno);
void inicializarUnAlumno(Alumno * alumno);
void imprimirAlumnoEnTxt(FILE	* archivo, Alumno alumno);
long incrementarContadorSistPlan();
SistemaPlaneta busquedaBinSistemasPlanetas(FILE * archivo, long codigoBuscado);
long cantidadSistemasPlanetas();

// FUNCIONES TRUCHAS

int main(int argc, char const *argv[]) {
	FILE * fp, * fpSP;
	char dEnc;
	Alumno unAlumno;
	SistemaPlaneta unSP;

	agregarSistema("uno");
	agregarSistema("dos");
	agregarPlaneta("tres");
	agregarSistema("cuatro");
	agregarPlaneta("cinco");
	agregarPlaneta("seis");
	agregarPlaneta("siete");
	agregarSistema("ocho");
	agregarPlaneta("nueve");
	agregarSistema("diez");
	agregarSistema("once");

	consultarSistemasYPlanetas();

	return 0;
}

void consultarSistemasYPlanetas() {
	FILE * archivo = fopen(SISTEMAS_PLANETAS_DAT, "r");
	long tope = cantidadSistemasPlanetas();
	SistemaPlaneta sistemasYPlanetas[tope];
	fread(sistemasYPlanetas, sizeof(SistemaPlaneta), tope, archivo);

	for (long i = 0; i < tope; i++) {
		imprimirUnSistemaPlaneta(sistemasYPlanetas[i]);
	}

	fclose(archivo);
}

void imprimirUnSistemaPlaneta(SistemaPlaneta sistemaPlaneta) {
	printf("Codigo: %ld\n", sistemaPlaneta.codigo);
	printf("descripcion: %s\n", sistemaPlaneta.descripcion);
	printf("Tipo: %s\n", (sistemaPlaneta.tipo == 'S') ? "Sistema" : "Planeta");
}

int agregarSistema(char descripcion[]) {
	return agregarSistemaOPlaneta(descripcion, SISTEMA);
}

int agregarPlaneta(char descripcion[]) {
	return agregarSistemaOPlaneta(descripcion, PLANETA);
}

int agregarSistemaOPlaneta(char descripcion[], char tipo) {
	long total;
	SistemaPlaneta nuevo;
	FILE * archivoSistemasPlanetas = fopen(SISTEMAS_PLANETAS_DAT, "a");

	if (strcmp(descripcion,"") == 0) {
		return ERROR_DESCRIPCION_VACIA;
	}

	total = incrementarContadorSistPlan();

	nuevo.codigo = total;
	strcpy(nuevo.descripcion, descripcion);
	nuevo.tipo = tipo;

	fwrite(&nuevo, sizeof(SistemaPlaneta), 1, archivoSistemasPlanetas);
	fclose(archivoSistemasPlanetas);
	return AGREGADO_CORRECTAMENTE;
}

SistemaPlaneta busquedaBinSistemasPlanetas(FILE * archivo, long codigoBuscado) {
	// Ordenado Descendentemente
	long total = cantidadSistemasPlanetas();
	long inicio = 0, fin = total-1, centro, codigoActual;
	SistemaPlaneta sistemasYPlanetas[total];

	fread(sistemasYPlanetas, sizeof(SistemaPlaneta), total, archivo);

	while (inicio <= fin) {
		centro = (inicio + fin) / 2;
		codigoActual = sistemasYPlanetas[centro].codigo;

		if (codigoActual < codigoBuscado)
			inicio = centro + 1;
		if (codigoActual > codigoBuscado)
			fin = centro - 1;
		if (codigoActual == codigoBuscado) {
			return sistemasYPlanetas[centro];
		}
	}

	return sistemasYPlanetas[centro];
}

void reimprimirSistemasPlanetasDat(SistemaPlaneta sistemasYPlanetas[]) {
	long i = cantidadSistemasPlanetas() - 1;
	FILE * archivo;
	archivo = fopen(SISTEMAS_PLANETAS_DAT, "w");
	fclose(archivo);
	archivo = fopen(SISTEMAS_PLANETAS_DAT, "a");

	for (i; i <= 0; i--) {
		fwrite(sistemasYPlanetas+i, sizeof(SistemaPlaneta), 1, archivo);
	}
	fclose(archivo);
}

long incrementarContadorSistPlan() {
	long contador;
	FILE * archivo;

	archivo = fopen(CONTADOR_SISTPLAN_TXT, "r");
	if (archivo == NULL) {
		contador = INICIALIZAR_CONTADOR;
	} else {
		fscanf(archivo, "%ld", &contador);
		contador++;
		fclose(archivo);
	}

	archivo = fopen(CONTADOR_SISTPLAN_TXT, "w");
	fprintf(archivo, "%ld", contador);
	fclose(archivo);

	return contador;
}

long leerLongDesdeTxt(FILE * archivoAbierto) {
	long longLeido;
	fscanf(archivoAbierto, "%ld", &longLeido);
	return longLeido;
}

long cantidadSistemasPlanetas() {
	long contador;
	FILE * archivoSistemasPlanetas = fopen(CONTADOR_SISTPLAN_TXT, "r");
	contador = leerLongDesdeTxt(archivoSistemasPlanetas);
	fclose(archivoSistemasPlanetas);
	return contador;
}



void inicializarUnAlumno(Alumno * alumno) {
	strcpy(alumno->codigo, "abc");
	strcpy(alumno->nombre, "rodrigo");
	strcpy(alumno->apellido, "mistogun");
	strcpy(alumno->email, "sceptile@hotmail.com");
	alumno->codigoSistemaOrigen = -1;
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
