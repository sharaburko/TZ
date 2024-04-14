#pragma once

extern "C"
{
	void* CreateServer();
	void StartServer(void* handle);
	int ReadData(void* handle, char* buffer, int size);
	void StopServer(void* handle);
	void DeleteServer(void* handle);
}
