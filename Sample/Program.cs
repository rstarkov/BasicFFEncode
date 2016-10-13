using BasicFFEncode;

namespace Sample
{
    class Program
    {
        unsafe static void Main(string[] args)
        {
            var filename = args[0];
            var settings = new BasicEncoderSettings();
            settings.VideoWidth = 1920;
            settings.VideoHeight = 1080;
            settings.VideoTimebaseDen = 60;
            settings.VideoBitrate = 10000000;
            using (var frame = new BasicVideoFrame(settings.VideoWidth, settings.VideoHeight, BasicPixelFormat.YUV420P))
            using (var enc = new BasicEncoder(filename, settings))
            {
                byte* bufY = frame.GetBuffer(0);
                byte* bufCb = frame.GetBuffer(1);
                byte* bufCr = frame.GetBuffer(2);
                int strideY = frame.GetStride(0);
                int strideCb = frame.GetStride(1);
                int strideCr = frame.GetStride(2);

                for (int i = 0; i < 5 * settings.VideoTimebaseDen / settings.VideoTimebaseNum; i++)
                {
                    for (int y = 0; y < settings.VideoHeight; y++)
                        for (int x = 0; x < settings.VideoWidth; x++)
                            bufY[y * strideY + x] = (byte) (x + y + i * 3);
                    for (int y = 0; y < settings.VideoHeight / 2; y++)
                    {
                        for (int x = 0; x < settings.VideoWidth / 2; x++)
                        {
                            bufCb[y * strideCb + x] = (byte) (128 + y + i * 2);
                            bufCr[y * strideCr + x] = (byte) (64 + x + i * 5);
                        }
                    }
                    enc.EncodeFrame(frame, i);
                }
            }
        }
    }
}
