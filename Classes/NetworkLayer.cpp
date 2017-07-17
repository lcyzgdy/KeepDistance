#include "NetworkLayer.h"
#include <thread>
using namespace cocos2d;
using namespace cocos2d::network;

Layer * NetworkLayer::createLayer()
{
	return dynamic_cast<Layer*>(NetworkLayer::create());
}

NetworkLayer * NetworkLayer::create()
{
	NetworkLayer *obj = new (std::nothrow) NetworkLayer();
	if (obj && obj->init())
	{
		obj->autorelease();
		return obj;
	}
	else
	{
		CC_SAFE_DELETE(obj);
		return nullptr;
	}
}

bool NetworkLayer::init()
{
	Director * director = Director::getInstance();
	setContentSize(director->getWinSize());
	this->setName("networkLayer");
	m_connected = false;
	m_important = false;

	ConnectThreadStart();
	//this->scheduleUpdate();
	return true;
}

void NetworkLayer::onExit()
{
	//m_client->closeAsync();
	Layer::onExit();
}

int NetworkLayer::ConnectThreadStart()
{
	int errCode = 0;

	m_client = new WebSocket();
	if (!m_client->init(*this, "ws://192.168.137.1:8087"))
	{
		errCode = 1;
	}
	return errCode;
}

void NetworkLayer::update(float dt)
{

}

void NetworkLayer::onOpen(WebSocket * ws)
{
	//log(ws->getUrl().c_str());
	m_connected = true;
	m_client->send(UpdateData::JoinGame());
}

void NetworkLayer::onMessage(WebSocket * ws, const WebSocket::Data & data)
{
	log("Receive: ");
	CCLOG("%s", (string(data.bytes)).c_str());

	Document d;
	var str = string(data.bytes);
	d.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	if (d.HasParseError()) return;
	if (d.IsObject())
	{
		COMMAND com = (COMMAND)d["COMMAND"].GetInt();
		switch (com)
		{
		case INIT:
		{
			m_after++;
			m_receiveData = str;
			break;
		}
		case NF:
		{
			m_after++;
			m_receiveData = str;
			break;
		}
		case OP:
		{
			m_opAfter++;
			m_opData = str;
			break;
		}
		case BPOS:
		{
			m_bposAfter++;
			m_bposData = str;
			break;
		}
		default:
			break;
		}
	}
	if (!m_important)
	{
		m_receiveData = data.bytes;
		if (m_receiveData.find("NF") || m_receiveData.find("INIT"))
		{
			m_important = true;
		}
	}
	m_after++;
}

void NetworkLayer::onClose(WebSocket * ws)
{
	log("Closed");
	//ws->closeAllConnections();
	//ws->closeAsync();
}

void NetworkLayer::onError(WebSocket * ws, const WebSocket::ErrorCode & error)
{
	//log(IntToString((int)error).c_str());
}

string NetworkLayer::GetData()
{
	m_before++;
	return m_receiveData;
}

string NetworkLayer::GetOpData()
{
	m_opBefore++;
	return m_opData;
}

string NetworkLayer::GetBposData()
{
	m_bposBefore++;
	return m_bposData;
}

void NetworkLayer::SetData(const string & data)
{
	m_sendData = data;
	if (m_connected && m_client->getReadyState() == WebSocket::State::OPEN)
	{
		m_client->send(m_sendData);
	}
}

bool NetworkLayer::Updated()
{
	return m_before != m_after;
}

bool NetworkLayer::OpUpdated()
{
	return m_opAfter != m_opBefore;
}

bool NetworkLayer::BposUpdated()
{
	return m_bposAfter != m_bposBefore;
}

void NetworkLayer::SafeImportant()
{
	m_important = false;
}

void NetworkLayer::SendImmediate(string str)
{
	if (m_connected && m_client->getReadyState() == WebSocket::State::OPEN)
	{
		m_client->send(str);
	}
}







string UpdateData::UpdatePlayerPositionAndState(const Vec2& pos, STATE state)
{
	Document d;
	Document::AllocatorType& alloc = d.GetAllocator();
	d.SetObject();

	d.AddMember("COMMAND", COMMAND::OP, alloc);

	d.AddMember("X", pos.x, alloc);
	d.AddMember("Y", pos.y, alloc);
	d.AddMember("STATE", state, alloc);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	CCLOG("%s", buffer.GetString());
	return buffer.GetString();
}

string UpdateData::UpdateAllBallPosition(const Vec2 pos[], const Vec2 velociy[], int num)
{
	Document d;
	Document::AllocatorType& alloc = d.GetAllocator();
	d.SetObject();
	rapidjson::Value arr(kArrayType);

	d.AddMember("COMMAND", COMMAND::BPOS, alloc);
	d.AddMember("COUNT", num, alloc);

	for (int i = 0; i < num; i++)
	{
		rapidjson::Value obj(rapidjson::kObjectType);
		obj.AddMember("X", pos[i].x, alloc);
		obj.AddMember("Y", pos[i].y, alloc);
		obj.AddMember("VX", velociy[i].x, alloc);
		obj.AddMember("VY", velociy[i].y, alloc);
		arr.PushBack(obj, alloc);
	}
	d.AddMember("BALLS", arr, alloc);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	//CCLOG("%s", buffer.GetString());
	return buffer.GetString();
}

void UpdateData::GetPlayerPositionAndState(const Document& d, Vec2 & pos, STATE & state, string & key)
{
	key = d["KEY"].GetString();
	pos.x = d["X"].GetFloat();
	pos.y = d["Y"].GetFloat();
	state = (STATE)d["STATE"].GetInt();
}

string UpdateData::JoinGame()
{
	Document d;
	Document::AllocatorType& alloc = d.GetAllocator();
	d.SetObject();
	rapidjson::Value arr(kArrayType);

	d.AddMember("COMMAND", COMMAND::JOIN, alloc);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	//CCLOG("%s", buffer.GetString());
	return buffer.GetString();
}
