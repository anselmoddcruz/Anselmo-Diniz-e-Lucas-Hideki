#include "mes.hpp"

Mes::Mes(){
  this->nome = "";
  this->numero_dias = -1;
  this->proximo = nullptr;
  this->conj = nullptr;
}

Mes::Mes(std::string nome, int numero_dias){
  this->nome = nome;
  this->numero_dias = numero_dias;
  this->proximo = nullptr;
  this->conj = new ConjuntoDias(numero_dias);
}

// Responsável por adicionar um compromisso em um dos dias do mês
void Mes::adiciona_compromisso(int hora, std::string descricao, int dia){
  this->get_conjunto_dias()->adicionar_compromisso(hora, descricao, dia);
}

Mes* Mes::get_iesimo_mes_seguinte(int numero_mes){
  Mes *mes_atual = this;
  int n_mes_atual = 1;
  // Acha o ponteiro para o mês com o número indicado
  while(mes_atual != nullptr && n_mes_atual < numero_mes){
    mes_atual = mes_atual->proximo;
    n_mes_atual++;
  }

  return mes_atual;
}

std::string Mes::get_nome(){
  return this->nome;
}

int Mes::get_numero_dias(){
  return this->numero_dias;
}

ConjuntoDias* Mes::get_conjunto_dias(){
  return this->conj;
}
