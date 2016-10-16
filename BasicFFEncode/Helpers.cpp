#include "Stdafx.h"
#include "Helpers.h"

using namespace System;
using namespace System::Runtime::InteropServices;

StringWrapper::StringWrapper(String^ str)
{
    hGlobalPtr = Marshal::StringToHGlobalAnsi(str);
    StrPtr = static_cast<char*>(hGlobalPtr.ToPointer());
}

StringWrapper::~StringWrapper()
{
    Marshal::FreeHGlobal(hGlobalPtr);
}
