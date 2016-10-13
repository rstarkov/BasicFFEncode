#include "Stdafx.h"
#include "Frames.h"

#pragma comment(lib, "avcodec.lib")

using namespace System;

BasicFFEncode::BasicVideoFrame::BasicVideoFrame(int width, int height, BasicPixelFormat pixelFormat)
{
    pFrame = av_frame_alloc();
    if (!pFrame)
        throw gcnew Exception("Could not allocate video frame");

    pFrame->format = static_cast<AVPixelFormat>(pixelFormat);
    pFrame->width = width;
    pFrame->height = height;

    if (av_frame_get_buffer(pFrame, 32) < 0)
    {
        pin_ptr<AVFrame*> pFrame_pinned = &pFrame;
        av_frame_free(pFrame_pinned);
        throw gcnew Exception("Could not allocate video frame buffer");
    }
}

BasicFFEncode::BasicVideoFrame::~BasicVideoFrame()
{
    pin_ptr<AVFrame*> pFrame_pinned = &pFrame;
    av_frame_free(pFrame_pinned);
}

Byte* BasicFFEncode::BasicVideoFrame::GetBuffer(int plane)
{
    if (plane < 0 || plane >= AV_NUM_DATA_POINTERS)
        throw gcnew ArgumentException("Plane index is out of range");
    return pFrame->data[plane];
}

Int32 BasicFFEncode::BasicVideoFrame::GetStride(int plane)
{
    if (plane < 0 || plane >= AV_NUM_DATA_POINTERS)
        throw gcnew ArgumentException("Plane index is out of range");
    return pFrame->linesize[plane];
}
