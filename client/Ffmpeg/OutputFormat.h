#ifndef PORTAL_OUTPUTFORMAT_H
#define PORTAL_OUTPUTFORMAT_H

#include <cstdio>
#include <string>
#include "FormatContext.h"

#define RECORDING_WIDTH 500
#define RECORDING_HEIGHT    500

class AVCodec;
class AVFrame;
class AVPacket;
class AVOutputFormat;
class AVStream;
class AVCodecContext;
class SwsContext;

class OutputFormat {
private:
    FormatContext _context;
    AVOutputFormat* _avOutputFormat;
    AVCodecContext* _codecContext;
    AVStream* _video_avstream;
    AVFrame* _frame;
    AVPacket* _pkt;
    FILE* _outputFile;
    int _currentPts;

    // Inicializa frame
    void initFrame();

    // Inicializa contexto de codec (codificador del video)
    void codecContextInit(AVCodec* codec);

public:
    OutputFormat(const std::string& filename);

    ~OutputFormat();

    // Escribe un frame a disco. Utiliza `swsContext` para convertir
    // de RGB24 a YUV420p
    void writeFrame(const char* data, SwsContext* swsContext);

    // Cierra el stream de video
    void close();
};


#endif //PORTAL_OUTPUTFORMAT_H
