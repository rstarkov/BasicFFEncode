#pragma once
#include "Helpers.h"
#include "Frames.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

class UnmanagedPrivates;

namespace BasicFFEncode
{
    public ref class BasicEncoder
    {
    private:
        String^ _filename;
        UnmanagedPrivates* _priv;

    private:
        static bool _initialised = false;
        static void Initialise();

    public:
        BasicEncoder(String^ filename, Dictionary<String^, String^>^ options);
        ~BasicEncoder();
        void EncodeFrame(BasicVideoFrame^ frame, Int64 presentationTimestamp);
    };
}
