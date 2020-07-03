#include "stdafx.h"
#include "AVException.h"
extern "C"
{
#include <libavutil/error.h>
}

String^ ErrorCodeToString(int av_error)
{
	char* errBuf = new char[AV_ERROR_MAX_STRING_SIZE];
	int result = av_strerror(av_error, errBuf, AV_ERROR_MAX_STRING_SIZE);

	String^ returnValue = nullptr;

	if (result == 0)
		returnValue = gcnew String(errBuf);

	delete[] errBuf;
	return returnValue;
}

String^ ErrorMessageAndCodeToString(String^ message, int av_error)
{
	String^ av_message = ErrorCodeToString(av_error);
	return av_message == nullptr
		? message
		: message + " (code " + av_error.ToString() + ": " + av_message + ")";
}

AVException::AVException() : Exception()
{
}
AVException::AVException(String^ message, int av_error) : Exception(ErrorMessageAndCodeToString(message, av_error))
{
}
AVException::AVException(int av_error) : Exception(ErrorCodeToString(av_error))
{
}
AVException::AVException(String^ message) : Exception(message)
{
}
AVException::AVException(String^ message, Exception^ inner) : Exception(message, inner)
{
}