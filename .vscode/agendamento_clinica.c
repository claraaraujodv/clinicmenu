/*SISTEMA DE AGENDAMENTO DE CONSULTAS DE UMA CLÍNICA MÉDICA
 * TRABALHO AVALIATIVO P2 - ALGORITMO E PROGRAMAÇÃO
 * Professor: Hilson Silva
 * Turma: SNYDER * Aluno(a): Maria Vitória Salgado, Clara Araújo, Leticia Valentino
 * Tema O: Sistema de Agendamento de Consultas - Clínica Médica
 */

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis das categorias Paciente, Médico e Consulta
#define MAX_PACIENTES 100
#define MAX_MEDICOS 20
#define MAX_CONSULTAS 50

 // structs para representar as entidades do sistema
 
typedef struct {
    char nome[50];
    char cpf[15];
    char dataNascimento[11];
    char telefone[15];
    char tipoSanguineo[4];
    char genero[10];
} Paciente;

typedef struct {
    char nome[50];
    char crm[15];
    char especialidade[30];
    float valorConsulta;
    char turno[10];
} Medico;

typedef struct {
    int codigoConsulta;
    char data[11];
    char horario[6];
    char crm[15];
    char cpfPaciente[15];
    char status[20];
} Consulta;

// Vetores para armazenar os dados dos pacientes, médicos e consultas

Paciente pacientes[MAX_PACIENTES];
int totalPacientes = 0;

Medico medicos[MAX_MEDICOS];
int totalMedicos = 0;

Consulta consultas[MAX_CONSULTAS];
int totalConsultas = 0;

// Prototipos das funcoes

void cadastrarPaciente();
void cadastrarMedico();
void imprimirPacientes();
void imprimirMedicos();
void imprimirConsultas();
void agendarConsulta();
void alterarStatus();

// Função para exibir o menu principal

void menuPrincipal() {
    printf("\n==============================\n");
    printf("        CLINICA SAÚDE + \n"  );
    printf("==============================\n");
    printf("  1 - CADASTROS\n");
    printf("  2 - IMPRESSAO\n");
    printf("  3 - CONSULTAS\n");
    printf("  4 - SAIR\n");
    printf("==============================\n");
    printf("  INFORME A OPERACAO DESEJADA: ");
}

// submenu de cadastros

