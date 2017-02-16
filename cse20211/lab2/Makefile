targets=graph mortgage table
all: $(targets)

%: %.c
	gcc $< -o $@ -lm

clean:
	rm $(targets)
