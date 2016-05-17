#ifndef LENC_ENCODER_H__
#define LENC_ENCODER_H__ 0

class Context;
class Encoder {
public:
    const char* name;
    
    virtual int initial(Context* ctx, char* config, int len) = 0;
    virtual int handle(Context* ctx, char* in, int inLen, char*& out, int& outLen) = 0;

    Encoder* next;
    Encoder* chain;

    virtual ~Encoder(){}
};

extern Encoder* root;

#endif
