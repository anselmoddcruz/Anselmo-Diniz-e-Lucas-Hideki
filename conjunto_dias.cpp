#include "conjunto_dias.hpp"

ConjuntoDias::ConjuntoDias(int numero_dias){
  this->numero_dias = numero_dias;
  this->compromissos = new Compromissos*[numero_dias];

  // Inicializa todos os compromissos como um ponteiro nulo
  for(int i = 0; i < numero_dias; i++){
    compromissos[i] = nullptr;
  }
}

int ConjuntoDias::get_numero_dias(){
  return this->numero_dias;
}

Compromissos* ConjuntoDias::get_compromisso_em_dia(int dia){
  return this->compromissos[dia];
}

// Responsável por adicionar um compromisso em um dos dias do mês
void ConjuntoDias::adicionar_compromisso(int hora, std::string descricao, int dia){
  if(this->compromissos[dia] == nullptr){
    // Case seja o primeiro compromisso, é necessário um tratamento especial
    this->compromissos[dia] = new Compromissos(hora, descricao);
  }else{
    Compromissos *compromisso_atual = this->compromissos[dia];
    // Percorre todos os compromissos até achar o ultimo
    while(compromisso_atual->proximo != nullptr){
      compromisso_atual = compromisso_atual->proximo;
    }
    // Faz o próximo compromisso depois do ultimo ser o novo compromisso
    compromisso_atual->proximo = new Compromissos(hora, descricao);
  }
}
