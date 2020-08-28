#include <iostream>
#include <cstring>
#include <cstdio>
#include <locale>
#include <cstdlib>
#include <conio.h>
#include <cctype>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <climits>
using namespace std;

//ESTRUTURA PARA CADASTRAR CLIENTES
struct clientes
{
	string NM_Cliente;
	string NR_CPF;
	string NR_Telefone;
	string DS_Email;
	string DS_Endereco;
	string DT_Cadastro;
	int ID_Cliente;
	int ClienteAtivo;
};
struct clientes Cliente[5000]; //VETOR PARA RECEBER OS CLIENTES QUANDO CADASTRADOS


//ESTRUTURA PARA CADASTRAR PROCEDIMENTOS
struct procedimentos
{
	clientes CliProcedimento;
	string NM_Procedimento;
	string QT_Sessao;
	double PR_Procedimento;
	double VL_Lucro;
	string DT_Procedimento;
	int ID_Categoria;
	int ID_Procedimento;
	int ProcedimentoAtivo;
};
struct procedimentos Procedimento[1000]; //VETOR PARA RECEBER OS PROCEDIMENTOS


fstream arquivo; //VARIÁVEL PARA MANIPULAR ARQUIVO, TANTO LEITURA COMO ESCRITA


int i = 0; //CONTADOR PARA GUARDAR E VISUALIZAR DADOS
int contador = 0; //CONTADOR PARA GUARDAR E VISUALIZAR DADOS
int menu = 0; //VARIÁVEL PARA RECEBER O CASE DO MENU
char op; // VARIÁVEL PARA RECEBER DECISÕES (S|N)
int listcadastro = 0; //VARIÁVEL PARA ESCOLHER DENTRO DO MENU CASE (3)
int opcaoexcliente = 0; //VARIÁVEL PARA ESCOLHER DENTRO DO MENU CASE (2)
int opcadastro = 0; //VARIÁVEL PARA ESCOLHER DENTRO DO MENU CASE (1)
int digitofinal = 0;
int geracodigo = 1; //VARIÁVEL UTILIZADA PARA DAR CÓDIGO AO CLIENTE NO CADASTRO, SOMANDO +1 A CADA CADASTRO
int geracodigoprocedimento = 1;
int verificador = 0;
int contadorprocedimento = 0;
int listprocedimento = 0;
int opcaolistagem = 0;
int menuadm = 0;
int logado = 0; //VARIÁVEL PARA SETAR SE O LOGIN FOI SUCEDIDO OU NÃO
int adm_logado = 0; //VARIÁVEL PARA SETAR SE O LOGIN ADM FOI SUCEDIDO OU NÃO


void cadastrar_cliente(); //FUNÇÃO PARA CADASTRAR CLIENTES
void backupcliente();
void carregarclientes();
void sonumeros();
void validanumerico(string campo);
void validaletra(string campo);
void validacampobranco(string campo);
void CPF_cadastrado(string campo);
void CPF_tamanho(string campo);
void consulta_cliente();
void excluir_cliente();
void lista_cliente();
void cadastrar_procedimento();
void backupprocedimento();
void carregarprocedimentos();
void consulta_procedimento();
void lista_todosprocedimentos();
void lista_porprocedimento(int idprocedimento);
void excluir_procedimento();
void procedimentos_cadastrados();
void clientes_cadastrados();
void gerenciamento();
void contabil();
void usuario_login();
void adm_login();
void alterar_e_excluir();
void alterar_cliente();



int main(void)
{
	system("title Studio Carol Cruz");
	system("Color 0F");
	system("MODE con cols=168 lines=10000");
	system("chcp 1252 > nul"); // resolvendo questão de acentuação, tanto em entrada quanto saída de dados.


	usuario_login();

	if(logado == 1) //VALIDAÇÃO, SE FOR 1 O LOGIN NÃO FOI SUCEDIDO
	{
		fflush(stdin);
		return main();
	}
	else if(logado == 2) //VALIDAÇÃO, SE FOR 2 O LOGIN FOI SUCEDIDO E LIBERA O SISTEMA
	{
		carregarclientes();
		carregarprocedimentos();
		
		do{
			system("cls");
			cout << "\n" << endl; //MENU PRINCIPAL COM TODAS AS OPÇÕES DISPONÍVEIS DO SISTEMA
			cout << "\t\t\t\t\t\t\t\t _________________________________________________________________ " << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                 |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                S T U D I O   C A R O L   C R U Z                |" << endl;
			cout << "\t\t\t\t\t\t\t\t|_________________________________________________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t|                          MENU PRINCIPAL                         |" << endl;
			cout << "\t\t\t\t\t\t\t\t|=================================================================|" << endl;
			cout << "\t\t\t\t\t\t\t\t|                               |                                 |" << endl;
			cout << "\t\t\t\t\t\t\t\t| [1] - CADASTRAR CLIENTE       | [4] - CADASTRAR PROCEDIMENTO    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|_______________________________|_________________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t|                               |                                 |" << endl;
			cout << "\t\t\t\t\t\t\t\t| [2] - ALTERAR/EXCLUIR CLIENTE | [5] - EXCLUIR PROCEDIMENTO      |" << endl;
			cout << "\t\t\t\t\t\t\t\t|_______________________________|_________________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t|                               |                                 |" << endl;
			cout << "\t\t\t\t\t\t\t\t| [3] - CLIENTES CADASTRADOS    | [6] - PROCEDIMENTOS CADASTRADOS |" << endl;
			cout << "\t\t\t\t\t\t\t\t|_______________________________|_________________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                 |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                   [7] - ACESSAR GERENCIAMENTO                   |" << endl;
			cout << "\t\t\t\t\t\t\t\t|_________________________________________________________________|" << endl;
			cout << "\n\t\t\t\t\t\t\t\t -> O QUE DESEJA REALIZAR: "; //PEDINDO A OPÇÃO DO MENU
			fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
			sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
			menu = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.
	
			while(menu < 0 || menu > 7 || menu == 13) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
			{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t _______________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t|              **OPCAO INVALIDA!!!**            |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t|____-> DIGITE UMA OPCAO APRESENTADA NO MENU____|" << endl;
					cout << "\n\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
					fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
					sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
					menu = digitofinal; //NOVAMENTE, PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.
			}
	
			system("cls");
	
			while(menu == 1) //<INICIO DO (1)PRIMEIRO CASE DO MENU> CADASTRAR CLIENTE******************
			{
				cadastrar_cliente();
			break;
			}
	
			while(menu == 2) //<INICIO DO (2)SEGUNDO CASE DO MENU> EXCLUIR CADASTRO***************
			{
				alterar_e_excluir();
			break;
			}
	
			while(menu == 3)//<INICIO DO (3)TERCEIRO CASE DO MENU> CLIENTES CADASTRADOS**************
			{
				clientes_cadastrados();
			break;
			}
	
			while(menu == 4)
			{
				cadastrar_procedimento();
			break;
			}
			
			while(menu == 5)
			{
				excluir_procedimento();
			break;
			}
			
			while(menu == 6)
			{
				procedimentos_cadastrados();
			break;
			}
			
			while(menu == 7)
			{
				adm_login();
				
				if(adm_logado == 1) //VALIDAÇÃO, SE FOR 1 O LOGIN NÃO FOI SUCEDIDO
				{
					fflush(stdin);
					break;
				}
				else if(adm_logado == 2) //VALIDAÇÃO, SE FOR 2 O LOGIN FOI SUCEDIDO E LIBERA O SISTEMA
				{
					gerenciamento();
				}
			
			break;
			}
	
		}while(menu != 8 || menu < 8);
	}
}



void cadastrar_cliente()
{
	cout << "\n" << endl; //DANDO AS OPÇÕES DENTRO DA OPÇÃO (1) DO MENU PRINCIPAL
	cout << "\t\t\t\t\t\t\t\t\t\t _____________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|    <<CADASTRAR CLIENTE>>    |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|=============================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU       |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - CADASTRAR CLIENTE      |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
	fflush(stdin);//LIMPANDO O BUFFER DE ENTRADA DE DADOS
	sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
	opcadastro = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.

	while(opcadastro != 1 && opcadastro != 2) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (1|2)_____|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
		fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
		sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
		opcadastro = digitofinal; //NOVAMENTE, PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.
	}


	while(opcadastro == 1)
	{
		break; //RETORNA AO MENU PRINCIPAL
	}

	while(opcadastro == 2)
	{
		do{ //LAÇO DE REPETIÇÃO PARA REALIZAR CADASTROS DE CLIENTES
			time_t agora;
		    char datahora[100];
		
		    /* Recupera a quantidade de segundos desde 01/01/1970 */
		    agora = time(NULL);
		
		    /* Formata a data e a hora da forma desejada */
		    strftime( datahora, sizeof(datahora), "%d.%m.%Y - %H:%M:%S", localtime( &agora ) );
		
		    Cliente[contador].DT_Cadastro = (std::string) datahora;
	
			Cliente[contador].ID_Cliente = geracodigo; //PASSANDO PARA O CLIENTE NA POSIÇÃO [] DO VETOR, O CÓDIGO GERADO PELA VARIÁVEL GERACODIGO
			
			bool cpfcadastrado = false;
	
			system("cls"); //LIMPANDO A TELA
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                     <<NOVO CADASTRO DE CLIENTE>>                   |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
			cout << "\t\t\t\t\t\t\t\t|" << endl;
	
			do{
				cout << "\t\t\t\t\t\t\t\t| NOME: ";
				fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
				getline(cin,Cliente[contador].NM_Cliente); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
				validacampobranco(Cliente[contador].NM_Cliente);
	
					if(verificador == 1)
					{
						validaletra(Cliente[contador].NM_Cliente);
					}
			}while(verificador == 0);
	
			do{
				cout << "\t\t\t\t\t\t\t\t| CPF: ";
				fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
				getline(cin,Cliente[contador].NR_CPF); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
				
				validacampobranco(Cliente[contador].NR_CPF);
					
					if(verificador == 1)
					{
						validanumerico(Cliente[contador].NR_CPF);
						
						if(verificador == 1)
						{
							CPF_tamanho(Cliente[contador].NR_CPF);
							
							if(verificador == 1)
							{
								CPF_cadastrado(Cliente[contador].NR_CPF);
									
								if(verificador == 0)
								{
									cout << "\t\t\t\t\t\t\t\t -> DESEJA INFORMAR OUTRO CPF? (S|N): ";								
									fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
									cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
									op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
									cout << endl;
							
									while(op != 'S' && op !='N') //VALIDAÇÃO DA OPÇÃO DIGITADA
									{
										cout << "\n" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
										cout << "\n\t\t\t\t\t\t\t\t -> DESEJA INFORMAR OUTRO CPF? (S|N): ";
										fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
										cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
										op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
										cout << endl;
									}
									
									if(op == 'S')
									{
										verificador = 0;
									}
									else
									{
										cpfcadastrado = true;
										break;
									}
								}
							}					
						}
						
					}					
			}while(verificador == 0);
	
			if(cpfcadastrado == false)
			{
				do{
					cout << "\t\t\t\t\t\t\t\t| TELEFONE: ";
					fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
					getline(cin,Cliente[contador].NR_Telefone); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
					
					validacampobranco(Cliente[contador].NR_Telefone);
		
					if(verificador == 1)
						{
							validanumerico(Cliente[contador].NR_Telefone);
						}
				}while(verificador == 0);
		
				do{
					cout << "\t\t\t\t\t\t\t\t| E-MAIL: ";
					fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
					getline(cin,Cliente[contador].DS_Email); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
		
					validacampobranco(Cliente[contador].DS_Email);	
								
				}while(verificador == 0);
		
				do{
					cout << "\t\t\t\t\t\t\t\t| ENDERECO: ";
					fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
					getline(cin,Cliente[contador].DS_Endereco); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
		
					validacampobranco(Cliente[contador].DS_Endereco);
					
				}while(verificador == 0);
		
				//MOSTRANDO A DATA QUE O CLIENTE ESTÁ CADASTRADO, DE ACORDO COM A DATA QUE ESTÁ NA MÁQUINA QUE ESTÁ EXECUTANDO O PROGRAMA
				cout << "\t\t\t\t\t\t\t\t| DATA DE CADASTRO: " << Cliente[contador].DT_Cadastro << endl;
		
				//MOSTRANDO O CÓDIGO DO CLIENTE QUE ESTÁ SENDO CADASTRADO
				cout << "\t\t\t\t\t\t\t\t| CODIGO DO CLIENTE: " << Cliente[contador].ID_Cliente << endl;
				cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
		
				Cliente[contador].ClienteAtivo = 1; //PASSANDO O VALOR (1), SIGNIFICANDO QUE O CLIENTE ESTÁ ATIVO
		
				cout << "\n\t\t\t\t\t\t\t\t -> CONFIRMAR CADASTRO DE CLIENTE? (S|N): ";
				fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
				cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
				op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
		
				while(op != 'S' && op !='N') //VALIDAÇÃO DA OPÇÃO DIGITADA
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
					cout << "\n\t\t\t\t\t\t\t\t -> CONFIRMAR CADASTRO DE CLIENTE? (S|N): ";
					fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
					cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
					op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
				}
		
				if(op == 'S')
				{
					contador++; //INCREMENTANDO CONTADOR DE CLIENTES PARA PODER RECEBER UM NOVO EM OUTRA POSIÇÃO DO VETOR
					geracodigo++; //INCREMENTANDO O GERACODIGO, PARA GERAR UM NOVO CODIGO DO CLIENTE
		
					backupcliente();
		
					cout << endl;
					cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
					cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
					cout << "\t\t\t\t\t\t\t\t|               -> CLIENTE CADASTRADO COM SUCESSO!!!                 |" << endl;
					cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
				}
				else if(op == 'N')
				{
					cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
					cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
					cout << "\t\t\t\t\t\t\t\t|               -> CADASTRO CANCELADO COM SUCESSO!!!                 |" << endl;
					cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
				}
			}
	
			cout << "\n\n";
			cout << "\t\t\t\t\t\t\t\t -> DESEJA REALIZAR NOVO CADASTRO? (S|N): ";
			fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
			cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
			op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
	
			while(op != 'S' && op !='N') //VALIDAÇÃO DA OPÇÃO DIGITADA
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
				cout << "\n\t\t\t\t\t\t\t\t -> DESEJA REALIZAR NOVO CADASTRO? (S|N): ";
				fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
				cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
				op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
			}
	
			system("cls"); //LIMPANDO A TELA
	
		} while(op == 'S'); //ENQUANTO FOR 'S', O LOOP CONTINUARÁ PARA CADASTRAR NOVO CLIENTE
	break;
	}   
}

