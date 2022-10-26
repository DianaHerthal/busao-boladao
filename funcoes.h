#define NPOLTRONAS 40 //Tamanho do onibus
#define TAMCPF 13     //Tamanho do array que armazena cpf
#define TAMNOME 100   //Tamanho do array que armazena nomes

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BBLU "\e[1;34m"
#define RESET "\x1b[0m"

typedef struct
{
    char nome[TAMNOME];
    char cpf[TAMCPF];
} cliente;

typedef struct
{
    char cpf[TAMCPF];
    int ocupacao;
} poltrona;

void reservar_assento(poltrona *vetorpoltrona, cliente *vetorcliente, int nc);

void vender_assento(poltrona *vetorpoltrona, cliente *vetorcliente, int nc);

void reservar_vender(poltrona *vetorpoltrona, cliente *vetorcliente, int nc, int a);

void cadastrar_cliente(cliente **vetorcliente, int *i, int *nc);

void excluir_cliente(cliente *vetorcliente, poltrona *vetorpoltrona, int *i, int nc);

void excluir_reserva_ou_venda(poltrona *vetorpoltrona);

void trocar_assento(poltrona *vetorpoltrona, cliente *vetorcliente, int nc);

void exibe_poltronas(poltrona *vetorpoltrona);

int procurar_cliente_pelo_nome(cliente *vetorcliente, int nc);

int procurar_cliente_pelo_cpf(cliente *vetorcliente, int nc);

int procurar_cliente_no_onibus(poltrona *vetorpoltrona, char *procura);

char *ler_ocupacao(poltrona *vetorpoltrona, int c);

void imprimir_cliente(cliente *vetorcliente, int pos);

void imprimir_todos_clientes(cliente *vetorcliente, int nc);

void salvar_clientes(cliente *vetorcliente, int *apontultpos, int *qtdclientesnamemoria, char *resultfilename, char *resultfilename2);

void salvar_onibus(poltrona *poltronas, char *resultfilename);

void retornar_clientes(cliente **vetorcliente, int *nc, int *i, char *filename, char *filename2);

void retornar_onibus(poltrona *poltronas, char *filename);

int numero_clientes(cliente *vetorcliente, char *filename, FILE *arq);

void cadastrar_clientes_random(cliente **vetorcliente, int *i, int *nc);