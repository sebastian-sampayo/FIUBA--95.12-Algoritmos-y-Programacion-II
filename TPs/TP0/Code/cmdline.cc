// cmdline - procesamiento de opciones en la linea de comando.
//
// $Date: 2012/09/14 13:08:33 $
//
#include <string>
#include <cstdlib>
#include <iostream>

#include "cmdline.h"

using namespace std;



cmdline::cmdline()
{
}

cmdline::cmdline(option_t *table) : option_table(table)
{
  /* 
  - Lo mismo que hacer:

  option_table = table;

  Siendo "option_table" un atributo de la clase cmdline
  y table un puntero a objeto o struct de "option_t".
  
  Se estaria contruyendo una instancia de la clase cmdline
  cargandole los datos que se hayan en table (la table con
  las opciones, ver el codigo en main.cc)

  */
}

void
cmdline::parse(int argc, char * const argv[])
{
#define END_OF_OPTIONS(p)       \
  ((p)->short_name == 0   \
   && (p)->long_name == 0 \
   && (p)->parse == 0)

  // Primer pasada por la secuencia de opciones: marcamos 
  // todas las opciones, como no procesadas. Ver codigo de
  // abajo.
  //
  for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op)
    op->flags &= ~OPT_SEEN;

  // Recorremos el arreglo argv. En cada paso, vemos
  // si se trata de una opcion corta, o larga. Luego,
  // llamamos a la funcion de parseo correspondiente.
  //
  for (int i = 1; i < argc; ++i) {
    // Todos los parametros de este programa deben
    // pasarse en forma de opciones. Encontrar un
    // parametro no-opcion es un error.
    //
    if (argv[i][0] != '-') {
      cerr << "Invalid non-option argument: "
           << argv[i]
           << endl;
      exit(1);
    }

    // Usamos "--" para marcar el fin de las
    // opciones; todo los argumentos que puedan
    // estar a continuacion no son interpretados
    // como opciones.
    //
    if (argv[i][1] == '-'
        && argv[i][2] == 0)
      break;

    // Finalmente, vemos si se trata o no de una
    // opcion larga; y llamamos al metodo que se
    // encarga de cada caso.
    //
    if (argv[i][1] == '-')
      i += do_long_opt(&argv[i][2], argv[i + 1]);
    else
      i += do_short_opt(&argv[i][1], argv[i + 1]);
  }

  // Segunda pasada: procesamos aquellas opciones que,
  // (1) no hayan figurado explicitamente en la linea 
  // de comandos, y (2) tengan valor por defecto.
  //
  for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op) {
#define OPTION_NAME(op) \
  (op->short_name ? op->short_name : op->long_name)
    if (op->flags & OPT_SEEN)
      continue;
    if (op->flags & OPT_MANDATORY) {
      cerr << "Option "
           << "-"
           << OPTION_NAME(op)
           << " is mandatory."
           << "\n";
      exit(1);
    }
    if (op->def_value == 0)
      continue;
    op->parse(string(op->def_value));
  }
}

int
cmdline::do_long_opt(const char *opt, const char *arg)
{
  // Recorremos la tabla de opciones, y buscamos la
  // entrada larga que se corresponda con la opcion de 
  // linea de comandos. De no encontrarse, indicamos el
  // error.
  //
  for (option_t *op = option_table; op->long_name != 0; ++op) {
    if (string(opt) == string(op->long_name)) {
      // Marcamos esta opcion como usada en
      // forma explicita, para evitar tener
      // que inicializarla con el valor por
      // defecto.
      //
      op->flags |= OPT_SEEN;

      if (op->has_arg) {
        // Como se trada de una opcion
        // con argumento, verificamos que
        // el mismo haya sido provisto.
        //
        if (arg == 0) {
          cerr << "Option requires argument: "
               << "--"
               << opt
               << "\n";
          exit(1);
        }
        op->parse(string(arg));
        return 1;
      } else {
        // Opcion sin argumento.
        //
        op->parse(string(""));
        return 0;
      }
    }
  }

  // Error: opcion no reconocida. Imprimimos un mensaje
  // de error, y finalizamos la ejecucion del programa.
  //
  cerr << "Unknown option: "
       << "--"
       << opt
       << "."
       << endl;
  exit(1);

  // Algunos compiladores se quejan con funciones que 
  // logicamente no pueden terminar, y que no devuelven
  // un valor en esta ultima parte.
  //
  return -1;
}

int
cmdline::do_short_opt(const char *opt, const char *arg)
{
  option_t *op;

  // Recorremos la tabla de opciones, y buscamos la
  // entrada corta que se corresponda con la opcion de 
  // linea de comandos. De no encontrarse, indicamos el
  // error.
  //
  for (op = option_table; op->short_name != 0; ++op) {
    if (string(opt) == string(op->short_name)) {
      // Marcamos esta opcion como usada en
      // forma explicita, para evitar tener
      // que inicializarla con el valor por
      // defecto.
      //
      op->flags |= OPT_SEEN;

      if (op->has_arg) {
        // Como se trata de una opcion
        // con argumento, verificamos que
        // el mismo haya sido provisto.
        //
        if (arg == 0) {
          cerr << "Option requires argument: "
               << "-"
               << opt
               << "\n";
          exit(1);
        }
        op->parse(string(arg));
        return 1;
      } else {
        // Opcion sin argumento.
        //
        op->parse(string(""));
        return 0;
      }
    }
  }

  // Error: opcion no reconocida. Imprimimos un mensaje
  // de error, y finalizamos la ejecucion del programa.
  //
  cerr << "Unknown option: "
       << "-"
       << opt
       << "."
       << endl;
  exit(1);

  // Algunos compiladores se quejan con funciones que 
  // logicamente no pueden terminar, y que no devuelven
  // un valor en esta ultima parte.
  //
  return -1;
}
