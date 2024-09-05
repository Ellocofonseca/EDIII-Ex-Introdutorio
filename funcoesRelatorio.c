#include "./funcoesCriadas.h"

//  Essa funcao abre um arquivo ja existente em modo de leitura
//  para que os registros de especie de todo o arquivo sejam exibidos
//  um atras do outro
    

void relatorio_especies()
{
    char nomearq[31];           //nome do arquivo que sera lido
    registro_especie REGISTRO;  //variavel de registro

    scanf("%s",nomearq);
    
    FILE *arquivo;
    arquivo = fopen(nomearq, "rb");
    //abre o arquivo no modo de leitura em binario

    //le os campos de cada registro um de cada vez
    //para evitar problemas, entao quando chegar no
    //fim do arquivo termina o processo

    if(arquivo == NULL){
        printf(ERRO_ARQUIVO);     
    }
    else{

        while(1){

            if(fread(&REGISTRO.SPECIES_ID, 4, 1, arquivo)==0)
                break;
            fread(REGISTRO.NAME, 41, 1, arquivo);
            fread(REGISTRO.SCIENTIFIC_NAME, 61, 1, arquivo);
            fread(&REGISTRO.POPULATION, 4, 1, arquivo);
            fread(REGISTRO.STATUS, 9, 1, arquivo);
            fread(&REGISTRO.LOCATION_LON, 4, 1, arquivo);
            fread(&REGISTRO.LOCATION_LAT, 4, 1, arquivo);
            if(fread(&REGISTRO.HUMAN_IMPACT, 4, 1, arquivo)==0)
                break;

            exibe_registro(REGISTRO);//exibe o registro apos salvar os campos
        }

        fclose(arquivo); // fecha o arquivo
    }
}


//  Essa funcao abre um arquivo ja existente em modo de leitura
//  para que um registro especifico seja exibido de acordo com
//  o RRN que o usuario escolher

void relatorio_RRN()
{
    int rrn;
    char nomearq[31];           //nome do arquivo que sera lido
    registro_especie REGISTRO;  //variavel de registro

    scanf("%s",nomearq);        //le o nome do arquivo que sera aberto
    
    FILE *arquivo;
    arquivo = fopen(nomearq, "rb");    //abre o arquivo no modo de leitura em binario

    if(arquivo == NULL){
        printf(ERRO_ARQUIVO);     
    }
    else{
        scanf("%d",&rrn);                                       //le o rrn do registro que esta sendo procurado
        fseek(arquivo,rrn*131,SEEK_SET);   //ajusta o ponteiro do arquivo para a posicao desejada, byteoffset
        

        if(!(fread(&REGISTRO.SPECIES_ID, 4, 1, arquivo)) || rrn<0){ //le o ID e checa se esta fora do arquivo
            printf(ERRO_RRN_ID);                                    //se o rrn estiver incoerente retorna erro
        }
        else{
            //le o resto dos campos do registro desejado
            fread(REGISTRO.NAME, 41, 1, arquivo);
            fread(REGISTRO.SCIENTIFIC_NAME, 61, 1, arquivo);
            fread(&REGISTRO.POPULATION, 4, 1, arquivo);
            fread(REGISTRO.STATUS, 9, 1, arquivo);
            fread(&REGISTRO.LOCATION_LON, 4, 1, arquivo);
            fread(&REGISTRO.LOCATION_LAT, 4, 1, arquivo);
            fread(&REGISTRO.HUMAN_IMPACT, 4, 1, arquivo);

            exibe_registro(REGISTRO);//exibe o registro apos salvar os campos
        }
        fclose(arquivo); // fecha o arquivo
    }
}


//funcao simples que recebe uma variavel de registro de especie
//e exibe as informacoes contidas naquele registro
void exibe_registro(registro_especie REGISTRO){

    
    setlocale(LC_ALL, "");      //caracteres da lingua portuguesa
    
    printf("ID: %d\n",REGISTRO.SPECIES_ID);
    printf("Nome: %s\n",REGISTRO.NAME);
    printf("Nome Científico: %s\n",REGISTRO.SCIENTIFIC_NAME);

    if(REGISTRO.POPULATION==0){
        printf("População: NULO\n");
    }
    else{
        printf("População: %d\n",REGISTRO.POPULATION);
    }
    
    printf("Status: %s\n",REGISTRO.STATUS);

    printf("Localização: ");
    //aqui os caracteres padrao sao retornados para que o print do numero em float nao use ',' e sim '.' na divisao decimal
    //setlocale(LC_ALL, "English");
    printf("(%.2f, %.2f)\n",REGISTRO.LOCATION_LON,REGISTRO.LOCATION_LAT);

    if(REGISTRO.HUMAN_IMPACT==0){
        printf("Impacto Humano: NULO\n\n");
    }
    else{
        printf("Impacto Humano: %d\n\n",REGISTRO.HUMAN_IMPACT);
    }

}