void backupcliente()
{
	int corrigecodigo = 1;
	
	for(i = 0; i < contador; i++)
	{
		Cliente[i].ID_Cliente = corrigecodigo;
		corrigecodigo++;
	}
	
	arquivo.open("clientes.txt", ios::out | ios::trunc);

	for(i = 0; i < contador; i++)
	{
		if(Cliente[i].ClienteAtivo == 1)
		{
			arquivo << Cliente[i].NM_Cliente << endl; //ESCREVENDO NO ARQUIVO A LINHA DIGITADA PELO USUÁRIO
			arquivo << Cliente[i].NR_CPF << endl; //ESCREVENDO NO ARQUIVO A LINHA DIGITADA PELO USUÁRIO
			arquivo << Cliente[i].NR_Telefone << endl; //ESCREVENDO NO ARQUIVO A LINHA DIGITADA PELO USUÁRIO
			arquivo << Cliente[i].DS_Email << endl;
			arquivo << Cliente[i].DS_Endereco << endl; //ESCREVENDO NO ARQUIVO A LINHA DIGITADA PELO USUÁRIO
			arquivo << Cliente[i].DT_Cadastro << endl; //ESCREVENDO NO ARQUIVO A DATA
			arquivo << Cliente[i].ID_Cliente << endl; //ESCREVENDO NO ARQUIVO O CÓDIGO DO CLIENTE CADASTRADO
			arquivo << Cliente[i].ClienteAtivo << endl;

			arquivo << "\n"; //PULANDO LINHA NO ARQUIVO
		}
	}
	arquivo.close(); //FECHANDO O ARQUIVO
}

void carregarclientes()
{
	//TRAZENDO OS CLIENTES NOVAMENTE PARA O SISTEMA, DO ARQUIVO TXT	
	clientes cli[5000];

	arquivo.open("clientes.txt", ios::in);

	if(arquivo.is_open())
	{
		string linha;
		int numlinha = 1;

		while(getline(arquivo, linha))
		{
			if(numlinha%9 == 1)
			{
				cli[contador].NM_Cliente = linha;
				Cliente[contador].NM_Cliente = cli[contador].NM_Cliente;
			}
			else if(numlinha%9 == 2)
			{
				cli[contador].NR_CPF = linha;
				Cliente[contador].NR_CPF = cli[contador].NR_CPF;
			}
			else if(numlinha%9 == 3)
			{
				cli[contador].NR_Telefone = linha;
				Cliente[contador].NR_Telefone = cli[contador].NR_Telefone;
			}
			else if(numlinha%9 == 4)
			{
				cli[contador].DS_Email = linha;
				Cliente[contador].DS_Email = cli[contador].DS_Email;
			}
			else if(numlinha%9 == 5)
			{
				cli[contador].DS_Endereco = linha;
				Cliente[contador].DS_Endereco = cli[contador].DS_Endereco;
			}
			else if(numlinha%9 == 6)
			{
				cli[contador].DT_Cadastro = linha;
				Cliente[contador].DT_Cadastro = cli[contador].DT_Cadastro;
			}
			else if(numlinha%9 == 7)
			{
				int converte;
				converte = atoi(linha.c_str());
				cli[contador].ID_Cliente = converte;
				Cliente[contador].ID_Cliente = cli[contador].ID_Cliente;
				geracodigo = (Cliente[contador].ID_Cliente + 1);
			}
			else if(numlinha%9 == 8)
			{
				int converte2;
				converte2 = atoi(linha.c_str());
				cli[contador].ClienteAtivo = converte2;
				Cliente[contador].ClienteAtivo = cli[contador].ClienteAtivo;
				contador++;
			}
		numlinha++;
		}
	arquivo.close();
	}
}

void sonumeros()
{
	char digitado[50];//armazena o que foi digitado pelo usuário
    char guarda_digito;//armazena cada caractere digitado pelo usuário
    int i=0;//variável para controlar o índice do vetor de caracteres
	digitofinal=0;//variável para armazenar a conversão do que foi digitado pelo usuário

   	 do
        {
       guarda_digito=getch();//captura o caractere digitado pelo usuário
           if (isdigit(guarda_digito)!=0)//se for um número
           {
          digitado[i] = guarda_digito;//armazena no vetor de caracteres
          i++;//incrementa o índice do vetor de caracteres
          cout << guarda_digito;//exibe o caractere digitado
       }
       else if(guarda_digito == 8&&i)//se for pressionada a tecla BACKSPACE e houver caracteres já digitados
       {
          digitado[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
          i--;//o índice do vetor de caracteres é decrementado
          cout << "\b \b";//o caractere digitado é apagado da tela
       }
    }while(guarda_digito!=13);//o loop vai ser executado até que a tecla pressionada seja o ENTER (código 13 na tabela ASCII)

    digitado[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
    digitofinal = atoi(digitado);//a variável numero recebe o valor do vetor de caracteres convertido para inteiro

}

void validacampobranco(string campo)
{
	int tamanhostring;
	tamanhostring = campo.size();

	if(tamanhostring < 1)
	{
		cout << "\n\t\t\t\t\t\t\t\t -> NAO SAO PERMITIDOS CAMPOS VAZIOS." << endl << endl;
		verificador = 0;
	}
	else
	{
		verificador = 1;
	}

}

void validaletra(string campo)
{
	int contador;
	int tamanhostring;
	int valida;

	tamanhostring = campo.size();

	for(contador = 0; contador < tamanhostring; contador++)
	{
		if(isdigit(campo[contador]))
		{
			valida = 0;
			contador = tamanhostring + 1;
		}
		else
		{
			valida = 1;
		}
	}

	if(valida == 0)
	{
		cout << "\n\t\t\t\t\t\t\t\t -> CARACTERE INVALIDO! NUMEROS NAO SAO PERMITIDOS." << endl << endl;
		verificador = 0;
	}
	else
	{
		verificador = 1;
	}

}

void validanumerico(string campo)
{
	int contador;
	int tamanhostring;
	int valida;

	tamanhostring = campo.size();

	for(contador = 0; contador < tamanhostring; contador++)
	{
		if(isalpha(campo[contador]))
		{
			valida = 0;
			contador = tamanhostring + 1;
		}
		else
		{
			valida = 1;
		}
	}

	if(valida == 0)
	{
		cout << "\n\t\t\t\t\t\t\t\t -> CARACTERE INVALIDO! LETRAS NAO SAO PERMITIDAS." << endl << endl;
		verificador = 0;
	}
	else
	{
		verificador = 1;
	}

}

void CPF_cadastrado(string campo)
{
	int i;
	int valida = 1;
	
	for(i = 0; i < contador; i++)
	{
		if(Cliente[i].NR_CPF == campo)
		{
			valida = 0;
		}
	}
	
	if(valida == 0)
	{
		cout << "\n\t\t\t\t\t\t\t\t -> ESTE CPF PERTENCE A UM CLIENTE JÁ CADASTRADO." << endl << endl;
		verificador = 0;
	}
	else
	{
		verificador = 1;
	}
}

void CPF_tamanho(string campo)
{
	int tamanhostring;
	tamanhostring = campo.size();

	if(tamanhostring < 11)
	{
		cout << "\n\t\t\t\t\t\t\t\t -> O CPF DEVE CONTER 11 DIGITOS." << endl << endl;
		verificador = 0;
	}
	else
	{
		verificador = 1;
	}	
}

void excluir_cliente()
{
	system("cls");
	cout << "\n" << endl; //DANDO AS OPÇÕES DENTRO DA OPÇÃO (2) DO MENU PRINCIPAL
	cout << "\t\t\t\t\t\t\t\t\t\t _____________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|     <<EXCLUIR CLIENTE>>     |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|=============================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU       |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - EXCLUIR CLIENTE        |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t -> O QUE DESEJA REALIZAR: ";
	fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
	sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
	opcaoexcliente = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.

	while(opcaoexcliente != 1 && opcaoexcliente != 2) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (1|2)_____|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
		fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
		sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
		opcaoexcliente = digitofinal; //NOVAMENTE, PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.
	}

	while(opcaoexcliente == 1)
	{
		break; //RETORNA AO MENU PRINCIPAL
	}
	
	while(opcaoexcliente == 2)
	{
		do{
			string CPFexcliente;
			bool opcaodeletar = false;
			
			system("cls");
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                 <<EXCLUSAO DE CADASTRO DE CLIENTE>>                |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
			
			do{
			cout << "\t\t\t\t\t\t\t\t -> DIGITE O CPF DO CLIENTE: ";
			fflush(stdin);
			getline(cin,CPFexcliente);
			validacampobranco(CPFexcliente);
			
			if(verificador == 1)
					{
						validanumerico(CPFexcliente);
					}
			
			}while(verificador == 0);
			
			for(i = 0; i < (contador+1); i++)
			{
				if(Cliente[i].NR_CPF == CPFexcliente)
				{
					if(Cliente[i].ClienteAtivo == 1)
					{
						cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
						cout << "\t\t\t\t\t\t\t\t|" << endl;
						cout << "\t\t\t\t\t\t\t\t| NOME: " << Cliente[i].NM_Cliente << endl;
						cout << "\t\t\t\t\t\t\t\t| CPF: " << Cliente[i].NR_CPF << endl;
						cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Cliente[i].NR_Telefone << endl;
						cout << "\t\t\t\t\t\t\t\t| E-MAIL: " << Cliente[i].DS_Email << endl;
						cout << "\t\t\t\t\t\t\t\t| ENDERECO: " << Cliente[i].DS_Endereco << endl;
						cout << "\t\t\t\t\t\t\t\t| DATA DE CADASTRO: " << Cliente[i].DT_Cadastro << endl;
						cout << "\t\t\t\t\t\t\t\t| CODIGO DO CLIENTE: " << Cliente[i].ID_Cliente << endl;
						cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
						cout << "\n\n";
			
						cout << "\t\t\t\t\t\t\t\t -> DESEJA REALMENTE EXCLUIR O CADASTRO DESTE CLIENTE? (S/N): ";
						fflush(stdin);
						cin >> op;
						op = toupper(op);
			
							while(op != 'S' && op !='N')
							{
								cout << "\n" << endl;
								cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
								cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
								cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
								cout << "\n";
								cout << "\t\t\t\t\t\t\t\t -> DESEJA REALMENTE EXCLUIR O CADASTRO DESTE CLIENTE? (S/N): ";
								cin.clear();
						       	cin.ignore(INT_MAX, '\n');
						       	fflush(stdin);
								cin >> op;
								op = toupper(op);
							}
			
						opcaodeletar = true;
			
						if(op == 'S')
						{
							Cliente[i].ClienteAtivo = 0;
							Cliente[i].NR_CPF = "";
							backupcliente();
							cout << "\n" << endl;
							cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
							cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
							cout << "\t\t\t\t\t\t\t\t|               ** EXCLUSAO EFETUADA COM SUCESSO!!! **               |" << endl;
							cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
							break;
						}
						else if(op == 'N')
						{
							cout << "\n" << endl;
							cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
							cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
							cout << "\t\t\t\t\t\t\t\t|               ** EXCLUSAO CANCELADA COM SUCESSO!!! **              |" << endl;
							cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
						}
					}
					break;
				}
			}
			
			if(opcaodeletar == false)
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|          CLIENTE NAO ENCONTRADO!!!          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________________________|" << endl;
			}
			
			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t -> DESEJA EXCLUIR OUTRO CADASTRO DE CLIENTE? (S/N): ";
			fflush(stdin);
			cin >> op;
			op = toupper(op);
			
			while(op != 'S' && op !='N')
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t -> DESEJA EXCLUIR OUTRO CADASTRO DE CLIENTE? (S/N): ";
				cin.clear();
		       	cin.ignore(INT_MAX, '\n');
		       	fflush(stdin);
				cin >> op;
				op = toupper(op);
			}
		
		}while(op == 'S');
	break;
	}
}


