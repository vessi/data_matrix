#ifndef REEDSOL_H
#define REEDSOL_H 1
/* don't compile in the main function from reedsol.c */
#define LIB

void rs_init_gf(int poly);
void rs_init_code(int nsym, int index);
void rs_encode(int len, unsigned char *data, unsigned char *res);

#endif
