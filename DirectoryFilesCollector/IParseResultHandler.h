#pragma once

#include <vector>
#include <string>

class IParseResultHandler
{
public:
    virtual ~IParseResultHandler() = default;
    virtual void handleResult(std::vector<std::wstring> files) = 0;
};