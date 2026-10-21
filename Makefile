CC     ?= gcc
CFLAGS  = -std=c11 -Wall -Wextra -Werror -O2

ifeq ($(OS),Windows_NT)
  EXT = .exe
else
  EXT =
endif

PROG = conversor$(EXT)

.PHONY: all test clean

all: $(PROG)

$(PROG): conversor.c
	$(CC) $(CFLAGS) -o $@ $<

# Proves de fum: comproven l'eixida i els codis d'eixida.
test: $(PROG)
	./$(PROG) c2f 100 | grep -q "= 212.00 F"
	./$(PROG) f2c 32  | grep -q "= 0.00 C"
	./$(PROG) k2c 0   | grep -q "= -273.15 C"
	./$(PROG) c2k -300 >/dev/null 2>&1; test $$? -eq 1
	./$(PROG) x2y 10  >/dev/null 2>&1; test $$? -eq 2
	@echo "Totes les proves han passat."

clean:
	rm -f conversor conversor.exe
