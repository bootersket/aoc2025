CC = gcc
n = 1

run: $(n)
	./$(n)

# Build executable from n.c
$(n) : $(n).c
	$(CC) -o $@ $<


.PHONY: run
