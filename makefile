TARGET=a.out
all: $(TARGET)

CC=g++
CPPFLAGS=-O3 

$(TARGET): mhs.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
