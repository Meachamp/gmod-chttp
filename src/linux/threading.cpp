#include <pthread.h>
#include "../chttp.h"
#include "../threading.h"

#include "../log.h"

pthread_t thread;
bool thread_exists = false;

void* threadFunc(void *data) {
	thread_exists = true;
	while (!getRequestQueue().empty()) {
		HTTPRequest *request = getRequestQueue().front();
		getRequestQueue().pop();
		DBGMSG("[%p] Retrieved request from queue.", request);
		processRequest(request);
		delete request;
	}
	thread_exists = false;
	pthread_exit(nullptr);
}

bool startThread() {
	if (thread_exists)
		return true;

	int retcode;

	if ((retcode = pthread_create(&thread, nullptr, threadFunc, nullptr))) {
		WARN("Could not create background thread: %d", retcode);
		return false;
	}

	if ((retcode = pthread_detach(thread))) {
		WARN("Could not detach background thread: %d", retcode);
		return false;
	}

	return true;
}
