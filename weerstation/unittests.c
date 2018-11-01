#include "buffermock.h"
#include "main/circularbuffer.h"
#include "main/parser.h"
#include "main/reader.h"
#include "main/tokenizer.h"
#include <glib.h>

#define BSIZE 10

void buffer_init() {

  cbuffer *b1 = cbInit(100, OVERWRITE_IF_FULL);

  g_assert(b1);

  g_assert(b1->data);

  g_assert_cmpint(b1->size, ==, 100);

  b1 = cbFree(b1);
}

void buffer_add_overwrite() {

  cbuffer *b = cbInit(3, OVERWRITE_IF_FULL);

  int succes = cbAdd(b, 100);

  g_assert(succes);

  g_assert_cmpint(b->data[0], ==, 100);

  succes = cbAdd(b, 200);

  g_assert(succes);

  g_assert_cmpint(b->data[1], ==, 200);

  succes = cbAdd(b, 300);

  g_assert(succes);

  g_assert_cmpint(b->data[2], ==, 300);

  succes = cbAdd(b, 400);

  g_assert(succes);

  g_assert_cmpint(b->data[0], ==, 400); // overwites [0]

  b = cbFree(b);
}

void buffer_add_ignore() {

  cbuffer *b = cbInit(3, IGNORE_IF_FULL);

  int succes = cbAdd(b, 100);

  g_assert(succes);

  g_assert_cmpint(b->data[0], ==, 100);

  succes = cbAdd(b, 200);

  g_assert(succes);

  g_assert_cmpint(b->data[1], ==, 200);

  succes = cbAdd(b, 300);

  g_assert(succes);

  g_assert_cmpint(b->data[2], ==, 300);

  g_assert_cmpint(b->mode, ==, IGNORE_IF_FULL);

  g_assert_cmpint(b->size, ==, 3);

  g_assert_cmpint(b->count, ==, 3);

  succes = cbAdd(b, 400);

  g_assert(!succes);

  g_assert_cmpint(b->data[0], ==, 100);

  b = cbFree(b);
}

void buffer_add_read() {

  cbuffer *b = cbInit(5, OVERWRITE_IF_FULL);

  int succes;

  cbtype val;

  succes = cbAdd(b, 100);

  g_assert(succes);

  g_assert_cmpint(b->data[0], ==, 100);

  succes = cbAdd(b, 200);

  g_assert(succes);

  g_assert_cmpint(b->data[0], ==, 100);

  g_assert_cmpint(b->data[1], ==, 200);

  succes = cbAdd(b, 300);

  g_assert(succes);

  g_assert_cmpint(b->data[0], ==, 100);

  g_assert_cmpint(b->data[1], ==, 200);

  g_assert_cmpint(b->data[2], ==, 300);

  val = cbRead(b);

  g_assert_cmpint(val, ==, 100);

  g_assert_cmpint(b->data[1], ==, 200);

  g_assert_cmpint(b->data[2], ==, 300);

  val = cbRead(b);

  g_assert_cmpint(val, ==, 200);

  g_assert_cmpint(b->data[2], ==, 300);

  succes = cbAdd(b, 400);

  g_assert(succes);

  g_assert_cmpint(b->data[2], ==, 300);

  g_assert_cmpint(b->data[3], ==, 400);

  succes = cbAdd(b, 500);

  g_assert(succes);

  g_assert_cmpint(b->data[2], ==, 300);

  g_assert_cmpint(b->data[3], ==, 400);

  g_assert_cmpint(b->data[4], ==, 500);

  val = cbRead(b);

  g_assert_cmpint(val, ==, 300);

  g_assert_cmpint(b->data[3], ==, 400);

  g_assert_cmpint(b->data[4], ==, 500);

  succes = cbAdd(b, 600);

  g_assert(succes);

  g_assert_cmpint(b->data[3], ==, 400);

  g_assert_cmpint(b->data[4], ==, 500);

  g_assert_cmpint(b->data[0], ==, 600);

  val = cbRead(b);

  g_assert_cmpint(val, ==, 400);

  g_assert_cmpint(b->data[4], ==, 500);

  g_assert_cmpint(b->data[0], ==, 600);

  val = cbRead(b);

  g_assert_cmpint(val, ==, 500);

  g_assert_cmpint(b->data[0], ==, 600);

  g_assert(cbAvailable(b));

  val = cbRead(b);

  g_assert_cmpint(val, ==, 600);

  g_assert(!cbAvailable(b));

  b = cbFree(b);
}

void reader_available() {

  // essentially tests the mock ...

  reset_buffer("x");

  g_assert(available());

  g_assert(read() == 'x');

  g_assert(!available());
}