//FUNÇÃO PARA CONSULTAR UM CLIENTE ESPECÍFICO UTILIZANDO O CÓDIGO
void consulta_cliente()
{
	int opcaoconsulta = 0; //VARIÁVEL PARA RECEBER A OPÇÃO DO MENU DE CONSULTA DE CLIENTE
	string consultaCPF; //VARIÁVEL PARA RECEBER CPF DIGITADO NA CONSULTA E COMPARAR COM O CPF CADASTRADO NA STRUCT CLIENTE
	string consultaNome; //VARIÁVEL PARA RECEBER CÓDIGO DIGITADO NA CONSULTA E COMPARAR COM O CÓDIGO CADASTRADO NA STRUCT CLIENTE
	bool exibiucliente = false;
	
	
	system("cls");
	cout << "\n" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t _________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                         |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|  <<CONSULTAR CLIENTE>>  |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                         |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|=========================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                         |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU   |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                         |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - POR NOME           |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                         |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[3] - POR CPF            |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t-> TIPO DE CONSULTA: ";
	sonumeros();
	opcaoconsulta = digitofinal;

	while(opcaoconsulta != 1 && opcaoconsulta != 2 && opcaoconsulta != 3)
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t ____________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|             **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (1|2|3)_____|" << endl;
   	 	cout << "\n\t\t\t\t\t\t\t\t\t\t-> TIPO DE CONSULTA: ";
		sonumeros();
		opcaoconsulta = digitofinal;
	}
	
	while(opcaoconsulta == 1)
	{
		break;
	}
	
	while(opcaoconsulta == 2)
	{
		do{
			system("cls");
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                   <<CONSULTAR CLIENTE POR NOME>>                   |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
			
			do{
				cout << "\t\t\t\t\t\t\t\t| -> DIGITE O NOME DO CLIENTE: ";
				fflush(stdin);
				getline(cin,consultaNome);
				validacampobranco(consultaNome);
	
				if(verificador == 1)
				{
					validaletra(consultaNome);
				}

			}while(verificador == 0);

			for(i = 0; i < contador; i++)
			{
				if(Cliente[i].NM_Cliente == consultaNome)
				{
					exibiucliente = true;
					
					if(Cliente[i].ClienteAtivo == 1)
					{
						cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
						cout << "\t\t\t\t\t\t\t\t|" << endl;
						cout << "\t\t\t\t\t\t\t\t| NOME: " << Cliente[i].NM_Cliente << endl;
						cout << "\t\t\t\t\t\t\t\t| CPF: " << Cliente[i].NR_CPF << endl;
						cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Cliente[i].NR_Telefone << endl;
						cout << "\t\t\t\t\t\t\t\t| E-MAIL: " << Cliente[i].DS_Email << endl;
						cout << "\t\t\t\t\t\t\t\t| ENDERECO: " << Cliente[i].DS_Endereco << endl;
						cout << "\t\t\t\t\t\t\t\t| DATA DE CADASTRO: " << Cliente[i].DT_Cadastro << endl;
						cout << "\t\t\t\t\t\t\t\t| CODIGO DO CLIENTE: " << Cliente[i].ID_Cliente << endl;
						cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
						cout << "\n";
					}
					else if(Cliente[i].ClienteAtivo == 0)
					{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t|          CLIENTE NAO ENCONTRADO!!!          |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t|_____________________________________________|" << endl;
					}
				}
			}
	
			if(exibiucliente == false)
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t|          CLIENTE NAO ENCONTRADO!!!          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t|_____________________________________________|" << endl;
			}
			
			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA CONSULTA POR NOME? (S|N): ";
			fflush(stdin);
			cin >> op;
			op = toupper(op);
		
			while(op != 'S' && op !='N')
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA CONSULTA POR CODIGO? (S|N): ";
				cin.clear();
		   		cin.ignore(INT_MAX, '\n');
		   		fflush(stdin);
				cin >> op;
				op = toupper(op);
			}				
			
		}while(op == 'S');
	break;
	}
	
	while(opcaoconsulta == 3)
	{
		do{
			system("cls");
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                     <<CONSULTAR CLIENTE POR CPF>>                  |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;

			do{
			cout << "\t\t\t\t\t\t\t\t| -> DIGITE O CPF DO CLIENTE: ";
			fflush(stdin);
			getline(cin,consultaCPF);
			validacampobranco(consultaCPF);

				if(verificador == 1)
				{
					validanumerico(consultaCPF);
				}

			}while(verificador == 0);

			for(i = 0; i < contador; i++)
			{
				if(Cliente[i].NR_CPF == consultaCPF)
				{
					if(Cliente[i].ClienteAtivo == 1)
					{
						cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
						cout << "\t\t\t\t\t\t\t\t|" << endl;
						cout << "\t\t\t\t\t\t\t\t| NOME: " << Cliente[i].NM_Cliente << endl;
						cout << "\t\t\t\t\t\t\t\t| CPF: " << Cliente[i].NR_CPF << endl;
						cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Cliente[i].NR_Telefone << endl;
						cout << "\t\t\t\t\t\t\t\t| E-MAIL: " << Cliente[i].DS_Email << endl;
						cout << "\t\t\t\t\t\t\t\t| ENDERECO: " << Cliente[i].DS_Endereco << endl;
						cout << "\t\t\t\t\t\t\t\t| DATA DE CADASTRO: " << Cliente[i].DT_Cadastro << endl;
						cout << "\t\t\t\t\t\t\t\t| CODIGO DO CLIENTE: " << Cliente[i].ID_Cliente << endl;
						cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
						cout << "\n";
					}
					else if(Cliente[i].ClienteAtivo == 0)
					{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t|          CLIENTE NAO ENCONTRADO!!!          |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t|_____________________________________________|" << endl;
					}
					break;
				}
			}
			
			if(Cliente[i].NR_CPF != consultaCPF)
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t|          CLIENTE NAO ENCONTRADO!!!          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t|_____________________________________________|" << endl;
			}
			
			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA CONSULTA POR CPF? (S|N): ";
			fflush(stdin);
			cin >> op;
			op = toupper(op);
		
			while(op != 'S' && op !='N')
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA CONSULTA POR CPF? (S|N): ";
				cin.clear();
		   		cin.ignore(INT_MAX, '\n');
		   		fflush(stdin);
				cin >> op;
				op = toupper(op);
			}
		}while(op == 'S');
	break;
	}
}


//FUNÇÃO PARA LISTAR CLIENTES CADASTRADOS (ABRINDO DO TXT)
void lista_cliente()
{
	clientes cli_lista; //VETOR PARA RECEBER A VARIÁVEL COM O CONTEÚDO DA LINHA DO ARQUIVO E MOSTRAR NA TELA

	system("cls"); //LIMPANDO A TELA

	arquivo.open("clientes.txt", ios::in); //ABRINDO ARQUIVO SOMENTE PARA LEITURA

	if(arquivo.is_open()) //SE O ARQUIVO ESTIVER ABERTO
	{
		string linha; //VARIÁVEL PARA RECEBER LINHA DO ARQUIVO
		int numlinha = 1; //CONTADOR DE LINHAS DO ARQUIVO

		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                 <<LISTA DE CLIENTES CADASTRADOS>>                  |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
		while(getline(arquivo, linha)) //PEGANDO LINHA A LINHA DO ARQUIVO E PASSANDO PARA A VARIÁVEL STRING LINHA
		{
			if(numlinha%9 == 1) //SE O RESTO DE DIVISÃO DO NÚMERO DE LINHA POR 9(QUANTIDADE DE LINHAS QUE TEM O CADASTRO DO SISTEMA) FOR 1
			{
				cli_lista.NM_Cliente = linha; //VETOR RECEBENDO LINHA COM NOME
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t| NOME: " << cli_lista.NM_Cliente << endl;
			}
			else if(numlinha%9 == 2) //SE O RESTO DE DIVISÃO DO NÚMERO DE LINHA POR 9(QUANTIDADE DE LINHAS QUE TEM O CADASTRO DO SISTEMA) FOR 2
			{
				cli_lista.NR_CPF = linha; //VETOR RECEBENDO LINHA COM CPF
				cout << "\t\t\t\t\t\t\t\t| CPF: " << cli_lista.NR_CPF << endl;
			}
			else if(numlinha%9 == 3) //SE O RESTO DE DIVISÃO DO NÚMERO DE LINHA POR 9(QUANTIDADE DE LINHAS QUE TEM O CADASTRO DO SISTEMA) FOR 3
			{
				cli_lista.NR_Telefone = linha; //VETOR RECEBENDO LINHA COM TELEFONE
				cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << cli_lista.NR_Telefone << endl;
			}
			else if(numlinha%9 == 4) //SE O RESTO DE DIVISÃO DO NÚMERO DE LINHA POR 9(QUANTIDADE DE LINHAS QUE TEM O CADASTRO DO SISTEMA) FOR 4
			{
				cli_lista.DS_Email = linha; //VETOR RECEBENDO LINHA COM ENDEREÇO
				cout << "\t\t\t\t\t\t\t\t| E-MAIL: " << cli_lista.DS_Email << endl;
			}
			else if(numlinha%9 == 5) //SE O RESTO DE DIVISÃO DO NÚMERO DE LINHA POR 9(QUANTIDADE DE LINHAS QUE TEM O CADASTRO DO SISTEMA) FOR 4
			{
				cli_lista.DS_Endereco = linha; //VETOR RECEBENDO LINHA COM ENDEREÇO
				cout << "\t\t\t\t\t\t\t\t| ENDERECO: " << cli_lista.DS_Endereco << endl;
			}
			else if(numlinha%9 == 6) //SE O RESTO DE DIVISÃO DO NÚMERO DE LINHA POR 9(QUANTIDADE DE LINHAS QUE TEM O CADASTRO DO SISTEMA) FOR 5
			{
				cli_lista.DT_Cadastro = linha; //VETOR RECEBENDO LINHA COM DATA
				cout << "\t\t\t\t\t\t\t\t| DATA DE CADASTRO: " << cli_lista.DT_Cadastro << endl;
			}
			else if(numlinha%9 == 7) //SE O RESTO DE DIVISÃO DO NÚMERO DE LINHA POR 9(QUANTIDADE DE LINHAS QUE TEM O CADASTRO DO SISTEMA) FOR 6
			{
				int converte;
				converte = atoi(linha.c_str());
				cli_lista.ID_Cliente = converte;

				cout << "\t\t\t\t\t\t\t\t| CODIGO DO CLIENTE: " << cli_lista.ID_Cliente << endl; //MOSTRANDO NA TELA O CÓDIGO DO CLIENTE
				cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
			}
			numlinha++; //INCREMENTANDO CONTADOR DE LINHAS DO ARQUIVO
		}
		arquivo.close(); //FECHANDO O ARQUIVO

		cout << "\n";
		cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|            -> PRESSIONE ENTER PARA RETORNAR AO MENU!               |" << endl;
		cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|";
		getch();
	}
	else //SENÃO, SE NÃO TIVER ARQUIVO PARA ABRIR
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t _________________________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t|                                                         |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t| NAO HA CADASTROS OU NAO FOI POSSIVEL ABRIR O ARQUIVO!!! |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t|       -> PRESSIONE ENTER PARA RETORNAR AO MENU!         |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t|_________________________________________________________|";
		getch();
	}
}

