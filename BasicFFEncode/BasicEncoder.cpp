// Parts of this code are derived from the muxing.c example for FFmpeg: https://raw.githubusercontent.com/FFmpeg/FFmpeg/master/doc/examples/muxing.c
#include "stdafx.h"

extern "C"
{
#include <libavutil/avassert.h>
#include <libavutil/channel_layout.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "swresample.lib")

#include "BasicEncoder.h"



class UnmanagedPrivates
{
public:
    const char* pFilename = NULL;
    AVFormatContext* pFormatContext = NULL;
    AVCodec* pVideoCodec = NULL;
    AVCodec* pAudioCodec = NULL;
    AVStream* pVideoStream = NULL;
    AVStream* pAudioStream = NULL;
    AVCodecContext* pVideoContext = NULL;
    AVCodecContext* pAudioContext = NULL;

private:
    StringWrapper swFilename;

public:
    UnmanagedPrivates(String^ filename) : swFilename(filename)
    {
        pFilename = swFilename.StrPtr;
    }

    ~UnmanagedPrivates()
    {
        if (pVideoContext)
            avcodec_free_context(&pVideoContext);
        if (pAudioContext)
            avcodec_free_context(&pAudioContext);
        if (pFormatContext)
            avformat_free_context(pFormatContext); // this also frees pVideoStream/pAudioStream
    }
};



void BasicFFEncode::BasicEncoder::Initialise()
{
    if (_initialised)
        return;
    av_log_set_level(AV_LOG_QUIET);
    av_register_all();
    _initialised = true;
}

void addStream(AVCodecID codecId, AVFormatContext* formatContext, AVCodec** codec, AVStream** stream, AVCodecContext** codecContext)
{
    *codec = avcodec_find_encoder(codecId);
    if (!(*codec))
        throw gcnew Exception("Could not find encoder."); // avcodec_get_name(codecId) for more info

    *codecContext = avcodec_alloc_context3(*codec);
    if (!(*codecContext))
        throw gcnew Exception("Could not create codec context.");

    *stream = avformat_new_stream(formatContext, NULL);
    if (!*stream)
        throw gcnew Exception("Could not create stream.");

    (*stream)->id = formatContext->nb_streams - 1;

    if (formatContext->oformat->flags & AVFMT_GLOBALHEADER)
        (*codecContext)->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
}

void openCodec(AVCodec* codec, AVCodecContext* context, AVStream* stream, AVDictionary* opts)
{
    AVDictionary* optsCopy = NULL;
    av_dict_copy(&optsCopy, opts, 0);
    int result = avcodec_open2(context, codec, &optsCopy);
    av_dict_free(&optsCopy);
    if (result < 0)
        throw gcnew Exception("Could not open codec");
    if (avcodec_parameters_from_context(stream->codecpar, context) < 0)
        throw gcnew Exception("Could not copy parameters from context");
}

BasicFFEncode::BasicEncoder::BasicEncoder(String^ filename, BasicEncoderSettings^ settings)
{
    Initialise();
    _filename = filename;
    _priv = new UnmanagedPrivates(filename);

    AVDictionary* opts = NULL;
    if (settings->Options)
        for each (auto kvp in settings->Options)
        {
            StringWrapper swKey(kvp.Key);
            StringWrapper swValue(kvp.Value);
            av_dict_set(&opts, swKey.StrPtr, swValue.StrPtr, 0); // this duplicates the strings, so they can be deallocated immediately
        }

    try
    {
        // Allocate a media context, while attempting to deduce the format from the file name, defaulting to MPEG if automatic deduction failed
        avformat_alloc_output_context2(&_priv->pFormatContext, NULL, NULL, _priv->pFilename);
        if (!_priv->pFormatContext)
            avformat_alloc_output_context2(&_priv->pFormatContext, NULL, "mpeg", _priv->pFilename);
        if (!_priv->pFormatContext)
            throw gcnew Exception("Unable to allocate output context.");
        AVCodecID videoCodecId = _priv->pFormatContext->oformat->video_codec;
        AVCodecID audioCodecId = _priv->pFormatContext->oformat->audio_codec;

        if (_priv->pFormatContext->oformat->flags & AVFMT_NOFILE)
            throw gcnew Exception("Output format has AVFMT_NOFILE flag set.");


        // Add the audio and video streams using the default format codecs and initialize the codecs.
        bool hasVideo = videoCodecId != AV_CODEC_ID_NONE;
        if (hasVideo)
            addStream(videoCodecId, _priv->pFormatContext, &_priv->pVideoCodec, &_priv->pVideoStream, &_priv->pVideoContext);

        bool hasAudio = audioCodecId != AV_CODEC_ID_NONE;
        if (hasAudio)
            addStream(audioCodecId, _priv->pFormatContext, &_priv->pAudioCodec, &_priv->pAudioStream, &_priv->pAudioContext);


        if (hasVideo)
        {
            // Configure video encoding
            _priv->pVideoContext->codec_id = videoCodecId;
            settings->Video->CodecId = static_cast<BasicVideoCodecId>(videoCodecId);
            _priv->pVideoContext->bit_rate = settings->Video->Bitrate;
            _priv->pVideoContext->width = settings->Video->Width;
            _priv->pVideoContext->height = settings->Video->Height;
            _priv->pVideoContext->time_base.num = settings->Video->Timebase.Num;
            _priv->pVideoContext->time_base.den = settings->Video->Timebase.Den;
            _priv->pVideoContext->pix_fmt = static_cast<AVPixelFormat>(settings->Video->PixelFormat);
            _priv->pVideoContext->gop_size = settings->Video->GopSize;
            _priv->pVideoContext->sample_aspect_ratio.num = settings->Video->PixelAspectRatio.Num;
            _priv->pVideoContext->sample_aspect_ratio.den = settings->Video->PixelAspectRatio.Den;

            _priv->pVideoStream->time_base = _priv->pVideoContext->time_base;

            // The following settings are from the muxing.c sample and should not be required in general:
            //if (_priv->pVideoContext->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
            //    _priv->pVideoContext->max_b_frames = 2;
            //}
            //if (_priv->pVideoContext->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
            //    _priv->pVideoContext->mb_decision = 2;
            //}

            // Open video codec
            openCodec(_priv->pVideoCodec, _priv->pVideoContext, _priv->pVideoStream, opts);
        }

        if (hasAudio)
        {
            // Configure audio encoding
            settings->Audio->CodecId = static_cast<BasicAudioCodecId>(audioCodecId);
            _priv->pAudioContext->sample_fmt = _priv->pAudioCodec->sample_fmts ? _priv->pAudioCodec->sample_fmts[0] : AV_SAMPLE_FMT_FLTP;
            _priv->pAudioContext->bit_rate = settings->Audio->Bitrate;
            _priv->pAudioContext->sample_rate = settings->Audio->SampleRate;
            if (_priv->pAudioCodec->supported_samplerates) {
                _priv->pAudioContext->sample_rate = _priv->pAudioCodec->supported_samplerates[0];
                for (int i = 0; _priv->pAudioCodec->supported_samplerates[i]; i++)
                    if (_priv->pAudioCodec->supported_samplerates[i] == settings->Audio->SampleRate)
                        _priv->pAudioContext->sample_rate = settings->Audio->SampleRate;
                settings->Audio->SampleRate = _priv->pAudioContext->sample_rate;
            }
            //_priv->pAudioContext->channels = av_get_channel_layout_nb_channels(_priv->pAudioContext->channel_layout); // was in the sample - not needed here?
            _priv->pAudioContext->channel_layout = AV_CH_LAYOUT_STEREO;
            if (_priv->pAudioCodec->channel_layouts) {
                _priv->pAudioContext->channel_layout = _priv->pAudioCodec->channel_layouts[0];
                for (int i = 0; _priv->pAudioCodec->channel_layouts[i]; i++)
                    if (_priv->pAudioCodec->channel_layouts[i] == AV_CH_LAYOUT_STEREO)
                        _priv->pAudioContext->channel_layout = AV_CH_LAYOUT_STEREO;
            }
            _priv->pAudioContext->channels = av_get_channel_layout_nb_channels(_priv->pAudioContext->channel_layout);
            settings->Audio->ChannelLayout = static_cast<BasicChannelLayout>(_priv->pAudioContext->channel_layout);
            settings->Audio->Channels = _priv->pAudioContext->channels;
            _priv->pAudioStream->time_base.num = 1;
            _priv->pAudioStream->time_base.den = _priv->pAudioContext->sample_rate;

            // Open audio codec
            openCodec(_priv->pAudioCodec, _priv->pAudioContext, _priv->pAudioStream, opts);

            settings->Audio->FrameSize = _priv->pAudioContext->codec->capabilities & AV_CODEC_CAP_VARIABLE_FRAME_SIZE ? 0 : _priv->pAudioContext->frame_size;
        }


        // Open the output file
        if (avio_open(&_priv->pFormatContext->pb, _priv->pFilename, AVIO_FLAG_WRITE) < 0)
            throw gcnew Exception("Unable to open the output file.");

        // Write the stream header
        if (avformat_write_header(_priv->pFormatContext, &opts) < 0)
            throw gcnew Exception("Unable to write stream header.");
    }
    catch (Exception^)
    {
        delete _priv;
        throw;
    }
}

void writePendingPackets(AVCodecContext* context, AVStream* stream, AVFormatContext* formatContext)
{
    AVPacket packet = { 0 };
    av_init_packet(&packet);

    int result;
    while ((result = avcodec_receive_packet(context, &packet)) == 0)
    {
        av_packet_rescale_ts(&packet, context->time_base, stream->time_base);
        packet.stream_index = stream->index;
        if (av_interleaved_write_frame(formatContext, &packet) < 0)
            throw gcnew Exception("Could not write frame.");
    }
    if (result != AVERROR(EAGAIN) && result != AVERROR_EOF)
        throw gcnew Exception("Error while receiving encoded packet.");
}

BasicFFEncode::BasicEncoder::~BasicEncoder()
{
    if (_priv->pVideoContext)
    {
        if (avcodec_send_frame(_priv->pVideoContext, NULL) < 0)
            throw gcnew Exception("Could not flush video encoder.");
        writePendingPackets(_priv->pVideoContext, _priv->pVideoStream, _priv->pFormatContext);
    }
    if (_priv->pAudioContext)
    {
        if (avcodec_send_frame(_priv->pAudioContext, NULL) < 0)
            throw gcnew Exception("Could not flush audio encoder.");
        writePendingPackets(_priv->pAudioContext, _priv->pAudioStream, _priv->pFormatContext);
    }

    av_write_trailer(_priv->pFormatContext);
    avio_closep(&_priv->pFormatContext->pb);

    delete _priv;
}

void BasicFFEncode::BasicEncoder::EncodeFrame(BasicVideoFrame^ frame, Int64 presentationTimestamp)
{
    frame->pFrame->pts = presentationTimestamp;
    if (avcodec_send_frame(_priv->pVideoContext, frame->pFrame) < 0)
        throw gcnew Exception("Could not encode video frame.");
    writePendingPackets(_priv->pVideoContext, _priv->pVideoStream, _priv->pFormatContext);
    // The codec may have kept a reference to this frame, making it un-writable. Allocate new buffers in this case to ensure the caller can still write to this frame.
    av_frame_make_writable(frame->pFrame);
}

void BasicFFEncode::BasicEncoder::EncodeFrame(BasicAudioFrame^ frame, Int64 presentationTimestamp)
{
    frame->pFrame->pts = presentationTimestamp;
    if (avcodec_send_frame(_priv->pAudioContext, frame->pFrame) < 0)
        throw gcnew Exception("Could not encode audio frame.");
    writePendingPackets(_priv->pAudioContext, _priv->pAudioStream, _priv->pFormatContext);
    // The codec may have kept a reference to this frame, making it un-writable. Allocate new buffers in this case to ensure the caller can still write to this frame.
    av_frame_make_writable(frame->pFrame);
}

BasicFFEncode::BasicRescaler::BasicRescaler(int srcWidth, int srcHeight, BasicPixelFormat srcFormat, int destWidth, int destHeight, BasicPixelFormat destFormat, BasicRescalerFlags flags)
{
    _pContext = sws_getContext(srcWidth, srcHeight, static_cast<AVPixelFormat>(srcFormat), destWidth, destHeight, static_cast<AVPixelFormat>(destFormat), (int)flags, NULL, NULL, NULL);
    if (!_pContext)
        throw gcnew Exception("Could not create rescaler context.");
}

BasicFFEncode::BasicRescaler::BasicRescaler(BasicVideoFrame^ srcFrameTemplate, BasicVideoFrame^ destFrameTemplate, BasicRescalerFlags flags)
    : BasicRescaler(srcFrameTemplate->Width, srcFrameTemplate->Height, srcFrameTemplate->PixelFormat, destFrameTemplate->Width, destFrameTemplate->Height, destFrameTemplate->PixelFormat, flags)
{
}

BasicFFEncode::BasicRescaler::~BasicRescaler()
{
    sws_freeContext(_pContext);
}

void BasicFFEncode::BasicRescaler::RescaleFrame(BasicVideoFrame^ src, BasicVideoFrame^ dest)
{
    sws_scale(_pContext, (const uint8_t * const *)src->pFrame->data, src->pFrame->linesize, 0, src->Height, dest->pFrame->data, dest->pFrame->linesize);
}
