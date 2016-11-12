/**
 * @file stack_max.hpp
 * @brief Fichero de cabecera del T.D.A. StackMax
 *
 * Gestiona una secuencia de parejas de elementos, con facilidades para la inserción
 * y borrado en uno de los extremos. El segundo elemento de la pareja es
 * el máximo (de entre los primeros elementos de las parejas) que hay en la secuencia
 * en ese momento.
 *
 * Además, se permite elegir entre tres representaciones distintas para este T.D.A.
 * @see stack_max_list.hpp
 * @see stack_max_dvector.hpp
 * @see stack_max_queue.hpp
 *
 * Un ejemplo de su uso puede verse en:
 * @example use_stack_max.cpp
 *
 */

#ifndef __STACK_MAX_HPP__
#define __STACK_MAX_HPP__

#include <iostream>

/**
 * @brief T.D.A. Element
 *
 * Una instancia @e e del tipo de datos abstracto Element es un objeto del conjunto
 * de las parejas de números enteros, compuesto por dos enteros @e num y @e max. Este T.D.A.
 * está pensado para usarse en conjunción con el T.D.A. StackMax, ya que el primer entero
 * representa un número cualquiera (que se introduce en la pila), y el segundo representa
 * el máximo número que en ese instante se encuentra en la pila.
 *
 * Lo representamos: `(num,max)`
 *
 * @relates StackMax
 *
 */

struct Element
{
  int num;    ///< Número entero.
  int max;    ///< Número máximo en StackMax.
};

/**
 * @brief Sobrecarga del operador << para Element
 * @param os Flujo de salida
 * @param e Objeto de tipo Element a escribir
 * @post El formato de escritura es el siguiente:
 * > e.num, e.max
 *
 * @relates Element
 */
std::ostream& operator<<(std::ostream& os, const Element& e);

/// Se define la representación deseada para el T.D.A. StackMax
#define COMPILE_HEADER 2

#if COMPILE_HEADER == 1
  #include "stack_max_list.hpp"
#elif COMPILE_HEADER == 2
  #include "stack_max_dvector.hpp"
#else
  #include "stack_max_queue.hpp"
#endif

/**
 * @brief T.D.A. StackMax
 *
 * Una instancia @e s del tipo de datos abstracto StackMax es un objeto que
 * representa una pila de objetos de tipo Element. Está compuesto por una estructura de
 * datos (@c StackType) @e v, que puede ser una de tres: un vector dinámico, una lista con
 * cabecera ó una cola. Este dato constituye la representación interna de la pila.
 * Una pila de longitud @e k la denotamos:
 *
 * > <(num_1,max_1),(num_2, max_2),...,(num_k, max_k)>
 *
 * @see List
 * @see DVector
 * @see Queue
 *
 * @author Antonio Coín Castro
 * @author Miguel Lentisco Ballesteros
 * @author José María Martín Luque
 * @date Noviembre 2016
 *
 */

class StackMax
{
  /**
   * @page repConjunto1 Rep del T.D.A. StackMax
   *
   * @section invConjunto1 Invariante de la representación
   *
   * El invariante es: @e v es de tipo DVector, List ó Queue.
   *
   * @section faConjunto1 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. StackMax representa a uno, y solo uno de
   * estos tres valores:
   *
   * > rep = (DVector v), rep = (List v), rep = (Queue v)
   *
   */
  private:
    StackType v;    ///< Representación interna de la pila

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     * @post Construye una pila vacía
     */
    StackMax() {};

    // ---------------  Funciones de acceso ----------------

    Element& top(); // pre: no vacia
    const Element& top() const; // pre: no vacia


    // ---------------  Funciones de modificación ----------------

    void push(int n);
    void pop(); // pre: no vacia
    void clear() {v.clear();}

    // ---------------  Funciones de consulta ----------------

    int size() const {return v.size();}
    bool empty() const {return v.empty();}
    bool sameMax(const StackMax& s) const;  // pre: ninguna de las dos vacía

    // ---------------  Funciones de entrada/salida ----------------

    std::istream& loadStack(std::istream& is);
    std::ostream& writeStack(std::ostream& os) const;
    std::ostream& prettyPrint(std::ostream& os = std::cout) const;  // formato: (num,max)
};

/**
 * @brief Sobrecarga del operador >> para StackMax
 * @param is Flujo de entrada
 * @param s Pila donde leer
 * @post StackMax leída en @e s
 * @pre Hay dos formatos de lectura. En ambos, el tope de la pila
 *      es el que se encuentra más arriba.
 *
 * - Formato 1:
 *
 *          n1 max1
 *          n2 max2
 *          n3 max3
 *          ...
 *
 * - Formato 2:
 *          $
 *          n1
 *          n2
 *          n3
 *          ...
 *
 * El segundo formato necesita el símbolo '$' al inicio del archivo
 * para ser reconocido como un formato válido de entrada. El primer formato
 * se mantiene por compatibilidad con el formato de escritura, aunque los
 * diferentes máximos son ignorados en la lectura.
 *
 * @see operator<<
 * @relates StackMax
 */
std::istream& operator>>(std::istream& is, StackMax& s);

/**
 * @brief Sobrecarga del operador << para StackMax
 * @param os Flujo de salida
 * @param s Pila a escribir
 * @post El formato de escritura es el mismo que el de lectura
 *
 * @see operator>>
 * @relates StackMax
 */
std::ostream& operator<<(std::ostream& os, const StackMax& s);

#endif

/* Fin fichero: stack_max.hpp */
