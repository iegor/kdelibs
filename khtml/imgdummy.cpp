#include <kdelibs_export.h>
extern "C"  KDE_EXPORT void* init_khtmlimagefactory();
extern "C"  KDE_EXPORT void* init_khtmlimagepart() { return init_khtmlimagefactory(); } 
