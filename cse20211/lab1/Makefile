targets=prog1 prog2 prog3
all: $(targets)

%: %.c
	gcc $< -o $@

clean:
	rm $(targets)
