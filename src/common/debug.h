#ifndef DEBUG_H_
#define DEBUG_H_

void message(const char* msg);
void message_va(const char* msg, ...);

void warning(const char* msg);
void warning_va(const char* msg, ...);

bool warning_if_not(bool check, const char* msg);
bool warning_if_not_va(bool check, const char* msg, ...);

void error(const char* msg);
void error_va(const char* msg, ...);

bool error_if_not(bool check, const char* msg);
bool error_if_not_va(bool check, const char* msg, ...);
    
void debug_break();

void not_implemented_error();

void put_your_code_here();

#endif