void menuCadastros() {

    int opcao;
do {
    printf("\n==============================\n");
    printf("         CADASTROS\n");
    printf("==============================\n");
    printf("  1 - CADASTRAR PACIENTE\n");
    printf("  2 - CADASTRAR MEDICO\n");
    printf("  3 - VOLTAR AO MENU PRINCIPAL\n");
    printf("================================\n");
    printf("  INFORME A OPERACAO DESEJADA: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao){
    case 1: cadastrarPaciente();
        break;
    case 2: cadastrarMedico();
        break;
    case 3: printf("Voltando ao menu principal...\n");
        break;
        default:
        printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

// submenu de impressão de dados
void menuImpressao() {
    int opcao;
     
do {
    printf("\n==============================\n");
    printf("         IMPRESSAO\n");
    printf("==============================\n");
    printf("  1 - IMPRIMIR PACIENTES\n");
    printf("  2 - IMPRIMIR MEDICOS\n");
    printf("  3 - IMPRIMIR CONSULTAS\n");
    printf("  4 - VOLTAR AO MENU PRINCIPAL\n");
    printf("==============================\n");
    printf("  INFORME A OPERACAO DESEJADA: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao){
    case 1: imprimirPacientes();
        break;
    case 2: imprimirMedicos();
        break;
    case 3: imprimirConsultas();
        break;
    case 4:
        printf("Voltando ao menu principal...\n");
        break;
    default:
        printf("Opcao invalida! Tente novamente.\n");
        break;
         }
        } while (opcao != 4);    
}

// submenu de agendamento de consultas
void menuConsultas() {
    int opcao;

    do {

    printf("\n==============================\n");
    printf("         AGENDAMENTO\n");
    printf("==============================\n");
    printf("  1 - AGENDAR CONSULTA\n");
    printf("  2 - ALTERAR STATUS\n");
    printf("  3 - VOLTAR AO MENU PRINCIPAL\n");
    printf("==============================\n");
    printf("  INFORME A OPERACAO DESEJADA: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao){
        case 1: agendarConsulta();
        break;
        case 2: alterarStatus();
        break;
        case 3:
        printf("Voltando ao menu principal...\n");
        break;
        default:
        printf("Opcao invalida! Tente novamente.\n");
        break;
        }
    } while (opcao != 3);
}



// Funcao para cadastrar um novo paciente
void cadastrarPaciente() {
    printf("\n--- CADASTRAR PACIENTE ---\n");

    if (totalPacientes >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido!\n");
        return;
    }

    Paciente p;

    printf("Nome: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("CPF: ");
    fgets(p.cpf, sizeof(p.cpf), stdin);
    p.cpf[strcspn(p.cpf, "\n")] = '\0';

    printf("Data de nascimento (DD/MM/AAAA): ");
    fgets(p.dataNascimento, sizeof(p.dataNascimento), stdin);
    p.dataNascimento[strcspn(p.dataNascimento, "\n")] = '\0';

    printf("Telefone: ");
    fgets(p.telefone, sizeof(p.telefone), stdin);
    p.telefone[strcspn(p.telefone, "\n")] = '\0';

    printf("Tipo sanguineo: ");
    fgets(p.tipoSanguineo, sizeof(p.tipoSanguineo), stdin);
    p.tipoSanguineo[strcspn(p.tipoSanguineo, "\n")] = '\0';

    printf("Genero: ");
    fgets(p.genero, sizeof(p.genero), stdin);
    p.genero[strcspn(p.genero, "\n")] = '\0';

    pacientes[totalPacientes] = p;
    totalPacientes++;

    // Salva o paciente no arquivo pacientes.txt
    FILE *arquivo = fopen("pacientes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo pacientes.txt!\n");
        return;
    }
    fprintf(arquivo, "%s;%s;%s;%s;%s;%s\n",
            p.nome, p.cpf, p.dataNascimento,
            p.telefone, p.tipoSanguineo, p.genero);
    fclose(arquivo);

    printf("Paciente cadastrado com sucesso!\n");
}

// Funcao para cadastrar um novo medico
void cadastrarMedico() {
    printf("\n--- CADASTRAR MEDICO ---\n");

    if (totalMedicos >= MAX_MEDICOS) {
        printf("Limite de medicos atingido!\n");
        return;
    }

    Medico m;

    printf("Nome: ");
    fgets(m.nome, sizeof(m.nome), stdin);
    m.nome[strcspn(m.nome, "\n")] = '\0';

    printf("CRM: ");
    fgets(m.crm, sizeof(m.crm), stdin);
    m.crm[strcspn(m.crm, "\n")] = '\0';

    printf("Especialidade: ");
    fgets(m.especialidade, sizeof(m.especialidade), stdin);
    m.especialidade[strcspn(m.especialidade, "\n")] = '\0';

    printf("Valor da consulta: ");
    scanf("%f", &m.valorConsulta);
    getchar();

    printf("Turno (manha/tarde/noite): ");
    fgets(m.turno, sizeof(m.turno), stdin);
    m.turno[strcspn(m.turno, "\n")] = '\0';

    medicos[totalMedicos] = m;
    totalMedicos++;

    // Salva o medico no arquivo medicos.txt
    FILE *arquivo = fopen("medicos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo medicos.txt!\n");
        return;
    }
    fprintf(arquivo, "%s;%s;%s;%.2f;%s\n",
            m.nome, m.crm, m.especialidade,
            m.valorConsulta, m.turno);
    fclose(arquivo);

    printf("Medico cadastrado com sucesso!\n");
}

// Funcao para imprimir a lista de pacientes
void imprimirPacientes() {
    printf("\n--- LISTA DE PACIENTES ---\n");

    if (totalPacientes == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalPacientes; i++) {
        printf("\nPaciente %d\n", i + 1);
        printf("  Nome: %s\n", pacientes[i].nome);
        printf("  CPF: %s\n", pacientes[i].cpf);
        printf("  Data de nascimento: %s\n", pacientes[i].dataNascimento);
        printf("  Telefone: %s\n", pacientes[i].telefone);
        printf("  Tipo sanguineo: %s\n", pacientes[i].tipoSanguineo);
        printf("  Genero: %s\n", pacientes[i].genero);
    }
}

// Funcao para imprimir a lista de medicos
void imprimirMedicos() {
    printf("\n--- LISTA DE MEDICOS ---\n");

    if (totalMedicos == 0) {
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalMedicos; i++) {
        printf("\nMedico %d\n", i + 1);
        printf("  Nome: %s\n", medicos[i].nome);
        printf("  CRM: %s\n", medicos[i].crm);
        printf("  Especialidade: %s\n", medicos[i].especialidade);
        printf("  Valor da consulta: R$ %.2f\n", medicos[i].valorConsulta);
        printf("  Turno: %s\n", medicos[i].turno);
    }
}

// Funcao para imprimir a lista de consultas
void imprimirConsultas() {
    printf("\n--- LISTA DE CONSULTAS ---\n");

    if (totalConsultas == 0) {
        printf("Nenhuma consulta agendada.\n");
        return;
    }

    for (int i = 0; i < totalConsultas; i++) {
        printf("\nConsulta %d\n", i + 1);
        printf("  Codigo: %d\n", consultas[i].codigoConsulta);
        printf("  Data: %s\n", consultas[i].data);
        printf("  Horario: %s\n", consultas[i].horario);
        printf("  CRM do medico: %s\n", consultas[i].crm);
        printf("  CPF do paciente: %s\n", consultas[i].cpfPaciente);
        printf("  Status: %s\n", consultas[i].status);
    }
}

// Funcao para agendar uma nova consulta
void agendarConsulta() {
    printf("\n--- AGENDAR CONSULTA ---\n");

    if (totalConsultas >= MAX_CONSULTAS) {
        printf("Limite de consultas atingido!\n");
        return;
    }

    if (totalPacientes == 0 || totalMedicos == 0) {
        printf("E necessario ter pelo menos um paciente e um medico cadastrados.\n");
        return;
    }

    Consulta c;

    printf("Codigo da consulta: ");
    scanf("%d", &c.codigoConsulta);
    getchar();

    printf("Data (DD/MM/AAAA): ");
    fgets(c.data, sizeof(c.data), stdin);
    c.data[strcspn(c.data, "\n")] = '\0';

    printf("Horario (HH:MM): ");
    fgets(c.horario, sizeof(c.horario), stdin);
    c.horario[strcspn(c.horario, "\n")] = '\0';

    printf("CRM do medico: ");
    fgets(c.crm, sizeof(c.crm), stdin);
    c.crm[strcspn(c.crm, "\n")] = '\0';

    // Verifica se o CRM existe
    int medicoEncontrado = 0;
    for (int i = 0; i < totalMedicos; i++) {
        if (strcmp(medicos[i].crm, c.crm) == 0) {
            medicoEncontrado = 1;
            break;
        }
    }
    if (!medicoEncontrado) {
        printf("Medico com CRM %s nao encontrado!\n", c.crm);
        return;
    }

    // Verifica se o medico ja tem consulta nesse mesmo dia e horario
    for (int i = 0; i < totalConsultas; i++) {
        if (strcmp(consultas[i].crm, c.crm) == 0 &&
            strcmp(consultas[i].data, c.data) == 0 &&
            strcmp(consultas[i].horario, c.horario) == 0) {
            printf("Esse medico ja tem uma consulta marcada nesse dia e horario!\n");
            return;
        }
    }

    printf("CPF do paciente: ");
    fgets(c.cpfPaciente, sizeof(c.cpfPaciente), stdin);
    c.cpfPaciente[strcspn(c.cpfPaciente, "\n")] = '\0';

    // Verifica se o CPF existe
    int pacienteEncontrado = 0;
    for (int i = 0; i < totalPacientes; i++) {
        if (strcmp(pacientes[i].cpf, c.cpfPaciente) == 0) {
            pacienteEncontrado = 1;
            break;
        }
    }
    if (!pacienteEncontrado) {
        printf("Paciente com CPF %s nao encontrado!\n", c.cpfPaciente);
        return;
    }

    // Toda consulta nova comeca com status "agendada"
    strcpy(c.status, "agendada");

    consultas[totalConsultas] = c;
    totalConsultas++;

    // Salva a consulta no arquivo consultas.txt
    FILE *arquivo = fopen("consultas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo consultas.txt!\n");
        return;
    }
    fprintf(arquivo, "%d;%s;%s;%s;%s;%s\n",
            c.codigoConsulta, c.data, c.horario,
            c.crm, c.cpfPaciente, c.status);
    fclose(arquivo);

    printf("Consulta agendada com sucesso!\n");
}

// Funcao para alterar o status de uma consulta
void alterarStatus() {
    printf("\n--- ALTERAR STATUS ---\n");

    if (totalConsultas == 0) {
        printf("Nenhuma consulta agendada.\n");
        return;
    }

    int codigo;
    printf("Informe o codigo da consulta: ");
    scanf("%d", &codigo);
    getchar();

    int posicao = -1;
    for (int i = 0; i < totalConsultas; i++) {
        if (consultas[i].codigoConsulta == codigo) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Consulta com codigo %d nao encontrada!\n", codigo);
        return;
    }

    printf("Status atual: %s\n", consultas[posicao].status);
    printf("Escolha o novo status:\n");
    printf("  1 - agendada\n");
    printf("  2 - confirmada\n");
    printf("  3 - cancelada\n");
    printf("  4 - concluida\n");
    printf("Opcao: ");

    int opcao;
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1: strcpy(consultas[posicao].status, "agendada"); break;
        case 2: strcpy(consultas[posicao].status, "confirmada"); break;
        case 3: strcpy(consultas[posicao].status, "cancelada"); break;
        case 4: strcpy(consultas[posicao].status, "concluida"); break;
        default:
            printf("Opcao invalida! Status nao alterado.\n");
            return;
    }

    printf("Status alterado para: %s\n", consultas[posicao].status);
}

int main() { //fica sempre no final do código, para evitar erros de declaração de funções
    int opcao;
    char usuario[50], senha[15];
    int LoginAtivo = 0;

    for (int tentativa = 1; tentativa <= 3; tentativa++) {
        printf("+==============================+\n");
        printf("|      Acesso a Aplicacao      |\n");
        printf("+==============================+\n");
        printf("Usuario.....:\n");
        scanf("%s", usuario);
        printf("Senha.......:\n");
        scanf("%s", senha);
        getchar();

        if(strcmp(usuario,"admin")==0 && strcmp(senha,"admin")==0){
            LoginAtivo=1;
            break;
        }else{
            printf("Usuario ou senha incorretos!\n");
        }
    }

    if (!LoginAtivo) {
        printf("Numero de tentativas excedido. Encerrando o sistema...\n");
        return 0;
    }

    do {
        menuPrincipal();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao){
        
            case 1: menuCadastros();
                break;
            case 2: menuImpressao();
                break;
            case 3: menuConsultas();
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
            }
        } while (opcao != 4);


}