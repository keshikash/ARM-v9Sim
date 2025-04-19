CC = gcc
CFLAGS = -O2 -Wall -lm -pthread

TARGETS = matmul conv attention thread

all: $(TARGETS)

THREADS ?= 4

matmul: sim3.c
	$(CC) $(CFLAGS) -o $@ $<

conv: sim2.c
	$(CC) $(CFLAGS) -o $@ $<

attention: sim1.c
	$(CC) $(CFLAGS) -o $@ $<

thread: sim4.c
	$(CC) $(CFLAGS) -o $@ $<

run: all
	@echo "Running matmul:"
	@./matmul
	@echo ""
	@echo "Running conv:"
	@./conv
	@echo ""
	@echo "Running attention:"
	@./attention
	@echo ""
	@echo "Threading performance"
	@./thread $(THREADS)

clean:
	rm -f $(TARGETS)
