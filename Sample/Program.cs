using System;
using BasicFFEncode;

namespace Sample
{
    class Program
    {
        unsafe static void Main(string[] args)
        {
            ExampleRGB(args[0]);
        }

        unsafe static void ExampleYUV(string filename)
        {
            var settings = new BasicEncoderSettings();
            settings.Video.Width = 1280;
            settings.Video.Height = 720;
            settings.Video.Timebase = new Rational(1, 60);
            settings.Video.Bitrate = 5000000;
            settings.Audio.SampleRate = 44100;
            settings.Audio.SampleFormat = BasicSampleFormat.FLTP;
            using (var enc = new BasicEncoder(filename, settings))
            using (var vFrame = new BasicVideoFrame(settings.Video.Width, settings.Video.Height, BasicPixelFormat.YUV420P))
            using (var aFrame = new BasicAudioFrame(settings.Audio.FrameSize == 0 ? 10000 : settings.Audio.FrameSize, settings.Audio.SampleFormat, settings.Audio.ChannelLayout))
            {
                byte* bufY = vFrame.GetBuffer(0);
                byte* bufCb = vFrame.GetBuffer(1);
                byte* bufCr = vFrame.GetBuffer(2);
                int strideY = vFrame.GetStride(0);
                int strideCb = vFrame.GetStride(1);
                int strideCr = vFrame.GetStride(2);
                float* bufA1 = (float*) aFrame.GetBuffer(0);
                float* bufA2 = (float*) aFrame.GetBuffer(1);

                float t = 0;
                float tInc = (float) (2 * Math.PI * 110.0 / settings.Audio.SampleRate);
                float tInc2 = tInc / settings.Audio.SampleRate;
                int aSamples = 0;

                for (int frameNumber = 0; frameNumber < 5 * settings.Video.Timebase.Den / settings.Video.Timebase.Num; frameNumber++)
                {
                    for (int y = 0; y < settings.Video.Height; y++)
                        for (int x = 0; x < settings.Video.Width; x++)
                            bufY[y * strideY + x] = (byte) (x + y + frameNumber * 3);
                    for (int y = 0; y < settings.Video.Height / 2; y++)
                    {
                        for (int x = 0; x < settings.Video.Width / 2; x++)
                        {
                            bufCb[y * strideCb + x] = (byte) (128 + y + frameNumber * 2);
                            bufCr[y * strideCr + x] = (byte) (64 + x + frameNumber * 5);
                        }
                    }
                    enc.EncodeFrame(vFrame, frameNumber);

                    while (aSamples < frameNumber * settings.Audio.SampleRate * settings.Video.Timebase.Num / settings.Video.Timebase.Den)
                    {
                        for (int k = 0; k < aFrame.SampleCount; k++)
                        {
                            float sample = (float) Math.Sin(t) * 0.5f;
                            bufA1[k] = sample;
                            bufA2[k] = sample;
                            t += tInc;
                            tInc += tInc2;
                        }
                        enc.EncodeFrame(aFrame, aSamples);
                        aSamples += aFrame.SampleCount;
                    }
                }
            }
        }

        unsafe static void ExampleRGB(string filename)
        {
            var settings = new BasicEncoderSettings();
            settings.Video.Width = 640;
            settings.Video.Height = 480;
            settings.Video.Timebase = new Rational(1, 30);
            settings.Video.Bitrate = 2000000;
            settings.Audio.SampleRate = 44100;
            settings.Audio.SampleFormat = BasicSampleFormat.FLTP;
            using (var enc = new BasicEncoder(filename, settings))
            using (var vFrameGen = new BasicVideoFrame(1000, 2000, BasicPixelFormat.GBRP))
            using (var vFrameEnc = new BasicVideoFrame(settings.Video.Width, settings.Video.Height, BasicPixelFormat.YUV420P))
            using (var rescaler = new BasicRescaler(vFrameGen, vFrameEnc, BasicRescalerFlags.Lanczos))
            using (var aFrame = new BasicAudioFrame(settings.Audio.FrameSize == 0 ? 10000 : settings.Audio.FrameSize, settings.Audio.SampleFormat, settings.Audio.ChannelLayout))
            {
                byte* bufR = vFrameGen.GetBuffer(2);
                byte* bufG = vFrameGen.GetBuffer(1);
                byte* bufB = vFrameGen.GetBuffer(0);
                int stride = vFrameGen.GetStride(0); // equal for 1 & 2
                float* bufA1 = (float*) aFrame.GetBuffer(0);
                float* bufA2 = (float*) aFrame.GetBuffer(1);

                float t = 0;
                float tInc = (float) (2 * Math.PI * 110.0 / settings.Audio.SampleRate);
                float tInc2 = tInc / settings.Audio.SampleRate;
                int aSamples = 0;

                for (int frameNumber = 0; frameNumber < 5 * settings.Video.Timebase.Den / settings.Video.Timebase.Num; frameNumber++)
                {
                    for (int y = 0; y < vFrameGen.Height; y++)
                        for (int x = 0; x < vFrameGen.Width; x++)
                        {
                            bufR[y * stride + x] = (byte) (x + y + frameNumber * 3);
                            bufG[y * stride + x] = (byte) (128 + y + frameNumber * 2);
                            bufB[y * stride + x] = (byte) (64 + x + frameNumber * 5);
                        }
                    rescaler.RescaleFrame(vFrameGen, vFrameEnc);
                    enc.EncodeFrame(vFrameEnc, frameNumber);

                    while (aSamples < frameNumber * settings.Audio.SampleRate * settings.Video.Timebase.Num / settings.Video.Timebase.Den)
                    {
                        for (int k = 0; k < aFrame.SampleCount; k++)
                        {
                            float sample = (float) Math.Sin(t) * 0.5f;
                            bufA1[k] = sample;
                            bufA2[k] = sample;
                            t += tInc;
                            tInc += tInc2;
                        }
                        enc.EncodeFrame(aFrame, aSamples);
                        aSamples += aFrame.SampleCount;
                    }
                }
            }
        }

    }
}
