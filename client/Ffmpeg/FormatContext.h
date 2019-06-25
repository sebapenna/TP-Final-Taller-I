#ifndef PORTAL_FORMATCONTEXT_H
#define PORTAL_FORMATCONTEXT_H

class AVFormatContext;

class FormatContext {
private:
    AVFormatContext *_context;

public:
    FormatContext();
    ~FormatContext();
};


#endif //PORTAL_FORMATCONTEXT_H
