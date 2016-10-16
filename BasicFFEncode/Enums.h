#pragma once
extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/channel_layout.h>
}

namespace BasicFFEncode
{
    public enum class BasicSampleFormat
    {
        U8 = AV_SAMPLE_FMT_U8,          ///< unsigned 8 bits
        S16 = AV_SAMPLE_FMT_S16,         ///< signed 16 bits
        S32 = AV_SAMPLE_FMT_S32,         ///< signed 32 bits
        S64 = AV_SAMPLE_FMT_S64,         ///< signed 64 bits
        FLT = AV_SAMPLE_FMT_FLT,         ///< float
        DBL = AV_SAMPLE_FMT_DBL,         ///< double

        U8P = AV_SAMPLE_FMT_U8P,         ///< unsigned 8 bits, planar
        S16P = AV_SAMPLE_FMT_S16P,        ///< signed 16 bits, planar
        S32P = AV_SAMPLE_FMT_S32P,        ///< signed 32 bits, planar
        S64P = AV_SAMPLE_FMT_S64P,        ///< signed 64 bits, planar
        FLTP = AV_SAMPLE_FMT_FLTP,        ///< float, planar
        DBLP = AV_SAMPLE_FMT_DBLP,        ///< double, planar
    };

    public enum class BasicPixelFormat
    {
        YUV420P = AV_PIX_FMT_YUV420P,   ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
        YUYV422 = AV_PIX_FMT_YUYV422,   ///< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
        RGB24 = AV_PIX_FMT_RGB24,     ///< packed RGB 8:8:8, 24bpp, RGBRGB...
        BGR24 = AV_PIX_FMT_BGR24,     ///< packed RGB 8:8:8, 24bpp, BGRBGR...
        YUV422P = AV_PIX_FMT_YUV422P,   ///< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
        YUV444P = AV_PIX_FMT_YUV444P,   ///< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples)
        YUV410P = AV_PIX_FMT_YUV410P,   ///< planar YUV 4:1:0,  9bpp, (1 Cr & Cb sample per 4x4 Y samples)
        YUV411P = AV_PIX_FMT_YUV411P,   ///< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples)
        GRAY8 = AV_PIX_FMT_GRAY8,     ///<        Y        ,  8bpp
        MONOWHITE = AV_PIX_FMT_MONOWHITE, ///<        Y        ,  1bpp, 0 is white, 1 is black, in each byte pixels are ordered from the msb to the lsb
        MONOBLACK = AV_PIX_FMT_MONOBLACK, ///<        Y        ,  1bpp, 0 is black, 1 is white, in each byte pixels are ordered from the msb to the lsb
        PAL8 = AV_PIX_FMT_PAL8,      ///< 8 bits with AV_PIX_FMT_RGB32 palette
        YUVJ420P = AV_PIX_FMT_YUVJ420P,  ///< planar YUV 4:2:0, 12bpp, full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV420P and setting color_range
        YUVJ422P = AV_PIX_FMT_YUVJ422P,  ///< planar YUV 4:2:2, 16bpp, full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV422P and setting color_range
        YUVJ444P = AV_PIX_FMT_YUVJ444P,  ///< planar YUV 4:4:4, 24bpp, full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV444P and setting color_range

        UYVY422 = AV_PIX_FMT_UYVY422,   ///< packed YUV 4:2:2, 16bpp, Cb Y0 Cr Y1
        UYYVYY411 = AV_PIX_FMT_UYYVYY411, ///< packed YUV 4:1:1, 12bpp, Cb Y0 Y1 Cr Y2 Y3
        BGR8 = AV_PIX_FMT_BGR8,      ///< packed RGB 3:3:2,  8bpp, (msb)2B 3G 3R(lsb)
        BGR4 = AV_PIX_FMT_BGR4,      ///< packed RGB 1:2:1 bitstream,  4bpp, (msb)1B 2G 1R(lsb), a byte contains two pixels, the first pixel in the byte is the one composed by the 4 msb bits
        BGR4_BYTE = AV_PIX_FMT_BGR4_BYTE, ///< packed RGB 1:2:1,  8bpp, (msb)1B 2G 1R(lsb)
        RGB8 = AV_PIX_FMT_RGB8,      ///< packed RGB 3:3:2,  8bpp, (msb)2R 3G 3B(lsb)
        RGB4 = AV_PIX_FMT_RGB4,      ///< packed RGB 1:2:1 bitstream,  4bpp, (msb)1R 2G 1B(lsb), a byte contains two pixels, the first pixel in the byte is the one composed by the 4 msb bits
        RGB4_BYTE = AV_PIX_FMT_RGB4_BYTE, ///< packed RGB 1:2:1,  8bpp, (msb)1R 2G 1B(lsb)
        NV12 = AV_PIX_FMT_NV12,      ///< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V)
        NV21 = AV_PIX_FMT_NV21,      ///< as above, but U and V bytes are swapped

        ARGB = AV_PIX_FMT_ARGB,      ///< packed ARGB 8:8:8:8, 32bpp, ARGBARGB...
        RGBA = AV_PIX_FMT_RGBA,      ///< packed RGBA 8:8:8:8, 32bpp, RGBARGBA...
        ABGR = AV_PIX_FMT_ABGR,      ///< packed ABGR 8:8:8:8, 32bpp, ABGRABGR...
        BGRA = AV_PIX_FMT_BGRA,      ///< packed BGRA 8:8:8:8, 32bpp, BGRABGRA...

        GRAY16BE = AV_PIX_FMT_GRAY16BE,  ///<        Y        , 16bpp, big-endian
        GRAY16LE = AV_PIX_FMT_GRAY16LE,  ///<        Y        , 16bpp, little-endian
        YUV440P = AV_PIX_FMT_YUV440P,   ///< planar YUV 4:4:0 (1 Cr & Cb sample per 1x2 Y samples)
        YUVJ440P = AV_PIX_FMT_YUVJ440P,  ///< planar YUV 4:4:0 full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV440P and setting color_range
        YUVA420P = AV_PIX_FMT_YUVA420P,  ///< planar YUV 4:2:0, 20bpp, (1 Cr & Cb sample per 2x2 Y & A samples)

        RGB48BE = AV_PIX_FMT_RGB48BE,   ///< packed RGB 16:16:16, 48bpp, 16R, 16G, 16B, the 2-byte value for each R/G/B component is stored as big-endian
        RGB48LE = AV_PIX_FMT_RGB48LE,   ///< packed RGB 16:16:16, 48bpp, 16R, 16G, 16B, the 2-byte value for each R/G/B component is stored as little-endian

        RGB565BE = AV_PIX_FMT_RGB565BE,  ///< packed RGB 5:6:5, 16bpp, (msb)   5R 6G 5B(lsb), big-endian
        RGB565LE = AV_PIX_FMT_RGB565LE,  ///< packed RGB 5:6:5, 16bpp, (msb)   5R 6G 5B(lsb), little-endian
        RGB555BE = AV_PIX_FMT_RGB555BE,  ///< packed RGB 5:5:5, 16bpp, (msb)1X 5R 5G 5B(lsb), big-endian   , X=unused/undefined
        RGB555LE = AV_PIX_FMT_RGB555LE,  ///< packed RGB 5:5:5, 16bpp, (msb)1X 5R 5G 5B(lsb), little-endian, X=unused/undefined

