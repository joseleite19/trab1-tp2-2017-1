TARGET  = quiz
FLAGS   = -Wall

CPP     = g++
SRCS    = $(shell find src -name '*.cpp')
HEADERS = $(shell find src -name '*.hpp')
OBJS    = $(addprefix obj/,$(notdir $(SRCS:%.cpp=%.o)))

$(TARGET): $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $@

obj/%.o: src/%.cpp $(HEADERS)
	mkdir -p obj
	$(CPP) -c $< -o $@

clean:
	rm -rf $(TARGET) obj
