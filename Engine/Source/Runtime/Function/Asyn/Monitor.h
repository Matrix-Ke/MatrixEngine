#pragma once
#include "Graphic.h"
#include "Synchronize.h"
#include "Thread.h"
#include "String.h"
#include "Array.h"
#include "Resource.h"
#include "SafeQueue.h"
#include "AnimSet.h"
namespace Matrix
{
    struct FileOperation
    {
        enum Type
        {
            Added,
            Removed,
            Modified
        };
    };
    struct FileChangedArgs
    {
        FileOperation::Type Operation;
        Container::MString FilePath;
        bool operator==(const FileChangedArgs &rhs) const;
    };
    inline bool FileChangedArgs::operator==(const FileChangedArgs &rhs) const
    {
        return (this->Operation == rhs.Operation) &&
               (this->FilePath == rhs.FilePath);
    }
    class MATRIX_FUNCTION_API VSResourceChangedHandler
    {
    public:
        VSResourceChangedHandler()
        {
        }
        virtual ~VSResourceChangedHandler() {}
        // 检测文件类型是否可以处理
        virtual bool CheckFileType(const Container::MString &path) = 0;
        // 处理文件更新事件
        virtual void OnFileChanged(const FileChangedArgs &args) = 0;
    };
    class MATRIX_FUNCTION_API VSAnimChangedHandler : public VSResourceChangedHandler
    {

    public:
        VSAnimChangedHandler()
        {
        }
        virtual ~VSAnimChangedHandler()
        {
        }
        virtual bool CheckFileType(const Container::MString &path)
        {
            return path.GetSubStringIndex(VSAnim::ms_FileSuffix, 1) != -1;
        }
        /// 处理文件更新事件
        virtual void OnFileChanged(const FileChangedArgs &args)
        {
        }
    };
    class VSMonitor;
    class MATRIX_FUNCTION_API VSFileMonitor : public VSThread
    {
    public:
        VSFileMonitor(VSMonitor *pOwner);
        virtual ~VSFileMonitor();

        // 设置监视目录
        void SetDirectory(const Container::MString &s);
        // 取得监视目录
        const Container::MString &GetDirectory() const;

        // 设置是否使用相对路径
        void SetUseRelativePath(bool b);
        // 是否使用相对路径
        bool IsUseRelativePath() const;

    private:
        virtual void Run();
        virtual const TCHAR *GetThreadName();

        void NotifyHandler();

    private:
        static const size_t BufferSize = 4096;
        Container::MString m_directory;
        bool m_isUseRelativePath;
        unsigned char *m_pReadBuffer;
        VSMonitor *m_pOwner;
    };

    //------------------------------------------------------------------------------
    inline const Container::MString &VSFileMonitor::GetDirectory() const
    {
        return m_directory;
    }

    //------------------------------------------------------------------------------
    inline void VSFileMonitor::SetDirectory(const Container::MString &s)
    {

        m_directory = s;
    }

    //------------------------------------------------------------------------------
    inline void VSFileMonitor::SetUseRelativePath(bool b)
    {
        m_isUseRelativePath = b;
    }

    //------------------------------------------------------------------------------
    inline bool VSFileMonitor::IsUseRelativePath() const
    {
        return m_isUseRelativePath;
    }
    class MATRIX_FUNCTION_API VSMonitor
    {
    public:
        VSMonitor()
        {
        }
        virtual ~VSMonitor()
        {
        }

    protected:
        friend class VSFileMonitor;
        virtual void OnFileChanged(const FileChangedArgs &args) = 0;
    };
    class MATRIX_FUNCTION_API VSResourceMonitor : public VSMonitor
    {
    public:
        VSResourceMonitor();
        virtual ~VSResourceMonitor();
        bool Open();
        void Update(double dAppTime);
        void Close();
        inline void RegisterHandler(VSResourceChangedHandler *handler)
        {
            m_handlers.AddElement(handler);
        }

        inline void UnregisterHandler(VSResourceChangedHandler *handler)
        {
            unsigned int index = m_handlers.FindElement(handler);
            m_handlers.Erase(index);
        }
        static VSResourceMonitor *ms_pResourceMonitor;

    protected:
        void OnFileChanged(const FileChangedArgs &args);

    private:
        VSFileMonitor *m_fileMonitor;
        VSSafeQueue<FileChangedArgs> m_changedFiles;
        Container::MArray<VSResourceChangedHandler *> m_handlers;
    };
};
