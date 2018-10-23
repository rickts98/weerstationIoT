#ifndef tokenizer_h

#define tokenizer_h


enum token {
  ILLEGAL,     // usually too long
  UNAVAILABLE, // no more chars available
  COLON,       // :
  WS,          // whitespace " " \t
  EOL,         // end of line \r \n
  OPEN,        // { - object open
  CLOSE,       // } - object close
  KEY,         // simple object key, without quotes
  VAL,         // simple object val, without quotes
  WORD         // remaining series of characters
};


// get next from stream, if token > tokenc, ILLEGAL
// is returned.

enum token scan(char *tokenv, int tokenc);


#endif
