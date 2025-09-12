# Trabalho-IPC02
Simulação de Sistema Operacional Simplificado 

Projeto acadêmico em linguagem C que simula um sistema operacional básico, com criação, execução e cancelamento de processos, além de gerenciamento de filas por prioridade. Desenvolvido para praticar estruturas de dados, pilhas, listas encadeadas e simulação de escalonamento.

<h2> Funcionalidades  </h2>

<h3> 1. Criação de Processos </h3>

Cada processo recebe um PID, nome, prioridade (alta, média, baixa) e número de chamadas de funções.

Pilha de funções associada a cada processo.

<h3> 2. Execução de Processos </h3>

O escalonador seleciona sempre o processo da maior prioridade disponível.

Pilha de funções é esvaziada simulando a execução.

Processo é transferido para a lista de finalizados.

<h3> 3. Impressão do Estado Atual </h3>

Exibe as filas de processos por prioridade.

Lista os processos já finalizados.

<h3> 4. Cancelamento de Processos </h3>

Remoção de um processo ativo pelo PID informado.

Liberação de memória associada ao processo e suas funções.

<h2> Tecnologias e Conceitos </h2>

Linguagem C

Estruturas de Dados: listas encadeadas, pilhas, filas

Conceitos de Sistemas Operacionais: escalonamento por prioridade, estados de processo

Boas práticas: código modular, separação em .h e .c, validação de entradas, uso de ponteiros e malloc/free

<h2> Como Executar </h2>

Compilar o projeto:
gcc main.c funcoes.c -o programa

Rodar no terminal:
./programa    # Linux/Mac
programa.exe  # Windows

<h4> Projeto desenvolvido por Bernardo Lebron – Estudante de Engenharia de Computação (CEFET-MG). </h4> 
