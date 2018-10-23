#include "parser.h"
#include "reader.h"
#include "tokenizer.h"
#include <string.h>


#define SPACE " "
#define CRLF "\r\n"
#define CRLFCRLF "\r\n\r\n"
#define GET "GET"
#define TEMPERATURE "/temp"
#define LIGHT "/lux"
#define CONFIGURATION "/conf"
#define HTTP10 "HTTP/1.0"
#define HTTP11 "HTTP/1.1"


/**
 * the parser parses per token and returns controll to the Arduino code.
 *
 * this enables the Arduino to print every token as to debug the connection.
 *
 * state represents the current stage of parsing.
 */

enum stage {
  verb,     // "GET", "PUT"
  space1,   // " "
  resource, // "/temp"
  space2,   // " "
  version,  // "HTTP/1.0" or "HTTP/1.1"
  crlf1     // "\r\n"
};


/**
 * some values are stored while parsing a request.  we use enumerations
 * instead of the original string values to safe memory
 */

enum verb { unknownV, get };
enum resource { unknownR, temp, lux, config };
enum version { unknownVn, http10, http11 };


struct {
  enum stage next;
  enum verb verb;
  enum resource resource;
  enum version version;
} request;


void resetParser() {
  request.next = verb;
  request.verb = unknownV;
  request.resource = unknownR;
  request.version = unknownVn;
}


enum response parseVerb(char *tokenv, int tokenc);
enum response parseSpace(char *tokenv, int tokenc, enum token ttype,
                         const char *expect);
enum response parseResource(char *tokenv, int tokenc);
enum response parseVersion(char *tokenv, int tokenc);

enum response parse(char *tokenv, int tokenc) {

  if (!available()){
    return BAD_REQUEST_400;
  }

  switch (request.next) {
  case verb:
    return parseVerb(tokenv, tokenc);
  case resource:
    return parseResource(tokenv, tokenc);
  case version:
    return parseVersion(tokenv, tokenc);
  case space1:
  case space2:
    return parseSpace(tokenv, tokenc, WS, SPACE);
  case crlf1: 
    return parseSpace(tokenv, tokenc, EOL, CRLF);
  }

  return INTERNAL_SERVER_ERROR_500;
}


enum response parseSpace(char *tokenv, int tokenc, enum token ttype,
                         const char *expect) {

  enum token tok;
  tok = scan(tokenv, tokenc);

  if (tok != ttype){
    return BAD_REQUEST_400;
  }

  if (strncmp(tokenv, expect, tokenc) != 0){
    return BAD_REQUEST_400;
  }

  request.next++;
  return IN_PROGRESS;
}


enum response parseVerb(char *tokenv, int tokenc) {
  enum token tok;
  tok = scan(tokenv, tokenc);

  if (tok != WORD){
    return BAD_REQUEST_400;
  }

  if (strncmp(tokenv, GET, tokenc) == 0)
    request.verb = get;

  if (request.verb == unknownV)
    return NOT_IMPLEMENTED_501;

  request.next++;
  return IN_PROGRESS;
}


enum response parseResource(char *tokenv, int tokenc) {
	enum token tok;
	tok = scan(tokenv, tokenc);

	if(tok != WORD){
		return BAD_REQUEST_400;
	}
	if(strncmp(tokenv, TEMPERATURE, tokenc) == 0){
		request.resource = temp;
	}else if(strncmp(tokenv, LIGHT, tokenc) == 0){
		request.resource = lux;
	}else if(strncmp(tokenv, CONFIGURATION, tokenc) == 0){
		request.resource = config;
	}

	if(request.resource == unknownR){
		return NOT_IMPLEMENTED_501;
	}else if(request.resource == temp){
    request.next ++;
    return TEMP_200;
  }else if(request.resource == lux){
    request.next++;
    return LUX_200;
  }


	request.next++;
  return IN_PROGRESS;

}


enum response parseVersion(char *tokenv, int tokenc) {
  enum token tok;
  tok = scan(tokenv, tokenc);

  if (tok != WORD){

    return BAD_REQUEST_400;
  }

  if (strncmp(tokenv, HTTP10, tokenc) == 0)
    request.version = http10;
  else if (strncmp(tokenv, HTTP11, tokenc) == 0)
    request.version = http11;

  if (request.version == unknownVn){
    return BAD_REQUEST_400;
  }

  request.next ++;
  return IN_PROGRESS;

}
