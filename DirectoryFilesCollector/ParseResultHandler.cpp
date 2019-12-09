#include "pch.h"
#include "ParseResultHandler.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>

ParseResultHandler::ParseResultHandler(std::wstring outputFileName)
    : m_outputFileName(std::move(outputFileName))
{
}

void ParseResultHandler::handleResult(std::vector<std::wstring> files)
{
    std::sort(files.begin(), files.end());

    std::wofstream out(m_outputFileName);
    if (out.is_open())
    {
        const std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>());
        out.imbue(utf8_locale);

        for (const auto& file : files)
        {
            out << file << std::endl;
        }
    }
    else
    {
        std::wcerr << L"Can't open file: '" << m_outputFileName << L"'" << std::endl;
    }
}
