CC = gcc
n = 1

run: $(n)
	./build/$(n)

# Build executable from n.c
$(n) : $(n).c
	$(CC) -o build/$@ $<


.PHONY: run
