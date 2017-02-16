targets=othello warmup

all: $(targets)

%: %.c
	gcc $< -o $@ -lm

clean:
	rm $(targets)
