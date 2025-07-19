#include "Core/Core.h"
#include "Log.h"

void Log::Info(std::string_view message)
{
	std::println("{}",message.data());
}
