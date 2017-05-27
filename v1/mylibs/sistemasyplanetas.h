#define TAMANIO_DESCRIPCION_SISTPLAN 51

#ifndef SISTEMASYPLANETAS_H
#define SISTEMASYPLANETAS_H

#include<stdio.h>
#include<string.h>

typedef struct sistemaPlaneta {
	long codigo;
	char descripcion[TAMANIO_DESCRIPCION_SISTPLAN];
	char tipo;
} SistemaPlaneta;

// DECLARACIONES PEDIDAS
int agregarSistema(char descripcion[]);
int agregarPlaneta(char descripcion[]);
void consultarSistemasYPlanetas();

// DECLARACIONES AUXILIARES
long cantidadSistemasPlanetas();
long leerLongDesdeTxt(FILE * archivoAbierto);
SistemaPlaneta busquedaBinSistemasPlanetas(long codigoBuscado);
long incrementarContadorSistPlan();
int agregarSistemaOPlaneta(char descripcion[], char tipo);
void imprimirUnSistemaPlaneta(SistemaPlaneta sistemaPlaneta);

#endif