void cadastrar_procedimento()
{
	int statuscliente;
	int opcaoproced = 0;
	string CPFstatuscliente;
	int confirmacliente = 0;
	int i = 0;
	int j = 0;


	cout << "\n" << endl; //MOSTRANDO AS OPÇÕES PARA IDENTIFICAR O CLIENTE PARA REALIZAR O PROCEDIMENTO
	cout << "\t\t\t\t\t\t\t\t\t\t ________________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|    <<REALIZAR PROCEDIMENTO>>   |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|================================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU          |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - CLIENTE JA CADASTRADO     |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[3] - CLIENTE SEM CADASTRO      |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t -> STATUS DO CLIENTE: ";
	fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
	sonumeros(); //FUNÇÃO PARA RECEBER SÓ NÚMEROS, EVITANDO ERROS
	statuscliente = digitofinal; //PASSANDO VALOR RETORNADO DA FUNÇÃO SÓ NUMEROS, PARA A VARIÁVEL QUE RECEBE O MENU

	while(statuscliente != 1 && statuscliente != 2 && statuscliente != 3) //VALIDAÇÃO DA OPÇÃO DIGITADA
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|____-> DIGITE UMA OPCAO VALIDA (1|2|3)____|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t -> STATUS DO CLIENTE: ";
		fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
		sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
		statuscliente = digitofinal; //PASSANDO VALOR RETORNADO DA FUNÇÃO SÓ NUMEROS, PARA A VARIÁVEL QUE RECEBE O MENU
	}

	while(statuscliente == 1) //OPÇÃO (1) RETORNAR AO MENU
	{
		break; //RETORNA AO MENU PRINCIPAL
	}

	while(statuscliente == 2) //OPÇÃO (2) CLIENTE JÁ CADASTRADO
	{
		do{
			do{ //INICIANDO LAÇO DE REPETIÇÃO PARA CONFIRMAÇÃO DO PROCEDIMENTO

				system("cls"); //LIMPANDO A TELA

				cout << "\n" << endl; //SOLICITANDO A ENTRADA DO CPF DO CLIENTE PARA VERIFICAR CADASTRO
				cout << "\t\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|           <<CLIENTE JA CADASTRADO>>         |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|=============================================|" << endl;

				do{
				cout << "\t\t\t\t\t\t\t\t\t\t -> INFORME O CPF DO CLIENTE: ";
					fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
					getline(cin,CPFstatuscliente); //RECEBENDO A LINHA DIGITADA PELO USUÁRIO, GUARDANDO NA VARIÁVEL CPFstatuscliente
					validacampobranco(CPFstatuscliente);

					if(verificador == 1)
					{
						validanumerico(CPFstatuscliente);
					}

				}while(verificador == 0);

					for(i = 0; i < contador; i++) //INICIANDO UM LAÇO DE REPETIÇÃO PARA VERIFICAR SE EXISTE O CLIENTE
					{
						if(Cliente[i].NR_CPF == CPFstatuscliente) //VERIFICANDO SE O CPF INFORMADO ESTÁ CADASTRADO NA ESTRUTURA DE CLIENTES
						{
							if(Cliente[i].ClienteAtivo == 1) //VERIFICANDO SE O CLIENTE ESTÁ ATIVO, SE (1), É MOSTRADO NA TELA
							{
								cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
								cout << "\t\t\t\t\t\t\t\t|" << endl;
								cout << "\t\t\t\t\t\t\t\t| NOME: " << Cliente[i].NM_Cliente << endl;
								cout << "\t\t\t\t\t\t\t\t| CPF: " << Cliente[i].NR_CPF << endl;
								cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Cliente[i].NR_Telefone << endl;
								cout << "\t\t\t\t\t\t\t\t| E-MAIL: " << Cliente[i].DS_Email << endl;
								cout << "\t\t\t\t\t\t\t\t| ENDERECO: " << Cliente[i].DS_Endereco << endl;
								cout << "\t\t\t\t\t\t\t\t| DATA DE CADASTRO: " << Cliente[i].DT_Cadastro << endl;
								cout << "\t\t\t\t\t\t\t\t| CODIGO DO CLIENTE: " << Cliente[i].ID_Cliente << endl;
								cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
								cout << "\n\t\t\t\t\t\t\t\t -> CONFIRMA O CLIENTE?  [1]-SIM | [2]-NAO | [3]-RETORNAR AO MENU : ";
								fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
								sonumeros(); //FUNÇÃO PARA SÓ RECEBER NÚMEROS
								confirmacliente = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE TRATARÁ O DADO

									while(confirmacliente != 1 && confirmacliente != 2 && confirmacliente != 3) //VALIDAÇÃO DA OPÇÃO DIGITADA
									{
										cout << "\n" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t|____-> DIGITE UMA OPCAO VALIDA (1|2|3)____|" << endl;
										cout << "\n" << endl;
										cout << "\t\t\t\t\t\t\t\t -> CONFIRMA O CLIENTE?  [1]-SIM | [2]-NAO | [3]-RETORNAR AO MENU : ";
										fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
										sonumeros(); //FUNÇÃO PARA SÓ RECEBER NÚMEROS
										confirmacliente = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE TRATARÁ O DADO
									}

								if(confirmacliente == 1) //SE CONFIRMA CLIENTE OPÇÃO (1), [1]-SIM
								{
									Procedimento[contadorprocedimento].CliProcedimento.NM_Cliente = Cliente[i].NM_Cliente;
									Procedimento[contadorprocedimento].CliProcedimento.NR_CPF = Cliente[i].NR_CPF;
									Procedimento[contadorprocedimento].CliProcedimento.NR_Telefone = Cliente[i].NR_Telefone;
									
									Procedimento[contadorprocedimento].ID_Procedimento = geracodigoprocedimento;

									cout << "\n" << endl;
									cout << "\t\t\t\t\t\t\t\t -> PRESSIONE ENTER PARA PROSSEGUIR E CADASTRAR O PROCEDIMENTO";
									getch(); //SISTEMA ESPERA O PRESSIONAMENTO NA TECLA PARA PROSSEGUIR

									system("cls"); //LIMPANDO A TELA

									cout << "\n" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t ________________________________" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|   <<OPCOES DE PROCEDIMENTOS>>  |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|================================|" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|[1] - ESTETICA                  |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|[2] - CABELO                    |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|[3] - MICROPIGMENTACAO          |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|[4] - MANICURE                  |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
									cout << "\n\t\t\t\t\t\t\t\t\t\t -> OPCAO DE PROCEDIMENTO: ";
									fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
									sonumeros(); //FUNÇÃO PARA RECEBER SÓ NÚMEROS
									opcaoproced = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE TRATARÁ O DADO

									while(opcaoproced != 1 && opcaoproced != 2 && opcaoproced != 3 && opcaoproced != 4) //VALIDAÇÃO DA OPÇÃO DIGITADA
									{
										cout << "\n" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t ______________________________________________" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t|              **OPCAO INVALIDA!!!**           |" << endl;
										cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (1|2|3|4)_____|" << endl;
										cout << "\n\t\t\t\t\t\t\t\t\t\t -> OPCAO DE PROCEDIMENTO: ";
										fflush(stdin);
										sonumeros();
										opcaoproced = digitofinal;
									}

										Procedimento[contadorprocedimento].ID_Categoria = opcaoproced;

										time_t agora;
									    char datahora[100];

									    /* Recupera a quantidade de segundos desde 01/01/1970 */
									    agora = time(NULL);

									    /* Formata a data e a hora da forma desejada */
									    strftime( datahora, sizeof(datahora), "%d.%m.%Y - %H:%M:%S", localtime( &agora ) );

									    Procedimento[contadorprocedimento].DT_Procedimento = (std::string) datahora;

										system("cls"); //LIMPANDO A TELA
										cout << "\n" << endl;
										cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
										cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
										cout << "\t\t\t\t\t\t\t\t|                  <<NOVO CADASTRO DE PROCEDIMENTO>>                 |" << endl;
										cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
										cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
										cout << "\t\t\t\t\t\t\t\t|                                CLIENTE                             |" << endl;
										cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
										cout << "\t\t\t\t\t\t\t\t|" << endl;
										cout << "\t\t\t\t\t\t\t\t| NOME: " << Procedimento[contadorprocedimento].CliProcedimento.NM_Cliente << endl;
										cout << "\t\t\t\t\t\t\t\t| CPF: " << Procedimento[contadorprocedimento].CliProcedimento.NR_CPF << endl;
										cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Procedimento[contadorprocedimento].CliProcedimento.NR_Telefone << endl;
										cout << "\t\t\t\t\t\t\t\t|" << endl;
										cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
										cout << "\t\t\t\t\t\t\t\t|                              PROCEDIMENTO                          |" << endl;
										cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
										cout << "\t\t\t\t\t\t\t\t|" << endl;

										do{
											cout << "\t\t\t\t\t\t\t\t| PROCEDIMENTO: ";
											fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
											getline(cin,Procedimento[contadorprocedimento].NM_Procedimento); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR

											validacampobranco(Procedimento[contadorprocedimento].NM_Procedimento);
										}while(verificador == 0);

										do{
											cout << "\t\t\t\t\t\t\t\t| SESSAO: ";
											fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
											getline(cin,Procedimento[contadorprocedimento].QT_Sessao); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
											validacampobranco(Procedimento[contadorprocedimento].QT_Sessao);

												if(verificador == 1)
												{
													validanumerico(Procedimento[contadorprocedimento].QT_Sessao);
												}
										}while(verificador == 0);

										do{
											cout << "\t\t\t\t\t\t\t\t| PRECO: R$";
											fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
											string precoproced;
											cin >> precoproced; //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
											validacampobranco(precoproced);

											if(verificador == 1)
												{
													validanumerico(precoproced);
												}												

											int convertestring;
											int tamanhostring;
											
											tamanhostring = precoproced.size();
											
											for(convertestring = 0; convertestring < tamanhostring; convertestring++)
											{
												if(precoproced[convertestring] == ',')
												{
													precoproced[convertestring] = '.';
												}											
											}
											
											double convertepreco = strtod(precoproced.c_str(), NULL);
											Procedimento[contadorprocedimento].PR_Procedimento = convertepreco;

										}while(verificador == 0);

										do{
											cout << "\t\t\t\t\t\t\t\t| LUCRO: R$";
											fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
											string lucroproced;
											cin >> lucroproced; //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
											validacampobranco(lucroproced);

											if(verificador == 1)
												{
													validanumerico(lucroproced);
												}
												
											int convertestring;
											int tamanhostring;
											
											tamanhostring = lucroproced.size();
											
											for(convertestring = 0; convertestring < tamanhostring; convertestring++)
											{
												if(lucroproced[convertestring] == ',')
												{
													lucroproced[convertestring] = '.';
												}											
											}	

											double convertelucro = strtod(lucroproced.c_str(), NULL);
											Procedimento[contadorprocedimento].VL_Lucro = convertelucro;

										}while(verificador == 0);

										cout << "\t\t\t\t\t\t\t\t| DATA DO PROCEDIMENTO: " << Procedimento[contadorprocedimento].DT_Procedimento << endl;

										//MOSTRANDO O CÓDIGO DO CLIENTE QUE ESTÁ SENDO CADASTRADO
										cout << "\t\t\t\t\t\t\t\t| CODIGO DO PROCEDIMENTO: " << Procedimento[contadorprocedimento].ID_Procedimento << endl;
										cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;

										Procedimento[contadorprocedimento].ProcedimentoAtivo = 1; //PASSANDO O VALOR (1), SIGNIFICANDO QUE O CLIENTE ESTÁ ATIVO
										
										cout << "\n";
										cout << "\t\t\t\t\t\t\t\t -> CONFIRMAR CADASTRO DO PROCEDIMENTO? (S|N): ";
										fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
										cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
										op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"

										while(op != 'S' && op !='N') //VALIDAÇÃO DA OPÇÃO DIGITADA
										{
											cout << "\n" << endl;
											cout << "\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
											cout << "\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
											cout << "\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
											cout << "\n";
											cout << "\t\t\t\t\t\t\t\t -> CONFIRMAR CADASTRO DO PROCEDIMENTO? (S|N): ";
											fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
											cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
											op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
										}

										if(op == 'S')
										{
											geracodigoprocedimento++;
											contadorprocedimento++; //INCREMENTANDO CONTADOR DE CLIENTES PARA PODER RECEBER UM NOVO EM OUTRA POSIÇÃO DO VETOR

											backupprocedimento();

											cout << endl;
											cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
											cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
											cout << "\t\t\t\t\t\t\t\t|             -> PROCEDIMENTO CADASTRADO COM SUCESSO!!!              |" << endl;
											cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
										}
										else if(op == 'N')
										{
											cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
											cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
											cout << "\t\t\t\t\t\t\t\t|        -> CADASTRO DO PROCEDIMENTO CANCELADO COM SUCESSO!!!        |" << endl;
											cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
										}

								break;
								}
							}
							else if(Cliente[i].ClienteAtivo == 0) //VERIFICANDO SE O CLIENTE ESTÁ ATIVO, SE (0), CLIENTE NÃO ENCONTRADO
							{
								cout << "\n";
								cout << "\t\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
								cout << "\t\t\t\t\t\t\t\t\t\t|            CLIENTE NAO ENCONTRADO!!!        |" << endl;
								cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________________________|";
								getch(); //AGUARDANDO O USUÁRIO PRESSIONAR ALGUMA TECLA
								break;
							}
							break;
						}
					}

					if(Cliente[i].NR_CPF != CPFstatuscliente) //SE O CPF INFORMADO FOR DIFERENTE, NÃO FOR LOCALIZADO NA ESTRUTURA DE CLIENTES
					{
						cout << "\n";
						cout << "\t\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t|            CLIENTE NAO ENCONTRADO!!!        |" << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________________________|";
						getch(); //AGUARDANDO O USUÁRIO PRESSIONAR ALGUMA TECLA
						break;
					}

				if(confirmacliente == 3) //SE CONFIRMA CLIENTE OPÇÃO (3), [3]-RETORNAR AO MENU
				{
					break; //QUEBRA O LAÇO DE REPETIÇÃO E RETORNA AO MENU PRINCIPAL
				}

			}while(confirmacliente == 2); //ENQUANTO CONFIRMA CLIENTE OPÇÃO (2), [2]-NÃO, LAÇO CONTINUA NO LOOP


			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t -> DESEJA REALIZAR NOVO CADASTRO DE PROCEDIMENTO? (S|N): ";
			fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
			cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
			op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"

			while(op != 'S' && op !='N') //VALIDAÇÃO DA OPÇÃO DIGITADA
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t -> DESEJA REALIZAR NOVO CADASTRO DE PROCEDIMENTO? (S|N): ";
				fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
				cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
				op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
			}

			system("cls"); //LIMPANDO A TELA

		}while(op == 'S');
		break;
	}

	while(statuscliente == 3) //OPÇÃO (3), CLIENTE SEM CADASTRO
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t -> DESEJA REALIZAR O CADASTRO DO CLIENTE? (S|N): ";
		fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
		cin >> op; //RECEBENDO A OPÇÃO DIGITADA PELO USUÁRIO
		op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"

		while(op != 'S' && op !='N') //VALIDAÇÃO DA OPÇÃO DIGITADA PELO USUÁRIO
		{
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t -> DESEJA REALIZAR O CADASTRO DO CLIENTE? (S|N): ";
			fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
			cin >> op; //RECEBENDO A OPÇÃO DIGITADA PELO USUÁRIO
			op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
		}

		if(op == 'S')
		{
			cadastrar_cliente();
			break;
		}
		else if(op == 'N')
		{
			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t\t\t ______________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|   -> PRESSIONE ENTER PARA RETORNAR AO MENU.  |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|______________________________________________|";
			getch(); //AGUARDANDO O USUÁRIO PRESSIONAR ALGUMA TECLA
			break;
		}
	}
}

