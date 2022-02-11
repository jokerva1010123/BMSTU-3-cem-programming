CC := gcc
STD := -std=c99
OPTION := -Wall -Werror -pedantic
INC := inc/
SRC := src/
UNIT := unit_tests/
OBJ := check_main.o check_add.o check_delete.o check_multi.o

all: app.exe unit_tests.exe

app.exe: main.o func_matrix.o read_print.o
	$(CC) -o $@ $^

unit_tests.exe: $(OBJ) func_matrix.o read_print.o 
	$(CC) -o $@ $^ -lcheck

%.o: $(SRC)%.c $(INC)*.h
	$(CC) $(CFLAGS) -c $<

%.o: $(UNIT)%.c $(INC)*.h $(UNIT)*.h
	$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean:
	rm *.o *.exe
