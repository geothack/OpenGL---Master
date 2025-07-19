#include "Core/Core.h"
#include "Application.h"

int main()
{
    try
    {
        Application app;
    }
    catch (std::exception exception)
    {
        Log::Info(exception.what());
        return -1;
    }
}