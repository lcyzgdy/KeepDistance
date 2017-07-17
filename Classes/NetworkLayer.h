#pragma once
#ifndef __NETWORKLAYER_H__
#define __NETWORKLAYER_H__

#include"cocos2d.h"
#include"network\WebSocket.h"
#include"network\SocketIO.h"
#include<atomic>
#include"onwind.h"
using namespace cocos2d;
using namespace cocos2d::network;

enum STATE : int
{
	LIVE = 0,
	DIED,
	WIN,
	LOST
};

enum COMMAND : int
{
	INIT = 0,
	NF,
	OP,
	BPOS,
	JOIN
};

class NetworkLayer : public Layer, public WebSocket::Delegate
{
	std::atomic_bool m_connected;
	std::thread::id m_id;
	//std::atomic<SIOClient*> m_client;
	WebSocket* m_client;

	std::string m_receiveData;
	std::string m_sendData;
	std::string m_opData; int m_opBefore, m_opAfter;
	std::string m_bposData; int m_bposBefore, m_bposAfter;
	int m_before;
	int m_after;

	bool m_important;

public:
	static Layer* createLayer();
	static NetworkLayer* create();
	virtual bool init() override;
	virtual void onExit() override;
	int ConnectThreadStart();

	virtual void update(float dt) override;

	// 通过 SIODelegate 继承
	//virtual void onConnect(SIOClient* client) override;
	//virtual void onClose(SIOClient * client) override;
	//virtual void onError(SIOClient * client, const std::string & data) override;

	// 通过 Delegate 继承
	virtual void onOpen(WebSocket * ws) override;
	virtual void onMessage(WebSocket * ws, const WebSocket::Data & data) override;
	virtual void onClose(WebSocket * ws) override;
	virtual void onError(WebSocket * ws, const WebSocket::ErrorCode & error) override;

	string GetData();
	string GetOpData();
	string GetBposData();
	void SetData(const string& data);
	bool Updated();
	bool OpUpdated();
	bool BposUpdated();
	void SafeImportant();
	void SendImmediate(string str);
};


#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

using namespace rapidjson;

class UpdateData
{
public:
	static string UpdatePlayerPositionAndState(const Vec2& pos, STATE state);
	static string UpdateAllBallPosition(const Vec2 pos[], const Vec2 velociy[], int num);

	static void GetPlayerPositionAndState(const Document& d, Vec2& pos, STATE& state, string& key);

	static string JoinGame();
};

#endif // !__NETWORKLAYER_H__
