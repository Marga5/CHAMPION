all: arbitro cliente jogos header

arbitro:
	gcc arbitro.c jogo1.c -o arbitro

cliente:
	gcc cliente.c -o cliente

header:
	gcc headerServer.h -o headerServer
	gcc header.h -o header

jogos:
	gcc jogo1.c arbitro.c -o jogo1
	gcc jogo2.c -o jogo2


clean:
	rm -rf arbitro cliente jogo1 headerServer header jogo2
