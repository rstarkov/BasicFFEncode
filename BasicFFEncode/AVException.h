#pragma once

using namespace System;

ref class AVException : public Exception
{
internal:
	AVException();
	AVException(int av_error);
	AVException(String^ message, int av_error);
	AVException(String^ message);
	AVException(String^ message, Exception^ inner);
};

