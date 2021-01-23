all: arbitro cliente jogo1 jogo2 jogo3 header

arbitro:
	gcc arbitro.c g_1.c -o arbitro -lpthread

cliente:
	gcc cliente.c -o cliente -lpthread

header:
	gcc headerServer.h -o headerServer
	gcc header.h -o header

jogo1:
	gcc g_1.c arbitro.c -o g_1 -lpthread
jogo2:
	gcc g_2.c arbitro.c -o g_2 -lpthread
jogo3:
	gcc g_3.c arbitro.c -o g_3 -lpthread


clean:
	rm -rf arbitro cliente g_1 g_2 g_3 headerServer header
