#include "FormatContext.h"
extern "C" {
#include <libavformat/avformat.h>
}

FormatContext::FormatContext() {
    _context = avformat_alloc_context();
}

FormatContext::~FormatContext() {
    avformat_free_context(_context);
}
