#ifndef CONJUNTO_DIAS_H
#define CONJUNTO_DIAS_H

#include "compromissos.hpp"
#include <string>

class ConjuntoDias{
public:
  Compromissos **compromissos;

  ConjuntoDias(int);

  int get_numero_dias();
  Compromissos* get_compromisso_em_dia(int);
  void adicionar_compromisso(int, std::string, int);

private:
  int numero_dias;
};

#endif
