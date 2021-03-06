/**
  * @file cronologia.cpp
  * @brief Implementación del T.D.A. Cronologia
  *
  */

#include <iostream>
#include <sstream>
#include <cassert>
#include "cronologia.hpp"

using namespace std;

EventoHistorico& Cronologia::operator[](const Fecha& f)
{
  assert(datos.count(f) > 0);
  return datos[f];
}

/* _________________________________________________________________________ */

void Cronologia::addEventoHistorico(const EventoHistorico& e)
{
  Fecha f = e.getFecha();

  if (datos.count(f) > 0)
  {
    datos[f].addEvento(e.getEvento());
  }
  else
  {
    pair<Fecha, EventoHistorico> new_element(f,e);
    datos.insert(new_element);
  }
}

/* _________________________________________________________________________ */

int Cronologia::eliminarPorClave (const string& key)
{
  int n = 0;
  const_iterator p = datos.begin();
  while (p != datos.end())
  {
    if (p->second.buscarPorClave(key).size() != 0)
    {
      p = datos.erase(p);
      n++;
    }
    else
      ++p;
  }
  return n;
}

/* _________________________________________________________________________ */

bool Cronologia::contieneAcontecimiento(const Acontecimiento& a) const
{
  for (const_iterator p = datos.begin(); p != datos.end(); ++p)
  {
    if (p->second.buscarAcontecimiento(a) != p->second.end())
      return true;
  }
  return false;
}

/* _________________________________________________________________________ */

Fecha Cronologia::fechaAcontecimiento(const Acontecimiento& a) const
{
  assert(contieneAcontecimiento(a));
  for (const_iterator p = datos.begin(); p != datos.end(); ++p)
  {
    if (p->second.buscarAcontecimiento(a) != p->second.end())
      return p->first;
  }
  // Debe encontrarlo siempre
}

/* _________________________________________________________________________ */

istream& Cronologia::cargarCronologia(istream& is)
{
  EventoHistorico tmp;
  container_type v;
  pair<Fecha, EventoHistorico> new_element;
  string s;

  // Ignorar blancos iniciales
  while(isspace(is.peek()))
    is.get();

  // Leer línea a línea
  while(getline(is,s))
  {
    istringstream ss(s);
    new_element.second.cargarEvento(ss);
    new_element.first = new_element.second.getFecha();
    v.insert(new_element);
  }

  if (is.eof())
  {
    setCronologia(v);
  }

  return is;
}

/* _________________________________________________________________________ */

ostream& Cronologia::mostrarCronologia(ostream& os) const
{
  for (const_iterator p = datos.begin(); p != datos.end(); ++p)
  {
    p->second.mostrarEvento(os);
    os << '\n';
  }
  return os;
}

/* _________________________________________________________________________ */

ostream& Cronologia::mostrarCronologiaInversa(ostream& os) const
{
  for (container_type::const_reverse_iterator p = datos.rbegin(); p != datos.rend(); ++p)
  {
    p->second.mostrarEvento(os);
    os << '\n';
  }
  return os;
}

/* _________________________________________________________________________ */

ostream& Cronologia::prettyPrint(ostream& os) const
{
  for (const_iterator p = datos.begin(); p != datos.end(); ++p)
  {
    p->second.prettyPrint();
    os << '\n';
  }
  return os;
}

/* _________________________________________________________________________ */

istream& operator>>(istream& is, Cronologia& cron)
{
  return cron.cargarCronologia(is);
}

/* _________________________________________________________________________ */

ostream& operator<<(ostream& os, const Cronologia& cron)
{
  return cron.mostrarCronologia(os);
}

/* Fin fichero: cronologia.cpp */
