#pragma once

#include <string>

class InputArgumentParser
{
public:
    bool parseInputArguments(int argc, wchar_t* argv[]);
    const std::wstring& getPathIn() const;
    const std::wstring& getLog() const;

private:
    std::wstring pathIn;
    std::wstring log;
};