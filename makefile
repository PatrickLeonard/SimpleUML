CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

ODIR = obj

DEPS = main.h Class.h ClassMember.h Edge.h EdgeList.h Graph.h 

_OBJ = main.o Class.o ClassMember.o Edge.o EdgeList.o Graph.o
OBJ = $(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(LFLAGS)

statholder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ statholder