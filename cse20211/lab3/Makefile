targets=bounce example rotate symbols testrotate
objects=gfx.o

all: $(targets)

%: %.c $(objects)
	gcc $^ -o $@ -lm -lX11

gfx.o: gfx.c
	gcc -c $< -o $@

clean:
	rm $(targets) $(objects)
