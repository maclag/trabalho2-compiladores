/*
 * ESTE CODIGO IMPLEMENTA UM ANALIZADOR LEXICO PARA O EXEMPLO DE FRAGMENTO DE LINGUAGEM APRESENTADO EM SALA DE AULA (VEJA OS SLIDES DA AULA 4: ANALISE LEXICA: PARTE 2)
 * E PODERA SER UTILIZADO COMO PONTO DE PARTIDA PARA IMPLEMENTACAO DO ANALISADOR LEXICO PARA LINGUAGEM ADOTADA NO TRABALHO PROPOSTO.
 * */

#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

//NOME TOKENS
#define IF  256;
#define THEN  257;
#define ELSE  258;
#define RELOP  259;
#define ID  260;
#define NUM  261;

//ATRIBUTOS
#define LT 262; // < menor que
#define LE 263; // <= menor ou igual
#define EQ 264; // = igual
#define NE 265; // <> diferente
#define GT 266; // > maior que 
#define GE 267; // >= maior ou igual

// outras definicoes
#define PLUS 268; // +
#define MINUS 269; // -
#define DOT 270 // .
#define SEMICOLON 271; // ;
#define COMMA 272; // ,
#define PAREN_OPEN 273; // (
#define PAREN_CLOSE 274; // )
#define ATTRIBUTION 275; // :=
#define COMMENT 276; // //
#define MULTIPLY 277; // *
#define CHAVE_OPEN 278; // {
#define CHAVE_CLOSE 279; // }

struct Token{
	string nome_token;
	int atributo;
};

// ANÁLISE SINTÁTICA----------------
int nome = 0; // nome referente às constantes para funcao proximo_token()
int nome_constante = 0; // nome referente às constantes para funcao analise_sintatica
int fase_atual = 0;
vector<string> lista_erros = {}; // listagem de erros sintáticos
// ---------------------------------

int estado = 0;
int partida = 0;
int cont_sim_lido = 0;
int cont_linhas = 1;
char *code;
string temp_atributo = "";
string nome_palavra = "";
vector<Token> tabela_simbolos = {};
Token simbolo_adicionado; 
vector<string> palavras_reservadas = {"program", "procedure", "begin", "end", "true", "false", "if", "then", "else", "while", "do", "not", "var", "and", "or", "int", "div", "read", "write"};
int simbolo_presente = 0; // variavel que controla se um simbolo ja existe na tabela. eh zero caso ele nao exista, um caso exista
int palavra_reservada; // variavel utilizada para verificar se um token eh uma palavra reservada. eh o indice no vetor de palavras, caso seja. eh -1, caso nao seja
int indice_palavra; // indice que indica a posicao na palavra nos vetores de simbolo

// verifica se o lexema encontrado eh uma palavra reservadas
int check_palavra_reservada (string nome_simbolo){
	for (int i = 0; i < palavras_reservadas.size(); i++){
		if (nome_simbolo == palavras_reservadas[i]){
			return i;
		}
	}	
	return -1;
} 

// procura e insere o lexama lido na tabela de simbolos
int busca_simbolo (Token simbolo){
	if (tabela_simbolos.size() == 0) { // se lista esta vazia, adicionar simbolo
		tabela_simbolos.push_back(simbolo);
		return 0;
	} else { // procura se o simbolo lido ja existe na tabela
		for (int i = 0; i < tabela_simbolos.size(); i++) {
			if (simbolo.nome_token == tabela_simbolos[i].nome_token){				
				simbolo_presente = i;
			}
		}
	if (simbolo_presente == 0) { // adiciona na tabela de simbolos, caso ele nao exista
		tabela_simbolos.push_back(simbolo);
		return (tabela_simbolos.size()-1);
	}
	simbolo_presente = 0;
	}
}

string copia_temp_atributo (string temp_atributo) {
	return temp_atributo;
}

