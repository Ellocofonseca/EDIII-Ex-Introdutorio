#include "./funcoesCriadas.h"

//funcao que direciona o codigo para cada funcao de acordo com o numero selecionado

void direcionaComando(int codigo){
    switch (codigo){

    case 1:
        registrar_especie();    //funcao de registro de especies em um arquivo novo
        break;

    case 2:
        relatorio_especies();   //funcao de exibicao de relatorio com os registros de um arquivo existente
        break;

    case 3:
        relatorio_RRN();        //funcao de exibicao de relatorio de uma especie especifica de acordo com o RRN escolhido
        break;

    case 4:
        registra_informacao();  //funcao que altera campos especificos de registros escolhidos
        break;

    default:
        printf(ERRO_PADRAO);    //PRINT DA MENSAGEM PADRAO DE ERRO CASO O USUARIO DIGITE UM COMANDO INEXISTENTE
        break;
    }

}
