#pragma once
#include "FunctionCore.h"
#include "Core/Priority.h"

#include "Container/Array.h"

namespace Matrix
{
    typedef bool (*Function)();
    class VSRtti;
    typedef bool (*FunctionProperty)(VSRtti *);
    class MATRIX_FUNCTION_API EngineInit
    {
    public:
        static void AddInitialPropertyFunction(FunctionProperty Func);
        static void AddTerminalPropertyFunction(Function Func);
        static void AddInitialFunction(Function Func);
        static void AddInitialFunction(Function Func, VSPriority *pPriority); //添加优先级，控制初始化顺序
        static bool Initialize();
        static void AddTerminalFunction(Function Func);
        static void AddTerminalFunction(Function Func, VSPriority *pPriority);
        static bool Terminate();

    private:
        EngineInit();
        ~EngineInit();
        struct Element
        {
        public:
            Element()
            {
                Func = NULL;
                pPriority = NULL;
            }
            ~Element()
            {
                Func = NULL;
                pPriority = NULL;
            }
            Function Func;
            VSPriority *pPriority;
            bool operator>(const Element &e) const
            {
                static VSPriority Pr1;
                static VSPriority Pr2;

                VSPriority *p1 = NULL;
                VSPriority *p2 = NULL;
                if (pPriority)
                    p1 = pPriority;
                else
                    p1 = &Pr1;
                if (e.pPriority)
                    p2 = e.pPriority;
                else
                    p2 = &Pr2;
                return (*p1) > (*p2);
            }
            bool operator<(const Element &e) const
            {
                static VSPriority Pr1;
                static VSPriority Pr2;

                VSPriority *p1 = NULL;
                VSPriority *p2 = NULL;
                if (pPriority)
                    p1 = pPriority;
                else
                    p1 = &Pr1;
                if (e.pPriority)
                    p2 = e.pPriority;
                else
                    p2 = &Pr2;
                return (*p1) > (*p2);
            }
            bool operator==(const Element &e) const
            {
                static VSPriority Pr1;
                static VSPriority Pr2;

                VSPriority *p1 = NULL;
                VSPriority *p2 = NULL;
                if (pPriority)
                    p1 = pPriority;
                else
                    p1 = &Pr1;
                if (e.pPriority)
                    p2 = e.pPriority;
                else
                    p2 = &Pr2;
                return (*p1) == (*p2);
            }
        };
        static Container::MArray<Element> *ms_pInitialArray; //控制各种管理器的初始化顺序
        static Container::MArray<FunctionProperty> *ms_pInitialPropertyArray;
        static Container::MArray<Function> *ms_pTerminalPropertyArray;
        static Container::MArray<Element> *ms_pTerminalArray;
        static unsigned int ms_uiInitialObject;
        static unsigned int ms_uiTerminalObject;

        class PriorityCompare
        {
        public:
            inline bool operator()(Element &e1, Element &e2)
            {
                static VSPriority Pr1;
                static VSPriority Pr2;

                VSPriority *p1 = NULL;
                VSPriority *p2 = NULL;
                if (e1.pPriority)
                    p1 = e1.pPriority;
                else
                    p1 = &Pr1;
                if (e2.pPriority)
                    p2 = e2.pPriority;
                else
                    p2 = &Pr2;
                return (*p1) <= (*p2);
            }
        };
    };
}
