CC := gcc
CFLAGS := -std=c99 -Wall -Werror 
LIB := lib/

.PHONY: clean

libfunc.dll: functions.o
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@

%.o: $(LIB)%.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) -rf *.dll *.o
