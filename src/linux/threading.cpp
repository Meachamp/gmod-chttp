#include <pthread.h>
#include "../chttp.h"
#include "../threading.h"

pthread_t thread;
bool thread_exists = false;

void* threadFunc(void *data) {
	thread_exists = true;
	while (!getRequestQueue().empty()) {
		HTTPRequest *request = getRequestQueue().front();
		getRequestQueue().pop();
		processRequest(request);
		delete request;
	}
	thread_exists = false;
	pthread_exit(nullptr);
}

bool startThread() {
	if (thread_exists)
		return true;

	if (pthread_create(&thread, nullptr, threadFunc, nullptr))
		return false;

	return pthread_detach(thread) == 0;
}