void backupprocedimento()
{
	arquivo.open("procedimentos.txt", ios::out | ios::trunc);
	
	for(i = 0; i < contadorprocedimento; i++)
	{
		if(Procedimento[i].ProcedimentoAtivo == 1)
		{
			arquivo << Procedimento[i].CliProcedimento.NM_Cliente << endl;
			arquivo << Procedimento[i].CliProcedimento.NR_CPF << endl;
			arquivo << Procedimento[i].CliProcedimento.NR_Telefone << endl;

			arquivo << Procedimento[i].NM_Procedimento << endl;
			arquivo << Procedimento[i].QT_Sessao << endl;
			arquivo << Procedimento[i].PR_Procedimento << endl;
			arquivo << Procedimento[i].VL_Lucro << endl;
			arquivo << Procedimento[i].DT_Procedimento << endl;
			arquivo << Procedimento[i].ID_Categoria << endl;
			arquivo << Procedimento[i].ID_Procedimento << endl;
			arquivo << Procedimento[i].ProcedimentoAtivo << endl;

			arquivo << "\n"; //PULANDO LINHA NO ARQUIVO
		}
	}
	arquivo.close(); //FECHANDO O ARQUIVO
}

void carregarprocedimentos()
{
	procedimentos proced[1000];

	arquivo.open("procedimentos.txt", ios::in);

	if(arquivo.is_open())
	{
		string linha;
		int numlinha = 1;

		while(getline(arquivo, linha))
		{
			if(numlinha%12 == 1)
			{
				proced[contadorprocedimento].CliProcedimento.NM_Cliente = linha;
				Procedimento[contadorprocedimento].CliProcedimento.NM_Cliente = proced[contadorprocedimento].CliProcedimento.NM_Cliente;
			}
			else if(numlinha%12 == 2)
			{
				proced[contadorprocedimento].CliProcedimento.NR_CPF = linha;
				Procedimento[contadorprocedimento].CliProcedimento.NR_CPF = proced[contadorprocedimento].CliProcedimento.NR_CPF;
			}
			else if(numlinha%12 == 3)
			{
				proced[contadorprocedimento].CliProcedimento.NR_Telefone = linha;
				Procedimento[contadorprocedimento].CliProcedimento.NR_Telefone = proced[contadorprocedimento].CliProcedimento.NR_Telefone;
			}
			else if(numlinha%12 == 4)
			{
				proced[contadorprocedimento].NM_Procedimento = linha;
				Procedimento[contadorprocedimento].NM_Procedimento = proced[contadorprocedimento].NM_Procedimento;
			}
			else if(numlinha%12 == 5)
			{
				proced[contadorprocedimento].QT_Sessao = linha;
				Procedimento[contadorprocedimento].QT_Sessao = proced[contadorprocedimento].QT_Sessao;
			}
			else if(numlinha%12 == 6)
			{
				double converte1;
				converte1 = strtod(linha.c_str(), NULL);
				proced[contadorprocedimento].PR_Procedimento = converte1;
				Procedimento[contadorprocedimento].PR_Procedimento = proced[contadorprocedimento].PR_Procedimento;
			}
			else if(numlinha%12 == 7)
			{
				double converte2;
				converte2 = strtod(linha.c_str(), NULL);
				proced[contadorprocedimento].VL_Lucro = converte2;
				Procedimento[contadorprocedimento].VL_Lucro = proced[contadorprocedimento].VL_Lucro;
			}
			else if(numlinha%12 == 8)
			{
				proced[contadorprocedimento].DT_Procedimento = linha;
				Procedimento[contadorprocedimento].DT_Procedimento = proced[contadorprocedimento].DT_Procedimento;
			}
			else if(numlinha%12 == 9)
			{
				int converte3;
				converte3 = atoi(linha.c_str());
				proced[contadorprocedimento].ID_Categoria = converte3;
				Procedimento[contadorprocedimento].ID_Categoria = proced[contadorprocedimento].ID_Categoria;
			}
			else if(numlinha%12 == 10)
			{
				int converte4;
				converte4 = atoi(linha.c_str());
				proced[contadorprocedimento].ID_Procedimento = converte4;
				Procedimento[contadorprocedimento].ID_Procedimento = proced[contadorprocedimento].ID_Procedimento;
			}
			else if(numlinha%12 == 11)
			{
				int converte5;
				converte5 = atoi(linha.c_str());
				proced[contadorprocedimento].ProcedimentoAtivo = converte5;
				Procedimento[contadorprocedimento].ProcedimentoAtivo = proced[contadorprocedimento].ProcedimentoAtivo;
				contadorprocedimento++;
				geracodigoprocedimento++;
			}
		numlinha++;
		}
	arquivo.close();
	}
}

void consulta_procedimento()
{
	int opcaoconsulta = 0; //VARIÁVEL PARA RECEBER A OPÇÃO DO MENU DE CONSULTA DE CLIENTE
	string consultaCPF; //VARIÁVEL PARA RECEBER CPF DIGITADO NA CONSULTA E COMPARAR COM O CPF CADASTRADO NA STRUCT CLIENTE
	string consultaNome;
	bool exibiuprocedimento = false;

		system("cls");
		cout << "\n" << endl;	
		cout << "\t\t\t\t\t\t\t\t\t\t ______________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|                              |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|  <<CONSULTAR PROCEDIMENTO>>  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|                              |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|==============================|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|                              |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU        |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|______________________________|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|                              |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|[2] - POR NOME DO CLIENTE     |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|______________________________|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|                              |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|[3] - POR CPF DO CLIENTE      |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|______________________________|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t-> TIPO DE CONSULTA: ";
		sonumeros();
		opcaoconsulta = digitofinal;
		
		while(opcaoconsulta != 1 && opcaoconsulta != 2 && opcaoconsulta != 3)
		{
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t ____________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|             **OPCAO INVALIDA!!!**          |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (1|2|3)_____|" << endl;
			cout << "\n";
       	 	cout << "\t\t\t\t\t\t\t\t\t\t-> TIPO DE CONSULTA: ";
			sonumeros();
			opcaoconsulta = digitofinal;
		}
		
		while(opcaoconsulta == 1)
		{
			break;
		}
		
		while(opcaoconsulta == 2)
		{
			do{
				system("cls");
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
				cout << "\t\t\t\t\t\t\t\t|           <<CONSULTAR PROCEDIMENTO POR NOME DO CLIENTE>>           |" << endl;
				cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
				cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;					
				
				do{
					cout << "\t\t\t\t\t\t\t\t| -> DIGITE O NOME DO CLIENTE: ";
					fflush(stdin);
					getline(cin,consultaNome);
					validacampobranco(consultaNome);
	
					if(verificador == 1)
					{
						validaletra(consultaNome);
					}

				}while(verificador == 0);
									
				for(i = 0; i < contadorprocedimento; i++)
				{
					if(Procedimento[i].CliProcedimento.NM_Cliente == consultaNome)
					{
						exibiuprocedimento = true;
						
						if(Procedimento[i].ProcedimentoAtivo == 1)
						{
							cout << "\n";
							cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl; 
							cout << "\t\t\t\t\t\t\t\t|                                CLIENTE                             |" << endl;
							cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
							cout << "\t\t\t\t\t\t\t\t|" << endl;
							cout << "\t\t\t\t\t\t\t\t| NOME: " << Procedimento[i].CliProcedimento.NM_Cliente << endl;
							cout << "\t\t\t\t\t\t\t\t| CPF: " << Procedimento[i].CliProcedimento.NR_CPF << endl;
							cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Procedimento[i].CliProcedimento.NR_Telefone << endl;
							cout << "\t\t\t\t\t\t\t\t|" << endl;
							cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
							cout << "\t\t\t\t\t\t\t\t|                              PROCEDIMENTO                          |" << endl;
							cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
							cout << "\t\t\t\t\t\t\t\t|" << endl;
							cout << "\t\t\t\t\t\t\t\t| PROCEDIMENTO: " << Procedimento[i].NM_Procedimento << endl;
							cout << "\t\t\t\t\t\t\t\t| SESSAO: " << Procedimento[i].QT_Sessao << endl;
							cout << "\t\t\t\t\t\t\t\t| PRECO: R$" << Procedimento[i].PR_Procedimento << endl;
							cout << "\t\t\t\t\t\t\t\t| LUCRO: R$" << Procedimento[i].VL_Lucro << endl;
							cout << "\t\t\t\t\t\t\t\t| DATA DO PROCEDIMENTO: " << Procedimento[i].DT_Procedimento << endl;
							cout << "\t\t\t\t\t\t\t\t| CODIGO DO PROCEDIMENTO: " << Procedimento[i].ID_Procedimento << endl;
							cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
							cout << "\n\n";
						}
					}
				}
				
				if(exibiuprocedimento == false)
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
					cout << "\t\t\t\t\t\t\t\t|      NAO HA PROCEDIMENTOS CADASTRADOS COM O NOME INFORMADO!!!      |" << endl;
					cout << "\t\t\t\t\t\t\t\t|      NOME: " << consultaNome << endl;
					cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
				}	
				
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA CONSULTA DE PROCEDIMENTO POR NOME? (S|N): ";
				fflush(stdin);
				cin >> op;
				op = toupper(op);
		
				while(op != 'S' && op !='N')
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
					cout << "\n";
					cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA CONSULTA DE PROCEDIMENTO POR NOME? (S|N): ";
					cin.clear();
		       		cin.ignore(INT_MAX, '\n');
		       		fflush(stdin);
					cin >> op;
					op = toupper(op);
				}
				
			}while(op == 'S');		
		break;	
		}
		
		while(opcaoconsulta == 3)
		{
			do{
				system("cls");
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
				cout << "\t\t\t\t\t\t\t\t|            <<CONSULTAR PROCEDIMENTO POR CPF DO CLIENTE>>           |" << endl;
				cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
				cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;					
				
				do{
					cout << "\t\t\t\t\t\t\t\t| -> DIGITE O CPF DO CLIENTE: ";
					fflush(stdin);
					getline(cin,consultaCPF);
					validacampobranco(consultaCPF);
	
					if(verificador == 1)
					{
						validanumerico(consultaCPF);
					}

				}while(verificador == 0);
									
				for(i = 0; i < contadorprocedimento; i++)
				{
					if(Procedimento[i].CliProcedimento.NR_CPF == consultaCPF)
					{
						exibiuprocedimento = true;
						
						if(Procedimento[i].ProcedimentoAtivo == 1)
						{
							cout << "\n";
							cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl; 
							cout << "\t\t\t\t\t\t\t\t|                                CLIENTE                             |" << endl;
							cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
							cout << "\t\t\t\t\t\t\t\t|" << endl;
							cout << "\t\t\t\t\t\t\t\t| NOME: " << Procedimento[i].CliProcedimento.NM_Cliente << endl;
							cout << "\t\t\t\t\t\t\t\t| CPF: " << Procedimento[i].CliProcedimento.NR_CPF << endl;
							cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Procedimento[i].CliProcedimento.NR_Telefone << endl;
							cout << "\t\t\t\t\t\t\t\t|" << endl;
							cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
							cout << "\t\t\t\t\t\t\t\t|                              PROCEDIMENTO                          |" << endl;
							cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
							cout << "\t\t\t\t\t\t\t\t|" << endl;
							cout << "\t\t\t\t\t\t\t\t| PROCEDIMENTO: " << Procedimento[i].NM_Procedimento << endl;
							cout << "\t\t\t\t\t\t\t\t| SESSAO: " << Procedimento[i].QT_Sessao << endl;
							cout << "\t\t\t\t\t\t\t\t| PRECO: R$" << Procedimento[i].PR_Procedimento << endl;
							cout << "\t\t\t\t\t\t\t\t| LUCRO: R$" << Procedimento[i].VL_Lucro << endl;
							cout << "\t\t\t\t\t\t\t\t| DATA DO PROCEDIMENTO: " << Procedimento[i].DT_Procedimento << endl;
							cout << "\t\t\t\t\t\t\t\t| CODIGO DO PROCEDIMENTO: " << Procedimento[i].ID_Procedimento << endl;
							cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
							cout << "\n\n";
						}
					}
				}
				
				if(exibiuprocedimento == false)
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
					cout << "\t\t\t\t\t\t\t\t|                  NAO HA PROCEDIMENTOS CADASTRADOS                  |" << endl;
					cout << "\t\t\t\t\t\t\t\t|                  COM O CPF INFORMADO: " << consultaCPF << endl;
					cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
				}
				
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA CONSULTA DE PROCEDIMENTO POR CPF? (S|N): ";
				fflush(stdin);
				cin >> op;
				op = toupper(op);
		
				while(op != 'S' && op !='N')
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
					cout << "\n";
					cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA CONSULTA DE PROCEDIMENTO POR CPF? (S|N): ";
					cin.clear();
		       		cin.ignore(INT_MAX, '\n');
		       		fflush(stdin);
					cin >> op;
					op = toupper(op);
				}	
					
			}while(op == 'S');			
		break;	
		}
}

