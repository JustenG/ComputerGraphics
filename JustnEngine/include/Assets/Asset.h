#pragma once

#include <string>

class Asset
{
public:
	Asset();
	virtual ~Asset() {};

	Asset(Asset&& other) = delete;
	Asset& operator=(Asset&& other) = delete;
	Asset(const Asset& other) = delete; //No copy
	Asset& operator=(Asset& other) = delete;

	void Bind();
	void Unbind();

protected:
	virtual void onBind() = 0;
	virtual void onUnbind() = 0;
};