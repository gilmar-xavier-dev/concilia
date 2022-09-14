# Makefile

STD = 

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g -D_FILE_OFFSET_BITS=64
# -O0: nao otimiza o codigo ao compilar
# -g:  prepara o terreno para que o gdb possa encontrar bugs

LIBRARIES = -I/home/gilmar/bdb/include -L/home/gilmar/bdb/lib -ldb-6.1 -lm 
bdb : concilia_pri.c concilia_wor.c concilia_bdb.c concilia_sep.c
	gcc $(STD) $(OPTIONS) concilia_pri.c concilia_wor.c concilia_bdb.c -o conciliapri $(LIBRARIES)
	gcc $(STD) $(OPTIONS) concilia_sep.c concilia_bdb.c concilia_wor.c -o conciliaout $(LIBRARIES)

conciliain : concilia_ind.c concilia_bdb.c concilia_wor.c
	gcc $(STD) $(OPTIONS) concilia_ind.c concilia_bdb.c concilia_wor.c -o conciliain $(LIBRARIES)

conciliaout : concilia_sep.c concilia_bdb.c concilia_wor.c
	gcc $(STD) $(OPTIONS) concilia_sep.c concilia_bdb.c concilia_wor.c -o conciliaout $(LIBRARIES)

clean:
	rm -f conciliain
	rm -f conciliaout