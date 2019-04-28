#ifndef MES_H
#define MES_H

#include <string>

#include "conjunto_dias.hpp"

class Mes{
public:
  Mes *proximo;

  Mes();
  Mes(std::string, int);

  // Responsável por adicionar um compromisso em um dos dias do mês
  void adiciona_compromisso(int, std::string, int);

  // Acha o iésimo mês depois desse
  Mes* get_iesimo_mes_seguinte(int);

  std::string get_nome();
  int get_numero_dias();
  ConjuntoDias* get_conjunto_dias();

private:
  std::string nome;
  int numero_dias;
  ConjuntoDias *conj;
};

#endif
