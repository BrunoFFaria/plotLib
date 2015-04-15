# escolhe compilador
CC=icc			
# flags a passar ao compilador 
# -O3 -mssse3 -align -xssse3 -axssse3
CFLAGS= -c  -Wall -O3 -std=c99
# flags de librarias
LDFLAGS =  -lglut -mkl -lGL -lGLU
# (ficheiros a compilar) 
SOURCES = full_example.c zpr.c 

# extenções dos ficheiros seja objectos .o ou ficheiros de código 
OBJECTS=$(SOURCES:.c=.o)

# nome do ficheiro executavel desejado...
EXECUTABLE=maxfrust

# clean
RM = rm -f

# especifica um target, neste caso todos...
all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	$(RM) *.o

