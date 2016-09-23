// ------------------------------------------------------------------------- //
// Facultad de Ingenieria de la Universidad de Buenos Aires
// Algoritmos y Programacion II
// 1er Cuatrimestre de 2015
// Trabajo Practico 0: Programacion en C++
// Demodulacion de senal FM
// 
// types.h
// Tipos definidos para el proposito de la aplicacion
//  - Opciones posibles de formato de entrada y salida.
// ------------------------------------------------------------------------- //

#ifndef _TYPES_H_INCLUDED_
#define _TYPES_H_INCLUDED_

#include <iostream>

// Opciones de formato de entrada y salida
typedef enum {
        
  FORMAT_OPTION_TEXT = 0, // (Real, Imaginario)
  FORMAT_OPTION_U8 = 1 // Binario: Real8bitsImag8bits
        
} format_option_t;

#endif
