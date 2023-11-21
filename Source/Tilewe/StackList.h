#pragma once 

#include "Types.h" 

#define Tw_DEFINE_STACK_LIST(name, type, max) \
    typedef struct Tw_##name Tw_##name; \
    \
    struct Tw_##name \
    { \
        Tw_Int32 Count; \
        type Elements[max]; \
    }; \
    \
    static inline void Tw_Init##name(Tw_##name* list) \
    { \
        list->Count = 0; \
    } \
    \
    static inline void Tw_##name##_Push(Tw_##name* list, type value) \
    { \
        list->Elements[list->Count++] = value; \
    } \
    \
    static inline void Tw_##name##_PushPtr(Tw_##name* list, const type* value) \
    { \
        list->Elements[list->Count++] = *value; \
    } \
    \
    static inline void Tw_##name##_Pop(Tw_##name* list) \
    { \
        list->Count--; \
    }
