TARGET=a.out
all: $(TARGET)

CC=g++
CPPFLAGS=-O3 -mavx -mavx2

$(TARGET): mhs.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
