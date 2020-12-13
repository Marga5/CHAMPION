all: arbitro cliente jogo1 header

arbitro:
	gcc arbitro.c g_1.c -o arbitro -lpthread

cliente:
	gcc cliente.c -o cliente -lpthread

header:
	gcc headerServer.h -o headerServer
	gcc header.h -o header

jogo1:
	gcc g_1.c arbitro.c -o g_1 -lpthread


clean:
	rm -rf arbitro cliente jogo1 headerServer header
