#ifndef parser_h

#define parser_h


enum response {

  IN_PROGRESS, // only part of the requests parsed

  DATA_200,

  CONFIG_200, // reply current config

  // CONFIG_201, // new config accepted

  TEMP_200, // reply temperature

  LUX_200, // reply light

  BAD_REQUEST_400,     // no host, syntax error

  NOT_IMPLEMENTED_501, // verb not implemented

  // METHOD_NOT_ALLOWED_405, // we're probably not going to do that

  // LENGTH_REQUIRED_411, // no Content-Length

  NOT_FOUND_404, // unrecognized resource

                 // UNAUTHORIZED_401 // no or invalid token

  INTERNAL_SERVER_ERROR_500

};


/**

 * reset parser, make it ready for next request

 */

void resetParser();


/**

 * parses the input stream using tokenv with length

 * tokenc as the token buffer.

 *

 * this makes the length of the token buffer easily

 * configurable.

 *

 * we probably need to introduce another token that

 * indicates we're not don yet: this preserves the

 * possibility to print the request in the arduino.

 */

enum response parse(char *tokenv, int tokenc);


#endif
