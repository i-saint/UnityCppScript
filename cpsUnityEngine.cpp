#include "cpsInternal.h"
#include "cpsUnityEngine.h"

namespace cpsUnityEngine
{
    cpsImage& GetImage()
    {
        static cpsImage s_image = cpsImage::findImage("UnityEngine");
        return s_image;
    }


    cpsClass Debug::getClass()
    {
        static cpsClass s_class = GetImage().findClass("UnityEngine", "Debug");
        return s_class;
    }


    void Debug::Log(const char *message)
    {
        static cpsMethod s_method = getClass().findMethod("Log", 1);
        MonoString *str = mono_string_new(mono_domain_get(), message);
        void *args[] = { str };
        s_method.invoke(nullptr, args);
    }

    void Debug::Log(const char *message, cpsObject obj)
    {
        static cpsMethod s_method = getClass().findMethod("Log", 2);
        MonoString *str = mono_string_new(mono_domain_get(), message);
        void *args[] = { str, obj };
        s_method.invoke(nullptr, args);
    }

} // namespace cpsUnityEngine
