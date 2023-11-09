CC = g++
CFLAGS = -std=c++14 -O2 -I ~/include -L ~/lib main.cpp -o main.o -lsdsl -ldivsufsort -ldivsufsort64

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Archivos de texto a probar
TEST_CASES_NUMBER := 1 2 3 4 5

# Experimentos a probar
RANGE_1 := 1 2 3 4 5 6 7 8

# ALFABETO BINARIO, LARGO 64 CADA LÍNEA, CAMBIO DE TAMAÑO DE INPUT
# 1 Boyer-Moore-Horspool
# 2 Sufijos

# ALFABETO A-Z, LARGO 64 CADA LÍNEA, CAMBIO DE TAMAÑO DE INPUT
# 3 Boyer-Moore-Horspool
# 4 Sufijos

# BINARIO, LARGO 64 CADA LÍNEA, CAMBIO LARGO PATRÓN, INPUT FIJO 10000 LÍNEAS
# 5 Boyer-Moore-Horspool
# 6 Sufijos

# ALFABETO A-Z, LARGO 64 CADA LÍNEA, CAMBIO LARGO PATRÓN, INPUT FIJO 10000 LÍNEAS
# 7 Boyer-Moore-Horspool
# 8 Sufijos



INPUT_PREFIX := datasets/input$(num_dataset)/input
OUTPUT_PREFIX := output/output$(num_dataset)/output

MIDE_SOLO_CONTEO = 0 # 1 ACTIVADO

all: program
	for j in $(RANGE_1); do \
		echo "Crea cabecera en CSV"; \
		./main.o $$j --head $(MIDE_SOLO_CONTEO); \
		for i in $(TEST_CASES_NUMBER); do \
			echo "./main.o $$j --pruebas $$i $(MIDE_SOLO_CONTEO) < $(INPUT_PREFIX)$$i.txt > $(OUTPUT_PREFIX)$$j$$i.txt"; \
			./main.o $$j --pruebas $$i $(MIDE_SOLO_CONTEO) < $(INPUT_PREFIX)$$i.txt > $(OUTPUT_PREFIX)$$j$$i.txt; \
		done; \
	done

program: $(OBJS)
	$(CC) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) 

clean:
	rm -f $(OBJS) program output*