char *readFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *code;
	int n = 0;
	int c;

	if(file == NULL) return NULL;

	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	code = new char (f_size);

	while ((c = fgetc(file))!= EOF)
	{
		code[n++] = (char) c;
	}
	code[n] = '\0';
	return code;
}


int falhar()
{
	switch(estado)
	{
	case 0: partida = 9; break;
	case 9: partida = 12; break;
	case 12: partida = 20; break;
	case 20: partida = 25; break;
	case 25: partida = 28; break;
	case 28: partida = 30; break;
	case 30: partida = 32; break;
	case 32: partida = 34; break;
	case 34: partida = 36; break;
	case 36: partida = 38; break;
	case 38: partida = 40; break;
	case 40: partida = 42; break;
	case 42: partida = 45; break;
	case 45: partida = 48; break;
	case 48: partida = 50; break;
	case 50: partida = 52; break;
	case 52: partida = 99; break;
	case 99:
		//retornar msg de erro
		cout << "Erro encontrado no codigo na linha " << cont_linhas << "\n";
		cont_sim_lido++;
		break;
	
	default: printf("Erro do compilador");
	}
	return(partida);
}

Token proximo_token()
{
	Token token;
	char c;
	while(code[cont_sim_lido] != '\0')
	{
		
 		switch(estado)
		{
			case 0:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 0\n";
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{			
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				}
				else if(c == '<') estado = 1;
				else if(c == '=') estado = 5;
				else if(c == '>') estado = 6;
				else
					{
					 estado = falhar();
					}
				break;

			case 1:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 1\n";
				if (c == '\n'){
					
					cont_linhas++;
				};		
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if(c == '=') estado = 2;
				else if(c == '>') estado = 3;
				else estado = 4;
				break;

			case 2:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 2\n";
				cont_sim_lido++;
				cout << "<relop, LE>\n";
				nome = RELOP;
				token.nome_token = to_string(nome);	
				token.atributo = LE;
				estado = 0;
				return(token);
				break;

			case 3:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 3\n";	
				cont_sim_lido++;
				cout << "<relop, NE>\n";
				nome = RELOP;
				token.nome_token = to_string(nome);
				token.atributo = NE;
				estado = 0;
				return(token);
				break;

			case 4:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 4\n";	
				cont_sim_lido++;
				cout << "<relop, LT>\n";
				nome = RELOP;
				token.nome_token = to_string(nome);
				token.atributo = LT;
				estado = 0;
				return(token);
				break;

			case 5:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 5\n";		
				cont_sim_lido++;
				cout << "<relop, EQ>\n";		
				nome = RELOP;
				token.nome_token = to_string(nome);
				token.atributo = EQ;
				estado = 0;
				return(token);
				break;

			case 6:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 6\n";		
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if(c == '=') estado = 7;
				else estado = 8;
				break;

			case 7:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 7\n";	
				cont_sim_lido++;
				cout << "<relop, GE>\n";	
				nome = RELOP;
				token.nome_token = to_string(nome);
				token.atributo = GE;
				estado = 0;
				return(token);
				break;

			case 8:
				//cout << "o valor de c atualmente eh: " << c << '\n';	
				//cout << "entrei no 8\n";
				cont_sim_lido++;
				cout << "<relop, GT>\n";	
				nome = RELOP;
				token.nome_token = to_string(nome);
				token.atributo = GT;
				estado = 0;
				return(token);
				break;

			case 9:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 9\n";
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};
					estado = 0;
					cont_sim_lido++;
				}
				else if (isalpha(c) != 0 || c == '_') {
					temp_atributo = temp_atributo + c;
					estado = 10;
				} 
				else
				{
					estado = falhar();
				}

				break;
			case 10:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 10\n";
				if (c == '\n'){
					
					cont_linhas++;

				};		
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (isdigit(c) == 0 && isalpha(c) == 0 && c != '_'){
					estado = 11;
				} 
				else if (isdigit(c) != 0) {
					temp_atributo = temp_atributo + c;
					estado = 10;
				} 										
				else if (isalpha(c) != 0) {
					temp_atributo = temp_atributo + c;
					estado = 10;
				}
				else if (c == '_') {
					temp_atributo = temp_atributo + c;
					estado = 10;
				}
				break;

			case 11:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 11\n";	
				if (check_palavra_reservada(temp_atributo) < 0){ 
				// se a palavra nao for reservada
					Token simbolo_adicionado;
					nome_palavra = copia_temp_atributo(temp_atributo); // copia do nome da palavra
					simbolo_adicionado.nome_token = temp_atributo;
					simbolo_adicionado.atributo = cont_linhas;
					indice_palavra = busca_simbolo(simbolo_adicionado);
					cout << "<ID, " << indice_palavra << "> \n";
					nome = ID;
					token.nome_token = to_string(nome);
					token.atributo = cont_linhas; 
					temp_atributo = "";
					estado = 0;
					return(token);
					break;
					
				} else {
				// se a palavra for reservada
					cout << "<" << palavras_reservadas[check_palavra_reservada(temp_atributo)] <<", >\n";
					nome_palavra = copia_temp_atributo(temp_atributo); // copia do nome da palavra
					temp_atributo = "";	
					nome = ID;
					token.nome_token = to_string(nome);
					token.atributo = -1; 
					estado = 0;
					return(token);
					break;
				}
			
				

			case 12:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 12\n";
				if (c == '\n'){
					
					cont_linhas++;

				};		
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					estado = falhar();
				} 
				break;

				/*implementar ações para os estados 13-19*/

			case 20:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
					
					cont_linhas++;

					};								
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					estado = falhar();
				}
				break;

				/*implementar ações para os estados 21-24*/

			case 25:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 25\n";
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
					
					cont_linhas++;

					};		
					estado = 0;
					cont_sim_lido++;
				} else if (isdigit(c) != 0) {
					temp_atributo = temp_atributo + c;
					estado = 26;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 26:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 26\n";
				if (c == '\n'){
					
					cont_linhas++;

				};
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (isdigit(c) != 0 ){
					temp_atributo = temp_atributo + c;
					estado = 26;
				} else {
					estado = 27;
				}
				break;


			case 27:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 27\n";
			cout << "<NUM, " << temp_atributo << "> \n";
				nome = NUM;
				token.nome_token = to_string(nome);
				token.atributo = stoi(temp_atributo); 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 28:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == '+') {
					temp_atributo = temp_atributo + c;
					estado = 29;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 29 :
			cont_sim_lido++;
			cout << "<+, >\n";	
				nome = PLUS;
				token.nome_token = to_string(nome);			
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 30:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{	
					estado = 0;
					cont_sim_lido++;
				} else if (c == '-') {
					temp_atributo = temp_atributo + c;
					estado = 31;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 31 :
			cont_sim_lido++;
			cout << "<-, >\n";	
				nome = MINUS;
				token.nome_token = to_string(nome);		
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;


			case 32:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == '.') {
					temp_atributo = temp_atributo + c;
					estado = 33;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 33 :
			cont_sim_lido++;
			cout << "<., >\n";
				nome = DOT;
				token.nome_token = to_string(nome);					
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 34:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 34\n";
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == ';') {
					temp_atributo = temp_atributo + c;
					estado = 35;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 35 :
			cont_sim_lido++;
			cout << "<;, >\n";
				nome = SEMICOLON;
				token.nome_token = to_string(nome);					
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 36:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 36\n";
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == ',') {
					temp_atributo = temp_atributo + c;
					estado = 37;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 37:
			cont_sim_lido++;
			cout << "<,>\n";
				nome = COMMA;
				token.nome_token = to_string(nome);	
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 38:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == '(') {
					temp_atributo = temp_atributo + c;
					estado = 39;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 39 :
			cont_sim_lido++;
			cout << "<(, >\n";	
				nome = PAREN_OPEN;
				token.nome_token = to_string(nome);				
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 40:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == ')') {
					temp_atributo = temp_atributo + c;
					estado = 41;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 41 :
			cont_sim_lido++;
			cout << "<), >\n";
				nome = PAREN_CLOSE;
				token.nome_token = to_string(nome);					
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 42:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 42\n";					
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};
					estado = 0;
					cont_sim_lido++;
				}
				else if (c == ':') {
					temp_atributo = temp_atributo + c;
					estado = 43;
				} 
				else
				{
					estado = falhar();
				}
				break;

			case 43:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 43\n";	
				cont_sim_lido++;	
				c = code[cont_sim_lido];
				if (c == '=') {
					temp_atributo = temp_atributo + c;
					estado = 44;
				} 
				else
				{
					estado = falhar();
				}
				break;

			case 44:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 44\n";		
				cont_sim_lido++;	
				cout << "<:=, > \n";
				nome = ATTRIBUTION;
				token.nome_token = to_string(nome);	
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 45:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 45\n";					
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};
					estado = 0;
					cont_sim_lido++;\
				}
				else if (c == '/') {
					temp_atributo = temp_atributo + c;
					estado = 46;
				} 
				else
				{
					estado = falhar();
				}
				break;

			case 46:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 46\n";	
				c = code[cont_sim_lido];
				if (c == '/') {
					temp_atributo = temp_atributo + c;
					estado = 47;
				} 
				else
				{
					estado = falhar();
				}
				break;

			case 47:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 47\n";		
				cont_sim_lido++;	
				cout << "<//, > \n";
				nome = COMMENT;
				token.nome_token = to_string(nome);
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 48:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 48\n";					
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == '*') {
					temp_atributo = temp_atributo + c;
					estado = 49;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 49 :
			cont_sim_lido++;
			cout << "<*, >\n";	
				nome = MULTIPLY;
				token.nome_token = to_string(nome);			
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 50:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 50\n";					
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == '{') {
					temp_atributo = temp_atributo + c;
					estado = 51;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 51 :
			cont_sim_lido++;
			cout << "<{, >\n";	
				nome = CHAVE_OPEN;
				token.nome_token = to_string(nome);			
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 52:
				//cout << "o valor de c atualmente eh: " << c << '\n';
				//cout << "entrei no 52\n";					
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				} else if (c == '}') {
					temp_atributo = temp_atributo + c;
					estado = 53;
				}
				else
				{
					estado = falhar();
				}
				break;

			case 53 :
			cont_sim_lido++;
			cout << "<}, >\n";	
				nome = CHAVE_CLOSE;
				token.nome_token = to_string(nome);			
				token.atributo = -1; 
				temp_atributo = "";
				estado = 0;
				return(token);
				break;

			case 99:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					if (c == '\n'){
						
						cont_linhas++;
					};		
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					
					estado = falhar();
					token.nome_token = -1;
					token.nome_token = -1;
					token.atributo = -1;
					return(token);
				}
				break;
		}
	}
	token.nome_token = EOF;
	token.atributo = -1;
	return(token);
}

