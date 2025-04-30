#pragma once

#ifndef _STR
#define _STR(m_x) #m_x
#define _MKSTR(m_x) _STR(m_x)
#endif

#define MAJOR 0
#define MINOR 0
#define PATCH 0

#define GET_VERSION _MKSTR(MAJOR) "." _MKSTR(MINOR) "." _MKSTR(PATCH)

