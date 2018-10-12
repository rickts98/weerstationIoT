#include "tokenizer.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "ethernet.h"

enum token scanWhiteSpace(char *tokenv, int tokenc);
enum token scanNewLines(char *tokenv, int tokenc);
enum token scanWord(char *tokenv, int tokenc);

int isWhiteSpace(char c)
{
  return (c == ' ' || c == '\t');
}

int isNewLine(char c)
{
  return (c == '\n' || c == '\r');
}

enum token scan(char *tokenv, int tokenc)
{
  assert(tokenc > 0);

  if (available())
  {
    memset(tokenv, 0, tokenc); // reset token value

    char c = peek1();

    if (c == ':')
    {
      tokenv[0] = read1();

      return COLON;
    }
    else if (isWhiteSpace(c))
    {

      return scanWhiteSpace(tokenv, tokenc);
    }
    else if (isNewLine(c))
    {

      return scanNewLines(tokenv, tokenc);
    }
    else
    {

      return scanWord(tokenv, tokenc);
    }
  }

  return UNAVAILABLE;
}

enum token scanWord(char *tokenv, int tokenc)
{
  int pos = 0;

  for (;;)
  {
    if (available() && !isWhiteSpace(peek1()) && !isNewLine(peek1()))
    {
      if (pos >= tokenc - 1)
      {
        return ILLEGAL;
      }
      tokenv[pos] = read1();
      pos++;
    }
    else
    {
      return WORD;
    }
  }
}

enum token scanWhiteSpace(char *tokenv, int tokenc)
{

  int pos = 0;

  for (;;)
  {

    if (available() && isWhiteSpace(peek1()))
    {

      if (pos >= tokenc - 1)
      {

        return ILLEGAL;
      }

      tokenv[pos] = read1();

      pos++;
    }
    else
    {

      return WS;
    }
  }
}

enum token scanNewLines(char *tokenv, int tokenc)
{

  int pos = 0;

  for (;;)
  {

    if (available() && isNewLine(peek1()))
    {

      if (pos >= tokenc - 1)
      {

        return ILLEGAL;
      }

      tokenv[pos] = read1();

      pos++;
    }
    else
    {

      return EOL;
    }
  }
}
