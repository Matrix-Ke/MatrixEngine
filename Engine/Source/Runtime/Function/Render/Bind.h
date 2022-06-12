#pragma once
#include "Object.h"
namespace Matrix
{

    class MATRIX_FUNCTION_API VSResourceIdentifier
    {
    public:
        virtual ~VSResourceIdentifier()
        { /**/
        }

    protected:
        VSResourceIdentifier()
        { /**/
        }
    };
    class MStream;
    class MATRIX_FUNCTION_API VSBind : public MObject
    {

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY;

    public:
        VSBind();
        virtual ~VSBind() = 0;

        virtual VSResourceIdentifier *GetIdentifier();
        unsigned int GetInfoQuantity() const;

        static Container::MArray<VSBind *> ms_BindArray;

    protected:
        friend class VSRenderer;

        void Bind(VSResourceIdentifier *pID);

        struct INFO_TYPE
        {
            INFO_TYPE()
            {
                ID = NULL;
            }
            ~INFO_TYPE()
            {
            }
            VSResourceIdentifier *ID;
        };
        Container::MArray<INFO_TYPE> m_InfoArray;

        VSRenderer *m_pUser;

    public:
        virtual bool LoadResource(VSRenderer *pRender);
        virtual bool ReleaseResource();

        bool IsBindResource() const
        {
            return m_InfoArray.GetNum() > 0;
        }

    protected:
        virtual bool OnLoadResource(VSResourceIdentifier *&pID) = 0;
        virtual bool OnReleaseResource(VSResourceIdentifier *pID);
    };
    DECLARE_Ptr(VSBind);
    VSTYPE_MARCO(VSBind);

}