void tokenizer_space() {

  char buffer[BSIZE];

  enum token tok;

  reset_buffer(" \t\n\n\rX");

  tok = scan(buffer, BSIZE);

  g_assert(tok == WS);

  g_assert(strncmp(buffer, " \t", BSIZE) == 0);

  g_assert(available());

  tok = scan(buffer, BSIZE);

  g_assert(tok == EOL);

  g_assert(strncmp(buffer, "\n\n\r", BSIZE) == 0);

  g_assert(available());
}

void tokenizer_line_colons() {

  char buffer[BSIZE];

  enum token tok;

  reset_buffer(":  ::");

  tok = scan(buffer, BSIZE);

  g_assert(tok == COLON);

  g_assert(strncmp(buffer, ":", BSIZE) == 0);

  g_assert(available());

  tok = scan(buffer, BSIZE);

  g_assert(tok == WS);

  g_assert(strncmp(buffer, "  ", BSIZE) == 0);

  g_assert(available());

  tok = scan(buffer, BSIZE);

  g_assert(tok == COLON);

  g_assert(strncmp(buffer, ":", BSIZE) == 0);

  g_assert(available());

  tok = scan(buffer, BSIZE);

  g_assert(tok == COLON);

  g_assert(strncmp(buffer, ":", BSIZE) == 0);

  g_assert(!available());
}

void tokenizer_line_words() {

  char buffer[BSIZE];

  enum token tok;

  // noot_mies is max size, wim_zus_jet is illegal

  reset_buffer("aap noot_mies wim_zus_jet");

  // don't be smart to make a function that tests all

  // three: failing tests produce line numbers that

  // do not point to the exact problem

  tok = scan(buffer, BSIZE);

  g_assert(tok == WORD);

  g_assert(strncmp(buffer, "aap", BSIZE) == 0);

  g_assert(available());

  tok = scan(buffer, BSIZE);

  g_assert(tok == WS);

  g_assert(strncmp(buffer, " ", BSIZE) == 0);

  g_assert(available());

  tok = scan(buffer, BSIZE);

  g_assert(tok == WORD);

  g_assert(strncmp(buffer, "noot_mies", BSIZE) == 0);

  g_assert(available());

  tok = scan(buffer, BSIZE);

  g_assert(tok == WS);

  g_assert(strncmp(buffer, " ", BSIZE) == 0);

  g_assert(available());

  tok = scan(buffer, BSIZE);

  g_assert(tok == ILLEGAL);

  g_assert(strncmp(buffer, "wim_zus_j", BSIZE) == 0);

  g_assert(available()); // part of jet remains to be read
}

void parser_get() {

  char buffer[BSIZE];

  enum response resp;

  reset_buffer("GET /temp HTTP/1.1\r\n");

  resetParser();

  // GET

  resp = parse(buffer, BSIZE);

  g_assert_cmpint(resp, ==, IN_PROGRESS);

  // " "

  resp = parse(buffer, BSIZE);

  g_assert_cmpint(resp, ==, IN_PROGRESS);

  // /temp

  resp = parse(buffer, BSIZE);

  g_assert_cmpint(resp, ==, TEMP_200);

  // " "

  resp = parse(buffer, BSIZE);

  g_assert_cmpint(resp, ==, IN_PROGRESS);

  // "HTTP/1.1"

  resp = parse(buffer, BSIZE);

  g_assert_cmpint(resp, ==, IN_PROGRESS);

  // "\r\n"

  resp = parse(buffer, BSIZE);

  g_assert_cmpint(resp, ==, IN_PROGRESS);

  reset_buffer("get /temp HTTP/1.1\r\n");

  resetParser();

  resp = parse(buffer, BSIZE);

  g_assert(resp == METHOD_NOT_ALLOWED_405);

  reset_buffer("GETX /temp HTTP/1.1\r\n");

  resetParser();

  resp = parse(buffer, BSIZE);

  g_assert(resp == METHOD_NOT_ALLOWED_405);
}

int main(int argc, char **argv) {
  initParser(available_buffer, read_buffer, peek_buffer);
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/reader/available", reader_available);
  g_test_add_func("/tokenizer/space", tokenizer_space);
  g_test_add_func("/tokenizer/line_colons", tokenizer_line_colons);
  g_test_add_func("/tokenizer/line_words", tokenizer_line_words);
  g_test_add_func("/parser/get", parser_get);

  g_test_add_func("/buffer/init", buffer_init);
  g_test_add_func("/buffer/add/overwrite", buffer_add_overwrite);
  g_test_add_func("/buffer/add/ignore", buffer_add_ignore);
  g_test_add_func("/buffer/add/read", buffer_add_read);

  return g_test_run();
}
