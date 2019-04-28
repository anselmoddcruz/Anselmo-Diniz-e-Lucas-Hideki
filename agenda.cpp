#include "agenda.hpp"

#include <iostream>

Agenda::Agenda(){
  this->primeiro_mes = nullptr;
}

// Responsável por inicializar a agenda
void Agenda::abre_agenda(){
  this->adiciona_mes("Janeiro", 31);
  this->adiciona_mes("Fevereiro", 28);
  this->adiciona_mes("Março", 31);
  this->adiciona_mes("Abril", 30);
  this->adiciona_mes("Maio", 31);
  this->adiciona_mes("Junho", 30);
  this->adiciona_mes("Julho", 31);
  this->adiciona_mes("Agosto", 31);
  this->adiciona_mes("Setembro", 30);
  this->adiciona_mes("Outubro", 31);
  this->adiciona_mes("Novembro", 30);
  this->adiciona_mes("Dezembro", 31);

  std::ifstream arquivo_ler;
  arquivo_ler.open(NOME_ARQUIVO);
  if(arquivo_ler.is_open()){
    std::string line;
    // Lê cada linha do arquivo
    while(getline(arquivo_ler, line)){
      if(!line.empty()){
        std::string delim = "\t";
        size_t prev = 0;
        size_t pos = 0;
        int part_contador = 0;

        int mes;
        int dia;
        int hora;
        std::string descricao;

        // Código responsável por pegar cada uma das linhas no arquivo de texto
        // que salva as sessões anteiores e quebra usando os delimitadores "\t"
        // para separar os valores de dia, mes, hora e descricao
        do{
          pos = line.find(delim, prev);
          if(pos == std::string::npos){
            pos = line.length();
          }
          std::string token = line.substr(prev, pos - prev);

          if (!token.empty()){
            if(part_contador == 0){
              // O token é o mês
              mes = std::stoi(token);
            }else if(part_contador == 1){
              // O token é o dia
              dia = std::stoi(token);
            }else if(part_contador == 2){
              // O token é a hora
              hora = std::stoi(token);
            }else if(part_contador == 3){
              // O token é a descricao
              descricao = token;
            }
          }

          prev = pos + delim.length();
          part_contador++;
        } while (pos < line.length() && prev < line.length());

        // Assim que cada linha tem os valores separados, so resta adicionar denovo
        // ao sistema
        this->insere_compromisso(hora, descricao, mes, dia);
      }
    }
    arquivo_ler.close();
  }
}

// Responsável por finalizar a agenda
void Agenda::fecha_agenda(){
  std::ofstream arquivo_salvar;
  // Apaga tudo do arquivo e reescreve tudo para evitar duplicatas
  arquivo_salvar.open(NOME_ARQUIVO, std::ofstream::out | std::ofstream::trunc);
  if(arquivo_salvar.is_open()){
    Mes *mes_atual = this->primeiro_mes;
    int n_mes = 1;
    // Passa por cada mês da lista
    while(mes_atual != nullptr){
      for(int i = 0; i < mes_atual->get_conjunto_dias()->get_numero_dias(); i++){
        Compromissos *compromisso_atual = mes_atual->get_conjunto_dias()->compromissos[i];
        // Passa por cada compromisso do mês e salva no arquivo
        while(compromisso_atual != nullptr){
          arquivo_salvar << (n_mes) << "\t" << (i + 1) << "\t" << compromisso_atual->get_hora() << "\t" << compromisso_atual->get_descricao() << "\n";

          compromisso_atual = compromisso_atual->proximo;
        }
      }

      mes_atual = mes_atual->proximo;
      n_mes++;
    }

    arquivo_salvar.close();
  }
}

// Responsável por achar o mês específico e adicionar um compromisso em um dia específico
// daquele mês
void Agenda::insere_compromisso(int hora, std::string descricao, int mes, int dia){
  Mes *mes_atual = this->primeiro_mes->get_iesimo_mes_seguinte(mes);
  mes_atual->adiciona_compromisso(hora, descricao, dia - 1);
}

// Adiciona um mês na lista de meses
void Agenda::adiciona_mes(std::string nome, int numero_dias){
  if(this->primeiro_mes == nullptr){
    // Se for o primeiro mês adicionado, precisa de um tratamento especial
    this->primeiro_mes = new Mes(nome, numero_dias);
  }else{
    Mes *ultimo_mes = this->primeiro_mes;
    // Percorre a lista até achar o mês especificado
    while(ultimo_mes->proximo != nullptr){
      ultimo_mes = ultimo_mes->proximo;
    }

    ultimo_mes->proximo = new Mes(nome, numero_dias);
  }
}

Mes* Agenda::get_primeiro_mes(){
  return this->primeiro_mes;
}
