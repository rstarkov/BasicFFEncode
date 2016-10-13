#pragma once
#include "Frames.h"

namespace BasicFFEncode
{
    public ref class BasicEncoderSettings
    {
    public:
        property int VideoWidth;
        property int VideoHeight;
        property BasicPixelFormat PixelFormat;
        property long VideoBitrate;
        property long AudioBitrate;
        property int VideoGopSize;
        property int AudioSampleRate; // may be updated by the BasicEncoder constructor to one of the supported sample rates
        property int VideoTimebaseNum;
        property int VideoTimebaseDen;
        property System::Collections::Generic::Dictionary<System::String^, System::String^>^ Options;

        BasicEncoderSettings()
        {
            VideoWidth = 640;
            VideoHeight = 480;
            PixelFormat = BasicPixelFormat::YUV420P;
            VideoBitrate = 400000;
            AudioBitrate = 64000;
            VideoGopSize = 12;
            AudioSampleRate = 44100;
            VideoTimebaseNum = 1;
            VideoTimebaseDen = 25;
            Options = gcnew System::Collections::Generic::Dictionary<System::String^, System::String^>();
        }
    };
}
