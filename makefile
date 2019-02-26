INC_DIR:= ./include/
SRC_DIR:= ./src/
LIB_DIR:= ./libs/

SRCS:= $(wildcard $(SRC_DIR)*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))

LIBS:= -lpthread -llog4cpp

CXX:= g++
CXXFLAGS:= -c -g $(addprefix -I, $(INC_DIR))

EXE:= ./bin/server.out

%.o:%.cc
	$(CXX) -o $@ $< $(CXXFLAGS)

$(EXE):$(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

print:
	@echo $(OBJS)
	@echo $(EXE)

clean:
	rm $(OBJS)
	rm $(EXE)
