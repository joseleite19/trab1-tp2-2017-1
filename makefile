# Assume-se o Linux como sistema operacional padrão:
# -----------------------------------------------------------------------------------------------------------------------------------------------------------
# Compilador a ser utilizado
CC=g++
# Comando para remover um diretório recursivamente e ignorar caso não exista
RMDIR = rm -rf
# Comando para remover um arquivo e ignorar caso não exista
RM = rm -f

# "Flags" para a geração automática das dependências
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d
# Diretivas que são utilizadas na compilação de cada objeto
DIRECTIVES = -std=c++11 -Wall -Wextra -c -I $(HEADER_PATH)
# Diretivas que são utilizadas na "linkagem" dos objetos gerando o executável
LIBS = -lm


# Um caminho para guardar e acessar cada tipo de arquivo .h (headers),
# .cpp (sources), .o (objects) e .d (dependencies), respectivamente
HEADER_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

# Uma lista de arquivos para cada tipo de arquivo:
# .cpp .o e .d respectivamente
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)

EXEC = TrabalhoPratico_1

# Caso o Sistema Operacional seja Windows, modifica-se as seguintes variáveis:
ifeq ($(OS),Windows_NT)
# Comando para remover um diretório recursivamente e ignorar caso não exista
RMDIR = rd /s /q
#Comando para deletar um arquivo
RM = del
# Nome do executável final (deve ter extensão .exe necessária para o Windows)
EXEC := $(EXEC).exe
endif


# Regra default:
all: $(EXEC)
# Regra de criação do executável final:
$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

# Regra de inferência para criação dos objetos de compilação: 
$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
# De acordo com o SO, tenta criar os diretórios
# dep e bin e ignora caso eles já existam
#----------------------------------------------------------------------------------------------------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH)
endif
#----------------------------------------------------------------------------------------------------------------------------------------------------------------

# Gera os objetos usando diretivas de compilação e as respectivas dependências 
	$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES)
# Inclui as regras geradas pelos arquivos de dependência
-include $(DEP_FILES)

# Regra para limpar/deletar todos os arquivos e diretórios criados pelo make
clean:
	$(RMDIR) $(BIN_PATH) $(DEP_PATH)
	$(RM) $(EXEC)	

# Regra que estabelece que arquivos .d são "preciosos"
.PRECIOUS: $(DEP_PATH)/%.d
# Regra que torna as dependências "phony"
.PHONY: debug clean release

# Regra para printar uma variável no terminal. Auxilia no debug do Makefile
print-% : ; @echo $* = $($*)

# Regra que inclui diretivas de debug na compilação
debug: DIRECTIVES += -ggdb -O0
debug: all

# Regra que inclui diretivas de compilação otimizada
release: DIRECTIVES += -Ofast -mtune=native
release: all

run : all
	./$(EXEC)