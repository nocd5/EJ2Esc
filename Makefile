BIN = EJ2Esc.exe
OBJS = EJ2Esc.o

LDSCRIPT = ldscript.x

CC = $(CROSS)gcc
CFLAGS = -Os
LFLAGS = -mwindows -nostdlib -lkernel32 -luser32 -Wl,$(LDSCRIPT) -s

$(BIN): $(OBJS) $(LDSCRIPT)
	$(CC) $(OBJS) $(LFLAGS) -o $@

.cpp.o:
	$(CC) -c $(CFLAGS) $<

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	$(RM) $(BIN) $(OBJS)
