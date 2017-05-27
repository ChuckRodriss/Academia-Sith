#include "sistemasyplanetas.h"

// CONSTANTES
const char CONTADOR_SISTPLAN_TXT[] = "contadorsistplan.txt";
const char SISTEMAS_PLANETAS_DAT[] = "sistyplan.dat";
const char SISTEMA = 'S';
const char PLANETA = 'P';
const long INICIALIZAR_CONTADOR = 1;
const int ERROR_DESCRIPCION_SISTEMA_PLANETA_VACIA = -128;
const int SISTEMA_PLANETA_AGREGADO_CORRECTAMENTE = 127;

// DEFINICIONES PEDIDAS
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


int agregarSistema(char descripcion[]) {
	return agregarSistemaOPlaneta(descripcion, SISTEMA);
}

int agregarPlaneta(char descripcion[]) {
	return agregarSistemaOPlaneta(descripcion, PLANETA);
}

// DEFINICIONES AUXILIARES
long cantidadSistemasPlanetas() {
	long contador;
	FILE * archivoSistemasPlanetas = fopen(CONTADOR_SISTPLAN_TXT, "r");
	contador = leerLongDesdeTxt(archivoSistemasPlanetas);
	fclose(archivoSistemasPlanetas);
	return contador;
}

long leerLongDesdeTxt(FILE * archivoAbierto) {
	long longLeido;
	fscanf(archivoAbierto, "%ld", &longLeido);
	return longLeido;
}

SistemaPlaneta busquedaBinSistemasPlanetas(long codigoBuscado) {
	// Ordenado Descendentemente
	FILE * archivo = fopen(SISTEMAS_PLANETAS_DAT, "r");
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

int agregarSistemaOPlaneta(char descripcion[], char tipo) {
	long total;
	SistemaPlaneta nuevo;
	FILE * archivoSistemasPlanetas = fopen(SISTEMAS_PLANETAS_DAT, "a");

	if (strcmp(descripcion,"") == 0) {
		return ERROR_DESCRIPCION_SISTEMA_PLANETA_VACIA;
	}

	total = incrementarContadorSistPlan();

	nuevo.codigo = total;
	strcpy(nuevo.descripcion, descripcion);
	nuevo.tipo = tipo;

	fwrite(&nuevo, sizeof(SistemaPlaneta), 1, archivoSistemasPlanetas);
	fclose(archivoSistemasPlanetas);
	return SISTEMA_PLANETA_AGREGADO_CORRECTAMENTE;
}

void imprimirUnSistemaPlaneta(SistemaPlaneta sistemaPlaneta) {
	printf("Codigo: %ld\n", sistemaPlaneta.codigo);
	printf("descripcion: %s\n", sistemaPlaneta.descripcion);
	printf("Tipo: %s\n", (sistemaPlaneta.tipo == 'S') ? "Sistema" : "Planeta");
}