        BGR565BE = AV_PIX_FMT_BGR565BE,  ///< packed BGR 5:6:5, 16bpp, (msb)   5B 6G 5R(lsb), big-endian
        BGR565LE = AV_PIX_FMT_BGR565LE,  ///< packed BGR 5:6:5, 16bpp, (msb)   5B 6G 5R(lsb), little-endian
        BGR555BE = AV_PIX_FMT_BGR555BE,  ///< packed BGR 5:5:5, 16bpp, (msb)1X 5B 5G 5R(lsb), big-endian   , X=unused/undefined
        BGR555LE = AV_PIX_FMT_BGR555LE,  ///< packed BGR 5:5:5, 16bpp, (msb)1X 5B 5G 5R(lsb), little-endian, X=unused/undefined

        YUV420P16LE = AV_PIX_FMT_YUV420P16LE,  ///< planar YUV 4:2:0, 24bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
        YUV420P16BE = AV_PIX_FMT_YUV420P16BE,  ///< planar YUV 4:2:0, 24bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
        YUV422P16LE = AV_PIX_FMT_YUV422P16LE,  ///< planar YUV 4:2:2, 32bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
        YUV422P16BE = AV_PIX_FMT_YUV422P16BE,  ///< planar YUV 4:2:2, 32bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
        YUV444P16LE = AV_PIX_FMT_YUV444P16LE,  ///< planar YUV 4:4:4, 48bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
        YUV444P16BE = AV_PIX_FMT_YUV444P16BE,  ///< planar YUV 4:4:4, 48bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian

        RGB444LE = AV_PIX_FMT_RGB444LE,  ///< packed RGB 4:4:4, 16bpp, (msb)4X 4R 4G 4B(lsb), little-endian, X=unused/undefined
        RGB444BE = AV_PIX_FMT_RGB444BE,  ///< packed RGB 4:4:4, 16bpp, (msb)4X 4R 4G 4B(lsb), big-endian,    X=unused/undefined
        BGR444LE = AV_PIX_FMT_BGR444LE,  ///< packed BGR 4:4:4, 16bpp, (msb)4X 4B 4G 4R(lsb), little-endian, X=unused/undefined
        BGR444BE = AV_PIX_FMT_BGR444BE,  ///< packed BGR 4:4:4, 16bpp, (msb)4X 4B 4G 4R(lsb), big-endian,    X=unused/undefined
        YA8 = AV_PIX_FMT_YA8,       ///< 8 bits gray, 8 bits alpha

        Y400A = AV_PIX_FMT_Y400A, ///< alias for AV_PIX_FMT_YA8
        GRAY8A = AV_PIX_FMT_GRAY8A, ///< alias for AV_PIX_FMT_YA8

        BGR48BE = AV_PIX_FMT_BGR48BE,   ///< packed RGB 16:16:16, 48bpp, 16B, 16G, 16R, the 2-byte value for each R/G/B component is stored as big-endian
        BGR48LE = AV_PIX_FMT_BGR48LE,   ///< packed RGB 16:16:16, 48bpp, 16B, 16G, 16R, the 2-byte value for each R/G/B component is stored as little-endian

        /**
        * The following 12 formats have the disadvantage of needing 1 format for each bit depth.
        * Notice that each 9/10 bits sample is stored in 16 bits with extra padding.
        * If you want to support multiple bit depths, then using AV_PIX_FMT_YUV420P16* with the bpp stored separately is better.
        */
        YUV420P9BE = AV_PIX_FMT_YUV420P9BE, ///< planar YUV 4:2:0, 13.5bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
        YUV420P9LE = AV_PIX_FMT_YUV420P9LE, ///< planar YUV 4:2:0, 13.5bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
        YUV420P10BE = AV_PIX_FMT_YUV420P10BE,///< planar YUV 4:2:0, 15bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
        YUV420P10LE = AV_PIX_FMT_YUV420P10LE,///< planar YUV 4:2:0, 15bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
        YUV422P10BE = AV_PIX_FMT_YUV422P10BE,///< planar YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
        YUV422P10LE = AV_PIX_FMT_YUV422P10LE,///< planar YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
        YUV444P9BE = AV_PIX_FMT_YUV444P9BE, ///< planar YUV 4:4:4, 27bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
        YUV444P9LE = AV_PIX_FMT_YUV444P9LE, ///< planar YUV 4:4:4, 27bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
        YUV444P10BE = AV_PIX_FMT_YUV444P10BE,///< planar YUV 4:4:4, 30bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
        YUV444P10LE = AV_PIX_FMT_YUV444P10LE,///< planar YUV 4:4:4, 30bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
        YUV422P9BE = AV_PIX_FMT_YUV422P9BE, ///< planar YUV 4:2:2, 18bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
        YUV422P9LE = AV_PIX_FMT_YUV422P9LE, ///< planar YUV 4:2:2, 18bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
        VDA_VLD = AV_PIX_FMT_VDA_VLD,    ///< hardware decoding through VDA
        GBRP = AV_PIX_FMT_GBRP,      ///< planar GBR 4:4:4 24bpp
        GBR24P = AV_PIX_FMT_GBR24P, // alias for #AV_PIX_FMT_GBRP
        GBRP9BE = AV_PIX_FMT_GBRP9BE,   ///< planar GBR 4:4:4 27bpp, big-endian
        GBRP9LE = AV_PIX_FMT_GBRP9LE,   ///< planar GBR 4:4:4 27bpp, little-endian
        GBRP10BE = AV_PIX_FMT_GBRP10BE,  ///< planar GBR 4:4:4 30bpp, big-endian
        GBRP10LE = AV_PIX_FMT_GBRP10LE,  ///< planar GBR 4:4:4 30bpp, little-endian
        GBRP16BE = AV_PIX_FMT_GBRP16BE,  ///< planar GBR 4:4:4 48bpp, big-endian
        GBRP16LE = AV_PIX_FMT_GBRP16LE,  ///< planar GBR 4:4:4 48bpp, little-endian
        YUVA422P = AV_PIX_FMT_YUVA422P,  ///< planar YUV 4:2:2 24bpp, (1 Cr & Cb sample per 2x1 Y & A samples)
        YUVA444P = AV_PIX_FMT_YUVA444P,  ///< planar YUV 4:4:4 32bpp, (1 Cr & Cb sample per 1x1 Y & A samples)
        YUVA420P9BE = AV_PIX_FMT_YUVA420P9BE,  ///< planar YUV 4:2:0 22.5bpp, (1 Cr & Cb sample per 2x2 Y & A samples), big-endian
        YUVA420P9LE = AV_PIX_FMT_YUVA420P9LE,  ///< planar YUV 4:2:0 22.5bpp, (1 Cr & Cb sample per 2x2 Y & A samples), little-endian
        YUVA422P9BE = AV_PIX_FMT_YUVA422P9BE,  ///< planar YUV 4:2:2 27bpp, (1 Cr & Cb sample per 2x1 Y & A samples), big-endian
        YUVA422P9LE = AV_PIX_FMT_YUVA422P9LE,  ///< planar YUV 4:2:2 27bpp, (1 Cr & Cb sample per 2x1 Y & A samples), little-endian
        YUVA444P9BE = AV_PIX_FMT_YUVA444P9BE,  ///< planar YUV 4:4:4 36bpp, (1 Cr & Cb sample per 1x1 Y & A samples), big-endian
        YUVA444P9LE = AV_PIX_FMT_YUVA444P9LE,  ///< planar YUV 4:4:4 36bpp, (1 Cr & Cb sample per 1x1 Y & A samples), little-endian
        YUVA420P10BE = AV_PIX_FMT_YUVA420P10BE, ///< planar YUV 4:2:0 25bpp, (1 Cr & Cb sample per 2x2 Y & A samples, big-endian)
        YUVA420P10LE = AV_PIX_FMT_YUVA420P10LE, ///< planar YUV 4:2:0 25bpp, (1 Cr & Cb sample per 2x2 Y & A samples, little-endian)
        YUVA422P10BE = AV_PIX_FMT_YUVA422P10BE, ///< planar YUV 4:2:2 30bpp, (1 Cr & Cb sample per 2x1 Y & A samples, big-endian)
        YUVA422P10LE = AV_PIX_FMT_YUVA422P10LE, ///< planar YUV 4:2:2 30bpp, (1 Cr & Cb sample per 2x1 Y & A samples, little-endian)
        YUVA444P10BE = AV_PIX_FMT_YUVA444P10BE, ///< planar YUV 4:4:4 40bpp, (1 Cr & Cb sample per 1x1 Y & A samples, big-endian)
        YUVA444P10LE = AV_PIX_FMT_YUVA444P10LE, ///< planar YUV 4:4:4 40bpp, (1 Cr & Cb sample per 1x1 Y & A samples, little-endian)
        YUVA420P16BE = AV_PIX_FMT_YUVA420P16BE, ///< planar YUV 4:2:0 40bpp, (1 Cr & Cb sample per 2x2 Y & A samples, big-endian)
        YUVA420P16LE = AV_PIX_FMT_YUVA420P16LE, ///< planar YUV 4:2:0 40bpp, (1 Cr & Cb sample per 2x2 Y & A samples, little-endian)
        YUVA422P16BE = AV_PIX_FMT_YUVA422P16BE, ///< planar YUV 4:2:2 48bpp, (1 Cr & Cb sample per 2x1 Y & A samples, big-endian)
        YUVA422P16LE = AV_PIX_FMT_YUVA422P16LE, ///< planar YUV 4:2:2 48bpp, (1 Cr & Cb sample per 2x1 Y & A samples, little-endian)
        YUVA444P16BE = AV_PIX_FMT_YUVA444P16BE, ///< planar YUV 4:4:4 64bpp, (1 Cr & Cb sample per 1x1 Y & A samples, big-endian)
        YUVA444P16LE = AV_PIX_FMT_YUVA444P16LE, ///< planar YUV 4:4:4 64bpp, (1 Cr & Cb sample per 1x1 Y & A samples, little-endian)

