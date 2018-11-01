#include "buffermock.h"
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 200

// input stream mock

struct {

  char *text;

  int length;

  int current;

} buffer;

// input stream buffer mock implementation

void reset_buffer(const char *text) {

  buffer.length = 0;

  for (;;) {

    if (text[buffer.length] == '\0')

      break;

    buffer.length++;

    if (buffer.length > MAX_LENGTH) {

      printf("ERROR: input text too long\n");

      break;
    }
  }

  buffer.text = strndup(text, buffer.length);

  buffer.current = 0;
}

int available_buffer() { return buffer.current < buffer.length; }

char peek_buffer() { return buffer.text[buffer.current]; }

char read_buffer() {

  char c = peek_buffer();

  buffer.current++;

  return c;
}
