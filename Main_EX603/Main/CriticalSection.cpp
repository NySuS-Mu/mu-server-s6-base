#include "stdafx.h"
#include <winsock2.h>
#include "CriticalSection.h"

CCriticalSection::CCriticalSection(){
	InitializeCriticalSection(&this->m_critical);
}

CCriticalSection::~CCriticalSection(){
	DeleteCriticalSection(&this->m_critical);
}

void CCriticalSection::lock(){
	EnterCriticalSection(&this->m_critical);
}

void CCriticalSection::unlock(){
	LeaveCriticalSection(&this->m_critical);
}