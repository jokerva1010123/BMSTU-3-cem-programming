CC := gcc
CFLAGS := -std=c99 -Wall -Werror 
INC := inc/
SRC_STATIC := src_static/
SRC_DYNAMIC := src_dynamic/
LIB := lib/
OJB := functions.o sort.o filter.o
UNIT := unit_tests/

all: app_static.exe app_dynamic.exe unit_tests.exe

lib/libarr.a: $(OJB)	
	ar rcs $@ $^
	ranlib $@

lib/arr.dll: $(OJB)
	gcc -shared $^ -Wl,--subsystem,windows -o $@

app_static.exe: main_static.o lib/libarr.a
	$(CC) $^ -L./lib -larr -o $@

app_dynamic.exe: main_dynamic.o lib/arr.dll
	$(CC) -o $@ $^

unit_tests.exe: check_main.o check_key.o check_sort.o
	$(CC) -o $@ $^

%.o: $(SRC_STATIC)%.c $(INC)*.h
	$(CC) $(CFLAGS) -c $<
%.o: $(SRC_DYNAMIC)%.c $(INC)*.h
	$(CC) $(CFLAGS) -c $<
%.o: $(LIB)%.c $(INC)*.h
	$(CC) $(CFLAGS) -c $<
%.o: $(UNIT)%.c $(INC)*.h $(UNIT)%.h
	$(CC) $(CFLAGS) -c $<

.PHONY : clean 
clean:
	rm *.o *.exe $(LIB)*.a $(LIB)*.dll