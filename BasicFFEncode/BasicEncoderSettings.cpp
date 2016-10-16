#include "Stdafx.h"

#using "Frames.obj"
#using "Enums.obj"

namespace BasicFFEncode
{
    using namespace System;
    using namespace System::Collections::Generic;

    public value class Rational
    {
    private:
        int _num, _den;
    public:
        property int Num { int get() { return _num; }}
        property int Den { int get() { return _den; }}
        Rational(int num, int den) : _num(num), _den(den) {}
        virtual String^ ToString() override { return String::Format("{0}/{1} ({2})", Num, Den, (Decimal)Den / (Decimal)Num); }
    };

    public ref class BasicVideoEncoderSettings
    {
    public:
        property BasicVideoCodecId CodecId;
        property Rational Timebase;
        property int Width;
        property int Height;
        property BasicPixelFormat PixelFormat;
        property Rational PixelAspectRatio;
        property UInt64 Bitrate;
        property int GopSize;
    };

    public ref class BasicAudioEncoderSettings
    {
    public:
        property BasicAudioCodecId CodecId;
        property UInt64 Bitrate;
        property int SampleRate; // may be updated by the BasicEncoder constructor to one of the supported sample rates
        property int Channels;
        property BasicSampleFormat SampleFormat;
        property int FrameSize;
        property BasicChannelLayout ChannelLayout;
    };

    public ref class BasicEncoderSettings
    {
    public:
        property BasicVideoEncoderSettings^ Video;
        property BasicAudioEncoderSettings^ Audio;
        property Dictionary<String^, String^>^ Options;

        BasicEncoderSettings()
        {
            Video = gcnew BasicVideoEncoderSettings();
            Video->Width = 640;
            Video->Height = 480;
            Video->PixelFormat = BasicPixelFormat::YUV420P;
            Video->Bitrate = 400000;
            Video->GopSize = 12;
            Video->Timebase = Rational(1, 25);
            Video->PixelAspectRatio = Rational(1, 1);

            Audio = gcnew BasicAudioEncoderSettings();
            Audio->Bitrate = 64000;
            Audio->SampleRate = 44100;

            Options = gcnew Dictionary<String^, String^>();
        }
    };
}
