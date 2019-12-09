#pragma once

#include <atomic>
#include <string>
#include <vector>
#include <thread>
#include <memory>

class IParseResultHandler;


class DirTreeCrawler
{
public:
    DirTreeCrawler(std::wstring pathIn, std::shared_ptr<IParseResultHandler> resultHandler);

    ~DirTreeCrawler();

    void start();

    void stop();

    bool isCompleted() const;

private:

    void scan();

    std::vector<std::wstring> listFiles();

    std::atomic_bool m_isCompleted;
    std::atomic_bool m_isCanceled;
    std::thread m_crawlerThread;
    
    const std::wstring m_pathIn;
    const std::shared_ptr<IParseResultHandler> m_resultHandler;
};