        XYZ12LE = AV_PIX_FMT_XYZ12LE,      ///< packed XYZ 4:4:4, 36 bpp, (msb) 12X, 12Y, 12Z (lsb), the 2-byte value for each X/Y/Z is stored as little-endian, the 4 lower bits are set to 0
        XYZ12BE = AV_PIX_FMT_XYZ12BE,      ///< packed XYZ 4:4:4, 36 bpp, (msb) 12X, 12Y, 12Z (lsb), the 2-byte value for each X/Y/Z is stored as big-endian, the 4 lower bits are set to 0
        NV16 = AV_PIX_FMT_NV16,         ///< interleaved chroma YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
        NV20LE = AV_PIX_FMT_NV20LE,       ///< interleaved chroma YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
        NV20BE = AV_PIX_FMT_NV20BE,       ///< interleaved chroma YUV 4:2:2, 20bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian

        RGBA64BE = AV_PIX_FMT_RGBA64BE,     ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
        RGBA64LE = AV_PIX_FMT_RGBA64LE,     ///< packed RGBA 16:16:16:16, 64bpp, 16R, 16G, 16B, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian
        BGRA64BE = AV_PIX_FMT_BGRA64BE,     ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as big-endian
        BGRA64LE = AV_PIX_FMT_BGRA64LE,     ///< packed RGBA 16:16:16:16, 64bpp, 16B, 16G, 16R, 16A, the 2-byte value for each R/G/B/A component is stored as little-endian

        YVYU422 = AV_PIX_FMT_YVYU422,   ///< packed YUV 4:2:2, 16bpp, Y0 Cr Y1 Cb

        VDA = AV_PIX_FMT_VDA,          ///< HW acceleration through VDA, data[3] contains a CVPixelBufferRef

        YA16BE = AV_PIX_FMT_YA16BE,       ///< 16 bits gray, 16 bits alpha (big-endian)
        YA16LE = AV_PIX_FMT_YA16LE,       ///< 16 bits gray, 16 bits alpha (little-endian)

        GBRAP = AV_PIX_FMT_GBRAP,        ///< planar GBRA 4:4:4:4 32bpp
        GBRAP16BE = AV_PIX_FMT_GBRAP16BE,    ///< planar GBRA 4:4:4:4 64bpp, big-endian
        GBRAP16LE = AV_PIX_FMT_GBRAP16LE,    ///< planar GBRA 4:4:4:4 64bpp, little-endian

        zRGB = AV_PIX_FMT_0RGB,        ///< packed RGB 8:8:8, 32bpp, XRGBXRGB...   X=unused/undefined
        RGBz = AV_PIX_FMT_RGB0,        ///< packed RGB 8:8:8, 32bpp, RGBXRGBX...   X=unused/undefined
        zBGR = AV_PIX_FMT_0BGR,        ///< packed BGR 8:8:8, 32bpp, XBGRXBGR...   X=unused/undefined
        BGRz = AV_PIX_FMT_BGR0,        ///< packed BGR 8:8:8, 32bpp, BGRXBGRX...   X=unused/undefined

