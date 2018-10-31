#include "circularbuffer.h"
#include <stdio.h>
#include <stdlib.h>

// initalisatie van de buffer
cbuffer *cbInit(int8_t size, enum cbmode mode) {
  cbuffer *newBuffer = malloc(sizeof(cbuffer));

  if (newBuffer != NULL) {
    newBuffer->data = malloc(size * sizeof(cbtype));

    if (newBuffer->data == NULL) {
      return NULL;
    }

    newBuffer->mode = mode;
    newBuffer->size = size;
    newBuffer->start = 0;
    newBuffer->count = 0;
  }

  return newBuffer;
}

cbuffer *cbFree(cbuffer *buffer) {
  free(buffer->data);
  free(buffer);
  return NULL;
}

// controle of de iets in de buffer staat
int cbAvailable(cbuffer *buffer) {
  if (buffer->count > buffer->start) {
    return 1;
  } else {
    return 0;
  }
}

// het kijken naar de laatste waarde
cbtype cbPeek(cbuffer *buffer) {
  cbtype oldest = buffer->data[buffer->start];

  return oldest;
}

// het lezen van een waarde uit de buffer
cbtype cbRead(cbuffer *buffer) {
  cbtype oldest = buffer->data[buffer->start];
  buffer->start = (buffer->start + 1) % buffer->size;
  return oldest;
}

// toevoegen van een niewe waarde in de buffer
int8_t cbAdd(cbuffer *buffer, cbtype value) {

  if (buffer->mode == OVERWRITE_IF_FULL) {
    buffer->data[buffer->count] = value;
    if (buffer->count < buffer->size) {
      buffer->count = (buffer->count + 1) % buffer->size;
    }
    return 1;
  } else if (buffer->mode == IGNORE_IF_FULL) {
    if (buffer->count < buffer->size) {
      buffer->data[buffer->count] = value;
      buffer->count += 1;
      return 1;
    } else {
      return 0;
    }
  }

  return 0;
}
