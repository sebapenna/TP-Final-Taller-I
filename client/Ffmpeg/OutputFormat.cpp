#include "OutputFormat.h"
#include <string>
#include <Common/exceptions.h>
extern "C" {
#include <libavutil/frame.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

void OutputFormat::initFrame() {
    _frame->format = _codecContext->pix_fmt;
    _frame->width  = _codecContext->width;
    _frame->height = _codecContext->height;

    av_frame_get_buffer(_frame, 0);
    _currentPts = 0;
}

void OutputFormat::codecContextInit(AVCodec *codec) {
    _codecContext = avcodec_alloc_context3(codec);
    // La resolución debe ser múltiplo de 2
    _codecContext->width = RECORDING_WIDTH;
    _codecContext->height = RECORDING_HEIGHT;
    _codecContext->time_base = {1,25};
    _codecContext->framerate = {25,1};
    _codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
    _codecContext->gop_size = 10;
    _codecContext->max_b_frames = 2;
    if (codec->id == AV_CODEC_ID_H264) {
        _codecContext->profile = FF_PROFILE_H264_BASELINE;
        av_opt_set(_codecContext->priv_data, "preset", "slow", 0);
    }
    avcodec_open2(_codecContext, codec, nullptr);
}

OutputFormat::OutputFormat(const std::string &filename) : _context() {
    _frame = av_frame_alloc();
    if (!_frame) 
        throw CouldntAllocateFrameException();
    
    _pkt = av_packet_alloc();

    _avOutputFormat = av_guess_format(nullptr, filename.c_str(), nullptr);    // Deduce extension
    if (!_avOutputFormat)
        _avOutputFormat = av_guess_format("mpeg", nullptr, nullptr);    // Usar formato standard

    if (!_avOutputFormat)
        throw CouldntFindOutputFormatException();

    _avOutputFormat->video_codec = AV_CODEC_ID_H264;
    AVCodec *codec = avcodec_find_encoder(_avOutputFormat->video_codec);
    if (!codec)
        throw CouldntFindEncoderException();

    codecContextInit(codec);
    _outputFile = fopen(filename.c_str(), "wb");
    initFrame();    
}

OutputFormat::~OutputFormat() {
    avcodec_close(_codecContext);
    avcodec_free_context(&_codecContext);
    av_packet_free(&_pkt);
    av_frame_free(&_frame);
    fclose(_outputFile);
}


static void encode(AVCodecContext *ctx, AVFrame *frame, AVPacket *pkt, FILE *outfile) {
    int ret = avcodec_send_frame(ctx, frame);
    if (ret < 0)
        throw SendFrameException();

    for (ret = avcodec_receive_packet(ctx, pkt); ret >= 0; ret = avcodec_receive_packet(ctx, pkt)) {
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0)
            throw EncodeErrorException();
        fwrite(pkt->data, 1, pkt->size, outfile);
        av_packet_unref(pkt);
    }
}

void OutputFormat::writeFrame(const char *data, SwsContext *ctx) {
    const auto* tmp = (const u_int8_t*) data;
    int width = RECORDING_WIDTH * 3;     // El ancho del video x3 por la cantidad de bytes
    sws_scale(ctx, &tmp, &width, 0, _frame->height, _frame->data, _frame->linesize);
    _frame->pts = _currentPts;
    _currentPts++;
    encode(_codecContext, _frame, _pkt, _outputFile); // Codifico imagen
}

void OutputFormat::close() {
    encode(_codecContext, nullptr, _pkt, _outputFile);
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };  // Creo archivo MPEG real con secuencia fin de codigo
    fwrite(endcode, 1, sizeof(endcode), _outputFile);
}