        YUV420P12BE = AV_PIX_FMT_YUV420P12BE, ///< planar YUV 4:2:0,18bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
        YUV420P12LE = AV_PIX_FMT_YUV420P12LE, ///< planar YUV 4:2:0,18bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
        YUV420P14BE = AV_PIX_FMT_YUV420P14BE, ///< planar YUV 4:2:0,21bpp, (1 Cr & Cb sample per 2x2 Y samples), big-endian
        YUV420P14LE = AV_PIX_FMT_YUV420P14LE, ///< planar YUV 4:2:0,21bpp, (1 Cr & Cb sample per 2x2 Y samples), little-endian
        YUV422P12BE = AV_PIX_FMT_YUV422P12BE, ///< planar YUV 4:2:2,24bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
        YUV422P12LE = AV_PIX_FMT_YUV422P12LE, ///< planar YUV 4:2:2,24bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
        YUV422P14BE = AV_PIX_FMT_YUV422P14BE, ///< planar YUV 4:2:2,28bpp, (1 Cr & Cb sample per 2x1 Y samples), big-endian
        YUV422P14LE = AV_PIX_FMT_YUV422P14LE, ///< planar YUV 4:2:2,28bpp, (1 Cr & Cb sample per 2x1 Y samples), little-endian
        YUV444P12BE = AV_PIX_FMT_YUV444P12BE, ///< planar YUV 4:4:4,36bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
        YUV444P12LE = AV_PIX_FMT_YUV444P12LE, ///< planar YUV 4:4:4,36bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
        YUV444P14BE = AV_PIX_FMT_YUV444P14BE, ///< planar YUV 4:4:4,42bpp, (1 Cr & Cb sample per 1x1 Y samples), big-endian
        YUV444P14LE = AV_PIX_FMT_YUV444P14LE, ///< planar YUV 4:4:4,42bpp, (1 Cr & Cb sample per 1x1 Y samples), little-endian
        GBRP12BE = AV_PIX_FMT_GBRP12BE,    ///< planar GBR 4:4:4 36bpp, big-endian
        GBRP12LE = AV_PIX_FMT_GBRP12LE,    ///< planar GBR 4:4:4 36bpp, little-endian
        GBRP14BE = AV_PIX_FMT_GBRP14BE,    ///< planar GBR 4:4:4 42bpp, big-endian
        GBRP14LE = AV_PIX_FMT_GBRP14LE,    ///< planar GBR 4:4:4 42bpp, little-endian
        YUVJ411P = AV_PIX_FMT_YUVJ411P,    ///< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples) full scale (JPEG), deprecated in favor of AV_PIX_FMT_YUV411P and setting color_range

        BAYER_BGGR8 = AV_PIX_FMT_BAYER_BGGR8,    ///< bayer, BGBG..(odd line), GRGR..(even line), 8-bit samples */
        BAYER_RGGB8 = AV_PIX_FMT_BAYER_RGGB8,    ///< bayer, RGRG..(odd line), GBGB..(even line), 8-bit samples */
        BAYER_GBRG8 = AV_PIX_FMT_BAYER_GBRG8,    ///< bayer, GBGB..(odd line), RGRG..(even line), 8-bit samples */
        BAYER_GRBG8 = AV_PIX_FMT_BAYER_GRBG8,    ///< bayer, GRGR..(odd line), BGBG..(even line), 8-bit samples */
        BAYER_BGGR16LE = AV_PIX_FMT_BAYER_BGGR16LE, ///< bayer, BGBG..(odd line), GRGR..(even line), 16-bit samples, little-endian */
        BAYER_BGGR16BE = AV_PIX_FMT_BAYER_BGGR16BE, ///< bayer, BGBG..(odd line), GRGR..(even line), 16-bit samples, big-endian */
        BAYER_RGGB16LE = AV_PIX_FMT_BAYER_RGGB16LE, ///< bayer, RGRG..(odd line), GBGB..(even line), 16-bit samples, little-endian */
        BAYER_RGGB16BE = AV_PIX_FMT_BAYER_RGGB16BE, ///< bayer, RGRG..(odd line), GBGB..(even line), 16-bit samples, big-endian */
        BAYER_GBRG16LE = AV_PIX_FMT_BAYER_GBRG16LE, ///< bayer, GBGB..(odd line), RGRG..(even line), 16-bit samples, little-endian */
        BAYER_GBRG16BE = AV_PIX_FMT_BAYER_GBRG16BE, ///< bayer, GBGB..(odd line), RGRG..(even line), 16-bit samples, big-endian */
        BAYER_GRBG16LE = AV_PIX_FMT_BAYER_GRBG16LE, ///< bayer, GRGR..(odd line), BGBG..(even line), 16-bit samples, little-endian */
        BAYER_GRBG16BE = AV_PIX_FMT_BAYER_GRBG16BE, ///< bayer, GRGR..(odd line), BGBG..(even line), 16-bit samples, big-endian */

        YUV440P10LE = AV_PIX_FMT_YUV440P10LE, ///< planar YUV 4:4:0,20bpp, (1 Cr & Cb sample per 1x2 Y samples), little-endian
        YUV440P10BE = AV_PIX_FMT_YUV440P10BE, ///< planar YUV 4:4:0,20bpp, (1 Cr & Cb sample per 1x2 Y samples), big-endian
        YUV440P12LE = AV_PIX_FMT_YUV440P12LE, ///< planar YUV 4:4:0,24bpp, (1 Cr & Cb sample per 1x2 Y samples), little-endian
        YUV440P12BE = AV_PIX_FMT_YUV440P12BE, ///< planar YUV 4:4:0,24bpp, (1 Cr & Cb sample per 1x2 Y samples), big-endian
        AYUV64LE = AV_PIX_FMT_AYUV64LE,    ///< packed AYUV 4:4:4,64bpp (1 Cr & Cb sample per 1x1 Y & A samples), little-endian
        AYUV64BE = AV_PIX_FMT_AYUV64BE,    ///< packed AYUV 4:4:4,64bpp (1 Cr & Cb sample per 1x1 Y & A samples), big-endian

        P010LE = AV_PIX_FMT_P010LE, ///< like NV12, with 10bpp per component, data in the high bits, zeros in the low bits, little-endian
        P010BE = AV_PIX_FMT_P010BE, ///< like NV12, with 10bpp per component, data in the high bits, zeros in the low bits, big-endian

        GBRAP12BE = AV_PIX_FMT_GBRAP12BE,  ///< planar GBR 4:4:4:4 48bpp, big-endian
        GBRAP12LE = AV_PIX_FMT_GBRAP12LE,  ///< planar GBR 4:4:4:4 48bpp, little-endian

        GBRAP10BE = AV_PIX_FMT_GBRAP10BE,  ///< planar GBR 4:4:4:4 40bpp, big-endian
        GBRAP10LE = AV_PIX_FMT_GBRAP10LE,  ///< planar GBR 4:4:4:4 40bpp, little-endian
    };

