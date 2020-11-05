all: arbitro cliente header jogo1

arbitro:
	gcc arbitro.c -o arbitro

cliente:
	gcc cliente.c -o cliente

header:
	gcc header.h -o header

jogo1:
	gcc jogo1.c -o jogo1

clean:
	rm -rf arbitro cliente jogo1 header
