#pragma once


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vNormal;
	D3DXMATRIX	matWorld;

	float fCX;
	float fCY;
} INFO;

enum TILE_TYPE
{
	FLOOR_TILE,
	BLOCK_TILE,
	WALL_TILE,
	BROKEN_TILE,
	TILE_TYPE_END
};

enum OBJ_STATUS
{
	OBJ_STATUS_BOMB,
	OBJ_STATUS_BOMB_IDLE,
	OBJ_STATUS_READY,
	OBJ_STATUS_WAIT,
	OBJ_STATUS_WALK_UP,
	OBJ_STATUS_WALK_DOWN,
	OBJ_STATUS_WALK_LEFT,
	OBJ_STATUS_WALK_RIGHT,
	OBJ_STATUS_TRAP,
	OBJ_STATUS_DIE,
	OBJ_STATUS_END
};


enum PROTOCOL_TYPE
{
	PROTOCOL_TYPE_TILE,
	PROTOCOL_TYPE_CREATE,
	PROTOCOL_TYPE_READ,
	PROTOCOL_TYPE_UPDATE,
	PROTOCOL_TYPE_DELETE,
	PROTOCOL_TYPE_END
};

enum OBJ_ID
{
	OBJ_ID_TILE,
	OBJ_ID_WATER_BOMB,
	OBJ_ID_WAVE,
	OBJ_ID_PLAYER,
	OBJ_ID_ENEMY,
	OBJ_ID_END
};


typedef struct tagProtocolInfo
{
	float _fX;
	float _fY;
	float _fCX;
	float _fCY;

	tagProtocolInfo& operator=(tagProtocolInfo& other)
	{
		_fX = other._fX;
		_fY = other._fY;
		_fCX = other._fCX;
		_fCY = other._fCY;
		return *this;
	}
} PROTOCOL_INFO;



typedef struct tagProtocolFrame
{
	int iFrameStart;
	int iFrameEnd;

	tagProtocolFrame& operator=(tagProtocolFrame& other)
	{
		iFrameStart = other.iFrameStart;
		iFrameEnd = other.iFrameEnd;
		return *this;
	}

} PROTOCOL_FRAME;

typedef struct tagProtocol
{
	int m_iClientID;
	OBJ_ID eObjID;
	PROTOCOL_TYPE eType;
	PROTOCOL_INFO tProtocolInfo;
	PROTOCOL_FRAME tProtocolFrame;
	OBJ_STATUS eObjStatus;
} PROTOCOL;

typedef struct tagTileProtocol
{
	int m_iTileID;
	OBJ_ID eObjId;
	PROTOCOL_TYPE eType;
	TILE_TYPE eTileType;
	D3DXVECTOR3 vPos;
	float fCX;
	float fCY;
	bool done;
} TILE_PROTOCOL;
