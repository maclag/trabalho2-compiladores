// ajeitar ;
// ajeitar quando há mais de uma variavel
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
		case 5: // encontrar 1ª variavel
			fase_atual = 6;
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

				// como nao encontrou o nome da variavel, vai procurar ;
				fase_atual = 6;
				numero_token = 6;
				declaracao_variaveis(token, numero_token);
			}
			break;
		case 6: { // apos a 1 variavel, ver se encontra outra variavel, , ou ;
			fase_atual = 8; // se após variavel verificar se é ponto e virgula
			cout << "CASE 6:\n";
			cout << "token.nome_token: " << token.nome_token << "\n";

			// casos em que nao seja ;:

			// - se for direto uma segunda variavel sem virgula
			nome_constante = ID;
			int nome2 = SEMICOLON;
			int nome3 = COMMA;
			if (token.nome_token != to_string(nome2) 
				&& token.nome_token != to_string(nome3)
				&& token.nome_token != to_string(nome_constante) 
				&& check_palavra_reservada(nome_palavra) != -1) {
				cout << "SEGUNDA VARIAVEL:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				cout << nome_palavra << "\n";
				lista_erros.push_back("- , esperado na declaracao entre variaveis.\n");
				fase_atual = 6; // procura proximo token pois ja achou a segunda variavel
			} 

			// - se for virgula
			nome_constante = COMMA;
			if (token.nome_token == to_string(nome_constante)) {
				cout << "COMMA CASE 6:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				cout << nome_palavra << "\n";
				fase_atual = 7;
			}
			break;
		}

		case 7: // se for virgula
			nome_constante = COMMA;
			if (token.nome_token == to_string(nome_constante)) { // aqui fase 4 (,)
				cout << "VIRGULA:\n";
				cout << "if to_string: " << to_string(nome_constante) << "\n";
				cout << "token.nome_token: " << token.nome_token << "\n";
				cout << nome_palavra << "\n";

				fase_atual = 6; // se identificou (,), volta para fase 6 (identificador)
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
			} else {
				cout << "- ; esperado no final da declaracao das variaveis.\n";
				lista_erros.push_back("- ; esperado no final da declaracao das variaveis.\n");
			}

			break;
	}
}