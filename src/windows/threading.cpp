#include <windows.h>
#include "../chttp.h"
#include "../threading.h"

#include "../log.h"

HANDLE hThread;
DWORD dwThreadId;

DWORD WINAPI threadFunc(LPVOID data) {
	while (!getRequestQueue().empty()) {
		HTTPRequest *request = getRequestQueue().front();
		getRequestQueue().pop();
		DBGMSG("[%p] Retrieved request from queue.", request);
		processRequest(request);
		delete request;
	}
	return 0;
}

bool startThread() {
	DWORD exitCode;

	if (GetExitCodeThread(hThread, &exitCode) && exitCode == STILL_ACTIVE)
		return true;

	// Free old thread
	if (hThread && !CloseHandle(hThread)) {
		WARN("Could not detach old background thread: %d", GetLastError());
		return false;
	}

	hThread = CreateThread(nullptr, 0, threadFunc, nullptr, 0, &dwThreadId);

	if (hThread == nullptr) {
		WARN("Could not create background thread: %d", GetLastError());
		return false;
	}

	return true;
}
