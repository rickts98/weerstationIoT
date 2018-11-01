CFLAGS=-std=c99 `pkg-config --cflags glib-2.0`

LDLIBS=`pkg-config --libs glib-2.0`


project=main

exe=unittests


all: fmt check clean


$(exe): $(project)/circularbuffer.o $(project)/reader.o $(project)/tokenizer.o $(project)/parser.o buffermock.o


fmt:

	clang-format -i $(project)/*.c $(project)/*.h $(project)/*.ino

	clang-format -i *.c *.h


check: $(exe)

	cppcheck -q --enable=all --inconclusive --std=c99 .

	./$(exe)

	

clean:
	-rm $(project)/*.o
	-rm -rf $(exe).dSYM/
	rm $(exe)