// ajeitar quando há virgula sem variavel após dela
// DECLARAÇÕES
void declaracao_variaveis (Token token, int numero_token) {
	cout << "Entrou em declaracao_variaveis\n"; // comeca em int
	switch(numero_token) { 
		case 4: // para "gastar" token atual int
			cout << "CASE 4:\n";
			cout << "if to_string: " << to_string(nome_constante) << "\n";
			cout << "token.nome_token: " << token.nome_token << "\n";
			cout << nome_palavra << "\n";
			fase_atual = 5;
			break;
		case 5: // encontrar variavel
			fase_atual = 8;
			nome_constante = ID;
			cout << "CASE 5:\n";
			cout << "if to_string: " << to_string(nome_constante) << "\n";
			cout << "token.nome_token: " << token.nome_token << "\n";
			cout << nome_palavra << "\n";
			
			if (token.nome_token != to_string(nome_constante) || check_palavra_reservada(nome_palavra) != -1) {
				cout << "NOME DA VARIAVEL:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				cout << nome_palavra << "\n";
				lista_erros.push_back("- nome da variavel esperado.\n"); // nao encontrou variavel

				// como nao encontrou, vai procurar ;
				fase_atual = 8;
				numero_token = 8;
				declaracao_variaveis(token, numero_token);
			}
			break;
		case 6: // se for direto uma variavel sem virgula
			fase_atual = 7;
			cout << "CASE 6:\n";
			cout << "token.nome_token: " << token.nome_token << "\n";
			cout << nome_palavra << "\n";
			
			// se for direto uma variavel sem virgula
			nome_constante = ID;
			if (check_palavra_reservada(nome_palavra) != -1) {
				cout << "VARIAVEL SEM VIRGULA:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				cout << nome_palavra << "\n";
				lista_erros.push_back("- , esperado na declaracao entre variaveis.\n");
				fase_atual = 7; // procura proximo token
			} 
			break;
		case 7: // se for virgula
			nome_constante = COMMA;
			if (token.nome_token == to_string(nome_constante)) { // aqui fase 4 (,)
				cout << "VIRGULA:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				cout << nome_palavra << "\n";

				fase_atual = 5; // se identificou (,), volta para fase 5 (identificador)
			}
			break;
		case 8: // se for ;
			fase_atual = 9;
			nome_constante = SEMICOLON;
			if (token.nome_token == to_string(nome_constante)) {
				cout << "PONTO E VIRGULA:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				cout << nome_palavra << "\n";
				fase_atual = 7;
			} else {
				fase_atual = 7;
				lista_erros.push_back("- ; esperado no final da declaracao das variaveis.\n");
			}

			break;
	}
}

