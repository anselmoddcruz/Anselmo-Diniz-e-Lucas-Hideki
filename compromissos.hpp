#ifndef COMPROMISSOS_H
#define COMPROMISSOS_H

#include <string>

class Compromissos{
public:
  Compromissos();
  Compromissos(int hora, std::string descricao);

  int get_hora();
  std::string get_descricao();

  Compromissos *proximo;

private:
  int hora;
  std::string descricao;

};

#endif
