#pragma once

#include "IParseResultHandler.h"

class ParseResultHandler final : public IParseResultHandler
{
public:
    ParseResultHandler(std::wstring outputFileName);
    void handleResult(std::vector<std::wstring> files) override;

private:
    const std::wstring m_outputFileName;
};