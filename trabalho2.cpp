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

int nome = 0;
int estado = 0;
int partida = 0;
int cont_sim_lido = 0;
int cont_linhas = 1;
char *code;
string temp_atributo = "";
string nome_palavra = "";
vector<Token> tabela_simbolos = {};
Token simbolo_adicionado; 
vector<string> palavras_reservadas = {"program", "procedure", "begin", "end", "true", "false", "if", "then", "else", "while", "do", "not", "var", "and", "or", "int", "div"};
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
					nome_palavra = copia_temp_atributo(temp_atributo);
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


// ANÁLISE SINTÁTICA
void analise_sintatica (Token token, int posicao) {
	//cout << token.nome_token + "\n";
	int nome = 0;
	switch(posicao) {
		case 0:
			nome = ID;
			if (token.nome_token == to_string(nome) && nome_palavra == "program") { // 260 == ID
				//cout << "Correto: program encontrado\n";
			} else {
				cout << "ERRO: program esperado\n";
			}
			break;
		case 1:
			nome = ID;
			if (token.nome_token == to_string(nome)) { // atributo de id = 1
				//cout << "Correto: nome do programa encontrado\n";
			} else {
				cout << "ERRO: nome do programa esperado\n";
			}
			break;
		case 2:
			nome = SEMICOLON;
			if (token.nome_token == to_string(nome)) {
				//cout << "Correto: ; encontrado\n";
			} else {
				cout << "ERRO: ; esperado\n";
			}
			break;
	}
}

int main ()
{
	Token token;
	code = readFile("programa2.txt");    

	int posicao = 0;
	while (code[cont_sim_lido] != '\0'){
		token = proximo_token();
		analise_sintatica(token, posicao);
		posicao++;
	}	
	
	cout << "\nTABELA DE SIMBOLOS\n\n";
	for (int i = 0; i < tabela_simbolos.size(); i++){
		cout <<  tabela_simbolos[i].nome_token << "|" << tabela_simbolos[i].atributo << "\n";
	}	
}
