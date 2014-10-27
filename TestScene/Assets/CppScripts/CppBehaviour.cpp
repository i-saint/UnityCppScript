#include "CppBehaviour.h"

#define cpsCurrentClass CppBehaviour
cpsExportClass()
cpsExportMethod(OnBeforeSerialize)
cpsExportMethod(OnAfterDeserialize)
#undef cpsCurrentClass

void CppBehaviour::OnBeforeSerialize()
{
    cpsDebugPrint("CppBehaviour::OnBeforeSerialize()\n");
    //*(int*)nullptr = 0;
}

void CppBehaviour::OnAfterDeserialize()
{
    cpsDebugPrint("CppBehaviour::OnAfterDeserialize()\n");
}