void lista_todosprocedimentos()
{
	procedimentos proced_lista; //VETOR PARA RECEBER A VARIÁVEL COM O CONTEÚDO DA LINHA DO ARQUIVO E MOSTRAR NA TELA

	system("cls"); //LIMPANDO A TELA

	arquivo.open("procedimentos.txt", ios::in); //ABRINDO ARQUIVO SOMENTE PARA LEITURA

	if(arquivo.is_open()) //SE O ARQUIVO ESTIVER ABERTO
	{
		string linha; //VARIÁVEL PARA RECEBER LINHA DO ARQUIVO
		int numlinha = 1; //CONTADOR DE LINHAS DO ARQUIVO

		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|           <<LISTA COM TODOS OS PROCEDIMENTOS CADASTRADOS>>         |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
		cout << "\n";
		
		while(getline(arquivo, linha)) //PEGANDO LINHA A LINHA DO ARQUIVO E PASSANDO PARA A VARIÁVEL STRING LINHA
		{
			if(numlinha%12 == 1)
			{
				proced_lista.CliProcedimento.NM_Cliente = linha;
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl; 
				cout << "\t\t\t\t\t\t\t\t|                                CLIENTE                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
				cout << "\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t| NOME: " << proced_lista.CliProcedimento.NM_Cliente << endl;
			}
			else if(numlinha%12 == 2)
			{
				proced_lista.CliProcedimento.NR_CPF = linha;
				cout << "\t\t\t\t\t\t\t\t| CPF: " << proced_lista.CliProcedimento.NR_CPF << endl;
			}
			else if(numlinha%12 == 3)
			{
				proced_lista.CliProcedimento.NR_Telefone = linha;
				cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << proced_lista.CliProcedimento.NR_Telefone << endl;
				cout << "\t\t\t\t\t\t\t\t|" << endl;
			}
			else if(numlinha%12 == 4)
			{
				proced_lista.NM_Procedimento = linha;
				cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
				cout << "\t\t\t\t\t\t\t\t|                              PROCEDIMENTO                          |" << endl;
				cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
				cout << "\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t| PROCEDIMENTO: " << proced_lista.NM_Procedimento << endl;
			}
			else if(numlinha%12 == 5)
			{
				proced_lista.QT_Sessao = linha;
				cout << "\t\t\t\t\t\t\t\t| SESSAO: " << proced_lista.QT_Sessao << endl;
			}
			else if(numlinha%12 == 6)
			{
				double converte1;
				converte1 = strtod(linha.c_str(), NULL);
				proced_lista.PR_Procedimento = converte1;
				cout << "\t\t\t\t\t\t\t\t| PRECO: R$" << proced_lista.PR_Procedimento << endl;
			}
			else if(numlinha%12 == 7)
			{
				double converte2;
				converte2 = strtod(linha.c_str(), NULL);
				proced_lista.VL_Lucro = converte2;
				cout << "\t\t\t\t\t\t\t\t| LUCRO: R$" << proced_lista.VL_Lucro << endl;
			}
			else if(numlinha%12 == 8)
			{
				proced_lista.DT_Procedimento = linha;
				cout << "\t\t\t\t\t\t\t\t| DATA DO PROCEDIMENTO: " << proced_lista.DT_Procedimento << endl;
			}
			else if(numlinha%12 == 10)
			{
				int converte4;
				converte4 = atoi(linha.c_str());
				proced_lista.ID_Procedimento = converte4;
				cout << "\t\t\t\t\t\t\t\t| CODIGO DO PROCEDIMENTO: " << proced_lista.ID_Procedimento << endl;
				cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
				cout << "\n\n";
			}
			numlinha++; //INCREMENTANDO CONTADOR DE LINHAS DO ARQUIVO
		}
		arquivo.close(); //FECHANDO O ARQUIVO

	}
	else //SENÃO, SE NÃO TIVER ARQUIVO PARA ABRIR
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t _________________________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                         |" << endl;
		cout << "\t\t\t\t\t\t\t\t| NAO HA PROCEDIMENTOS CADASTRADOS                        |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                  OU NAO FOI POSSIVEL ABRIR O ARQUIVO!!  |" << endl;
		cout << "\t\t\t\t\t\t\t\t|       -> PRESSIONE ENTER PARA RETORNAR AO MENU!         |" << endl;
		cout << "\t\t\t\t\t\t\t\t|_________________________________________________________|";
		getch();
	}
}

void lista_porprocedimento(int idprocedimento)
{
	string proced_escolhido;
	
	if(idprocedimento == 1)
	{
		proced_escolhido = "ESTETICA";
	}
	else if(idprocedimento == 2)
	{
		proced_escolhido = "CABELO";
	}
	else if(idprocedimento == 3)
	{
		proced_escolhido = "MICROPIGMENTACAO";
	}
	else if(idprocedimento == 4)
	{
		proced_escolhido = "MANICURE";
	}
	
	system("cls");
	
	cout << "\n" << endl;
	cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
	cout << "\t\t\t\t\t\t\t\t|                <<LISTA DE PROCEDIMENTOS CADASTRADOS>>              |" << endl;
	cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
	cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
	cout << "\t\t\t\t\t\t\t\t                 PROCEDIMENTOS DE << " << proced_escolhido << " >>" << endl;
	cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
	cout << "\n\n";
	
	for(i = 0; i < contadorprocedimento; i++)
	{
		if(Procedimento[i].ID_Categoria == idprocedimento)
		{
			if(Procedimento[i].ProcedimentoAtivo == 1)
			{
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl; 
				cout << "\t\t\t\t\t\t\t\t|                                CLIENTE                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
				cout << "\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t| NOME: " << Procedimento[i].CliProcedimento.NM_Cliente << endl;
				cout << "\t\t\t\t\t\t\t\t| CPF: " << Procedimento[i].CliProcedimento.NR_CPF << endl;
				cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Procedimento[i].CliProcedimento.NR_Telefone << endl;
				cout << "\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
				cout << "\t\t\t\t\t\t\t\t|                              PROCEDIMENTO                          |" << endl;
				cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
				cout << "\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t| PROCEDIMENTO: " << Procedimento[i].NM_Procedimento << endl;
				cout << "\t\t\t\t\t\t\t\t| SESSAO: " << Procedimento[i].QT_Sessao << endl;
				cout << "\t\t\t\t\t\t\t\t| PRECO: R$" << Procedimento[i].PR_Procedimento << endl;
				cout << "\t\t\t\t\t\t\t\t| LUCRO: R$" << Procedimento[i].VL_Lucro << endl;
				cout << "\t\t\t\t\t\t\t\t| DATA DO PROCEDIMENTO: " << Procedimento[i].DT_Procedimento << endl;
				cout << "\t\t\t\t\t\t\t\t| CODIGO DO PROCEDIMENTO: " << Procedimento[i].ID_Procedimento << endl;
				cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
				cout << "\n\n";
			}
		}
	}
}

void excluir_procedimento()
{
	int opcaoexprocedimento = 0;
	
	cout << "\n" << endl; //DANDO AS OPÇÕES DENTRO DA OPÇÃO (2) DO MENU PRINCIPAL
	cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                          |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t| <<EXCLUSAO DE CADASTRO DE PROCEDIMENTO>> |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                          |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|==========================================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                          |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU                    |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|__________________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                          |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - EXCLUIR CADASTRO DE PROCEDIMENTO    |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|__________________________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t -> O QUE DESEJA REALIZAR: ";
	fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
	sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
	opcaoexprocedimento = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.

	while(opcaoexprocedimento != 1 && opcaoexprocedimento != 2) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (1|2)_____|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t -> O QUE DESEJA REALIZAR: ";
		fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
		sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
		opcaoexcliente = digitofinal; //NOVAMENTE, PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.
	}

	while(opcaoexprocedimento == 1)
	{
		break; //RETORNA AO MENU PRINCIPAL
	}	
	
	while(opcaoexprocedimento == 2)
	{
		int idexprocedimento;
	
		do{
	
		bool opcaodeletar = false;
	
		system("cls");
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|               <<EXCLUSAO DE CADASTRO DE PROCEDIMENTO>>             |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t -> DIGITE O CODIGO DO PROCEDIMENTO: ";
		fflush(stdin);
		sonumeros();
		idexprocedimento = digitofinal;
		cout << endl;
	
		for(i = 0; i < contadorprocedimento; i++)
		{
			if(Procedimento[i].ID_Procedimento == idexprocedimento)
			{
				if(Procedimento[i].ProcedimentoAtivo == 1)
				{
					cout << "\n";
					cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl; 
					cout << "\t\t\t\t\t\t\t\t|                                CLIENTE                             |" << endl;
					cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
					cout << "\t\t\t\t\t\t\t\t|" << endl;
					cout << "\t\t\t\t\t\t\t\t| NOME: " << Procedimento[i].CliProcedimento.NM_Cliente << endl;
					cout << "\t\t\t\t\t\t\t\t| CPF: " << Procedimento[i].CliProcedimento.NR_CPF << endl;
					cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Procedimento[i].CliProcedimento.NR_Telefone << endl;
					cout << "\t\t\t\t\t\t\t\t|" << endl;
					cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
					cout << "\t\t\t\t\t\t\t\t|                              PROCEDIMENTO                          |" << endl;
					cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
					cout << "\t\t\t\t\t\t\t\t|" << endl;
					cout << "\t\t\t\t\t\t\t\t| PROCEDIMENTO: " << Procedimento[i].NM_Procedimento << endl;
					cout << "\t\t\t\t\t\t\t\t| SESSAO: " << Procedimento[i].QT_Sessao << endl;
					cout << "\t\t\t\t\t\t\t\t| PRECO: R$" << Procedimento[i].PR_Procedimento << endl;
					cout << "\t\t\t\t\t\t\t\t| LUCRO: R$" << Procedimento[i].VL_Lucro << endl;
					cout << "\t\t\t\t\t\t\t\t| DATA DO PROCEDIMENTO: " << Procedimento[i].DT_Procedimento << endl;
					cout << "\t\t\t\t\t\t\t\t| CODIGO DO PROCEDIMENTO: " << Procedimento[i].ID_Procedimento << endl;
					cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
					cout << "\n\n";
					
					cout << "\t\t\t\t\t\t\t\t -> DESEJA REALMENTE EXCLUIR O CADASTRO DESTE PROCEDIMENTO? (S/N): ";
					fflush(stdin);
					cin >> op;
					op = toupper(op);
	
						while(op != 'S' && op !='N')
						{
							cout << "\n" << endl;
							cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
							cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
							cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
							cout << "\n";
							cout << "\t\t\t\t\t\t\t\t -> DESEJA REALMENTE EXCLUIR O CADASTRO DESTE PROCEDIMENTO? (S/N): ";
							cin.clear();
					       	cin.ignore(INT_MAX, '\n');
					       	fflush(stdin);
							cin >> op;
							op = toupper(op);
						}
	
					opcaodeletar = true;
	
					if(op == 'S')
					{
						Procedimento[i].ProcedimentoAtivo = 0;
						backupprocedimento();
						cout << "\n" << endl;
						cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
						cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
						cout << "\t\t\t\t\t\t\t\t|               ** EXCLUSAO EFETUADA COM SUCESSO!!! **               |" << endl;
						cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
						break;
					}
					else if(op == 'N')
					{
						cout << "\n" << endl;
						cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
						cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
						cout << "\t\t\t\t\t\t\t\t|               ** EXCLUSAO CANCELADA COM SUCESSO!!! **              |" << endl;
						cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
					}
				}
			}
		}
		
		if(opcaodeletar == false)
		{
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|        PROCEDIMENTO NAO ENCONTRADO!!!       |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________________________|" << endl;
		}
	
			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t -> DESEJA EXCLUIR OUTRO CADASTRO DE PROCEDIMENTO? (S/N): ";
			fflush(stdin);
			cin >> op;
			op = toupper(op);
	
				while(op != 'S' && op !='N')
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
					cout << "\n";
					cout << "\t\t\t\t\t\t\t\t -> DESEJA EXCLUIR OUTRO CADASTRO DE PROCEDIMENTO? (S/N): ";
					cin.clear();
			       	cin.ignore(INT_MAX, '\n');
			       	fflush(stdin);
					cin >> op;
					op = toupper(op);
				}
	
		}while(op == 'S');
	break;
	}
}

void procedimentos_cadastrados()
{
	cout << "\n" << endl; //DANDO AS OPÇÕES DENTRO DA OPÇÃO (3) DO MENU PRINCIPAL
	cout << "\t\t\t\t\t\t\t\t\t\t __________________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                  |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|   <<PROCEDIMENTOS CADASTRADOS>>  |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                  |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|==================================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                  |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU            |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|__________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                  |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - CONSULTAR PROCEDIMENTO      |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|__________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                  |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[3] - LISTAR PROCEDIMENTOS        |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|__________________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
	fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
	sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
	listprocedimento = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU

	while(listprocedimento != 1 && listprocedimento != 2 && listprocedimento != 3) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|____-> DIGITE UMA OPCAO VALIDA (1|2|3)____|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
		fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
		sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
		listprocedimento = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU
	}


	switch(listprocedimento)
	{
		case 1: //<OPÇÃO (1) DENTRO DO MENU CASE (2)
			break; //RETORNA AO MENU PRINCIPAL

		case 2: //<OPÇÃO (2) DENTRO DO MENU CASE (2)
			consulta_procedimento();	//FUNÇÃO PARA CONSULTA POR CÓDIGO DO CLIENTE
			break;

		case 3: //<OPÇÃO (3) DENTRO DO MENU CASE (2)				
			do{
				system("cls");
				cout << "\n" << endl; //DANDO AS OPÇÕES DENTRO DA OPÇÃO (3) DO MENU PRINCIPAL
				cout << "\t\t\t\t\t\t\t\t\t\t _____________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|   <<LISTAR PROCEDIMENTOS>>  |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|=============================|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|[0] - RETORNAR AO MENU       |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|[1] - ESTETICA               |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|[2] - CABELO                 |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|[3] - MICROPIGMENTACAO       |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|[4] - MANICURE               |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|[5] - LISTAR TODOS           |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
				cout << "\n\t\t\t\t\t\t\t\t\t\t-> TIPO DE LISTAGEM: ";
				fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
				sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
				opcaolistagem = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU
	
				while(opcaolistagem != 0 && opcaolistagem != 1 && opcaolistagem != 2 && opcaolistagem != 3 && opcaolistagem != 4 && opcaolistagem != 5) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t _________________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|                **OPCAO INVALIDA!!!**            |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (0|1|2|3|4|5)____|" << endl;
					cout << "\n";
					cout << "\t\t\t\t\t\t\t\t\t\t -> TIPO DE LISTAGEM: ";
					fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
					sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
					opcaolistagem = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU
				}
				
				if(opcaolistagem == 0)
				{
					break;
				}
				else if(opcaolistagem == 1 || opcaolistagem == 2 || opcaolistagem == 3 || opcaolistagem == 4)
				{
					lista_porprocedimento(opcaolistagem);
				}
				else if(opcaolistagem == 5)
				{
					lista_todosprocedimentos();
				}
				
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA LISTAGEM DE PROCEDIMENTOS? (S|N): ";
				fflush(stdin);
				cin >> op;
				op = toupper(op);
		
				while(op != 'S' && op !='N')
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
					cout << "\n";
					cout << "\t\t\t\t\t\t\t\t-> DESEJA REALIZAR NOVA LISTAGEM DE PROCEDIMENTOS? (S|N): ";
					cin.clear();
		       		cin.ignore(INT_MAX, '\n');
		       		fflush(stdin);
					cin >> op;
					op = toupper(op);
				}
				
			}while(op == 'S');
			break;
	}	
}

