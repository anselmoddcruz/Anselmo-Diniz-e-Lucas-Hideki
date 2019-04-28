#include "compromissos.hpp"

Compromissos::Compromissos(){
  this->hora = -1;
  this->descricao = "";
  this->proximo = nullptr;
}

Compromissos::Compromissos(int hora, std::string descricao){
  this->hora = hora;
  this->descricao = descricao;
  this->proximo = nullptr;
}

int Compromissos::get_hora(){
  return this->hora;
}

std::string Compromissos::get_descricao(){
  return this->descricao;
}