    public enum class BasicAudioCodecId
    {
        PCM_S16LE = AV_CODEC_ID_PCM_S16LE,
        PCM_S16BE = AV_CODEC_ID_PCM_S16BE,
        PCM_U16LE = AV_CODEC_ID_PCM_U16LE,
        PCM_U16BE = AV_CODEC_ID_PCM_U16BE,
        PCM_S8 = AV_CODEC_ID_PCM_S8,
        PCM_U8 = AV_CODEC_ID_PCM_U8,
        PCM_MULAW = AV_CODEC_ID_PCM_MULAW,
        PCM_ALAW = AV_CODEC_ID_PCM_ALAW,
        PCM_S32LE = AV_CODEC_ID_PCM_S32LE,
        PCM_S32BE = AV_CODEC_ID_PCM_S32BE,
        PCM_U32LE = AV_CODEC_ID_PCM_U32LE,
        PCM_U32BE = AV_CODEC_ID_PCM_U32BE,
        PCM_S24LE = AV_CODEC_ID_PCM_S24LE,
        PCM_S24BE = AV_CODEC_ID_PCM_S24BE,
        PCM_U24LE = AV_CODEC_ID_PCM_U24LE,
        PCM_U24BE = AV_CODEC_ID_PCM_U24BE,
        PCM_S24DAUD = AV_CODEC_ID_PCM_S24DAUD,
        PCM_ZORK = AV_CODEC_ID_PCM_ZORK,
        PCM_S16LE_PLANAR = AV_CODEC_ID_PCM_S16LE_PLANAR,
        PCM_DVD = AV_CODEC_ID_PCM_DVD,
        PCM_F32BE = AV_CODEC_ID_PCM_F32BE,
        PCM_F32LE = AV_CODEC_ID_PCM_F32LE,
        PCM_F64BE = AV_CODEC_ID_PCM_F64BE,
        PCM_F64LE = AV_CODEC_ID_PCM_F64LE,
        PCM_BLURAY = AV_CODEC_ID_PCM_BLURAY,
        PCM_LXF = AV_CODEC_ID_PCM_LXF,
        S302M = AV_CODEC_ID_S302M,
        PCM_S8_PLANAR = AV_CODEC_ID_PCM_S8_PLANAR,
        PCM_S24LE_PLANAR = AV_CODEC_ID_PCM_S24LE_PLANAR,
        PCM_S32LE_PLANAR = AV_CODEC_ID_PCM_S32LE_PLANAR,
        PCM_S16BE_PLANAR = AV_CODEC_ID_PCM_S16BE_PLANAR,

        PCM_S64LE = AV_CODEC_ID_PCM_S64LE,
        PCM_S64BE = AV_CODEC_ID_PCM_S64BE,

        /* various ADPCM codecs */
        ADPCM_IMA_QT = AV_CODEC_ID_ADPCM_IMA_QT,
        ADPCM_IMA_WAV = AV_CODEC_ID_ADPCM_IMA_WAV,
        ADPCM_IMA_DK3 = AV_CODEC_ID_ADPCM_IMA_DK3,
        ADPCM_IMA_DK4 = AV_CODEC_ID_ADPCM_IMA_DK4,
        ADPCM_IMA_WS = AV_CODEC_ID_ADPCM_IMA_WS,
        ADPCM_IMA_SMJPEG = AV_CODEC_ID_ADPCM_IMA_SMJPEG,
        ADPCM_MS = AV_CODEC_ID_ADPCM_MS,
        ADPCM_4XM = AV_CODEC_ID_ADPCM_4XM,
        ADPCM_XA = AV_CODEC_ID_ADPCM_XA,
        ADPCM_ADX = AV_CODEC_ID_ADPCM_ADX,
        ADPCM_EA = AV_CODEC_ID_ADPCM_EA,
        ADPCM_G726 = AV_CODEC_ID_ADPCM_G726,
        ADPCM_CT = AV_CODEC_ID_ADPCM_CT,
        ADPCM_SWF = AV_CODEC_ID_ADPCM_SWF,
        ADPCM_YAMAHA = AV_CODEC_ID_ADPCM_YAMAHA,
        ADPCM_SBPRO_4 = AV_CODEC_ID_ADPCM_SBPRO_4,
        ADPCM_SBPRO_3 = AV_CODEC_ID_ADPCM_SBPRO_3,
        ADPCM_SBPRO_2 = AV_CODEC_ID_ADPCM_SBPRO_2,
        ADPCM_THP = AV_CODEC_ID_ADPCM_THP,
        ADPCM_IMA_AMV = AV_CODEC_ID_ADPCM_IMA_AMV,
        ADPCM_EA_R1 = AV_CODEC_ID_ADPCM_EA_R1,
        ADPCM_EA_R3 = AV_CODEC_ID_ADPCM_EA_R3,
        ADPCM_EA_R2 = AV_CODEC_ID_ADPCM_EA_R2,
        ADPCM_IMA_EA_SEAD = AV_CODEC_ID_ADPCM_IMA_EA_SEAD,
        ADPCM_IMA_EA_EACS = AV_CODEC_ID_ADPCM_IMA_EA_EACS,
        ADPCM_EA_XAS = AV_CODEC_ID_ADPCM_EA_XAS,
        ADPCM_EA_MAXIS_XA = AV_CODEC_ID_ADPCM_EA_MAXIS_XA,
        ADPCM_IMA_ISS = AV_CODEC_ID_ADPCM_IMA_ISS,
        ADPCM_G722 = AV_CODEC_ID_ADPCM_G722,
        ADPCM_IMA_APC = AV_CODEC_ID_ADPCM_IMA_APC,
        ADPCM_VIMA = AV_CODEC_ID_ADPCM_VIMA,
#if FF_API_VIMA_DECODER
        VIMA = AV_CODEC_ID_VIMA,
#endif

        ADPCM_AFC = AV_CODEC_ID_ADPCM_AFC,
        ADPCM_IMA_OKI = AV_CODEC_ID_ADPCM_IMA_OKI,
        ADPCM_DTK = AV_CODEC_ID_ADPCM_DTK,
        ADPCM_IMA_RAD = AV_CODEC_ID_ADPCM_IMA_RAD,
        ADPCM_G726LE = AV_CODEC_ID_ADPCM_G726LE,
        ADPCM_THP_LE = AV_CODEC_ID_ADPCM_THP_LE,
        ADPCM_PSX = AV_CODEC_ID_ADPCM_PSX,
        ADPCM_AICA = AV_CODEC_ID_ADPCM_AICA,
        ADPCM_IMA_DAT4 = AV_CODEC_ID_ADPCM_IMA_DAT4,
        ADPCM_MTAF = AV_CODEC_ID_ADPCM_MTAF,

        /* AMR */
        AMR_NB = AV_CODEC_ID_AMR_NB,
        AMR_WB = AV_CODEC_ID_AMR_WB,

        /* RealAudio codecs*/
        RA_144 = AV_CODEC_ID_RA_144,
        RA_288 = AV_CODEC_ID_RA_288,

        /* various DPCM codecs */
        ROQ_DPCM = AV_CODEC_ID_ROQ_DPCM,
        INTERPLAY_DPCM = AV_CODEC_ID_INTERPLAY_DPCM,
        XAN_DPCM = AV_CODEC_ID_XAN_DPCM,
        SOL_DPCM = AV_CODEC_ID_SOL_DPCM,

        SDX2_DPCM = AV_CODEC_ID_SDX2_DPCM,

