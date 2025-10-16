OPENSSL_INC = /opt/homebrew/opt/openssl@3/include
OPENSSL_LIB = /opt/homebrew/opt/openssl@3/lib
CFLAGS = -I$(OPENSSL_INC) -L$(OPENSSL_LIB) -lcrypto

all:
	mkdir -p ./targets
	gcc fib.c -o targets/fib
	gcc server.c -o targets/server $(CFLAGS)
	gcc hash.c -o targets/hash $(CFLAGS)
