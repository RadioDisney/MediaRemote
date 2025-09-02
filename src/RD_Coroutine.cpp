#include "RD_Coroutine.h"
#include "SerialDefine.h"

RD_Coroutine rd_coroutine;

std::multimap<uint32_t, RD_Coroutine::Func_Arg>::iterator RD_Coroutine::Add(std::function<void(void *)> func, void *userData, uint32_t delay_ms)
{
    return asyncFunctionQ_.insert(std::pair<uint32_t, Func_Arg>(millis() + delay_ms, Func_Arg{func, userData}));
}

bool RD_Coroutine::Exist(std::multimap<uint32_t, Func_Arg>::iterator targetIt)
{
    return asyncFunctionQ_.find (targetIt->first) != asyncFunctionQ_.end();
}

bool RD_Coroutine::Remove(std::multimap<uint32_t, Func_Arg>::iterator targetIt)
{
    if (targetIt == std::multimap<uint32_t, Func_Arg>::iterator{})
    {
        return false;
    }

    std::multimap<uint32_t, Func_Arg>::iterator foundKeyIt = asyncFunctionQ_.find(targetIt->first);
    if (foundKeyIt != asyncFunctionQ_.end())
    {
        if (foundKeyIt == targetIt)
        {
            asyncFunctionQ_.erase(targetIt);
            return true;
        }
        else
        {
            std::pair<std::multimap<uint32_t, Func_Arg>::iterator, std::multimap<uint32_t, Func_Arg>::iterator> range =
                asyncFunctionQ_.equal_range(foundKeyIt->first);
            for (std::multimap<uint32_t, Func_Arg>::iterator it = range.first; it != range.second; ++it)
            {
                if (it == targetIt)
                {
                    asyncFunctionQ_.erase(it);
                    return true;
                }
            }
        }
    }

    return false;
}

void RD_Coroutine::loop()
{
    while (!asyncFunctionQ_.empty())
    {
        auto it = asyncFunctionQ_.begin();
        if (it->first <= millis())
        {
            Func_Arg func_arg = it->second;
            asyncFunctionQ_.erase(it);

            try
            {
                func_arg.function(func_arg.argument);
            }
            catch (...)
            {
                CONSOLE_PRINTF("Legacy coroutine execution failed");
            }
        }
        else
        {
            break;
        }
    }
}