// #pragma once
// #include "Container/String.h"
// #include "Map.h"
// #include Container / Array.h "
// #include "Function/FunctionCore.h"
// namespace Matrix
// {
//     class MATRIX_FUNCTION_API VSEnumTrans
//     {
//     public:
//         VSEnumTrans();
//         ~VSEnumTrans();
//         static VSEnumTrans &GetInstance();
//         void Add(const TCHAR *EnumName, const TCHAR *Value);
//         void Get(const TCHAR *EnumName, Container::MArray<Container::MString> &AS);

//     protected:
//         Container::MMap<Container::MString, Container::MArray<Container::MString>> m_EnumSaver;
//     };
// }
// #define ADD_ENUM(EnumName, Value) \
//     VSEnumTrans::GetInstance().Add(_T(#EnumName), _T(#Value));
// #define GET_ENUMARRAY(EnumName, Array) \
//     VSEnumTrans::GetInstance().Get(_T(#EnumName), Array);
