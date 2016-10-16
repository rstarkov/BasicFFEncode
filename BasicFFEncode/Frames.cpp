#include "Stdafx.h"
extern "C"
{
#include <libavformat/avformat.h>
}
#pragma comment(lib, "avcodec.lib")
#using "Enums.obj"



namespace BasicFFEncode
{
    using namespace System;

    public ref class BasicVideoFrame
    {
    private:
        AVFrame* _pFrame;

    internal:
        property AVFrame* pFrame { AVFrame* get() {
            return _pFrame;
        }
        void set(AVFrame* f) {
            _pFrame = f;
        }
        }

    public:
        BasicVideoFrame(int width, int height, BasicPixelFormat pixelFormat)
        {
            pFrame = av_frame_alloc();
            if (!pFrame)
                throw gcnew Exception("Could not allocate video frame");

            pFrame->format = static_cast<AVPixelFormat>(pixelFormat);
            pFrame->width = width;
            pFrame->height = height;

            if (av_frame_get_buffer(pFrame, 32) < 0)
            {
                pin_ptr<AVFrame*> pFrame_pinned = &_pFrame;
                av_frame_free(pFrame_pinned);
                throw gcnew Exception("Could not allocate video frame buffer");
            }
        }

        ~BasicVideoFrame()
        {
            pin_ptr<AVFrame*> pFrame_pinned = &_pFrame;
            av_frame_free(pFrame_pinned);
        }

        Byte* GetBuffer(int plane)
        {
            if (plane < 0 || plane >= AV_NUM_DATA_POINTERS)
                throw gcnew ArgumentException("Plane index is out of range");
            return pFrame->data[plane];
        }

        Int32 GetStride(int plane)
        {
            if (plane < 0 || plane >= AV_NUM_DATA_POINTERS)
                throw gcnew ArgumentException("Plane index is out of range");
            return pFrame->linesize[plane];
        }
    };



    public ref class BasicAudioFrame
    {
    internal:
        AVFrame* pFrame;

    public:
        BasicAudioFrame(int sampleCount, BasicSampleFormat sampleFormat, BasicChannelLayout channelLayout)
        {
            pFrame = av_frame_alloc();
            if (!pFrame)
                throw gcnew Exception("Could not allocate audio frame");

            pFrame->format = static_cast<AVSampleFormat>(sampleFormat);
            pFrame->channel_layout = static_cast<uint64_t>(channelLayout);
            pFrame->nb_samples = sampleCount;

            if (av_frame_get_buffer(pFrame, 0) < 0)
            {
                pin_ptr<AVFrame*> pFrame_pinned = &pFrame;
                av_frame_free(pFrame_pinned);
                throw gcnew Exception("Could not allocate audio frame buffer");
            }
        }

        ~BasicAudioFrame()
        {
            pin_ptr<AVFrame*> pFrame_pinned = &pFrame;
            av_frame_free(pFrame_pinned);
        }

        Byte* GetBuffer(int plane)
        {
            if (plane < 0 || plane >= AV_NUM_DATA_POINTERS)
                throw gcnew ArgumentException("Plane index is out of range");
            return pFrame->data[plane];
        }

        Int32 GetStride(int plane)
        {
            if (plane < 0 || plane >= AV_NUM_DATA_POINTERS)
                throw gcnew ArgumentException("Plane index is out of range");
            return pFrame->linesize[plane];
        }

        property Int32 SampleCount { Int32 get() { return pFrame->nb_samples; }}
    };

}







