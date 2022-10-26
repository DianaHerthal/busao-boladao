#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "funcoes.h"
#include "utilities.h"

//Salvar clientes da memoria no arquivo
void salvar_clientes(cliente *vetorcliente, int *apontultpos, int *qtdclientesnamemoria, char *resultfilename, char *resultfilename2)
{
    FILE *arq = fopen(resultfilename, "w+b");

    if (arq == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE\n");
        return;
    }

    FILE *arq2 = fopen(resultfilename2, "w+b");

    if (arq2 == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE\n");
        return;
    }

    fwrite(vetorcliente, sizeof(cliente), *qtdclientesnamemoria, arq);

    fwrite(apontultpos, sizeof(int), 1, arq2);

    fwrite(qtdclientesnamemoria, sizeof(int), 1, arq2);

    fclose(arq);

    fclose(arq2);

    printf("Arquivo Salvo com Sucesso!\n\n");
}

//Salvar poltronas no arquivo
void salvar_onibus(poltrona *vetorpoltrona, char *resultfilename)
{
    FILE *arq = fopen(resultfilename, "w+b");
    if (arq == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE\n");
        return;
    }

    fwrite(vetorpoltrona, sizeof(poltrona), NPOLTRONAS, arq);

    fclose(arq);

    printf("Arquivo Salvo com Sucesso!\n\n");
}

//Retornar clientes do arquivo para a memoria
void retornar_clientes(cliente **vetorcliente, int *nc, int *i, char *filename, char *filename2)
{
    FILE *arq = fopen(filename, "r+b");

    if (arq == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE\n");
        return;
    }

    FILE *arq2 = fopen(filename2, "r+b");

    if (arq2 == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE\n");
        return;
    }

    fread(i, sizeof(int), 1, arq2);

    fread(nc, sizeof(int), 1, arq2);

    if ((*i) != (*nc)) //Realoca array do tamanho certo
    {
        *vetorcliente = (cliente *)realloc(*vetorcliente, (*nc) * sizeof(cliente));
    }

    fread(*vetorcliente, sizeof(cliente), *i, arq);

    printf("\n\nRetornando %d clientes para memoria\n\n", *i);

    fclose(arq);

    fclose(arq2);

    printf("Arquivo Retornado para Memoria com Sucesso!\n\n");
}

//Retornar poltronas do arquivo para a memoria
void retornar_onibus(poltrona *vetorpoltrona, char *filename)
{
    FILE *arq = fopen(filename, "r+b");
    if (arq == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE\n");
        return;
    }

    int i = 0;
    while (fread(&vetorpoltrona[i], sizeof(poltrona), 1, arq) == 1)
    {
        i++;
    }

    fclose(arq);

    printf("Arquivo Retornado para Memoria com Sucesso!\n\n");
}

//Reserva assento
void reservar_assento(poltrona *vetorpoltrona, cliente *vetorcliente, int nc)
{
    reservar_vender(vetorpoltrona, vetorcliente, nc, 1);
}

//Vende assento
void vender_assento(poltrona *vetorpoltrona, cliente *vetorcliente, int nc)
{
    reservar_vender(vetorpoltrona, vetorcliente, nc, 2);
}

//Funcao auxiliar para reservar ou vender, parametro a // a=0 - vazio, a=1 - reservado, a=2 - vendido
void reservar_vender(poltrona *vetorpoltrona, cliente *vetorcliente, int nc, int a)
{
    int p;
    int n = procurar_cliente_pelo_cpf(vetorcliente, nc);

    if (n == -1)
    {
        return;
    }

    printf("Digite a poltrona desejada\n");
    scanf("%d", &p);

    if (p < 1 || p > NPOLTRONAS)
    {
        printf("Poltrona nao existe\n");
        return;
    }

    strcpy(vetorpoltrona[p - 1].cpf, vetorcliente[n].cpf);
    vetorpoltrona[p - 1].ocupacao = a;
}

//Funcao para cadastrar novos clientes
void cadastrar_cliente(cliente **vetorcliente, int *i, int *nc)
{
    if ((*i) >= (*nc)) //Dobra o tamanho do array quando necessario
    {
        *vetorcliente = (cliente *)realloc(*vetorcliente, (*nc) * 2 * sizeof(cliente));
        (*nc) = (*nc) * 2;
    }
    printf("Digite nome do cliente\n");
    scanf(" %[^\n]", (*vetorcliente)[*i].nome);
    printf("Digite CPF\n");
    scanf("%s", (*vetorcliente)[*i].cpf);
    (*i)++;
}

