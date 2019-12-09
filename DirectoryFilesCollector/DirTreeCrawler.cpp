#include "pch.h"

#include "DirTreeCrawler.h"
#include "IParseResultHandler.h"

#include <iostream>
#include <stack>
#include <windows.h>


DirTreeCrawler::DirTreeCrawler(std::wstring pathIn, std::shared_ptr<IParseResultHandler> resultHandler)
    : m_isCompleted(false)
    , m_isCanceled(false)
    , m_pathIn(std::move(pathIn))
    , m_resultHandler(std::move(resultHandler))
{

}

DirTreeCrawler::~DirTreeCrawler()
{
    stop();
}

void DirTreeCrawler::start()
{
    m_crawlerThread = std::thread(&DirTreeCrawler::scan, this);
}

void DirTreeCrawler::stop()
{
    m_isCanceled = true;
    if (m_crawlerThread.joinable())
    {
        m_crawlerThread.join();
    }
}

bool DirTreeCrawler::isCompleted() const
{
    return m_isCompleted;
}

void DirTreeCrawler::scan()
{
    auto files = listFiles();
    const auto filesNumber = files.size();
    if (m_isCanceled)
    {
        std::cout << "Operation aborted " << filesNumber << std::endl;
    }
    else
    {
        m_resultHandler->handleResult(std::move(files));
        std::cout << "Operation finished " << filesNumber << std::endl;
    }

    m_isCompleted = true;
}


std::vector<std::wstring> DirTreeCrawler::listFiles()
{
    std::vector<std::wstring> files;

    std::stack<std::wstring> foldersToVisit;
    foldersToVisit.push(m_pathIn);

    while (!foldersToVisit.empty())
    {
        auto folder = std::move(foldersToVisit.top());
        foldersToVisit.pop();

        const std::wstring root = folder;
        if (folder.back() != '*') folder.push_back('*');

        WIN32_FIND_DATA file;
        HANDLE hSearch = FindFirstFileW(folder.c_str(), &file);
        if (hSearch == INVALID_HANDLE_VALUE)
        {
            DWORD dwError = GetLastError();
            if (dwError != ERROR_FILE_NOT_FOUND)
            {
                //std::wcout << L"Invalid file handle for filter " << folder << L". Error is " << dwError << std::endl;
            }
            continue;
        }

        do
        {
            if (!wcscmp(file.cFileName, L".") || !wcscmp(file.cFileName, L".."))
            {
                continue;
            }

            if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                foldersToVisit.push((root + file.cFileName) + L'\\');
            }
            else
            {
                files.push_back(file.cFileName);
            }
        } while (FindNextFileW(hSearch, &file) && !m_isCanceled);

        FindClose(hSearch);
    }

    return files;
}

