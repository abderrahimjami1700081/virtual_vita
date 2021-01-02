
#include "StateInfo.h"

StateInitInfo* g_state_init_info_;

void StateInitInfo::createPointer(gef::Platform &_p)
{
	g_state_init_info_ = new StateInitInfo(_p);
}

StateInitInfo* StateInitInfo::getInstance()
{
	return g_state_init_info_;
}
