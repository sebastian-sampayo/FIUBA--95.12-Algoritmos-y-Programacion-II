// ------------------------------------------------------------------------- //
// Facultad de Ingenieria de la Universidad de Buenos Aires
// Algoritmos y Programacion II
// 1er Cuatrimestre de 2015
// Trabajo Practico 0: Programacion en C++
// Demodulacion de senal FM
// 
// arguments.h
// Funciones a llamar para cada opcion posible de la aplicacion
// Nombres de los argumentos de la opcion "--format"
// ------------------------------------------------------------------------- //

#ifndef _ARGUMENTS_H_INCLUDED_
#define _ARGUMENTS_H_INCLUDED_

#include <iostream>

#define FORMAT_OPTIONS 2
#define FORMAT_TEXT "txt"
#define FORMAT_U8 "U8"

void opt_input(std::string const &);
void opt_output(std::string const &);
void opt_format(std::string const &);

#endif
