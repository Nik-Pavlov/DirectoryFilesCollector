#include "pch.h"

#include "DirTreeCrawler.h"
#include "InputArgumentsParser.h"
#include "InterruptionWatcher.h"
#include "ParseResultHandler.h"


int wmain(int argc, wchar_t* argv[])
{
    InputArgumentParser parser;
    if (!parser.parseInputArguments(argc, argv))
    {
        return 1;
    }

    auto resultHandler = std::make_shared<ParseResultHandler>(parser.getLog());

    DirTreeCrawler presenter(parser.getPathIn(), resultHandler);
    presenter.start();

    InterruptionWatcher watcher;
    while (!presenter.isCompleted()) 
    {
        if (watcher.isInterrupted())
        {
            presenter.stop();
            break;
        }
    }

    return 0;
}

