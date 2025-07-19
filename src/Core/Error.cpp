#include "Core/Core.h"
#include "Error.h"

Error::Error(std::string_view message)
{
	Log::Info(message);
	throw std::runtime_error(std::format("{}", std::stacktrace::current()));
}
