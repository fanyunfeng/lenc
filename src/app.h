#ifndef LENC_APP_H__
#define LENC_APP_H__ 0
#include <stdio.h>

class Encoder;
class Context{
public:
    int maxLineSize;
    Encoder* chain;

    Context(){
        chain = NULL;
        maxLineSize = 1024 * 8;
    }
};

#endif

