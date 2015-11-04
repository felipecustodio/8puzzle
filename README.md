# Projeto 02 - Jogo do 8

	O Jogo do 8 é um quebra-cabeças que consiste em um 
	tabuleiro 3x3 com 8 peças e um espaço vazio para movimentação.
	Utilizando uma fila de prioridade, armazenamos todos os 
	estados possíveis de movimento, cada um com prioridade definida
	pela função de Hamming, dada pelo número de peças na posição 
	errada somado ao número de movimentos totais feitos até o momento.
	Percorrendo os estados com prioridade mínima, o algoritmo 
	chega ao tabuleiro resolvido com o menor número de movimentos possíveis.

## Instalação

	Basta rodar o arquivo compilado ./8puzzle

## Organização dos Arquivos

	build, includes, src

## Créditos

	Felipe Scrochio Custódio

## Licença

	MIT License (c)
	Projeto acadêmico desenvolvido exclusivamente 
	para a disciplina de Algoritmos e Estruturas de Dados 1 
	no ICMC-USP, São Carlos. 