//Funcao para preencher automaticamente nome e cpf de 10 em 10 porem nao aumenta o array
void cadastrar_clientes_random(cliente **vetorcliente, int *i, int *nc)
{
    if ((*i) >= (*nc)) //Dobra o tamanho do array quando necessario
    {
        *vetorcliente = (cliente *)realloc(*vetorcliente, (*nc) * 2 * sizeof(cliente));
        (*nc) = (*nc) * 2;
    }
    int z = 0;
    while (z < 10)
    {
        strcpy((*vetorcliente)[*i].nome, randstring(40));
        strcpy((*vetorcliente)[*i].cpf, randstring(11));
        (*i)++;
        z++;
    }
}

//Funcao para excluir clientes existentes
void excluir_cliente(cliente *vetorcliente, poltrona *vetorpoltrona, int *i, int nc)
{
    char cpf[TAMCPF];
    printf("Digite o CPF do cliente a ser excluido\n");
    scanf("%s", cpf);
    int k = 0;
    for (int j = 0; j < nc; j++)
    {
        if (strcmp(cpf, vetorcliente[j].cpf) == 0)
        {
            k = 1;
            for (int k = j; k < (nc - 1); k++)
            {
                strcpy(vetorcliente[k].cpf, vetorcliente[k + 1].cpf);
                strcpy(vetorcliente[k].nome, vetorcliente[k + 1].nome);
            }
            (*i)--;
        }
    }

    if (k == 0)
    {
        printf("Nome nao esta cadastrado\n");
        return;
    }

    int excluido = procurar_cliente_no_onibus(vetorpoltrona, cpf);

    if (excluido != -1)
    {
        strcpy(vetorpoltrona[excluido].cpf, "");
        vetorpoltrona[excluido].ocupacao = 0;
    }

    strcpy(vetorcliente[nc].cpf, "");
    strcpy(vetorcliente[nc].nome, "");
}

//Funcao para excluir reserva ou venda realizada
void excluir_reserva_ou_venda(poltrona *vetorpoltrona)
{
    int e;
    printf("Qual posicao excluir?\n");
    scanf("%d", &e);

    if (vetorpoltrona[e - 1].ocupacao == 0)
    {
        printf("Poltrona nao esta ocupada");
        return;
    }

    if (e < 1 || e > NPOLTRONAS)
    {
        printf("Poltrona nao existe\n");
        return;
    }

    strcpy(vetorpoltrona[e - 1].cpf, "");
    vetorpoltrona[e - 1].ocupacao = 0;
}

//Funcao para trocar o cliente que ja realizou a reserva ou compra de lugar
void trocar_assento(poltrona *vetorpoltrona, cliente *vetorcliente, int nc)
{
    int p, o;

    int n = procurar_cliente_pelo_cpf(vetorcliente, nc);

    o = procurar_cliente_no_onibus(vetorpoltrona, vetorcliente[n].cpf);

    if (o == -1)
    {
        printf("Cliente nao esta no poltrona\n");
        return;
    }

    if (vetorpoltrona[o].ocupacao == 0)
    {
        printf("Poltrona de origem esta vazia\n");
        return;
    }

    if (o < 1 || o > NPOLTRONAS)
    {
        printf("Poltrona nao existe\n");
        return;
    }

    printf("Digite a poltrona desejada\n");
    scanf("%d", &p);

    if (vetorpoltrona[p].ocupacao != 0)
    {
        printf("Poltrona ja ocupada\n");
        return;
    }

    if (p < 1 || p > NPOLTRONAS)
    {
        printf("Poltrona nao existe\n");
        return;
    }

    //Troca o assento reservado ou vendido escolhido pelo cliente
    strcpy(vetorpoltrona[p - 1].cpf, vetorpoltrona[o].cpf);
    strcpy(vetorpoltrona[o].cpf, "");
    vetorpoltrona[p - 1].ocupacao = vetorpoltrona[o].ocupacao;
    vetorpoltrona[o].ocupacao = 0;
}

