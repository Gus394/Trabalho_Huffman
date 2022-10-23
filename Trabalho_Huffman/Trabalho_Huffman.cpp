#include <iostream>
#include "HHuffman.h"

//* Criar algoritmo huffman
//* 1.Criar  a lista de frequencia
//* 2.Ordenar a lista de frequencia
//* 3.Criar arvore
//* 4.Criar tabela de cÃ³digo
//* 5.Codificar

int main()
{
	std::string texto = "passarinho que anda com morcego acaba dormindo de ponta cabeca";
	std::list<TNoHuffman*> lista;
	for (int i = 0; i < texto.length(); i++) {
		if (!verificar_existencia(lista, texto[i])) {
			int frequencia = 0;
			for (int j = 0; j < texto.length(); j++) {
				if (texto[i] == texto[j]) {
					frequencia++;
				}
			}
			lista.push_back(new TNoHuffman(texto[i], frequencia));
		}
	}
	lista.sort([](TNoHuffman* a, TNoHuffman* b) {return a->frequencia < b->frequencia; });
	criar_huffman(lista);
	imprimir_arvore(lista.front(), 0);

	std::list<letra_e_codigo> tabela;
	codificar(lista.front(), "", texto, tabela);

	std::cout << "\n";

	std::string binario = "001111111001010010111000110011011011001001010111001100000011110111101101000111101110101000101010010010000111010111001100101011111101111110001111011000010000100101001101101000010101100001111010011101001100000111110111011111100001111101111";

	//for (std::list<letra_e_codigo>::iterator nav = tabela.begin(); nav != tabela.end(); nav++) {
	//	std::cout << (nav)->letra << " " << (nav)->codigo << std::endl;
	//}
	std::cout << "\n";
	decodificar(lista, binario);
}