
CC            = gcc
CFLAGS        = -g -O4 -Wall -I/usr/local/include
# DEST          = /usr/local/bin
LDFLAGS       = -L/usr/local/lib -lm
# LIBS          = -lhoge -lm
OBJS          = main.o field.o move.o sequence.o
PROGRAM       = zen

# all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) # $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

.c.o:
	$(CC) -c -MMD $<

clean:; $(RM) -rf $(PROGRAM) $(OBJS)