void clientes_cadastrados()
{
	cout << "\n" << endl; //DANDO AS OPÇÕES DENTRO DA OPÇÃO (3) DO MENU PRINCIPAL
	cout << "\t\t\t\t\t\t\t\t\t\t _____________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|   <<CLIENTES CADASTRADOS>>  |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|=============================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU       |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - CONSULTAR CLIENTE      |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[3] - LISTAR CLIENTES        |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
	fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
	sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
	listcadastro = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU

	while(listcadastro != 1 && listcadastro != 2 && listcadastro != 3) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|____-> DIGITE UMA OPCAO VALIDA (1|2|3)____|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
		fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
		sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
		listcadastro = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU
	}


	switch(listcadastro)
	{
		case 1: //<OPÇÃO (1) DENTRO DO MENU CASE (2)
			break; //RETORNA AO MENU PRINCIPAL

		case 2: //<OPÇÃO (2) DENTRO DO MENU CASE (2)
			consulta_cliente();	//FUNÇÃO PARA CONSULTA POR CÓDIGO DO CLIENTE
			break;

		case 3: //<OPÇÃO (3) DENTRO DO MENU CASE (2)
			lista_cliente(); //FUNÇÃO PARA LISTAR CLIENTES CADASTRADOS
			break;
	}
}

void gerenciamento()
{
	do{
		system("cls");
		cout << "\n" << endl; //MENU PRINCIPAL COM TODAS AS OPÇÕES DISPONÍVEIS DO SISTEMA
		cout << "\t\t\t\t\t\t\t\t _______________________________________________________________ " << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                               |" << endl;
		cout << "\t\t\t\t\t\t\t\t|               S T U D I O   C A R O L   C R U Z               |" << endl;
		cout << "\t\t\t\t\t\t\t\t|_______________________________________________________________|" << endl;
		cout << "\t\t\t\t\t\t\t\t|                     MENU DE GERENCIAMENTO                     |" << endl;
		cout << "\t\t\t\t\t\t\t\t|===============================================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                               |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                   [1] - VISUALIZAR FATURAMENTO                |" << endl;
		cout << "\t\t\t\t\t\t\t\t|_______________________________________________________________|" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                               |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                   [0] - SAIR DO GERENCIAMENTO                 |" << endl;
		cout << "\t\t\t\t\t\t\t\t|_______________________________________________________________|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t -> O QUE DESEJA REALIZAR: "; //PEDINDO A OPÇÃO DO MENU ADM
		fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
		sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
		menuadm = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.
		
		while(menuadm < 0 || menuadm > 1) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
		{
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t _______________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t|              **OPCAO INVALIDA!!!**            |" << endl;
			cout << "\t\t\t\t\t\t\t\t|____-> DIGITE UMA OPCAO APRESENTADA NO MENU____|" << endl;
			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
			fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
			sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
			menuadm = digitofinal; //NOVAMENTE, PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.
		}
		
		while(menuadm == 0)
		{
			break;
		}
		
		while(menuadm == 1)
		{
			contabil();
		break;	
		}
		
	}while(menuadm != 0 || menuadm > 0);
}

void contabil()
{
	int opcaocontabil = 0;
	int opcaoprocedimento = 0;
	string contabil_escolhido;
	double faturamento = 0;
	double lucro = 0;
	
	system("cls");
	cout << "\n" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t ________________________________" << endl;	
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|         <<FATURAMENTO>>        |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|================================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU          |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - OPCAO POR PROCEDIMENTO    |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[3] - FATURAMENTO & LUCRO TOTAL |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA VISUALIZAR: ";	
	fflush(stdin);
	sonumeros();
	opcaocontabil = digitofinal;
	cout << endl;
	
	while(opcaocontabil == 1)
	{
		break;
	}
	
	while(opcaocontabil == 2)
	{
		do{
			system("cls");
			cout << "\n" << endl; //DANDO AS OPÇÕES DENTRO DA OPÇÃO (3) DO MENU PRINCIPAL
			cout << "\t\t\t\t\t\t\t\t\t\t _____________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|  <<CONTABIL PROCEDIMENTOS>> |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|=============================|" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|[0] - RETORNAR AO MENU       |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|[1] - ESTETICA               |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|[2] - CABELO                 |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|[3] - MICROPIGMENTACAO       |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|                             |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|[4] - MANICURE               |" << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________|" << endl;
			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA VISUALIZAR: ";
			fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
			sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
			opcaoprocedimento = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU

			while(opcaoprocedimento != 0 && opcaoprocedimento != 1 && opcaoprocedimento != 2 && opcaoprocedimento != 3 && opcaoprocedimento != 4) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t _______________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|               **OPCAO INVALIDA!!!**           |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (0|1|2|3|4)____|" << endl;
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t\t\t -> O QUE DESEJA VISUALIZAR: ";
				fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
				sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
				opcaoprocedimento = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU
			}			
			
			if(opcaoprocedimento == 0)
			{
				op = 'N';
				break;
			}
			else if(opcaoprocedimento == 1 || opcaoprocedimento == 2 || opcaoprocedimento == 3 || opcaoprocedimento == 4)
			{
				if(opcaoprocedimento == 1)
				{
					contabil_escolhido = "ESTETICA";
				}
				else if(opcaoprocedimento == 2)
				{
					contabil_escolhido = "CABELO";
				}
				else if(opcaoprocedimento == 3)
				{
					contabil_escolhido = "MICROPIGMENTACAO";
				}
				else if(opcaoprocedimento == 4)
				{
					contabil_escolhido = "MANICURE";
				}
				
				faturamento = 0;
				lucro = 0;
				
				for(i = 0; i < contadorprocedimento; i++)
				{
					if(Procedimento[i].ID_Categoria == opcaoprocedimento)
					{
						faturamento = faturamento + Procedimento[i].PR_Procedimento;
						lucro = lucro + Procedimento[i].VL_Lucro;
					}
				}
				
				system("cls");
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|                                          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t| CONTABILIDADE DE " << contabil_escolhido << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|__________________________________________|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t| TOTAL FATURAMENTO: R$" << faturamento << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|==========================================|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t| TOTAL LUCRO: R$" << lucro << endl; 
				cout << "\t\t\t\t\t\t\t\t\t\t|__________________________________________|" << endl;
				
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t\t\t -> DESEJA CONFERIR OUTRA CONTABILIDADE? (S/N): ";
				fflush(stdin);
				cin >> op;
				op = toupper(op);

				while(op != 'S' && op !='N')
				{
					cout << "\n" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
					cout << "\n";
					cout << "\t\t\t\t\t\t\t\t\t\t -> DESEJA CONFERIR OUTRA CONTABILIDADE? (S/N): ";
					cin.clear();
			       	cin.ignore(INT_MAX, '\n');
			       	fflush(stdin);
					cin >> op;
					op = toupper(op);
				}
			}
		}while(op == 'S');
	break;
	}
	
	while(opcaocontabil == 3)
	{
		double faturamentototal = 0;
		double lucrototalC = 0;
		double lucrototalM = 0;
		
		for(i = 0; i < contadorprocedimento; i++)
		{
			faturamentototal = faturamentototal + Procedimento[i].PR_Procedimento;
			
			if(Procedimento[i].ID_Categoria == 1 || Procedimento[i].ID_Categoria == 2)
			{
				lucrototalC = lucrototalC + Procedimento[i].VL_Lucro;
			}
			else if(Procedimento[i].ID_Categoria == 3 || Procedimento[i].ID_Categoria == 4)
			{
				lucrototalM = lucrototalM + Procedimento[i].VL_Lucro;
			}
		}
		
		system("cls");
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t _______________________________________" << endl;	
		cout << "\t\t\t\t\t\t\t\t\t\t|                                       |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|     <<FATURAMENTO & LUCRO TOTAL>>     |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|                                       |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|=======================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t| TOTAL FATURAMENTO: R$" << faturamentototal << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|=======================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t| TOTAL LUCRO CAROLINA: R$" << lucrototalC << endl; 
		cout << "\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|=======================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t| TOTAL LUCRO MARLENE: R$" << lucrototalM << endl; 
		cout << "\t\t\t\t\t\t\t\t\t\t|_______________________________________|" << endl;
		
		cout << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t -> PRESSIONE ENTER PARA RETORNAR AO MENU";
		getch();
		
	break;
	}
}

void usuario_login()
{
	char usuariolog[16];
	char senhalog[14];
	int i = 0;
	char mascara_senhalog[11];
	
	strcpy(usuariolog, "studiocarolcruz");
	strcpy(senhalog, "estudio123456");
	
	char recebe_usuariolog[16];
	char recebe_senhalog[14];
	char guarda_digito;
	
	cout << "\n" << endl;
	
	cout << "\t\t\t\t\t\t\t\t __________________________________________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t|                    |                                     |" << endl;
	cout << "\t\t\t\t\t\t\t\t| B E M - V I N D O  |  S T U D I O   C A R O L   C R U Z  |" << endl;
	cout << "\t\t\t\t\t\t\t\t|____________________|_____________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t __________________________________________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t|                                                          |" << endl;
	cout << "\t\t\t\t\t\t\t\t|          ** [REALIZE O LOGIN PARA PROSSEGUIR] **         |" << endl;
	cout << "\t\t\t\t\t\t\t\t|                                                          |" << endl;
	cout << "\t\t\t\t\t\t\t\t|==========================================================|" << endl;
	cout << "\t\t\t\t\t\t\t\t|USUARIO: ";
	fflush(stdin);
	cin.getline(recebe_usuariolog, 16);
	cout << "\t\t\t\t\t\t\t\t|SENHA: ";
	fflush(stdin);
	
	for(i = 0; i < 20; i++)
	{
		guarda_digito = getch();
		mascara_senhalog[i] = guarda_digito;
		putchar('*');
		if(guarda_digito == 13)
		{
			break;
		}
	}
	
	cout << "\n";
	mascara_senhalog[i] = '\0';
	strcpy(recebe_senhalog, mascara_senhalog);
	
	if(strcmp(recebe_usuariolog, usuariolog) != 0 || strcmp(recebe_senhalog, senhalog) != 0)
	{
		cout << "\t\t\t\t\t\t\t\t|==========================================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                          |" << endl;
		cout << "\t\t\t\t\t\t\t\t|          **** USUARIO OU SENHA INCORRETA!!! ****         |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                          |" << endl;
		cout << "\t\t\t\t\t\t\t\t|==========================================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t|   -> PRESSIONE ENTER PARA RETORNAR AO LOGIN NOVAMENTE    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|__________________________________________________________|";
		getch();
		system("cls");
		logado = 1;
	}
	else if(strcmp(recebe_usuariolog, usuariolog) == 0 || strcmp(recebe_senhalog, senhalog) == 0)
	{
		logado = 2;
		cout << "\t\t\t\t\t\t\t\t|==========================================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                          |" << endl;
		cout << "\t\t\t\t\t\t\t\t|         **** LOGIN REALIZADO COM SUCESSO!!! ****         |" << endl;
		cout << "\t\t\t\t\t\t\t\t|                                                          |" << endl;
		cout << "\t\t\t\t\t\t\t\t|==========================================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t|          -> PRESSIONE ENTER PARA ABRIR O MENU            |" << endl;
		cout << "\t\t\t\t\t\t\t\t|__________________________________________________________|";
		getch();
	}
}