        /* audio codecs */
        MP2 = AV_CODEC_ID_MP2,
        MP3 = AV_CODEC_ID_MP3, ///< preferred ID for decoding MPEG audio layer 1, 2 or 3
        AAC = AV_CODEC_ID_AAC,
        AC3 = AV_CODEC_ID_AC3,
        DTS = AV_CODEC_ID_DTS,
        VORBIS = AV_CODEC_ID_VORBIS,
        DVAUDIO = AV_CODEC_ID_DVAUDIO,
        WMAV1 = AV_CODEC_ID_WMAV1,
        WMAV2 = AV_CODEC_ID_WMAV2,
        MACE3 = AV_CODEC_ID_MACE3,
        MACE6 = AV_CODEC_ID_MACE6,
        VMDAUDIO = AV_CODEC_ID_VMDAUDIO,
        FLAC = AV_CODEC_ID_FLAC,
        MP3ADU = AV_CODEC_ID_MP3ADU,
        MP3ON4 = AV_CODEC_ID_MP3ON4,
        SHORTEN = AV_CODEC_ID_SHORTEN,
        ALAC = AV_CODEC_ID_ALAC,
        WESTWOOD_SND1 = AV_CODEC_ID_WESTWOOD_SND1,
        GSM = AV_CODEC_ID_GSM, ///< as in Berlin toast format
        QDM2 = AV_CODEC_ID_QDM2,
        COOK = AV_CODEC_ID_COOK,
        TRUESPEECH = AV_CODEC_ID_TRUESPEECH,
        TTA = AV_CODEC_ID_TTA,
        SMACKAUDIO = AV_CODEC_ID_SMACKAUDIO,
        QCELP = AV_CODEC_ID_QCELP,
        WAVPACK = AV_CODEC_ID_WAVPACK,
        DSICINAUDIO = AV_CODEC_ID_DSICINAUDIO,
        IMC = AV_CODEC_ID_IMC,
        MUSEPACK7 = AV_CODEC_ID_MUSEPACK7,
        MLP = AV_CODEC_ID_MLP,
        GSM_MS = AV_CODEC_ID_GSM_MS, /* as found in WAV */
        ATRAC3 = AV_CODEC_ID_ATRAC3,
#if FF_API_VOXWARE
        VOXWARE = AV_CODEC_ID_VOXWARE,
#endif
        APE = AV_CODEC_ID_APE,
        NELLYMOSER = AV_CODEC_ID_NELLYMOSER,
        MUSEPACK8 = AV_CODEC_ID_MUSEPACK8,
        SPEEX = AV_CODEC_ID_SPEEX,
        WMAVOICE = AV_CODEC_ID_WMAVOICE,
        WMAPRO = AV_CODEC_ID_WMAPRO,
        WMALOSSLESS = AV_CODEC_ID_WMALOSSLESS,
        ATRAC3P = AV_CODEC_ID_ATRAC3P,
        EAC3 = AV_CODEC_ID_EAC3,
        SIPR = AV_CODEC_ID_SIPR,
        MP1 = AV_CODEC_ID_MP1,
        TWINVQ = AV_CODEC_ID_TWINVQ,
        TRUEHD = AV_CODEC_ID_TRUEHD,
        MP4ALS = AV_CODEC_ID_MP4ALS,
        ATRAC1 = AV_CODEC_ID_ATRAC1,
        BINKAUDIO_RDFT = AV_CODEC_ID_BINKAUDIO_RDFT,
        BINKAUDIO_DCT = AV_CODEC_ID_BINKAUDIO_DCT,
        AAC_LATM = AV_CODEC_ID_AAC_LATM,
        QDMC = AV_CODEC_ID_QDMC,
        CELT = AV_CODEC_ID_CELT,
        G723_1 = AV_CODEC_ID_G723_1,
        G729 = AV_CODEC_ID_G729,
        _8SVX_EXP = AV_CODEC_ID_8SVX_EXP,
        _8SVX_FIB = AV_CODEC_ID_8SVX_FIB,
        BMV_AUDIO = AV_CODEC_ID_BMV_AUDIO,
        RALF = AV_CODEC_ID_RALF,
        IAC = AV_CODEC_ID_IAC,
        ILBC = AV_CODEC_ID_ILBC,
        OPUS = AV_CODEC_ID_OPUS,
        COMFORT_NOISE = AV_CODEC_ID_COMFORT_NOISE,
        TAK = AV_CODEC_ID_TAK,
        METASOUND = AV_CODEC_ID_METASOUND,
        PAF_AUDIO = AV_CODEC_ID_PAF_AUDIO,
        ON2AVC = AV_CODEC_ID_ON2AVC,
        DSS_SP = AV_CODEC_ID_DSS_SP,

        FFWAVESYNTH = AV_CODEC_ID_FFWAVESYNTH,
        SONIC = AV_CODEC_ID_SONIC,
        SONIC_LS = AV_CODEC_ID_SONIC_LS,
        EVRC = AV_CODEC_ID_EVRC,
        SMV = AV_CODEC_ID_SMV,
        DSD_LSBF = AV_CODEC_ID_DSD_LSBF,
        DSD_MSBF = AV_CODEC_ID_DSD_MSBF,
        DSD_LSBF_PLANAR = AV_CODEC_ID_DSD_LSBF_PLANAR,
        DSD_MSBF_PLANAR = AV_CODEC_ID_DSD_MSBF_PLANAR,
        _4GV = AV_CODEC_ID_4GV,
        INTERPLAY_ACM = AV_CODEC_ID_INTERPLAY_ACM,
        XMA1 = AV_CODEC_ID_XMA1,
        XMA2 = AV_CODEC_ID_XMA2,
        DST = AV_CODEC_ID_DST,
    };

