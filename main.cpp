#include <iostream>
#include <string>

#include "agenda.hpp"

// Define os números que serão utilizados no input
#define OPCAO_INSERE 0
#define OPCAO_REMOVE 1
#define OPCAO_LISTA_COMPROMISSOS 2
#define OPCAO_VERIFICA_AGENDAMENTO 3
#define OPCAO_SAIR 4

int main(){
  Agenda agenda;
  agenda.abre_agenda();

  int opcao_usuario = OPCAO_SAIR;
  do{
    std::cout << "/--------------------------------------------------------------------/" << std::endl;
    std::cout << "Digite qual opção você deseja executar:" << std::endl;
    std::cout << " - [" << OPCAO_INSERE << "] Inserir compromisso" << std::endl;
    std::cout << " - [" << OPCAO_REMOVE << "] Remover compromisso" << std::endl;
    std::cout << " - [" << OPCAO_LISTA_COMPROMISSOS << "] Listar todos os compromissos" << std::endl;
    std::cout << " - [" << OPCAO_VERIFICA_AGENDAMENTO << "] Listar todos os compromissos em horário específico" << std::endl;
    std::cout << " - [" << OPCAO_SAIR << "] Sair do programa e fechar a lista" << std::endl;
    std::cout << "Sua opção: ";
    std::cin >> opcao_usuario;
    std::cout << std::endl;

    if(opcao_usuario == OPCAO_INSERE){
      std::cout << "Inserindo novo compromisso" << std::endl;
      std::cout << " - Digite o número do mês: ";
      int numero_mes;
      std::cin >> numero_mes;
      if(numero_mes < 1 && numero_mes > 12){
        std::cout << "O número do mês tem que ser um inteiro entre 1 e 12. Operação cancelada." << std::endl;
        continue;
      }
      std::cout << " - Digite o dia: ";
      int numero_dia;
      std::cin >> numero_dia;
      if(numero_dia < 1 && numero_dia > 31){
        std::cout << "O número do dia tem que ser um inteiro entre 1 e 31. Operação cancelada." << std::endl;
        continue;
      }
      std::cout << " - Digite a hora: ";
      int numero_hora;
      std::cin >> numero_hora;
      if(numero_hora < 1 && numero_hora > 24){
        std::cout << "O número da hora tem que ser um inteiro entre 1 e 24. Operação cancelada." << std::endl;
        continue;
      }
      std::cout << " - Digite a descrição: ";
      std::string descricao;

      // Lê a linha toda que o usuário digitar
      while(std::getline(std::cin, descricao)){
        if(descricao.size() > 0) break;
      }

      agenda.insere_compromisso(numero_hora, descricao, numero_mes, numero_dia);

      std::cout << "Compromisso adicionado com sucesso!" << std::endl;
      std::cout << std::endl;
    }else if(opcao_usuario == OPCAO_REMOVE){
      std::cout << " - Digite o número do mês que o compromisso está: ";
      int numero_mes;
      std::cin >> numero_mes;
      if(numero_mes < 1 && numero_mes > 12){
        std::cout << "O número do mês tem que ser um inteiro entre 1 e 12. Operação cancelada." << std::endl;
        continue;
      }
      std::cout << " - Digite o dia que o compromisso está: ";
      int numero_dia;
      std::cin >> numero_dia;
      if(numero_dia < 1 && numero_dia > 31){
        std::cout << "O número do dia tem que ser um inteiro entre 1 e 31. Operação cancelada." << std::endl;
        continue;
      }

      std::cout << std::endl << "Lista de compromissos no dia especificado:" << std::endl;

      Mes *mes_atual = agenda.get_primeiro_mes()->get_iesimo_mes_seguinte(numero_mes);

      int n_compromisso = 0;
      Compromissos *compromisso_atual = mes_atual->get_conjunto_dias()->compromissos[numero_dia - 1];
      // Passa por todos os compromissos da lista escrevendo na tela cada um deles
      while(compromisso_atual != nullptr){
        std::cout << "    - [" << n_compromisso << "] - " << compromisso_atual->get_descricao() << std::endl;
        compromisso_atual = compromisso_atual->proximo;
        n_compromisso++;
      }

      std::cout << std::endl;

      if(n_compromisso > 0){
        std::cout << " - Digite o [ID] do compromisso a ser apagado: ";
        int id_compromisso;
        std::cin >> id_compromisso;

        if(id_compromisso > n_compromisso || id_compromisso < 0){
          std::cout << "ID inválido. Operação Cancelada" << std::endl;
          continue;
        }

        n_compromisso = 0;
        compromisso_atual = mes_atual->get_conjunto_dias()->compromissos[numero_dia - 1];
        // Passa por cada um dos compromissos até que a contagem chegue em "id_compromisso",
        // indicando que chegamos no compromisso indifcado
        while(compromisso_atual != nullptr && n_compromisso < id_compromisso - 1){
          compromisso_atual = compromisso_atual->proximo;
          n_compromisso++;
        }

        // 'compromisso_atual' -> Compromisso anterior ao que deverá ser excluido
        // 'compromisso_atual->proximo' -> Compromisso que deverá ser excluido

        if(compromisso_atual != nullptr){
          if(id_compromisso == 0){
            // Se for o primeiro compromisso da lista, precisa de um tratamento especial
            mes_atual->get_conjunto_dias()->compromissos[numero_dia - 1] = mes_atual->get_conjunto_dias()->compromissos[numero_dia - 1]->proximo;
          }else{
            // Faz o próximo do compromisso anterior ao que será excluido ser o próximo
            // do compromisso a ser excluido, efetivamente tirando o compromisso
            // desejado da lista
            compromisso_atual->proximo = compromisso_atual->proximo->proximo;
          }
        }
      }else{
        std::cout << "  - Não existem compromissos no horário especificado" << std::endl;
      }

      std::cout << std::endl;
    }else if(opcao_usuario == OPCAO_LISTA_COMPROMISSOS){
      std::cout << "Sua lista de compromissos:" << std::endl;
      Mes *mes_atual = agenda.get_primeiro_mes();
      int num_compromissos = 0;
      // Passa por cada mês da lista
      while(mes_atual != nullptr){
        for(int i = 0; i < mes_atual->get_conjunto_dias()->get_numero_dias(); i++){
          Compromissos *compromisso_atual = mes_atual->get_conjunto_dias()->compromissos[i];
          // Passa por cada compromisso do mês e mostra na tela
          while(compromisso_atual != nullptr){
            std::cout << " - [" << (i + 1) << " de " << mes_atual->get_nome() << ", " << compromisso_atual->get_hora() << "hrs] " << compromisso_atual->get_descricao() << std::endl;
            compromisso_atual = compromisso_atual->proximo;
            num_compromissos++;
          }
        }

        mes_atual = mes_atual->proximo;
      }

      if(num_compromissos == 0){
        std::cout << "  - Não existem compromissos cadastrados" << std::endl;
      }

      std::cout << std::endl;
    }else if(opcao_usuario == OPCAO_VERIFICA_AGENDAMENTO){
      std::cout << "Checando se existe compromisso em determinada hora" << std::endl;
      std::cout << " - Digite o número do mês em que será pesquisado: ";
      int numero_mes;
      std::cin >> numero_mes;
      if(numero_mes < 1 && numero_mes > 12){
        std::cout << "O número do mês tem que ser um inteiro entre 1 e 12. Operação cancelada." << std::endl;
        continue;
      }
      std::cout << " - Digite o dia em que será pesquisado: ";
      int numero_dia;
      std::cin >> numero_dia;
      if(numero_dia < 1 && numero_dia > 31){
        std::cout << "O número do dia tem que ser um inteiro entre 1 e 31. Operação cancelada." << std::endl;
        continue;
      }
      std::cout << " - Digite a hora em que será pesquisado: ";
      int numero_hora;
      std::cin >> numero_hora;
      if(numero_hora < 1 && numero_hora > 24){
        std::cout << "O número da hora tem que ser um inteiro entre 1 e 24. Operação cancelada." << std::endl;
        continue;
      }

      Mes *mes_atual = agenda.get_primeiro_mes()->get_iesimo_mes_seguinte(numero_mes);

      std::cout << std::endl;
      std::cout << "Compromissos em " << numero_dia << " de " << mes_atual->get_nome() << " às " << numero_hora << "hrs:" << std::endl;

      Compromissos *compromisso_atual = mes_atual->get_conjunto_dias()->compromissos[numero_dia - 1];
      // Acha o compromisso na hora específica indicada por 'numero_hora' e
      // mostra na tela os resultados
      int num_agendamentos = 0;
      while(compromisso_atual != nullptr){
        if(compromisso_atual->get_hora() == numero_hora){
          std::cout << "    - " << compromisso_atual->get_descricao() << std::endl;
          num_agendamentos++;
        }
        compromisso_atual = compromisso_atual->proximo;
      }

      if(num_agendamentos == 0){
        std::cout << "  - Não existem agendamentos no horário especificado." << std::endl;
      }

      std::cout << std::endl;
    }
  }while(opcao_usuario != OPCAO_SAIR);

  agenda.fecha_agenda();
}
