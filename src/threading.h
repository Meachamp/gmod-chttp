#include <queue>
#include <GarrysMod/Lua/Interface.h>
#include "http.h"

// Data on the success queue
struct SuccessQueueData {
	int SuccessHandler;
	int FailHandler;
	HTTPResponse *response;
};

// Data on the success queue
struct FailedQueueData {
	int SuccessHandler;
	int FailHandler;
	std::string reason;
};

// Different queues for different things
std::queue<HTTPRequest*>& getRequestQueue();
std::queue<FailedQueueData>& getFailQueue();
std::queue<SuccessQueueData>& getSuccessQueue();

// Implemented by LUA_FUNCTION(threadingDoThink)
int threadingDoThink(lua_State *L);

bool scheduleRequest(HTTPRequest *request);

bool startThread();