    public enum class BasicVideoCodecId
    {
        MPEG1VIDEO = AV_CODEC_ID_MPEG1VIDEO,
        MPEG2VIDEO = AV_CODEC_ID_MPEG2VIDEO, ///< preferred ID for MPEG-1/2 video decoding
#if FF_API_XVMC
        MPEG2VIDEO_XVMC = AV_CODEC_ID_MPEG2VIDEO_XVMC,
#endif /* FF_API_XVMC */
        H261 = AV_CODEC_ID_H261,
        H263 = AV_CODEC_ID_H263,
        RV10 = AV_CODEC_ID_RV10,
        RV20 = AV_CODEC_ID_RV20,
        MJPEG = AV_CODEC_ID_MJPEG,
        MJPEGB = AV_CODEC_ID_MJPEGB,
        LJPEG = AV_CODEC_ID_LJPEG,
        SP5X = AV_CODEC_ID_SP5X,
        JPEGLS = AV_CODEC_ID_JPEGLS,
        MPEG4 = AV_CODEC_ID_MPEG4,
        RAWVIDEO = AV_CODEC_ID_RAWVIDEO,
        MSMPEG4V1 = AV_CODEC_ID_MSMPEG4V1,
        MSMPEG4V2 = AV_CODEC_ID_MSMPEG4V2,
        MSMPEG4V3 = AV_CODEC_ID_MSMPEG4V3,
        WMV1 = AV_CODEC_ID_WMV1,
        WMV2 = AV_CODEC_ID_WMV2,
        H263P = AV_CODEC_ID_H263P,
        H263I = AV_CODEC_ID_H263I,
        FLV1 = AV_CODEC_ID_FLV1,
        SVQ1 = AV_CODEC_ID_SVQ1,
        SVQ3 = AV_CODEC_ID_SVQ3,
        DVVIDEO = AV_CODEC_ID_DVVIDEO,
        HUFFYUV = AV_CODEC_ID_HUFFYUV,
        CYUV = AV_CODEC_ID_CYUV,
        H264 = AV_CODEC_ID_H264,
        INDEO3 = AV_CODEC_ID_INDEO3,
        VP3 = AV_CODEC_ID_VP3,
        THEORA = AV_CODEC_ID_THEORA,
        ASV1 = AV_CODEC_ID_ASV1,
        ASV2 = AV_CODEC_ID_ASV2,
        FFV1 = AV_CODEC_ID_FFV1,
        _4XM = AV_CODEC_ID_4XM,
        VCR1 = AV_CODEC_ID_VCR1,
        CLJR = AV_CODEC_ID_CLJR,
        MDEC = AV_CODEC_ID_MDEC,
        ROQ = AV_CODEC_ID_ROQ,
        INTERPLAY_VIDEO = AV_CODEC_ID_INTERPLAY_VIDEO,
        XAN_WC3 = AV_CODEC_ID_XAN_WC3,
        XAN_WC4 = AV_CODEC_ID_XAN_WC4,
        RPZA = AV_CODEC_ID_RPZA,
        CINEPAK = AV_CODEC_ID_CINEPAK,
        WS_VQA = AV_CODEC_ID_WS_VQA,
        MSRLE = AV_CODEC_ID_MSRLE,
        MSVIDEO1 = AV_CODEC_ID_MSVIDEO1,
        IDCIN = AV_CODEC_ID_IDCIN,
        _8BPS = AV_CODEC_ID_8BPS,
        SMC = AV_CODEC_ID_SMC,
        FLIC = AV_CODEC_ID_FLIC,
        TRUEMOTION1 = AV_CODEC_ID_TRUEMOTION1,
        VMDVIDEO = AV_CODEC_ID_VMDVIDEO,
        MSZH = AV_CODEC_ID_MSZH,
        ZLIB = AV_CODEC_ID_ZLIB,
        QTRLE = AV_CODEC_ID_QTRLE,
        TSCC = AV_CODEC_ID_TSCC,
        ULTI = AV_CODEC_ID_ULTI,
        QDRAW = AV_CODEC_ID_QDRAW,
        VIXL = AV_CODEC_ID_VIXL,
        QPEG = AV_CODEC_ID_QPEG,
        PNG = AV_CODEC_ID_PNG,
        PPM = AV_CODEC_ID_PPM,
        PBM = AV_CODEC_ID_PBM,
        PGM = AV_CODEC_ID_PGM,
        PGMYUV = AV_CODEC_ID_PGMYUV,
        PAM = AV_CODEC_ID_PAM,
        FFVHUFF = AV_CODEC_ID_FFVHUFF,
        RV30 = AV_CODEC_ID_RV30,
        RV40 = AV_CODEC_ID_RV40,
        VC1 = AV_CODEC_ID_VC1,
        WMV3 = AV_CODEC_ID_WMV3,
        LOCO = AV_CODEC_ID_LOCO,
        WNV1 = AV_CODEC_ID_WNV1,
        AASC = AV_CODEC_ID_AASC,
        INDEO2 = AV_CODEC_ID_INDEO2,
        FRAPS = AV_CODEC_ID_FRAPS,
        TRUEMOTION2 = AV_CODEC_ID_TRUEMOTION2,
        BMP = AV_CODEC_ID_BMP,
        CSCD = AV_CODEC_ID_CSCD,
        MMVIDEO = AV_CODEC_ID_MMVIDEO,
        ZMBV = AV_CODEC_ID_ZMBV,
        AVS = AV_CODEC_ID_AVS,
        SMACKVIDEO = AV_CODEC_ID_SMACKVIDEO,
        NUV = AV_CODEC_ID_NUV,
        KMVC = AV_CODEC_ID_KMVC,
        FLASHSV = AV_CODEC_ID_FLASHSV,
        CAVS = AV_CODEC_ID_CAVS,
        JPEG2000 = AV_CODEC_ID_JPEG2000,
        VMNC = AV_CODEC_ID_VMNC,
        VP5 = AV_CODEC_ID_VP5,
        VP6 = AV_CODEC_ID_VP6,
        VP6F = AV_CODEC_ID_VP6F,
        TARGA = AV_CODEC_ID_TARGA,
        DSICINVIDEO = AV_CODEC_ID_DSICINVIDEO,
        TIERTEXSEQVIDEO = AV_CODEC_ID_TIERTEXSEQVIDEO,
        TIFF = AV_CODEC_ID_TIFF,
        GIF = AV_CODEC_ID_GIF,
        DXA = AV_CODEC_ID_DXA,
        DNXHD = AV_CODEC_ID_DNXHD,
        THP = AV_CODEC_ID_THP,
        SGI = AV_CODEC_ID_SGI,
        C93 = AV_CODEC_ID_C93,
        BETHSOFTVID = AV_CODEC_ID_BETHSOFTVID,
        PTX = AV_CODEC_ID_PTX,
        TXD = AV_CODEC_ID_TXD,
        VP6A = AV_CODEC_ID_VP6A,
        AMV = AV_CODEC_ID_AMV,
        VB = AV_CODEC_ID_VB,
        PCX = AV_CODEC_ID_PCX,
        SUNRAST = AV_CODEC_ID_SUNRAST,
        INDEO4 = AV_CODEC_ID_INDEO4,
        INDEO5 = AV_CODEC_ID_INDEO5,
        MIMIC = AV_CODEC_ID_MIMIC,
        RL2 = AV_CODEC_ID_RL2,
        ESCAPE124 = AV_CODEC_ID_ESCAPE124,
        DIRAC = AV_CODEC_ID_DIRAC,
        BFI = AV_CODEC_ID_BFI,
        CMV = AV_CODEC_ID_CMV,
        MOTIONPIXELS = AV_CODEC_ID_MOTIONPIXELS,
        TGV = AV_CODEC_ID_TGV,
        TGQ = AV_CODEC_ID_TGQ,
        TQI = AV_CODEC_ID_TQI,
        AURA = AV_CODEC_ID_AURA,
        AURA2 = AV_CODEC_ID_AURA2,
        V210X = AV_CODEC_ID_V210X,
        TMV = AV_CODEC_ID_TMV,
        V210 = AV_CODEC_ID_V210,
        DPX = AV_CODEC_ID_DPX,
        MAD = AV_CODEC_ID_MAD,
        FRWU = AV_CODEC_ID_FRWU,
        FLASHSV2 = AV_CODEC_ID_FLASHSV2,
        CDGRAPHICS = AV_CODEC_ID_CDGRAPHICS,
        R210 = AV_CODEC_ID_R210,
        ANM = AV_CODEC_ID_ANM,
        BINKVIDEO = AV_CODEC_ID_BINKVIDEO,
        IFF_ILBM = AV_CODEC_ID_IFF_ILBM,
#define AV_CODEC_ID_IFF_BYTERUN1 AV_CODEC_ID_IFF_ILBM
        KGV1 = AV_CODEC_ID_KGV1,
        YOP = AV_CODEC_ID_YOP,
        VP8 = AV_CODEC_ID_VP8,
        PICTOR = AV_CODEC_ID_PICTOR,
        ANSI = AV_CODEC_ID_ANSI,
        A64_MULTI = AV_CODEC_ID_A64_MULTI,
        A64_MULTI5 = AV_CODEC_ID_A64_MULTI5,
        R10K = AV_CODEC_ID_R10K,
        MXPEG = AV_CODEC_ID_MXPEG,
        LAGARITH = AV_CODEC_ID_LAGARITH,
        PRORES = AV_CODEC_ID_PRORES,
        JV = AV_CODEC_ID_JV,
        DFA = AV_CODEC_ID_DFA,
        WMV3IMAGE = AV_CODEC_ID_WMV3IMAGE,
        VC1IMAGE = AV_CODEC_ID_VC1IMAGE,
        UTVIDEO = AV_CODEC_ID_UTVIDEO,
        BMV_VIDEO = AV_CODEC_ID_BMV_VIDEO,
        VBLE = AV_CODEC_ID_VBLE,
        DXTORY = AV_CODEC_ID_DXTORY,
        V410 = AV_CODEC_ID_V410,
        XWD = AV_CODEC_ID_XWD,
        CDXL = AV_CODEC_ID_CDXL,
        XBM = AV_CODEC_ID_XBM,
        ZEROCODEC = AV_CODEC_ID_ZEROCODEC,
        MSS1 = AV_CODEC_ID_MSS1,
        MSA1 = AV_CODEC_ID_MSA1,
        TSCC2 = AV_CODEC_ID_TSCC2,
        MTS2 = AV_CODEC_ID_MTS2,
        CLLC = AV_CODEC_ID_CLLC,
        MSS2 = AV_CODEC_ID_MSS2,
        VP9 = AV_CODEC_ID_VP9,
        AIC = AV_CODEC_ID_AIC,
        ESCAPE130 = AV_CODEC_ID_ESCAPE130,
        G2M = AV_CODEC_ID_G2M,
        WEBP = AV_CODEC_ID_WEBP,
        HNM4_VIDEO = AV_CODEC_ID_HNM4_VIDEO,
        HEVC = AV_CODEC_ID_HEVC,
#define AV_CODEC_ID_H265 AV_CODEC_ID_HEVC
        FIC = AV_CODEC_ID_FIC,
        ALIAS_PIX = AV_CODEC_ID_ALIAS_PIX,
        BRENDER_PIX = AV_CODEC_ID_BRENDER_PIX,
        PAF_VIDEO = AV_CODEC_ID_PAF_VIDEO,
        EXR = AV_CODEC_ID_EXR,
        VP7 = AV_CODEC_ID_VP7,
        SANM = AV_CODEC_ID_SANM,
        SGIRLE = AV_CODEC_ID_SGIRLE,
        MVC1 = AV_CODEC_ID_MVC1,
        MVC2 = AV_CODEC_ID_MVC2,
        HQX = AV_CODEC_ID_HQX,
        TDSC = AV_CODEC_ID_TDSC,
        HQ_HQA = AV_CODEC_ID_HQ_HQA,
        HAP = AV_CODEC_ID_HAP,
        DDS = AV_CODEC_ID_DDS,
        DXV = AV_CODEC_ID_DXV,
        SCREENPRESSO = AV_CODEC_ID_SCREENPRESSO,
        RSCC = AV_CODEC_ID_RSCC,

