#ifndef __FUNCOES__
#define __FUNCOES__

//-------BIBLIOTECAS------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

//------MENSAGENS-DE-ERRO-----
#define ERRO_PADRAO     "Falha no processamento do arquivo\n" //mensagem padrao de erro
#define ERRO_RRN_ID     "Espécie não encontrada\n"            //mensagem de erro para rrn invalido ou species_id inexistente
#define ERRO_ARQUIVO    "Falha no processamento do arquivo\n" //mensagem de erro para arquivo inexistente
#define ERRO_CADASTRO   "Informação já inserida no arquivo\n" //mensagem de erro para dados ja cadastrados


// CAMPOS DO REGISTRO DE ESPECIE, MOSTRAM O FORMATO DE ENTRADA, REGISTRO DE 131 BYTES POR ESPECIE
typedef struct
{
    int SPECIES_ID;             // Numero de identificacao da especie               4 bytes
    char NAME[41];              // Nome popular da especie                          41 bytes
    char SCIENTIFIC_NAME[61];   // Nome cientifico da especie                       61 bytes
    int POPULATION;             // Populacao da especie                             4 bytes
    char STATUS[9];             // Status (como a especie se encontra no momento)   9 bytes
    float LOCATION_LON;         // Latitude da localizacao geral da especie         4 bytes
    float LOCATION_LAT;         // Longitude da localizacao geral da especie        4 bytes
    int HUMAN_IMPACT;           // Impacto humano na populacao da especie           4 bytes

} registro_especie;


//--------FUNCOES-DO-PROGRAMA------------

//FUNCOES PADRAO, REDIRECIONAMENTO
void direcionaComando(int codigo);                              //FUNCAO DE SELECAO DE FUNCAO DE ACORDO COM O COMANDO


//FUNCOES DE GRAVACAO/EDICAO DE ARQUIVOS (comandos 1 e 4) 
void registrar_especie();                                       //FUNCAO QUE LE DO TECLADO E ESCREVE NO ARQUIVO
void registra_informacao();                                     //FUNCAO QUE EDITA A INFORMACAO EM REGISTROS ESCOLHIDOS


//FUNCOES DE RELATORIO (comandos 2 e 3)
void relatorio_especies();                      //FUNCOES QUE PRINTAM O RELATORIO DE ESPECIES DE TODO UM ARQUIVO
void relatorio_RRN();                           //FUNCAO QUE EXIBE O RELATORIO DE UMA ESPECIE ESPECIFICA DE ACORDO COM O RRN
void exibe_registro(registro_especie REGISTRO); //FUNCAO QUE PRINTA UM REGISTRO NA TELA


#endif // __FUNCOES__