void adm_login()
{
		char codigoadm[14];
		char recebe_codigoadm[14];
		char mascara_codigoadm[14];
		char guarda_digito;
		int i = 0;
		
		strcpy(codigoadm, "estudio123456");
	
		system("cls");
		cout << "\n " << endl;
		cout << "\t\t\t\t\t\t\t\t __________________________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t|   ###################                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|   ## GERENCIAMENTO ##  [NECESSARIO LOGIN ADMINISTRATIVO] |" << endl;
		cout << "\t\t\t\t\t\t\t\t|   ###################                                    |" << endl;
		cout << "\t\t\t\t\t\t\t\t|==========================================================|" << endl;
		cout << "\t\t\t\t\t\t\t\t|DIGITE A SENHA ADMINISTRATIVA: ";
		fflush(stdin);
			
		for(i = 0; i < 20; i++)
		{
			guarda_digito = getch();
			mascara_codigoadm[i] = guarda_digito;
			putchar('*');
			
			if(guarda_digito == 13)
			{
				break;
			}
		}
	
		cout << endl;
		mascara_codigoadm[i] = '\0';
		strcpy(recebe_codigoadm, mascara_codigoadm);
		
		if(strcmp(recebe_codigoadm, codigoadm) != 0)
		{
			adm_logado = 1;
			cout << "\t\t\t\t\t\t\t\t|==========================================================|" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                          |" << endl;
			cout << "\t\t\t\t\t\t\t\t|        **** SENHA ADMINISTRATIVA INCORRETA!!! ****       |" << endl;
			cout << "\t\t\t\t\t\t\t\t|__________________________________________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t|_________ PRESSIONE ENTER PARA RETORNAR AO MENU __________|";
			getch();
			system("cls");
				
		}
		else if(strcmp(recebe_codigoadm, codigoadm) == 0)
		{
			adm_logado = 2;
			cout << "\t\t\t\t\t\t\t\t|==========================================================|" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                          |" << endl;
			cout << "\t\t\t\t\t\t\t\t| [LOGIN REALIZADO]  **BEM-VINDO A AREA ADMINISTRATIVA**   |" << endl;
			cout << "\t\t\t\t\t\t\t\t|__________________________________________________________|" << endl;
			cout << "\t\t\t\t\t\t\t\t|____________ PRESSIONE ENTER PARA ABRIR O MENU ___________|";
			getch();
			
		}
}

void alterar_e_excluir()
{
	int opcaoalterarexlcuir;
	
	system("cls");
	cout << "\n" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t ________________________________" << endl;	
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|  <<ALTERAR/EXCLUIR CLIENTE>>   |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|================================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU          |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - ALTERAR CLIENTE           |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[3] - EXCLUIR CLIENTE           |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";	
	fflush(stdin);
	sonumeros();
	opcaoalterarexlcuir = digitofinal;
	
	while(opcaoalterarexlcuir != 1 && opcaoalterarexlcuir != 2 && opcaoalterarexlcuir != 3) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|____-> DIGITE UMA OPCAO VALIDA (1|2|3)____|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
		fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
		sonumeros(); //FUNÇÃO PARA RECEBER SÓ NUMEROS, EVITANDO ERROS
		opcaoalterarexlcuir = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU
	}
	
	while(opcaoalterarexlcuir == 1)
	{
		break;
	}
	
	while(opcaoalterarexlcuir == 2)
	{
		alterar_cliente();
	break;	
	}	
	
	while(opcaoalterarexlcuir == 3)
	{
		excluir_cliente();
	break;	
	}
}

void alterar_cliente()
{
	int opcaoalterar = 0;
	
	system("cls");
	cout << "\n" << endl; //DANDO AS OPÇÕES DENTRO DA OPÇÃO (2) DO MENU PRINCIPAL
	cout << "\t\t\t\t\t\t\t\t\t\t ________________________________" << endl;	
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|  <<ALTERAR/EXCLUIR CLIENTE>>   |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|================================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[1] - RETORNAR AO MENU          |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|                                |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|[2] - ALTERAR CLIENTE           |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|________________________________|" << endl;
	cout << "\n\t\t\t\t\t\t\t\t\t\t -> O QUE DESEJA REALIZAR: ";
	fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
	sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
	opcaoalterar = digitofinal; //PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.

	while(opcaoalterar != 1 && opcaoalterar != 2) //VALIDAÇÃO DA OPÇÃO DIGITADA, PARA EVITAR ERROS
	{
		cout << "\n" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (1|2)_____|" << endl;
		cout << "\n\t\t\t\t\t\t\t\t\t\t-> O QUE DESEJA REALIZAR: ";
		fflush(stdin); //LIMPANDO O BUFFER DE ENTRADA DE DADOS
		sonumeros(); //UTILIZANDO DA FUNÇÃO DE SÓ ACEITAR NÚMEROS PARA NÃO OCORRER ERROS
		opcaoexcliente = digitofinal; //NOVAMENTE, PASSANDO O VALOR RETORNADO DA FUNÇÃO PARA A VARIÁVEL QUE RECEBE A OPÇÃO DO MENU.
	}

	while(opcaoalterar == 1)
	{
		break; //RETORNA AO MENU PRINCIPAL
	}
	
	while(opcaoalterar == 2)
	{
		do{
			string CPFaltcliente;
			bool opcaoalterar = false;
			bool cpfcadastrado = false;
			
			string altnome;
			string altcpf;
			string alttelefone;
			string altemail;
			string altendereco;
			
			system("cls");
			cout << "\n" << endl;
			cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                 <<ALTERACAO NO CADASTRO DO CLIENTE>>                |" << endl;
			cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
			cout << "\t\t\t\t\t\t\t\t|====================================================================|" << endl;
			
			do{
			cout << "\t\t\t\t\t\t\t\t -> DIGITE O CPF DO CLIENTE: ";
			fflush(stdin);
			getline(cin,CPFaltcliente);
			validacampobranco(CPFaltcliente);
			
			if(verificador == 1)
					{
						validanumerico(CPFaltcliente);
					}
			
			}while(verificador == 0);
			
			for(i = 0; i < contador; i++)
			{
				if(Cliente[i].NR_CPF == CPFaltcliente)
				{
					opcaoalterar = true;
					
					if(Cliente[i].ClienteAtivo == 1)
					{
						cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
						cout << "\t\t\t\t\t\t\t\t|" << endl;
						cout << "\t\t\t\t\t\t\t\t| NOME: " << Cliente[i].NM_Cliente << endl;
						cout << "\t\t\t\t\t\t\t\t| CPF: " << Cliente[i].NR_CPF << endl;
						cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Cliente[i].NR_Telefone << endl;
						cout << "\t\t\t\t\t\t\t\t| E-MAIL: " << Cliente[i].DS_Email << endl;
						cout << "\t\t\t\t\t\t\t\t| ENDERECO: " << Cliente[i].DS_Endereco << endl;
						cout << "\t\t\t\t\t\t\t\t| DATA DE CADASTRO: " << Cliente[i].DT_Cadastro << endl;
						cout << "\t\t\t\t\t\t\t\t| CODIGO DO CLIENTE: " << Cliente[i].ID_Cliente << endl;
						cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
						cout << "\n\n";
			
						cout << "\t\t\t\t\t\t\t\t -> DESEJA REALMENTE ALTERAR O CADASTRO DESTE CLIENTE? (S/N): ";
						fflush(stdin);
						cin >> op;
						op = toupper(op);
			
							while(op != 'S' && op !='N')
							{
								cout << "\n" << endl;
								cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
								cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
								cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
								cout << "\n";
								cout << "\t\t\t\t\t\t\t\t -> DESEJA REALMENTE ALTERAR O CADASTRO DESTE CLIENTE? (S/N): ";
								cin.clear();
						       	cin.ignore(INT_MAX, '\n');
						       	fflush(stdin);
								cin >> op;
								op = toupper(op);
							}
									
			
						if(op == 'S')
						{
							do{
								cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
								cout << "\t\t\t\t\t\t\t\t|" << endl;
								cout << "\t\t\t\t\t\t\t\t| NOME: ";
								fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
								getline(cin,altnome); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
								validacampobranco(altnome);
					
									if(verificador == 1)
									{
										validaletra(altnome);
									}
							}while(verificador == 0);
					
							do{
								cout << "\t\t\t\t\t\t\t\t| CPF: ";
								fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
								getline(cin,altcpf); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
								
								validacampobranco(altcpf);
									
									if(verificador == 1)
									{
										validanumerico(altcpf);
										
										if(verificador == 1)
										{
											CPF_tamanho(altcpf);
											
											if(verificador == 1)
											{
												if(altcpf == Cliente[i].NR_CPF)
												{
													
												}
												else
												{
													CPF_cadastrado(altcpf);
														
													if(verificador == 0)
													{
														cout << "\t\t\t\t\t\t\t\t -> DESEJA INFORMAR OUTRO CPF? (S|N): ";								
														fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
														cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
														op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
														cout << endl;
												
														while(op != 'S' && op !='N') //VALIDAÇÃO DA OPÇÃO DIGITADA
														{
															cout << "\n" << endl;
															cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
															cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
															cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
															cout << "\n\t\t\t\t\t\t\t\t -> DESEJA INFORMAR OUTRO CPF? (S|N): ";
															fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
															cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
															op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
															cout << endl;
														}
														
														if(op == 'S')
														{
															verificador = 0;
														}
														else
														{
															cpfcadastrado = true;
															break;
														}
													}
												}
											}
										}
									}					
							}while(verificador == 0);
					
							if(cpfcadastrado == false)
							{
								do{
									cout << "\t\t\t\t\t\t\t\t| TELEFONE: ";
									fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
									getline(cin,alttelefone); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
									
									validacampobranco(alttelefone);
						
									if(verificador == 1)
										{
											validanumerico(alttelefone);
										}
								}while(verificador == 0);
						
								do{
									cout << "\t\t\t\t\t\t\t\t| E-MAIL: ";
									fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
									getline(cin,altemail); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
						
									validacampobranco(altemail);	
												
								}while(verificador == 0);
						
								do{
									cout << "\t\t\t\t\t\t\t\t| ENDERECO: ";
									fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
									getline(cin,altendereco); //PEGANDO A LINHA DIGITADA PELO USUÁRIO NA POSIÇÃO [] DO VETOR
						
									validacampobranco(altendereco);
									
								}while(verificador == 0);
								
								cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
											
								cout << "\n\t\t\t\t\t\t\t\t -> CONFIRMAR ALTERACAO NO CADASTRO DO CLIENTE? (S|N): ";
								fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
								cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
								op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
						
								while(op != 'S' && op !='N') //VALIDAÇÃO DA OPÇÃO DIGITADA
								{
									cout << "\n" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
									cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
									cout << "\n\t\t\t\t\t\t\t\t -> CONFIRMAR ALTERACAO NO CADASTRO DO CLIENTE? (S|N): ";
									fflush(stdin); //LIMPANDO BUFFER DE ENTRADA DE DADOS
									cin >> op; //RECEBENDO A OPÇÃO NA VARIÁVEL
									op = toupper(op); //CONVERTENDO A OPÇÃO DIGITADA PARA LETRA MAIÚSCULA EX: DE "s" PARA "S"
								}
						
								if(op == 'S')
								{
									Cliente[i].NM_Cliente = altnome;
									Cliente[i].NR_CPF = altcpf;
									Cliente[i].NR_Telefone = alttelefone;
									Cliente[i].DS_Email = altemail;
									Cliente[i].DS_Endereco = altendereco;
									
									cout << "\n\t\t\t\t\t\t\t\t -> CADASTRO COM AS ALTERACOES REALIZADAS! VISUALIZE-O ABAIXO." << endl;
									cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
									cout << "\t\t\t\t\t\t\t\t|" << endl;
									cout << "\t\t\t\t\t\t\t\t| NOME: " << Cliente[i].NM_Cliente << endl;
									cout << "\t\t\t\t\t\t\t\t| CPF: " << Cliente[i].NR_CPF << endl;
									cout << "\t\t\t\t\t\t\t\t| TELEFONE: " << Cliente[i].NR_Telefone << endl;
									cout << "\t\t\t\t\t\t\t\t| E-MAIL: " << Cliente[i].DS_Email << endl;
									cout << "\t\t\t\t\t\t\t\t| ENDERECO: " << Cliente[i].DS_Endereco << endl;
									cout << "\t\t\t\t\t\t\t\t| DATA DE CADASTRO: " << Cliente[i].DT_Cadastro << endl;
									cout << "\t\t\t\t\t\t\t\t| CODIGO DO CLIENTE: " << Cliente[i].ID_Cliente << endl;
									cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________" << endl;
									cout << "\n\n";
							
						
									backupcliente();
						
									cout << "\n" << endl;
									cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
									cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
									cout << "\t\t\t\t\t\t\t\t|               ** ALTERACAO EFETUADA COM SUCESSO!!! **              |" << endl;
									cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
								}
								else if(op == 'N')
								{
									cout << "\n" << endl;
									cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
									cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
									cout << "\t\t\t\t\t\t\t\t|               ** ALTERACAO CANCELADA COM SUCESSO!!! **             |" << endl;
									cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
								}	
							}													

							break;
						}
						else if(op == 'N')
						{
							cout << "\n" << endl;
							cout << "\t\t\t\t\t\t\t\t ____________________________________________________________________" << endl;
							cout << "\t\t\t\t\t\t\t\t|                                                                    |" << endl;
							cout << "\t\t\t\t\t\t\t\t|               ** ALTERACAO CANCELADA COM SUCESSO!!! **             |" << endl;
							cout << "\t\t\t\t\t\t\t\t|____________________________________________________________________|" << endl;
						}

						}
					}
				}
			
			if(opcaoalterar == false)
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t _____________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|          CLIENTE NAO ENCONTRADO!!!          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____________________________________________|" << endl;
			}
			
			cout << "\n";
			cout << "\t\t\t\t\t\t\t\t -> DESEJA ALTERAR OUTRO CADASTRO DE CLIENTE? (S/N): ";
			fflush(stdin);
			cin >> op;
			op = toupper(op);
			
			while(op != 'S' && op !='N')
			{
				cout << "\n" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t __________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|           **OPCAO INVALIDA!!!**          |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|_____-> DIGITE UMA OPCAO VALIDA (S|N)_____|" << endl;
				cout << "\n";
				cout << "\t\t\t\t\t\t\t\t -> DESEJA ALTERAR OUTRO CADASTRO DE CLIENTE? (S/N): ";
				cin.clear();
		       	cin.ignore(INT_MAX, '\n');
		       	fflush(stdin);
				cin >> op;
				op = toupper(op);
			}
		
		}while(op == 'S');
	break;
	}	
}
