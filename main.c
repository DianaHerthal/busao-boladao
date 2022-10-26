#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "funcoes.h"
#include "utilities.h"

void main()
{
    int c, i = 0;
    int nc = 10;
    srand(time(NULL));
    cliente *vetorcliente;
    vetorcliente = calloc(nc, sizeof(cliente)); //Cria um vetor estruturado com tamanho nc

    poltrona vetorpoltrona[NPOLTRONAS];
    memset(vetorpoltrona, 0, NPOLTRONAS * sizeof(*vetorpoltrona)); //Zera as posicoes do vetor estruturado vetorpoltrona

    exibe_poltronas(vetorpoltrona);

    while (c != -1)
    {
        printf("##### SELECIONE OPCAO #####\n\n0 - Mostrar Ocupacao do Onibus\n1 - Reservar Assento\n2 - Vender Assento\n3 - Cadastrar Cliente\n4 - Excluir Cliente\n5 - Excluir Reserva ou Venda\n6 - Trocar Assento\n7 - Mostrar Informacoes do Cliente pelo Nome\n8 - Mostrar Informacoes do Cliente pelo CPF\n9 - Mostrar Todos os Clientes\n10 - Salva Clientes no Arquivo\n11 - Salva Poltronas no Arquivo\n12 - Retorna Clientes para Memoria\n13 - Retorna Poltronas para Memoria\n14 - Ordena array de cadastros pelo nome do cliente\n15 - Ordena array de cadastro pelo cpf do cliente\n99 - Adiciona 10 pessoas random no onibus\n-1 - Sair\n\nDigite: ");
        scanf("%d", &c);

        switch (c)
        {
        case 0:
            exibe_poltronas(vetorpoltrona);
            break;
        case 1:
            reservar_assento(vetorpoltrona, vetorcliente, nc);
            break;
        case 2:
            vender_assento(vetorpoltrona, vetorcliente, nc);
            break;
        case 3:
            cadastrar_cliente(&vetorcliente, &i, &nc);
            break;
        case 4:
            excluir_cliente(vetorcliente, vetorpoltrona, &i, nc);
            break;
        case 5:
            excluir_reserva_ou_venda(vetorpoltrona);
            break;
        case 6:
            trocar_assento(vetorpoltrona, vetorcliente, nc);
            break;
        case 7:
            imprimir_cliente(vetorcliente, procurar_cliente_pelo_nome(vetorcliente, nc));
            break;
        case 8:
            imprimir_cliente(vetorcliente, procurar_cliente_pelo_cpf(vetorcliente, nc));
            break;
        case 9:
            imprimir_todos_clientes(vetorcliente, nc);
            break;
        case 10:
            salvar_clientes(vetorcliente, &i, &nc, "/home/lucas/Documents/VSCode/clientes.bin", "/home/lucas/Documents/VSCode/info.bin"); //Coloque o endereco do arquivo onde sera escrito
            break;
        case 11:
            salvar_onibus(vetorpoltrona, "/home/lucas/Documents/VSCode/poltronas.bin"); //Coloque o endereco do arquivo lido
            break;
        case 12:
            retornar_clientes(&vetorcliente, &nc, &i, "/home/lucas/Documents/VSCode/clientes.bin", "/home/lucas/Documents/VSCode/info.bin"); //Coloque o endereco do arquivo onde sera escrito
            break;
        case 13:
            retornar_onibus(vetorpoltrona, "/home/lucas/Documents/VSCode/poltronas.bin"); //Coloque o endereco do arquivo lido
            break;
        case 14:
            qsort(vetorcliente, i, sizeof(cliente), compara_nome);
            break;
        case 15:
            qsort(vetorcliente, i, sizeof(cliente), compara_cpf);
            break;
        case 99:
            cadastrar_clientes_random(&vetorcliente, &i, &nc);
            break;
        case -1:
            printf("BYE!\n\n");
            break;
        default:
            printf("ERROR: NO VALID OPTION SELECTED");
            break;
        }
    }
}