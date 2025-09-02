#ifndef __RD_COROUTINE_H__
#define __RD_COROUTINE_H__

#include <Arduino.h>
#include <map>
#include <functional>

class RD_Coroutine
{
public:
    struct Func_Arg
    {
        std::function<void(void *)> function;
        void * argument;
    };

private:
    std::multimap<uint32_t, Func_Arg> asyncFunctionQ_;
    
public:
    std::multimap<uint32_t, Func_Arg>::iterator Add(std::function<void(void *)> func, void *userData, uint32_t delay_ms = 0);
    bool Remove(std::multimap<uint32_t, Func_Arg>::iterator targetIt);

    bool Exist(std::multimap<uint32_t, Func_Arg>::iterator targetIt);

    void loop();
};

extern RD_Coroutine rd_coroutine;

#endif  // __COROUTINE_H__