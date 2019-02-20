INC_DIR:= ./include
SRC_DIR:= ./src
LIB_DIR:= ./libs

SRCS:= $(wildcard *.cc)
OJBS:= $(patsubst %.cc, %.o, $(SRCS))

LIBS:= -lpthread -llog4cpp

CXXFLAGS:= -g $(addprefix -I, $(INC_DIR)) $(LIBS)

EXE:= ./bin/server.out

$(EXE):$(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CXXFLAGS)

print:
	@echo $(OJBS)
	@echo $(EXE)

clean:
	rm $(EXE)
	rm $(OJBS)
