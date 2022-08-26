TARGET=main
TARGET_SOURCES=main.c
FLAGS=-O2 -Wall -MMD
LIBS=

CMP = gcc
LDFLAGS=$(LIBS)

all: $(TARGET) clean

$(TARGET): main.o
	$(CMP) $(FLAGS) -o $@ $^ $(LDFLAGS)

main.o : main.c
	$(CMP) $(FLAGS) -c -o $@ $<

clean :
	@rm -rf *. o *. d *~