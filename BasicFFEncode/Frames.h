#pragma once
#include "Enums.h"
extern "C"
{
#include <libavformat/avformat.h>
}

namespace BasicFFEncode
{
    using namespace System;

    public ref class BasicVideoFrame
    {
    internal:
        AVFrame* pFrame;

    public:
        BasicVideoFrame(int width, int height, BasicPixelFormat pixelFormat);
        ~BasicVideoFrame();
        Byte* GetBuffer(int plane);
        Int32 GetStride(int plane);
    };

    public ref class BasicAudioFrame
    {
    internal:
        AVFrame* pFrame;

    public:
        BasicAudioFrame(Int32 sampleCount, BasicSampleFormat sampleFormat, BasicChannelLayout channelLayout);
        ~BasicAudioFrame();
        Byte* GetBuffer(Int32 plane);
        Int32 GetStride(Int32 plane);
        property Int32 SampleCount { Int32 get() { return pFrame->nb_samples; }}
    };

}
