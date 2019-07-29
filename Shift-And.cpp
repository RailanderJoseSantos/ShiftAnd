
/*
* Trabalho: Implementa��o do m�todo ShiftAnd
* Autores: Daniel Sabino e Railander Jose
* Faculdade Unica
*/
#include <string.h> //para trabalhar com string
#include<iostream> //padrao de entrada/saida do Cin e cout
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include<locale.h> //padrao para pontua�ao/acentos em palavras
#include <stdlib.h> //para aloca��o
#include<stdio.h> //(Biblioteca adicionada para funcionamento nos computadores do laboratorio de informatica)
using namespace std; // para usar o cin, cout

int main(){
	setlocale (LC_ALL, "Portuguese_Brazil"); //para exibir caracteres especiais (da lingua portuguesa)
	bool enc = false; //para verifica��o (final), se padrao foi ou nao encontrado
	
	FILE *arqv; //ponteiro para o arquivo txt
	
	// Abrindo arquivo .txt para leitura;
	arqv = fopen ("arqv.txt", "r+"); //abre arqv para leitura "read"
		if (!arqv){ //se erro ao abrir arqv
			cout << "\n\n\tErro na abertura do arquivo!"; //Mensagem de erro.
			return 0; //Finaliza o programa
		}
	
	// Imprime o texto.
	char caracter, copia_do_txt[100000]; //variavel para controle de caracter / string para armazenar o texto do arqv
	int n = 0;
	cout <<	"\n\tTexto:\n\t";
	


	while ( (caracter = getc(arqv) ) != EOF ){//caractere recebe cada caractere do arquivo enquanto n�o chegar ao fim do texto
		copia_do_txt[n] = caracter;//string em posi��o n recebe o caractere
		n++;//incrementa n
	}
	copia_do_txt[n] = '\0';//na ultima posi��o adcione \0 (tratamento para lixo de memoria que tava dando)
	
	int numcaracteres = 0; //variavel numcaracteres recebe a quantidade de caracteres do texto
	n = 0;	
	while ( copia_do_txt[n] != '\0' ){ //come�a da posi��o do primeiro caractere, enquanto n�o chegar ao final do texto
		cout << copia_do_txt[n]; //imprime o caractere de cada posi��o
		
		if ( copia_do_txt[n] == '\n' ){ //se durante impress�o for encontrada tabula��o, ele ira aplica-la no texto mostrado
			cout << "\t";
		}
		n++; //n recebe + 1 (Pasando o copia_do_txt[n] para o proximo caractere do txt)
		numcaracteres++;
	}
	


	
	
	char alfabeto[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ', '\n'};//defini��o alfabeto	
	
	int tam_alfa = 28; //variavel recebe a quantidade de caracteres do alfabeto
	
	cout << "\n\n\tAlfabeto = {"; //Exibir alfabeto
	for ( int i = 0; i < tam_alfa; i++ ){ //Percorre todo o alfabeto
		if ( alfabeto[i] == ' ' ) //Se o caractere da posi��o [i] for igual a espa�o, ele deve imprimir ' ' (representa��o para o espa�o)
			cout << "'" << alfabeto[i] << "'";
		else if ( alfabeto[i] == '\n' ) //Se o caracter da posi��o [i] for igual "\n" (enter), ele deve imprimir \n (representa��o para o enter)
			cout << "\\n";
		else
			cout << alfabeto[i]; //Exibe o caractere na posi��o [i]
			
		if ( i + 1 != tam_alfa ) //Enquanto o proximo (i + 1) for diferente do ultimo caractere do alfabeto, ele ir� escrever ", "
			cout << ", ";
		if ( i != 0 ) // Se a posi��o indice for diferente de 0,
			if ( i%15 == 0 ) //Faz a verifica��o, para o uso tabula�ao especial
				cout << "\n\t";
	}
	cout << "}";
	
	// Recebe o Padr�o
	cout << "\n\n\tInforme o padr�o para ser buscado: "; //Solicita do usuario o padr�o que deseja buscar
	char padrao[100]; //String para receer o padr�o
	gets ( padrao ); //Recebe o padrao digitado
	
	int tam_padrao = strlen(padrao); //tam_padrao recebe o numero de caracteres do padrao digitado
	
	// Alocando a matriz 'tabela de ocorrencias'
	int **ocorrencia, l, c, *Rzero; //Ponteiro para matriz, variavel para linhas e colunas da matriz, ponteiro para vetor
	l = tam_alfa; //l (linha) recebe o numero de caracteres do alfabeto
	c = tam_padrao; //c (coluna) recebe o numero de caracteres do padrao
	
	ocorrencia = ( int ** ) calloc ( l, sizeof ( int * ) );//aloca dinamicamente linhas da matriz de ocorrencia
	if( ocorrencia == NULL ){//se houver erro ao alocar
		cout<<"\nN�o foi poss�el alocar ocorrencia!";//informe ao usuario
		exit(0);// e feche
	}
	
	for ( int i = 0; i < l; i++ ){//percorre de 0 ao tamanho de lin (tam_alfabeto)
		ocorrencia[i] = ( int * ) calloc ( c, sizeof ( int ) );//enquanto aloca  dinamicamente coluna da matriz de ocorrencia
		if ( !ocorrencia[i] ){//se houver erro na aloca��o
			cout<<"\nN�o foi poss�el alocar ocorrencia!";//informe sobre erro
			exit(0);
		}
	}
	
	// Coloca 0 ou 1 na tabela de ocorrencia
	for ( int lin = 0; lin < l; lin++ )//pecorre todas a linhas da matriz ocorrencia
		for ( int col = 0; col < c; col++ )//percorre todas as coluna da matriz ocorrencia
			ocorrencia[lin][col] = alfabeto[lin] == padrao[col];//se posi��o caractere alfabeto igual pos��o caracter padrao, matriz ocorrencia recebe 1, senao recebe 0
	
	// Criando a linha de Rzero
	Rzero = ( int * ) calloc ( c, sizeof ( int ) );//aloca dinamicamente vetor RZERO com tamanho do padrao
	if( Rzero == NULL){//se erro ao alocar matriz
		cout<<"\nN�o foi poss�el alocar Rzero!";//informe erro
		exit(0);//fecha programa
	}
	
	// Zerando Rzero
	for ( int z = 0; z < c; z++ )//percore todo vetor RZERO
		Rzero[z] = 0;//coloca 0 em todas posi��es do RZERO
	
	// Impress�o da Tabela de Ocorrencia e o R0
	cout << "\n\n\tTabela de Ocorr�ncias:\n";
	for ( int lin = 0; lin < l; lin++ ){//percorre toda linha (q tem tam_alfabeto)
		if ( alfabeto[lin] == ' ' )// se alfabeto determinado indice tiver caractere igual a aspas espa�o
			cout << "      '" << alfabeto[lin] << "': ";//imprima espa�o, e ainda o caractere de determinada posi��o do alfabeto
		else if ( alfabeto[lin] == '\n' )//se caractere alfabeto determinado indice for igual a \n
			cout << "      \\n : ";//imprima \n
		else//senao
			cout << "\t" << alfabeto[lin] << ": ";// imprima caractere 
		
		
		for ( int col = 0; col < c; col++ )//percorre toda posi��o coluna (q tem tamanho do padrao)
			cout << ocorrencia[lin][col] << " " ;//imprime caractere da matriz ocorrencia  determinada posi��o 
		
		if ( ( lin + 1 ) == l ){  //se proximo indice for ultimo indice da matriz
			cout << "\n\tRz:";//imprima RZ
			for ( int col = 0; col < c; col++ ) //percorre novamente todos indices de coluna
				cout << Rzero[col] << " ";//imprime Rzero de cada posi��o
		}
		cout << "\n";
		Sleep(10);
	}
	
	// Imprime a tabela 
	cout<<"\n\n\t\tR0ant >> 1		M[T[i]]		R0atual\n";
	for ( int lin = 0; lin < numcaracteres; lin++ ){//percorre todas posi��es de caracteres do texto do aarqv
		if ( copia_do_txt[lin] == ' ' )//se caractere de determinado indice igual a espa�o 
			cout << "      '" << copia_do_txt[lin] << "':\t";//imprima caractere em tal posi��o 
		else if ( copia_do_txt[lin] == '\n' )//sen�o se, caractere do texto arqv for igual a \n
			cout << "      \\n :\t";//imprima o \n
		else
			cout << "\t" << copia_do_txt[lin] << ":\t"; //Mostra o caractere do .txt
		
		
		// R0ant >> 1
		for ( int col = c-1; col > 0; col-- )// contador col recebe numero de colunas (q tem tamanho do padrao) subtraido de 1, enquanto isso decrementa se col
			Rzero[col] = Rzero[col-1];//Vetor Rzero em dada posi��o recebe ele mesmo em posi��o -1 [ocorre a chufagem, deslocamento de bit]
		Rzero[0] = 1; //Rzero posi��o 0 recebe 1
		
		// Imprime R0ant >> 1
		for ( int col = 0; col < c; col++ ){//percorre toda coluna (tamanho padrao) 
			cout << Rzero[col] << " ";//enquanto isso exibe binario de RZERO
			Sleep(5);
		}
		
		cout << "\t	";
		// M [ T [ I ] ]
		cout << "	";
		for ( int alf = 0; alf < tam_alfa; alf++ ){//percorre todos caracteres do alfabeto
			if ( copia_do_txt[lin] == alfabeto[alf] ){//compara caractere do texto arqv � igual a caractere do alfabeto, se sim:
				for ( int col = 0; col < c; col++ ){//percorre toda coluna(tamanho padrao) 
					cout << ocorrencia[alf][col] << " " ;//imprime M[I[T]]
					if ( Rzero[col] == 1 && ocorrencia[alf][col] == 1 ){ //verifca��o para E logico, Se Rzero for 1 e matriz ocorrencia for 1  :
						Rzero[col] = 1;//Rzero  recebe 1 (fazendo papel de E logico de binarios)
						Sleep(10);
					}
					else{//se�o (nao for Rzero==1 e ocorrencia==1
						Rzero[col] = 0;//Rzero recebe 0 (so recebe 1 quando: 1 e 1
						Sleep(5);
					}
				}
			}
		}
		cout << "\t	";
		
		//R0atual;
		for(int j=0; j<c; j++){//percorre toda coluna (tamanho de padrao)
			cout<<Rzero[j]<<" ";//imprime o Rzero em cada posi��o
			Sleep(5);
		}
		
		if(Rzero[c-1] == 1){ //se Rzero coluna -1 for ingual 1 (ultimo indice igual 1)
			lin -= (c-1); // faz deslocamento do bit
			for(int aux=0; aux<c; aux++){//percorre todas posi�oes de coluna
				if(padrao[aux] != ' ' )//verifica se padrao em determinada posi��o � diferente de espa�o
					if ( padrao[aux] != '\n' )//verifica se padrao em determinada posi��o � diferente de \n
						copia_do_txt[lin] = char(padrao[aux] - 32); //caso caractere nao seja caracter especial converta em maiusculo
						
				// Caso seja necessario o uso de caracteres especiais, adicione os caracteres no alfabeo e, os "ifs"
					/*if ( padrao[aux] != '.' )//verifica se padrao em determinada posi��o � diferente de ponto final
						if ( padrao[aux] != ',' )//verifica se padrao em determinada posi��o � diferente de virgula
							if ( padrao[aux] != '?' )//verifica se padrao em determinada posi��o � diferente de interroga��o
								if ( padrao[aux] != '!' )//verifica se padrao em determinada posi��o � diferente de exclama��o
									if ( padrao[aux] != ';' ) //verifica se padrao em determinada posi��o � diferente de ponto e virgula
										if ( padrao[aux] != ':' )//verifica se padrao em determinada posi��o � diferente de dois pontos */
				
				lin++; //incremente lin
				enc = true; //variavel que informa que o padrao foi encontrado (recebe verdadeiro)
			}
			lin--; //decremente lin
		}
	
		cout << "\n";
	}
	
	if ( enc ==  false ){ //verifica se padrao  nao foi encontrado ou n�o, caso n�o tenha sido encontrado, imprime a mensagem:
		cout << "\n\tPadr�o n�o encontrado!";
	}
	
	cout<<"\n\n";
	arqv = fopen("arqvsaida.txt","w");  //grava (w= write 'escreva') no arqvsaida.txt 
	fprintf( arqv, copia_do_txt); //grava no arquivo toda string contida em "copia_do_txt"
	cout<<"\n\tTexto gravado:\n\t"; //imprime o que foi gravado
	
	n = 0;	
	while ( copia_do_txt[n] != '\0' ){//enquanto texto do arqv nao chegar ultimo caractere
		cout << copia_do_txt[n];//imprima cada caracter
		Sleep(100);
		if ( copia_do_txt[n] == '\n' ){//se houver caractere em outra linha no texto
			cout << "\t";//imprima tabula��o
		}
		n++;
	}
	
	fclose(arqv); //fecha/salva o arquivo
	free(Rzero);//libera vetor alocado
	for ( int limp = 0 ; limp < l ; limp++ )
		free(ocorrencia[limp]);//libera matriz alocada
	free(ocorrencia);

  return 0;
}
