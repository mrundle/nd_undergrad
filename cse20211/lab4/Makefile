targets=carnival graph numbers max
objects=gfx.o

all: $(targets)

%: %.c $(objects)
	gcc $^ -o $@ -lm -lX11

gfx.o: gfx.c
	gcc -c $< -o $@

clean:
	rm $(targets) $(objects)
