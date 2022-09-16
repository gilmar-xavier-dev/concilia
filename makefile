# Makefile

STD = 

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g -D_FILE_OFFSET_BITS=64
# -O0: nao otimiza o codigo ao compilar
# -g:  prepara o terreno para que o gdb possa encontrar bugs

LIBRARIES = -I/home/gilmar/bdb/include -L/home/gilmar/bdb/lib -ldb-6.1 -lm 
bdb : concilia_main.c concilia_global.c concilia_bdb.c concilia_work.c
	gcc $(STD) $(OPTIONS) concilia_main.c concilia_work.c concilia_global.c concilia_bdb.c -o concilia $(LIBRARIES)

clean:
	rm -f concilia
