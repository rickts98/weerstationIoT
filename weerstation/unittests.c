#include "main/circularbuffer.h"
//#include "main/tempControl.ino"
#include "buffermock.h"
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

// void sensor_temp() {
//   int val;

//   val = printTemperature();

//   g_assert_cmpint(val, >, -20);
//   g_assert_cmpint(val, <, 45);
// }

void reader_available() {

  // essentially tests the mock ...

  reset_buffer("x");

  // g_assert(available());

  // g_assert(read() == 'x');

  // g_assert(!available());
}

int main(int argc, char **argv) {
  initParser(available_buffer, read_buffer, peek_buffer);
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/reader/available", reader_available);

  // g_test_add_func("/buffer/init", buffer_init);
  // g_test_add_func("/buffer/add/overwrite", buffer_add_overwrite);
  // g_test_add_func("/buffer/add/ignore", buffer_add_ignore);
  // g_test_add_func("/buffer/add/read", buffer_add_read);
  // g_test_add_func("/sensor/temp", sensor_temp);

  return g_test_run();
}
