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
 *******************************************************************/
void registrar_especie()
{
    int i,j;                      //variavel auxiliar
    char nomearq[31];           //nome do arquivo que sera criado
    int nroRegistros;           //nro de registros que serao lidos da entrada padrao
    registro_especie REGISTRO;  //variavel de registro

    scanf("%s",nomearq);
    
    FILE *arquivo;
    arquivo = fopen(nomearq, "ab"); //cria e 
    fclose(arquivo);                //fecha o arquivo

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
            int IDs_registrados[nroRegistros];
            for(i=0;i<nroRegistros;i++){
                
                scanf("%d",&REGISTRO.SPECIES_ID);
                IDs_registrados[i]=REGISTRO.SPECIES_ID; //salva o ID para checagem posterior de repeticoes


                if(REGISTRO.SPECIES_ID<0){
                    printf(ERRO_CADASTRO);      //caso o usuario insira um ID invalido
                    REGISTRO.SPECIES_ID==-1;
                    IDs_registrados[i]=-1;  //invalida o resgistro como "salvo"  
                }
                for(j=0;j<i;j++){                                       //roda o loop um total de vezes igual a quantas tentativas de insercao ja foram feitas no sistema
                    if(REGISTRO.SPECIES_ID==IDs_registrados[j]){        //se o ID atual for igual a algum id salvo anterior retorna erro
                        printf(ERRO_CADASTRO);                          //caso o usuario insira um ID repetido retorna erro
                        REGISTRO.SPECIES_ID==-1;
                        IDs_registrados[i]=-1;  //invalida o resgistro como "salvo" 
                    } 
                }

                //LEITURA DO NOME DA ESPECIE

                readline(REGISTRO.NAME);
                for(j=strlen(REGISTRO.NAME)+1; j<41;j++){               //coloca o cifrao no lugar dos espacos em branco

                    if(strlen(REGISTRO.NAME)==41) //caso o tamanho da string seja 41, nao adiciona lixo
                        break;

                    REGISTRO.NAME[j] = '$';
                }

                //LEITURA DO NOME CIENTIFICO DA ESPECIE

                readline(REGISTRO.SCIENTIFIC_NAME);
                for(j=strlen(REGISTRO.SCIENTIFIC_NAME)+1; j<61;j++){    //coloca o cifrao no lugar dos espacos em branco

                    if(strlen(REGISTRO.SCIENTIFIC_NAME)==61) //caso o tamanho da string seja 61, nao adiciona lixo
                        break;

                    REGISTRO.SCIENTIFIC_NAME[j] = '$';

                }

                //LEITURA DA POPULACAO DA ESPECIE

                scanf("%d",&REGISTRO.POPULATION);
                if(REGISTRO.POPULATION<0 ){
                    REGISTRO.SPECIES_ID==-1;
                    printf(ERRO_PADRAO);    //caso o usuario insira uma populacao invalida nao insere o registro no arquivo e retorna erro 
                    IDs_registrados[i]=-1;  //invalida o resgistro como "salvo"
                }

                //LEITURA DO STATUS DA ESPECIE

                readline(REGISTRO.STATUS);
                for(j=strlen(REGISTRO.STATUS)+1; j<9;j++){  //coloca o cifrao no lugar dos espacos em branco

                    if(strlen(REGISTRO.STATUS)==9)  //caso o tamanho da string seja 9, nao adiciona lixo
                        break;

                    REGISTRO.STATUS[j] = '$';
                }

                //LEITURA DA COORDENADA X

                scanf("%f",&REGISTRO.LOCATION_LON);
                //if(REGISTRO.LOCATION_LON<-180 ||  REGISTRO.LOCATION_LON>180){
                //    REGISTRO.SPECIES_ID==-1;
                //    printf(ERRO_PADRAO);    //caso o usuario insira uma coordenada x inexistente   
                //    IDs_registrados[i]=-1;  //invalida o resgistro como "salvo"
                //}

                //LEITURA DA COORDENADA Y
         
                scanf("%f",&REGISTRO.LOCATION_LAT);
                //if(REGISTRO.LOCATION_LAT<-90 ||  REGISTRO.LOCATION_LAT>90){
                //    REGISTRO.SPECIES_ID==-1;
                //    printf(ERRO_PADRAO);    //caso o usuario insira uma coordenada y inexistente   
                //    IDs_registrados[i]=-1;  //invalida o resgistro como "salvo"
                //}

                //LEITURA DO IMPACTO HUMANO ASSOCIADO

                scanf("%d",&REGISTRO.HUMAN_IMPACT);
                if(REGISTRO.HUMAN_IMPACT<0 || REGISTRO.HUMAN_IMPACT>3){
                    REGISTRO.SPECIES_ID==-1;
                    printf(ERRO_PADRAO);    //caso o usuario insira um HUMAN_IMPACT menor que 0 e maior que 3 retorna erro e nao insere o registro no arquivo
                    IDs_registrados[i]=-1;  //invalida o resgistro como "salvo"   
                }
                

                if(REGISTRO.SPECIES_ID!=-1){    //caso algo de errado tenha acontecido na leitura de dados a informacao nao eh inserida no arquivo
                    arquivo = fopen(nomearq, "ab");
                    fwrite(&REGISTRO.SPECIES_ID, 4, 1, arquivo);
                    fwrite(REGISTRO.NAME, 41, 1, arquivo);
                    fwrite(REGISTRO.SCIENTIFIC_NAME, 61, 1, arquivo);
                    fwrite(&REGISTRO.POPULATION, 4, 1, arquivo);
                    fwrite(REGISTRO.STATUS, 9, 1, arquivo);
                    fwrite(&REGISTRO.LOCATION_LON, 4, 1, arquivo);
                    fwrite(&REGISTRO.LOCATION_LAT, 4, 1, arquivo);
                    fwrite(&REGISTRO.HUMAN_IMPACT, 4, 1, arquivo);
                    fclose(arquivo);
                }


            }
        }
        
        binarioNaTela(nomearq); //binario na tela, resultado
    }
}