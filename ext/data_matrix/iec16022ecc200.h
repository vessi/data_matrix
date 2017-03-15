// IEC16022 bar code generation library
// Adrian Kennard, Andrews & Arnold Ltd
// with help from Cliff Hones on the RS coding
//
// Revision 1.3  2004/09/09 07:45:09  cvs
// Added change history to source files
// Added "info" type to IEC16022
// Added exact size checking shortcodes on encoding generation for iec16022
//

// Main encoding function
// Returns the grid (malloced) containing the matrix. L corner at 0,0.
// Takes suggested size in *Wptr, *Hptr, or 0,0. Fills in actual size.
// Takes barcodelen and barcode to be encoded
// Note, if *encodingptr is null, then fills with auto picked (malloced) encoding
// If lenp not null, then the length of encoded data before any final unlatch or pad is stored
// If maxp not null, then the max storage of this size code is stored
// If eccp not null, then the number of ecc bytes used in this size is stored
// Returns 0 on error (writes to stderr with details).

#ifndef IEC16022ECC200_H
#define IEC16022ECC200_H 1

#define IEC16022ECC200_MAXBARCODE 3116
#define IEC16022ECC200_ERROR_STRING_TOO_SHORT -1
#define IEC16022ECC200_ERROR_CANNOT_ENCODE_CHARACTER_X12 -2
#define IEC16022ECC200_ERROR_UNEXPECTED_FAILURE -3
#define IEC16022ECC200_ERROR_UNKNOWN_ENCODING -4
#define IEC16022ECC200_ERROR_DID_NOT_FIT -5
#define IEC16022ECC200_BARCODE_TOO_LONG -6

unsigned char* iec16022ecc200(int *Wptr, int *Hptr, char **encodingptr, const int barcodelen, const unsigned char *barcode,
                              int *lenp,int *maxp,int *eccp);
void iec16022init(int *Wptr, int *Hptr, const char *barcode);

#endif
