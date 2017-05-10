SRC_DIR = src
HEADERS_DIR = include
OBJ_DIR = obj
COMP = g++
EXE = exe
DIRECTIVES = -Wall -std=c++11 -I$(HEADERS_DIR)

CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
HPP_FILES = $(wildcard $(HEADERS_DIR)/*.hpp)


all: obj_dir compile


#cria os arquivos .o
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(HPP_FILES)
	$(COMP) -c -o $@ $< $(DIRECTIVES)

#junta os .o em um arquivo executavel
compile: $(OBJ_FILES)
	$(COMP) -o $(EXE) $^

#cria a pasta para os arquivos .o caso nao exista
obj_dir :
	mkdir -p $(OBJ_DIR)

#compila e roda o programa
run : all
	./$(EXE)

#deleta a pasta dos arquivos .o e o executavel
clean :
	rm -f -r $(OBJ_DIR)
	rm -f $(EXE)