//Exibe as poltronas do poltrona
void exibe_poltronas(poltrona *vetorpoltrona)
{
    printf("-------MOTORISTA-----------------------------------\n---------------------------------------------------\n");
    for (int i = 0; i < NPOLTRONAS; i++)
    {
        if (strcmp(ler_ocupacao(vetorpoltrona, vetorpoltrona[i].ocupacao), "LIVRE") == 0)
            printf(BGRN "[%02d]: %s " RESET, i + 1, ler_ocupacao(vetorpoltrona, vetorpoltrona[i].ocupacao));
        if (strcmp(ler_ocupacao(vetorpoltrona, vetorpoltrona[i].ocupacao), "AV   ") == 0)
            printf(BRED "[%02d]: %s " RESET, i + 1, ler_ocupacao(vetorpoltrona, vetorpoltrona[i].ocupacao));
        if (strcmp(ler_ocupacao(vetorpoltrona, vetorpoltrona[i].ocupacao), "AR   ") == 0)
            printf(BBLU "[%02d]: %s " RESET, i + 1, ler_ocupacao(vetorpoltrona, vetorpoltrona[i].ocupacao));
        if ((i + 1) % 2 == 0)
        {
            printf("    ");
        }
        if ((i + 1) % 4 == 0)
        {
            printf("\n\n");
        }
    }
    printf("\n\n");
}

// Procura o cliente cadastrado pelo nome no array de clientes e retorna sua posicao
int procurar_cliente_pelo_nome(cliente *vetorcliente, int nc)
{
    char procura[TAMNOME];
    printf("Digite o nome do cliente cadastrado\n");
    scanf(" %[^\n]", procura);

    for (int i = 0; i < nc; i++)
    {
        if (strcmp(procura, vetorcliente[i].nome) == 0)
        {
            return i;
        }
    }

    printf("Cliente nao esta cadastrado\n");
    return -1;
}

// Procura o cliente cadastrado pelo cpf no array de clientes e retorna sua posicao
int procurar_cliente_pelo_cpf(cliente *vetorcliente, int nc)
{
    char procura[TAMCPF];
    printf("Digite o cpf do cliente cadastrado\n");
    scanf("%s", procura);

    for (int i = 0; i < nc; i++)
    {
        if (strcmp(procura, vetorcliente[i].cpf) == 0)
        {
            return i;
        }
    }

    printf("Cliente nao esta cadastrado\n");
    return -1;
}

//Procura se o cliente esta no poltrona e retorna -1 se nao estiver
int procurar_cliente_no_onibus(poltrona *vetorpoltrona, char *procura)
{
    for (int i = 0; i < NPOLTRONAS; i++)
    {
        if (strcmp(procura, vetorpoltrona[i].cpf) == 0)
        {
            return i;
        }
    }
    return -1;
}

//Retorna se o assento esta vazio, reservado ou comprado
char *ler_ocupacao(poltrona *vetorpoltrona, int c)
{
    switch (c)
    {
    case 0:
        return "LIVRE";
        break;
    case 1:
        return "AR   ";
        break;
    case 2:
        return "AV   ";
        break;
    default:
        return "NULL ";
        break;
    }
}

//Imprime os dados do cliente cuja a posicao no array foi passada por parametro
void imprimir_cliente(cliente *vetorcliente, int pos)
{
    printf("Nome: %s - CPF: %s\n", vetorcliente[pos].nome, vetorcliente[pos].cpf);
}

//Imprime todos os clientes cadastrados no array
void imprimir_todos_clientes(cliente *vetorcliente, int nc)
{
    for (int i = 0; i < nc; i++)
    {
        imprimir_cliente(vetorcliente, i);
        if (strcmp(vetorcliente[i].nome, "") == 0)
        break;
    }
}

//Retorna numero de clientes no arquivo
int numero_clientes(cliente *vetorcliente, char *filename, FILE *arq)
{
    int count = 0;
    cliente aux;
    int sz;

    while (fread(&aux, sizeof(cliente), 1, arq) != 0)
    {
        count++;
    }

    fseek(arq, 0L, SEEK_END);
    sz = ftell(arq);
    sz /= sizeof(cliente);

    rewind(arq);

    return count;
}