void declaracao_procedimento (Token token, int numero_token) {
	cout << "Entrou em declaracao_procedimento\n";
	switch (numero_token) {
		case 6: // nome do procedimento (identificador)
			fase_atual = 7;
			nome_constante = ID;
			
			if (token.nome_token != to_string(nome_constante) || check_palavra_reservada(nome_palavra) != -1) {
				lista_erros.push_back("- nome do procedimento esperado.\n");
			}
			break;
	}
}

void declaracao_subrotinas (Token token, int numero_token) {
	cout << "Entrou em declaracao_subrotinas\n"; // comeca em procedure
	switch (numero_token) {
		case 6: 
			declaracao_procedimento(token, numero_token);
			break;
	}
}

// COMANDOS
void atribuicao (Token token, int numero_token) {
	cout << "Entrou em atribuicao\n";
}

void chamada_procedimento (Token token, int numero_token) {
	cout << "Entrou em chamada_procedimento\n"; // comeca em procedure
	
}

void comando_condicional (Token token, int numero_token) {
	cout << "Entrou em comando_condicional\n";
}

void comando_repetitivo (Token token, int numero_token) {
	cout << "Entrou em comando_repetitivo\n";
}

void comando (Token token, int numero_token) {
	cout << "Entrou em comando\n";
	switch(numero_token) {
		case 40:
			fase_atual = 50;
			nome_constante = ID;
		
			// Atribuicao
			if (token.nome_token == to_string(nome_constante) && check_palavra_reservada(nome_palavra) == -1) {
				atribuicao(token, numero_token);
			}

			// Chamada de procedimento

			// Comando composto

			// Comando condicional
			if (token.nome_token == to_string(nome_constante) && nome_palavra == "if") {
				comando_condicional(token, numero_token);
			}

			// Comando repetitivo
			if (token.nome_token == to_string(nome_constante) && nome_palavra == "while") {
				comando_condicional(token, numero_token);
			}

			break;
	}
}

