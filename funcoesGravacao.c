#include "./funcoesCriadas.h"
#include "./funcoesFornecidas.h"


/***************FUNCAO-DE-LEITURA-E-GRAVACAO-DOS-REGISTROS**********
/ 
/  esta funcao cria um arquivo binario para armazenar registros de especie
/  que serao lidos na entrada padrao do sistema (teclado). Para tal, cada
/  registro eh lido totalmente em cada loop for. Apos a insercao de todos
/  os campos de um registro o registro eh inserido no arquivo binario criado
/  e o loop reinicia ate o nro indicado de registros serem inseridos
/
/  vale ressaltar que em todos os loops eh necessario checar os ID's de cada
/  especie para que nao hajam repeticoes 
/
/  tambem foi criada uma funcao que, ao ler strings, evita que o usuario insira strings 
/  maiores que o tamanho maximo do campo de um registro

 *******************************************************************/
void registrar_especie()
{
    int i,j;                      //variavel auxiliar
    char nomearq[31];           //nome do arquivo que sera criado
    int nroRegistros;           //nro de registros que serao lidos da entrada padrao
    registro_especie REGISTRO;  //variavel de registro

    scanf("%s",nomearq);
    
    FILE *arquivo;
    arquivo = fopen(nomearq, "ab"); 
    //abre o arquivo no modo append, ele cria e escreve do zero caso o arquivo n exista
    //caso o arquivo ja exista ele continua escrevendo a partir do fim dele

    //checa se o arquivo foi devidamente aberto
    if(arquivo == NULL){
           printf(ERRO_ARQUIVO);     
    }
    else{

        scanf("%d",&nroRegistros);

        if(nroRegistros<0){         //se o usuario colocar um nro de registros menor que zero
            printf(ERRO_PADRAO);    //mensagem de erro
        }
        else{
            for(i=0;i<nroRegistros;i++){

                REGISTRO=le_registro(nomearq);
                if(REGISTRO.SPECIES_ID==-1){    //caso algo de errado tenha acontecido na leitura de dados a informacao nao eh inserida no arquivo
                    break;
                }

            }
        }
        
        fclose(arquivo);        //fecha o arquivo
        binarioNaTela(nomearq); //binario na tela, resultado
    }
}


//  Essa funcao faz as leituras do teclado e checagens de erros na hora de ler informacoes sobre cada especie
//  Caso um erro seja encontrado o campo SPECIES_ID da especie eh alterado para -1, assim quando retornar para a funcao
//  anterior o registro com algum dado incoerente nao sera inserido no arquivo aberto e o programa termina de fazer
//  a leitura do teclado

registro_especie le_registro(char nomearq[31]){

    registro_especie REGISTRO;
    int j;

    while (1)
    {

        //LEITURA DO ID DE ESPECIE

        getchar();
        scanf("%d",&REGISTRO.SPECIES_ID);
        if(REGISTRO.SPECIES_ID<0){
            printf(ERRO_PADRAO);        //caso o usuario insira um ID invalido a inserção é interrompida
            REGISTRO.SPECIES_ID==-1;
            break;    
        }
        if(checa_ID(REGISTRO.SPECIES_ID,nomearq)){
            printf(ERRO_CADASTRO);      //caso o usuario insira um ID repetido retorna erro
            REGISTRO.SPECIES_ID==-1;
            break;    
        }

        //LEITURA DO NOME DA ESPECIE

        getchar();
        scanf("%s",REGISTRO.NAME);
        for(j=strlen(REGISTRO.NAME)-1; j<40;j++){               //coloca o cifrao no lugar dos espacos em branco
            REGISTRO.NAME[j] = '$';
        }

        //LEITURA DO NOME CIENTIFICO DA ESPECIE

        getchar();
        scanf("%s",REGISTRO.SCIENTIFIC_NAME);
        for(j=strlen(REGISTRO.SCIENTIFIC_NAME)-1; j<60;j++){    //coloca o cifrao no lugar dos espacos em branco
            REGISTRO.SCIENTIFIC_NAME[j] = '$';
        }

        //LEITURA DA POPULACAO DA ESPECIE

        getchar();
        scanf("%d",&REGISTRO.POPULATION);
        if(REGISTRO.POPULATION<0 ){
            REGISTRO.SPECIES_ID==-1;
            printf(ERRO_PADRAO);    //caso o usuario insira uma populacao invalida nao insere o registro no arquivo e retorna erro
            break;    
        }

        //LEITURA DO STATUS DA ESPECIE

        getchar();
        scanf("%s",REGISTRO.STATUS);
        for(j=strlen(REGISTRO.STATUS)-1; j<8;j++){  //coloca o cifrao no lugar dos espacos em branco
            REGISTRO.STATUS[j] = '$';
        }

        //LEITURA DA COORDENADA X

        getchar();
        scanf("%f",&REGISTRO.LOCATION_LON);
        if(REGISTRO.LOCATION_LON<-180 ||  REGISTRO.LOCATION_LON>180){
            REGISTRO.SPECIES_ID==-1;
            printf(ERRO_PADRAO);    //caso o usuario insira uma coordenada x inexistente
            break;    
        }

        //LEITURA DA COORDENADA Y

        getchar();
        scanf("%f",&REGISTRO.LOCATION_LAT);
        if(REGISTRO.LOCATION_LAT<-90 ||  REGISTRO.LOCATION_LAT>90){
            REGISTRO.SPECIES_ID==-1;
            printf(ERRO_PADRAO);    //caso o usuario insira uma coordenada y inexistente
            break;    
        }

        //LEITURA DO IMPACTO HUMANO ASSOCIADO

        getchar();
        scanf("%d",&REGISTRO.HUMAN_IMPACT);
        if(REGISTRO.HUMAN_IMPACT<0 || REGISTRO.HUMAN_IMPACT>3){
            REGISTRO.SPECIES_ID==-1;
            printf(ERRO_PADRAO);    //caso o usuario insira um HUMAN_IMPACT menor que 0 e maior que 3 retorna erro e nao insere o registro no arquivo
            break;    
        }
        break;
    }

    return REGISTRO;    //retorna o registro apos feito todo o trabalho de leitura
}

int checa_ID(int ID, char nomearq[31]){

    return 0;
}