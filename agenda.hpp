#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <fstream>

#include "compromissos.hpp"
#include "conjunto_dias.hpp"
#include "mes.hpp"

#define NOME_ARQUIVO "agenda_salva.txt"

class Agenda{
public:
  Agenda();

  // Adiciona um mês na lista de meses
  void adiciona_mes(std::string, int numero_dias);

  // Responsável por inicializar a agenda
  void abre_agenda();

  // Responsável por finalizar a agenda
  void fecha_agenda();

  // Responsável por achar o mês específico e adicionar um compromisso em um dia específico
  // daquele mês
  void insere_compromisso(int, std::string, int, int);

  Mes* get_primeiro_mes();

private:
  Mes *primeiro_mes;
};

#endif