void comando_composto (Token token, int numero_token) {
	cout << "Entrou em comando_composto\n";
	switch(numero_token) { // <comando>
		case 30:
			comando(token, numero_token);
			break;
		
		case 100: // última etapa (end)
			nome_constante = ID;
			if (token.nome_token != to_string(nome_constante) || nome_palavra == "end") {
				lista_erros.push_back("- end esperado no final do comando composto.\n");
			} 
	}
}

void bloco (Token token, int numero_token) {
	cout << "Entrou em bloco\n";
	switch(numero_token) {
		case 3:
			fase_atual = 120; // 120 apenas para exemplo => alterar
			numero_token = fase_atual;
			nome_constante = ID;

			if (token.nome_token == to_string(nome_constante) && nome_palavra == "int") {
				fase_atual = 4;
				numero_token = 4;
				declaracao_variaveis(token, numero_token);
			} 
			
			else if (token.nome_token == to_string(nome_constante) && nome_palavra == "procedure") {
				// fase_atual = 7;
				declaracao_subrotinas(token, numero_token);
			} 
			
			else if (token.nome_token == to_string(nome_constante) && nome_palavra == "begin") {
				// fase_atual = 15;
				comando_composto(token, numero_token);
			} 
			
			else {
				//cout << nome_palavra << "\n";
				lista_erros.push_back("- begin esperado no início do bloco.\n");
			}

			break;
	}
}

