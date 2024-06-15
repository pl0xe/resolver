CC=gcc
OUT=resolver

resolver : resolver.c resolver.h
	$(CC) ./resolver.c -o $(OUT)

clean : resolver
	rm -f resolver
