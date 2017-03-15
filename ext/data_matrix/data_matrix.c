#include "data_matrix.h"

VALUE rb_mDataMatrix;

void
Init_data_matrix(void)
{
  rb_mDataMatrix = rb_define_module("DataMatrix");
}