void programa (Token token, int numero_token) {
	cout << "Entrou em programa\n";
	switch(numero_token) {
		case 0: // program
			fase_atual = 1;
			nome_constante = ID;
			if (token.nome_token != to_string(nome_constante) || nome_palavra != "program") {
				lista_erros.push_back("- program esperado.\n");

				numero_token = 1;
				programa(token, numero_token); // caso não tenha program, retorna para a mesma funcao, mas em outra fase
			}
			break;
		case 1: // nome do programa
			fase_atual = 2;
			nome_constante = ID;
			if (token.nome_token != to_string(nome_constante) || check_palavra_reservada(nome_palavra) != -1) {
				cout << "NOME DO PROGRAMA:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				cout << nome_palavra << "\n";
				lista_erros.push_back("- nome do programa (id) esperado.\n");

				numero_token = 2;
				programa(token, numero_token); // caso não tenha nome, retorna para a mesma funcao, mas em outra fase
			}
			break;
		case 2: // ;
			fase_atual = 3;
			nome_constante = SEMICOLON;
			if (token.nome_token != to_string(nome_constante)) {
				cout << "SEMICOLON:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				lista_erros.push_back("- ; esperado após nome do programa.\n");

				numero_token = 3;
				bloco(token, numero_token); // caso não tenha ;, vai direto para a função bloco
			}
			break;

	}
}


// ANÁLISE SINTÁTICA
void analise_sintatica (Token token) {
	switch (fase_atual) {
		case 0:
		case 1:
		case 2:
			programa(token, fase_atual);
			break;
		case 3:
			bloco(token, fase_atual);
			break;
		case 4:
		case 5:
		case 6:
			declaracao_variaveis(token, fase_atual);
			break;
		
	}
}

int main ()
{
	Token token;
	code = readFile("programa2.txt");    

	while (code[cont_sim_lido] != '\0'){
		token = proximo_token();
		cout << token.nome_token << "\n";
		analise_sintatica(token);
	}	
	
	cout << "\nTABELA DE SIMBOLOS\n";
	if (tabela_simbolos.empty()) {
		cout<<"Tabela vazia.\n";
	} else {
		for (int i = 0; i < tabela_simbolos.size(); i++){
			cout <<  tabela_simbolos[i].nome_token << "|" << tabela_simbolos[i].atributo << "\n";
		}	
	}

	cout << "\nANÁLISE SINTÁTICA\n";
	if (lista_erros.empty()) {
		cout << "Não há erros sintáticos.\n";
	} else {
		for (int i = 0; i < lista_erros.size(); i++) {
				cout << lista_erros[i];
		}
	}
	
}
