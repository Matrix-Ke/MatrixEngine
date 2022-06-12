#define DECLARE_INITIAL                    \
 public:                                    \
     static bool RegisterClassToMainFactory();     \
                                            \
 public:                                    \
     static bool CreateClassFactory();      \
     static MObject *NewObject();           \
     static bool InitialProperty(VSRtti *); \
     static bool TerminalProperty(); \
     static bool ms_bRegisterMainFactory;   

/********************************************************************************/
//create classFactory
//
#define IMPLEMENT_INITIAL_BEGIN(classname)                                           \
     static bool gs_bStreamRegistered_##classname = classname::RegisterClassToMainFactory(); \
     bool classname::ms_bRegisterMainFactory = false;                                 \
     bool classname::CreateClassFactory()                                            \
     {                                                                                \
         ms_ClassFactory.AddElement(ms_Type.GetName(), NewObject);                  \
         return 1;                                                                    \
     }                                                                                \
     MObject *classname::NewObject()                                               \
     {                                                                                \
         return MX_NEW classname;                                                     \
     }                                                                                \
     bool classname::RegisterClassToMainFactory()                                            \
     {                                                                                \
         if (!ms_bRegisterMainFactory)                                                \
         {

 /********************************************************************************/
//pRtti->AddProperty(activeProperty)函数并没有执行。通过IMPLEMENT_INITIAL_END(最开始初始化classFactory的方式)
//加了初始化和终止属性表的两个函数 InitialProperty 和TerminalProperty  完成pRtti->AddProperty() 函数的执行
#define IMPLEMENT_INITIAL_END                              \
     EngineInit::AddInitialFunction(CreateClassFactory);       \
     EngineInit::AddInitialPropertyFunction(InitialProperty);   \
     EngineInit::AddTerminalPropertyFunction(TerminalProperty); \
     ms_bRegisterMainFactory = true;                        \
     }                                                      \
     return ms_bRegisterMainFactory;                        \
     }


 /********************************************************************************/
#define DECLARE_INITIAL_ONLY           \
 public:                                \
     static bool RegisterClassToMainFactory(); \
                                        \
 public:                                \
     static bool ms_bRegisterMainFactory;
 /********************************************************************************/
#define IMPLEMENT_INITIAL_ONLY_BEGIN(classname)                                      \
     static bool gs_bStreamRegistered_##classname = classname::RegisterClassToMainFactory(); \
     bool classname::ms_bRegisterMainFactory = false;                                 \
     bool classname::RegisterClassToMainFactory()                                            \
     {                                                                                \
         if (!ms_bRegisterMainFactory)                                                \
         {

 /********************************************************************************/
#define IMPLEMENT_INITIAL_ONLY_END  \
     ms_bRegisterMainFactory = true; \
     }                               \
     return ms_bRegisterMainFactory; \
     }

 /********************************************************************************/
#define DECLARE_INITIAL_NO_CLASS_FACTORY   \
 public:                                    \
     static bool RegisterClassToMainFactory();     \
                                            \
 public:                                    \
     static bool ms_bRegisterMainFactory;   \
     static bool InitialProperty(VSRtti *); \
     static bool TerminalProperty();

//gs_bStreamRegistered_##classname  静态变量的初始化依赖factory函数前，这样就可以完成所有初始化函数的收集
/********************************************************************************/
#define IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(classname)                          \
     static bool gs_bStreamRegistered_##classname = classname::RegisterClassToMainFactory(); \
     bool classname::ms_bRegisterMainFactory = false;                                 \
     bool classname::RegisterClassToMainFactory()                                            \
     {                                                                                \
         if (!ms_bRegisterMainFactory)                                                \
         {

 /********************************************************************************/
#define IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END             \
     EngineInit::AddInitialPropertyFunction(InitialProperty);   \
     EngineInit::AddTerminalPropertyFunction(TerminalProperty); \
     ms_bRegisterMainFactory = true;                        \
     }                                                      \
     return ms_bRegisterMainFactory;                        \
     }
 /********************************************************************************/
#define ADD_INITIAL_FUNCTION(function_name) \
     EngineInit::AddInitialFunction(function_name);
 /********************************************************************************/
#define ADD_INITIAL_FUNCTION_WITH_PRIORITY(function_name) \
     EngineInit::AddInitialFunction(function_name, &ms_Priority);
 /********************************************************************************/
#define ADD_TERMINAL_FUNCTION(function_name) \
     EngineInit::AddTerminalFunction(function_name);
 /********************************************************************************/
#define ADD_TERMINAL_FUNCTION_WITH_PRIORITY(function_name) \
     EngineInit::AddTerminalFunction(function_name, &ms_Priority);
