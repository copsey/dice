CXXFLAGS = -std=c++11 -O2

src = \
	die.cpp \
	io.cpp \
	main.cpp \
	random.cpp \
	util/cli.cpp \
	util/string.cpp
objs = $(addprefix build/,$(src:.cpp=.o))
 
dice: $(objs)
	$(CXX) $(CXXFLAGS) $(objs) -o dice

$(objs): build/%.o: source/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f dice
	rm -fr build/

.PHONY: clean
