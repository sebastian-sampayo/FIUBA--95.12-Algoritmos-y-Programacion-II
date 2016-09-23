// ------------------------------------------------------------------------- //
// Facultad de Ingenieria de la Universidad de Buenos Aires
// Algoritmos y Programacion II
// 1er Cuatrimestre de 2015
// Trabajo Practico 0: Programacion en C++
// Demodulacion de senal FM
//  
// arguments.cc
// Funciones a llamar para cada opcion posible de la aplicacion
// ------------------------------------------------------------------------- //

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include "arguments.h"
#include "types.h"

using namespace std;



istream *iss;
ostream *oss;
fstream ifs;
fstream ofs;
format_option_t format_option;

// Nombres de los argumentos de la opcion "--format"
string description_format_option[] = {
  
  FORMAT_TEXT,
  FORMAT_U8
  
};

void
opt_input(string const &arg)
{
  // Si el nombre del archivos es "-", usaremos la entrada
  // estandar. De lo contrario, abrimos un archivo en modo
  // de lectura.
  //
  if (arg == "-") {
    iss = &cin;    // Establezco la entrada estandar cin como flujo de entrada
  }
  else {
    ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
                    // sequence of characters (i.e., a C-string) representing
                    // the current value of the string object.
    iss = &ifs;
  }

  // Verificamos que el stream este OK.
  //
  if (!iss->good()) {
    cerr << "Cannot open "
         << arg
         << "."
         << endl;
    exit(1);
  }
}

void
opt_output(string const &arg)
{
  // Si el nombre del archivos es "-", usaremos la salida
  // estandar. De lo contrario, abrimos un archivo en modo
  // de escritura.
  //
  if (arg == "-") {
    oss = &cout;  // Establezco la salida estandar cout como flujo de salida
  } else {
    ofs.open(arg.c_str(), ios::out);
    oss = &ofs;
  }

  // Verificamos que el stream este OK.
  //
  if (!oss->good()) {
    cerr << "Cannot open "
         << arg
         << "."
         << endl;
    exit(1);    // EXIT: Terminacion del programa en su totalidad
  }
}

void
opt_format(string const &arg)
{
  size_t i;
  // Recorremos diccionario de argumentos hasta encontrar uno que coincida
  for(i=0; i < FORMAT_OPTIONS; i++) {
    if(arg == description_format_option[i]) {
      format_option = (format_option_t)i;  // Casteo
      break;
    }
  }
  // Si recorrio todo el diccionario, el argumento no esta implementado
  if (i == FORMAT_OPTIONS) {
    cerr << "Unknown format" << endl;
    exit(1);
  }
}
