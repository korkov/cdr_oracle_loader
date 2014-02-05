#ifndef CDR_ORACLE_LOADER_VERSION_1346839434
#define CDR_ORACLE_LOADER_VERSION_1346839434

#define CDR_ORACLE_LOADER_VERSION(MAJOR, MINOR)\
namespace cdr_oracle_loader\
{\
    struct version\
    {\
        static unsigned const full = MAJOR ## MINOR;\
        static unsigned const major = MAJOR;\
        static unsigned const minor = MINOR;\
        static char const* str() { return #MAJOR "." #MINOR; }\
    };\
}

CDR_ORACLE_LOADER_VERSION(1, 00)

#undef CDR_ORACLE_LOADER_VERSION

#endif // CDR_ORACLE_LOADER_VERSION_1346839434
