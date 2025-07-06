# FILA---Empresa-de-Desenvolvimento-de-Software
Projeto desenvolvido para a disciplina de Estruturas de Dados I, simulando o sistema de gerenciamento de tarefas de uma empresa de desenvolvimento de software. As tarefas são organizadas em uma fila de prioridades com três níveis: Crítico, Importante e Melhoria.

# 🧠 Simulador de Gerenciamento de Tarefas com Fila de Prioridades

Projeto desenvolvido para a disciplina **Estruturas de Dados I**, simulando o sistema de organização de tarefas de uma empresa de desenvolvimento de software. O programa utiliza **fila de prioridades** para gerenciar tarefas e desenvolvedores, com exibição visual no terminal.

## 📋 Funcionalidades

- 📥 Leitura de tarefas a partir de um arquivo `.csv`
- 🔁 Simulação do atendimento de tarefas por desenvolvedores disponíveis
- ⏳ Fila de prioridade baseada no tipo de tarefa:
  - Crítico (alta prioridade)
  - Importante (prioridade média)
  - Melhoria (baixa prioridade)
- 📊 Exibição em tempo real dos desenvolvedores, tarefas pendentes e progresso
- 📈 Relatórios ao final da simulação:
  - Total de tarefas concluídas por tipo
  - Tempo médio de espera por tipo
  - Número de tarefas não concluídas

## 📁 Estrutura dos Arquivos

- `ED1Main.cpp`: Código principal da simulação
- `TADFila.h`: Definições de TADs, estrutura da fila e funções auxiliares
- `Tarefa.csv`: Base de dados com as tarefas a serem simuladas

### 🧾 Formato do Arquivo de Tarefas (`Tarefa.csv`)

