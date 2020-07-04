BINS = func_call_g func_call func_call_fast
all: $(BINS)

func_call_g: func_call.c
	$(CC) -o $@ $< -g
func_call: func_call.c
	$(CC) -o $@ $<

func_call_fast: func_call.c
	$(CC) -o $@ $< -DFAST

.PNOHY: clean
clean:
	rm -f $(BINS)
