#ifndef Huffman
#define Huffman

#include <list>
#include <iostream>

struct TNoHuffman
{
	char letra;
	int frequencia;
	TNoHuffman* esquerda;
	TNoHuffman* direita;

	TNoHuffman(char letra, int frequencia) {  // Construtor
		esquerda = NULL;
		direita = NULL;
		this->letra = letra;
		this->frequencia = frequencia;
	}

};

struct letra_e_codigo {
	char letra;
	std::string codigo;
};

bool verificar_existencia(std::list<TNoHuffman*> lista, char letra) {
	for (std::list<TNoHuffman*>::iterator nav = lista.begin(); nav != lista.end(); nav++) {      //boolean para verificar existencia de um elemento na lista
		if ((*nav)->letra == letra) {
			return true;
		}
	}
	return false;
}

void criar_huffman(std::list<TNoHuffman*>& lista) {
	for (std::list<TNoHuffman*>::iterator nav = lista.begin(); nav != lista.end(); nav++) { //impressao das letras com frequencia
		std::cout << (*nav)->letra << " - frequencia -  " << (*nav)->frequencia << std::endl;
	}


	while (lista.size() > 1) {
		TNoHuffman* Esquerda = lista.front();  //retira dois nos do inicio
		lista.pop_front();
		TNoHuffman* Direita = lista.front();
		lista.pop_front();
		TNoHuffman* Pai = new TNoHuffman(' ', Esquerda->frequencia + Direita->frequencia); //cria um pai com a soma das frequencias dos filhos
		Pai->esquerda = Esquerda;
		Pai->direita = Direita;  //adiciona os filhos ao pai
		lista.push_back(Pai); //adiciona o pai a lista
		lista.sort([](TNoHuffman* a, TNoHuffman* b) {return a->frequencia < b->frequencia; }); // ordena a lista e compara a frequencia dos filhos
	}

}

void imprimir_arvore(TNoHuffman* raiz, int nivel) {
	if (raiz == nullptr)
		return;
	//TNoHuffman* esquerda = raiz->esquerda;
	//TNoHuffman* direita = raiz->direita;
	for (int i = 0; i < nivel; i++)
		std::cout << "\t";
	
	std::cout  << nivel << " - " << raiz->letra << " - " << raiz->frequencia << std::endl;
	imprimir_arvore(raiz->esquerda, nivel + 1);
	imprimir_arvore(raiz->direita, nivel + 1);

	/*TNoHuffman* nav = raiz;
	while (nav->direita != nullptr) {
		std::cout << "\t" << nav->direita->frequencia << std::endl << nav->esquerda->frequencia;
		imprimir_arvore(nav->direita);
	}*/
}

void codificar(TNoHuffman* raiz, std::string codigo, std::string texto, std::list<letra_e_codigo>& lista) {
	if (raiz->esquerda == NULL && raiz->direita == NULL) {
		std::cout << raiz->letra << " " << codigo << std::endl;
		letra_e_codigo x = { raiz->letra, codigo };
		lista.push_back(x);
	}
	else {
		codificar(raiz->esquerda, codigo + "0", texto, lista);
		codificar(raiz->direita, codigo + "1", texto, lista);
	}
}

void decodificar(std::list<TNoHuffman*>& lista, std::string binario) {
	std::string frase_final = "";
	TNoHuffman* nav = lista.front();

	for (int i = 0; i < binario.size() ; i++) {
		if (binario[i] == '0')
			nav = nav->esquerda;
		else
			nav = nav->direita;

		if (nav->esquerda == NULL && nav->direita == NULL)
		{
			frase_final += nav->letra;
			nav = lista.front();
		}
	}
	std::cout << frase_final << std::endl;
}

#endif