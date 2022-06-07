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
//pRtti->AddProperty(activeProperty)������û��ִ�С�ͨ��IMPLEMENT_INITIAL_END(�ʼ��ʼ��classFactory�ķ�ʽ)
//���˳�ʼ������ֹ���Ա���������� InitialProperty ��TerminalProperty  ���pRtti->AddProperty() ������ִ��
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

//gs_bStreamRegistered_##classname  ��̬�����ĳ�ʼ������factory����ǰ�������Ϳ���������г�ʼ���������ռ�
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
