#include "data_matrix.h"

VALUE rb_mDataMatrix, rb_cEncoder;

semacode_t* encode_string(semacode_t* semacode, char *message) {
  if (semacode == NULL || message == NULL || strlen(message) < 1) {
    return NULL;
  }

  if (semacode->data != NULL) {
    free(semacode->data);
  }
  if (semacode->encoding != NULL) {
    free(semacode->encoding);
  }

  bzero(semacode, sizeof(semacode_t));
  strcat(message, " ");

  iec16022init(&semacode->width, &semacode->height, message);

  semacode->data = (char *) iec16022ecc200(
    &semacode->width,
    &semacode->height,
    &semacode->encoding,
    (int) strlen(message),
    (unsigned char *) message,
    &semacode->raw_encoded_length,
    &semacode->symbol_capacity,
    &semacode->ecc_bytes
  );

  return semacode;
}

static void data_matrix_mark(semacode_t* semacode) {}

static void data_matrix_free(semacode_t* semacode) {
  if (semacode != NULL) {
    if (semacode->data != NULL) {
      free(semacode->encoding);
      free(semacode->data);
    }
    bzero(semacode, sizeof(semacode));
    free(semacode);
  }
}

static VALUE data_matrix_grid(semacode_t *semacode) {
  int w = semacode->width;
  int h = semacode->height;

  VALUE ret = rb_ary_new2(h);

  int x, y;
  for (y = h - 1; y >= 0; y--) {
    VALUE ary = rb_ary_new2(w);
    for (x = 0; x < w; x++) {
      if(semacode->data[y * w + x])
        rb_ary_push(ary, Qtrue);
      else
        rb_ary_push(ary, Qfalse);
    }
    rb_ary_push(ret, ary);
  }

  return ret;
}

static VALUE data_matrix_allocate(VALUE klass) {
  semacode_t *semacode;
  return Data_Make_Struct(klass, semacode_t, data_matrix_mark, data_matrix_free, semacode);
}

static VALUE data_matrix_init(VALUE self, VALUE message) {
  semacode_t *semacode;

  // Check if passed argument is convertable to string
  if (!rb_respond_to(message, rb_intern("to_s")))
    rb_raise(rb_eRuntimeError, "target must respond to 'to_s'");

  Data_Get_Struct(self, semacode_t, semacode);
  encode_string(semacode, StringValuePtr(message));

  return self;
}

static VALUE data_matrix_encode(VALUE self, VALUE encoding) {
  semacode_t *semacode;

  if (!rb_respond_to(encoding, rb_intern ("to_s")))
    rb_raise(rb_eRuntimeError, "target must respond to 'to_s'");

  Data_Get_Struct(self, semacode_t, semacode);

  /* free previous string if that exists */
  if(semacode->data != NULL) {
    free(semacode->data);
    semacode->data = NULL;
  }

  /* do a new encoding */
  DATA_PTR(self) = encode_string(semacode, StringValuePtr(encoding));
  return data_matrix_grid(semacode);
}

static VALUE data_matrix_data(VALUE self) {
  semacode_t *semacode;
  Data_Get_Struct(self, semacode_t, semacode);

  if(semacode->data == NULL)
    return Qnil;
  else
    return data_matrix_grid(semacode);
}

static VALUE data_matrix_encoded(VALUE self) {
  semacode_t *semacode;
  Data_Get_Struct(self, semacode_t, semacode);

  return rb_str_new2(semacode->encoding);
}

static VALUE data_matrix_to_s(VALUE self) {
  semacode_t *semacode;
  VALUE str;
  int x, y, w, h;

  Data_Get_Struct(self, semacode_t, semacode);

  if(semacode == NULL || semacode->data == NULL) return Qnil;

  w = semacode->width;
  h = semacode->height;

  str = rb_str_new2("");

  for (y = h - 1; y >= 0; y--) {
    for (x = 0; x < w; x++) {
      if(semacode->data[y * w + x])
        rb_str_cat(str, "1", 1);
      else
        rb_str_cat(str, "0", 1);
    }
    rb_str_cat(str, ",", 1);
  }
  return str;
}

static VALUE data_matrix_width(VALUE self) {
  semacode_t *semacode;
  Data_Get_Struct(self, semacode_t, semacode);

  return INT2FIX(semacode->width);
}

static VALUE data_matrix_height(VALUE self) {
  semacode_t *semacode;
  Data_Get_Struct(self, semacode_t, semacode);

  return INT2FIX(semacode->height);
}

static VALUE data_matrix_raw_encoded_length(VALUE self) {
  semacode_t *semacode;
  Data_Get_Struct(self, semacode_t, semacode);

  return INT2FIX(semacode->raw_encoded_length);
}

static VALUE data_matrix_symbol_size(VALUE self) {
  semacode_t *semacode;
  Data_Get_Struct(self, semacode_t, semacode);

  return INT2FIX(semacode->symbol_capacity);
}

static VALUE data_matrix_ecc_bytes(VALUE self) {
  semacode_t *semacode;
  Data_Get_Struct(self, semacode_t, semacode);

  return INT2FIX(semacode->ecc_bytes);
}

void Init_data_matrix(void) {
  rb_mDataMatrix = rb_define_module("DataMatrix");
  rb_cEncoder = rb_define_class_under(rb_mDataMatrix, "Encoder", rb_cObject);

  rb_define_alloc_func(rb_cEncoder, data_matrix_allocate);

  rb_define_method(rb_cEncoder, "initialize", data_matrix_init, 1);
  rb_define_method(rb_cEncoder, "encode", data_matrix_encode, 1);
  rb_define_method(rb_cEncoder, "data", data_matrix_data, 0);
  rb_define_method(rb_cEncoder, "encoding", data_matrix_encoded, 0);
  rb_define_method(rb_cEncoder, "to_s", data_matrix_to_s, 0);
  rb_define_method(rb_cEncoder, "width", data_matrix_width, 0);
  rb_define_method(rb_cEncoder, "height", data_matrix_height, 0);
  rb_define_method(rb_cEncoder, "raw_encoded_length", data_matrix_raw_encoded_length, 0);
  rb_define_method(rb_cEncoder, "symbol_size", data_matrix_symbol_size, 0);
  rb_define_method(rb_cEncoder, "ecc_bytes", data_matrix_ecc_bytes, 0);
}
