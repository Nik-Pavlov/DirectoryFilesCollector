#include "pch.h"
#include "InputArgumentsParser.h"

#include <iostream>


bool InputArgumentParser::parseInputArguments(int argc, wchar_t* argv[])
{
    if (argc != 3)
    {
        std::wcerr << "Please provide 2 arguments" << std::endl;
        std::wcerr << L"Usage: " << argv[0] << L" PATHIN LOG" << std::endl;
        return false;
    }

    pathIn = argv[1];
    for (auto& ch : pathIn)
    {
        if (ch == '/')
        {
            ch = '\\';
        }
    }
    if (!pathIn.empty() && pathIn.back() != '\\')
    {
        pathIn.push_back('\\');
    }


    log = argv[2];
    for (auto& ch : log)
    {
        if (ch == '/')
        {
            ch = '\\';
        }
    }
    while (!log.empty() && log.back() == '\\')
    {
        log.pop_back();
    }

    return true;
}

const std::wstring& InputArgumentParser::getPathIn() const
{
    return pathIn;
}

const std::wstring& InputArgumentParser::getLog() const
{
    return log;
}
