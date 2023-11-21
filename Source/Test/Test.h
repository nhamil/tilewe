#pragma once 

#include <stdbool.h> 
#include <stdio.h> 
#include <string.h> 

static char _suite[4096]; 

#define TEST_PASS() \
do \
{ \
    snprintf(_error, 4095, "%s", ""); \
    printf("%s - PASS\n", _name); \
    return true; \
} while (0); 

#define TEST_FAIL() \
do \
{ \
    snprintf(_error, 4095, "%s", ""); \
    printf("%s - FAIL (Line %d)\n", _name, __LINE__); \
    return true; \
} while (0); 

#define TEST_FAIL_MSG(...) \
do \
{ \
    snprintf(_error, 4095, __VA_ARGS__); \
    printf("%s - FAIL (Line %d%s%s)\n", _name, __LINE__, strlen(_error) > 0 ? ": " : "", _error); \
    return false; \
} while (0); 

#define TEST_EXPECT_EQ(a, b) \
do \
{ \
    long long _a = (long long) a; \
    long long _b = (long long) b; \
    if (_a != _b) TEST_FAIL_MSG("Expected %lld == %lld", _a, _b); \
} while (0); 

#define TEST_EXPECT_NEQ(a, b) \
do \
{ \
    long long _a = (long long) a; \
    long long _b = (long long) b; \
    if (_a == _b) TEST_FAIL_MSG("Expected %lld != %lld", _a, _b); \
} while (0); 

#define TEST_EXPECT_LT(a, b) \
do \
{ \
    long long _a = (long long) a; \
    long long _b = (long long) b; \
    if (_a >= _b) TEST_FAIL_MSG("Expected %lld < %lld", _a, _b); \
} while (0); 

#define TEST_EXPECT_LTE(a, b) \
do \
{ \
    long long _a = (long long) a; \
    long long _b = (long long) b; \
    if (_a > _b) TEST_FAIL_MSG("Expected %lld <= %lld", _a, _b); \
} while (0); 

#define TEST_EXPECT_GT(a, b) \
do \
{ \
    long long _a = (long long) a; \
    long long _b = (long long) b; \
    if (_a <= _b) TEST_FAIL_MSG("Expected %lld > %lld", _a, _b); \
} while (0); 

#define TEST_EXPECT_GTE(a, b) \
do \
{ \
    long long _a = (long long) a; \
    long long _b = (long long) b; \
    if (_a < _b) TEST_FAIL_MSG("Expected %lld >= %lld", _a, _b); \
} while (0); 

#define TEST_CASE(name, test) \
bool name(void) \
{ \
    static const char* _name = #name; \
    char _error[4096]; \
    printf("%s\n", _name); \
    _error[0] = 0; \
    { \
        test; \
    } \
    TEST_PASS(); \
}

#define TEST_RUN(name) \
{ \
    _total++; \
    _numPassed += name(); \
}

#define TEST_MAIN(name, tests) \
int main(void) \
{ \
    snprintf(_suite, 4095, #name); \
    printf("[======== %s ========]\n", _suite); \
    int _total = 0; \
    int _numPassed = 0; \
    { \
        tests \
    } \
    printf("[======== %s ========] - %s %d / %d\n", _suite, _numPassed == _total ? "PASS" : "FAIL", _numPassed, _total); \
    return _numPassed == _total ? 0 : -1; \
}
