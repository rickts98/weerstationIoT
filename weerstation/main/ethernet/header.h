#ifndef reader_h

#define reader_h


/**

   initParser makes read functions available to reader code

*/

void initParser(int (*availableFunc)(), // client available function

                char (*readFunc)(),     // client read function

                char (*peekFunc)()      // client peek function

);


/**

 * these function pointers can be reqgarded as functionsion defined

 * in header.c.

 *

 * so, read this as "function available()" defined here.  This is not

 * actually true, but conceptually it makes things easier to understand.

 *

 * see @kenr p. 45

 */

extern int (*available)();

extern char (*read)();

extern char (*peek)();


#endif
