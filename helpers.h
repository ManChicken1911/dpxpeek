extern void print_prebuf( const char *prebuf );
extern void print_postbuf( const char *postbuf, int newline = true );

extern void print_DPXfloat( const char *prebuf, float val, unsigned int newline = true, const char *postbuf = "" );
extern void print_DPXint32( const char *prebuf, unsigned int val, unsigned int newline = true, const char *postbuf = "" );
extern void print_DPXint16( const char *prebuf, unsigned short val, unsigned int newline = true, const char *postbuf = "" );
extern void print_DPXint8( const char *prebuf, unsigned char val, unsigned int newline = true, const char *postbuf = "" );
extern void print_DPXstring( const char *prebuf, char *buf, unsigned int newline = true, const char *postbuf = "" );

#define  UNDEF_STR "<undef>"
#define  UNDEF_STR_INF "<undef - nonstandard>"
