#ifndef DATA_MATRIX_H
#define DATA_MATRIX_H 1

#include "ruby.h"
#include "iec16022ecc200.h"

typedef struct semacode_t {
  int width;
  int height;
  int raw_encoded_length;
  int symbol_capacity;
  int ecc_bytes;
  char *encoding;
  char *data;
} semacode_t;

semacode_t* encode_string(semacode_t* semacode, const char *message);
static void data_matrix_mark(semacode_t* semacode);
static void data_matrix_free(semacode_t* semacode);

#endif /* DATA_MATRIX_H */
