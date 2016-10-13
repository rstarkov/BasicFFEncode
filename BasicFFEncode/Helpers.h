#pragma once

class StringWrapper
{
private:
    System::IntPtr hGlobalPtr;
public:
    const char* StrPtr;
    StringWrapper(System::String^ str);
    ~StringWrapper();
};
