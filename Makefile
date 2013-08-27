CXX = $(shell fltk-config --cxx)
DEBUG = -g
CXXFLAGS = $(shell fltk-config --use-images --cxxflags ) -I. -Iinclude
LDFLAGS = $(shell fltk-config --use-gl --use-images --ldflags )
LDSTATIC = $(shell fltk-config --ldstaticflags )
LINK = $(CXX)
TARGEDIR=target
VPATH = src include $(TARGEDIR)

TARGET =  $(TARGEDIR)/hello
SRCS = hello.cpp
OBJS = hello.o
.SUFFIXES: .o .cpp

$(TARGEDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $< -o $@

all: $(TARGET)


$(TARGET): $(TARGEDIR)/$(OBJS)
	$(LINK) -o $@ $< $(LDSTATIC)

hello.o: hello.cpp

clean:
	rm -rf $(TARGEDIR)/*
	rm -f *.o
	rm -f $(TARGET)

.PHONY: clean
