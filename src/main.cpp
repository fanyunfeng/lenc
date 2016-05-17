#include <stdio.h>
#include <malloc.h>

#include "encoder.h"
#include "app.h"

int parseArgs(Context* ctx, int argc, char** argv){
    return 0;
}

int buildChain(Context* ctx){
    return 0;
}


int rmTermChr(char* buf, int size){
    while(size){
        -- size;

        switch(buf[size]){
        case '\r':
        case '\n':
            buf[size] = 0;
            continue;
        default:
            return size + 1;
        }
    }

    return 0;
}

int processFile(Context* ctx, FILE* istream, FILE* ostream){
    size_t size;
    Encoder* chain;
    
    char* in, *out;
    int inLen, outLen;

    char* lineptr = (char*) malloc(ctx->maxLineSize + 1);

    if(lineptr == NULL){
        return 1;
    }

    while(true){
        size = getline(&lineptr, &(ctx->maxLineSize), istream);

        if(size < 0){
            break;
        }

        size = rmTermChr(lineptr, size);

        out = lineptr;
        outLen = size;

        if(size > 0){
            chain = ctx->chain;

            while(chain){
                in = out;
                inLen = outLen;

                if(chain->handle(ctx, in, inLen, out, outLen)){
                    goto exit;
                }

                chain = chain->chain;
            }
        }
      
        if(outLen == 0){
            fprintf(ostream, "\n");
        }
        else{
            fprintf(istream, "%s\n", out);
        }
    }

exit:
    free(lineptr);
}

int main(int argc, char** argv){

    ctx = new Context();

    if(parseArgs(ctx, argc, argv)){
        return 1;
    }

    if(buildChain(ctx)){
        return 1;
    }

    processFile(ctx, stdin, stdout);

    return 0; 
}