        Y41P = AV_CODEC_ID_Y41P,
        AVRP = AV_CODEC_ID_AVRP,
        _012V = AV_CODEC_ID_012V,
        AVUI = AV_CODEC_ID_AVUI,
        AYUV = AV_CODEC_ID_AYUV,
        TARGA_Y216 = AV_CODEC_ID_TARGA_Y216,
        V308 = AV_CODEC_ID_V308,
        V408 = AV_CODEC_ID_V408,
        YUV4 = AV_CODEC_ID_YUV4,
        AVRN = AV_CODEC_ID_AVRN,
        CPIA = AV_CODEC_ID_CPIA,
        XFACE = AV_CODEC_ID_XFACE,
        SNOW = AV_CODEC_ID_SNOW,
        SMVJPEG = AV_CODEC_ID_SMVJPEG,
        APNG = AV_CODEC_ID_APNG,
        DAALA = AV_CODEC_ID_DAALA,
        CFHD = AV_CODEC_ID_CFHD,
        TRUEMOTION2RT = AV_CODEC_ID_TRUEMOTION2RT,
        M101 = AV_CODEC_ID_M101,
        MAGICYUV = AV_CODEC_ID_MAGICYUV,
        SHEERVIDEO = AV_CODEC_ID_SHEERVIDEO,
        YLC = AV_CODEC_ID_YLC,
    };

    [System::FlagsAttribute]
    public enum class BasicChannelLayout : System::UInt64
    {
        FrontLeft = AV_CH_FRONT_LEFT,
        FrontRight = AV_CH_FRONT_RIGHT,
        FrontCenter = AV_CH_FRONT_CENTER,
        LowFrequency = AV_CH_LOW_FREQUENCY,
        BackLeft = AV_CH_BACK_LEFT,
        BackRight = AV_CH_BACK_RIGHT,
        FrontLeftOfCenter = AV_CH_FRONT_LEFT_OF_CENTER,
        FrontRightOfCenter = AV_CH_FRONT_RIGHT_OF_CENTER,
        BackCenter = AV_CH_BACK_CENTER,
        SideLeft = AV_CH_SIDE_LEFT,
        SideRight = AV_CH_SIDE_RIGHT,
        TopCenter = AV_CH_TOP_CENTER,
        TopFrontLeft = AV_CH_TOP_FRONT_LEFT,
        TopFrontCenter = AV_CH_TOP_FRONT_CENTER,
        TopFrontRight = AV_CH_TOP_FRONT_RIGHT,
        TopBackLeft = AV_CH_TOP_BACK_LEFT,
        TopBackCenter = AV_CH_TOP_BACK_CENTER,
        TopBackRight = AV_CH_TOP_BACK_RIGHT,
        StereoLeft = AV_CH_STEREO_LEFT,
        StereoRight = AV_CH_STEREO_RIGHT,
        WideLeft = AV_CH_WIDE_LEFT,
        WideRight = AV_CH_WIDE_RIGHT,
        SurroundDirectLeft = AV_CH_SURROUND_DIRECT_LEFT,
        SurroundDirectRight = AV_CH_SURROUND_DIRECT_RIGHT,
        LowFrequency2 = AV_CH_LOW_FREQUENCY_2
    };
}