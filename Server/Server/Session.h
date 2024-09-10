#pragma once
class CSession
{
public:
	CSession();
	CSession(
		int _iSessionID,
		SOCKET _hClientSocket,
		OBJ_ID _eObjId,
		PROTOCOL_INFO _tInfo,
		PROTOCOL_FRAME _tFrame
	);
	~CSession();
public:
	inline const int Get_Session_ID() const { return m_iSessionID; }
	inline const SOCKET& Get_Client_Socket() const { return m_hClientSocket; }
	inline const PROTOCOL_INFO& Get_Protocol_Info() const { return m_tInfo; }
	inline const PROTOCOL_FRAME& Get_Protocol_Frame() const { return m_tFrame; }
	inline const OBJ_STATUS& Get_Obj_Status() const { return m_eObjStatus; }

	void Release();
public:
	void Set_Info(PROTOCOL_INFO _tInfo) { m_tInfo = _tInfo; }
	void Set_Frame(PROTOCOL_FRAME _tFrame) { m_tFrame = _tFrame; }
	void Set_Obj_Status(OBJ_STATUS _eObjStatus) { m_eObjStatus = _eObjStatus; }

private:
	int m_iSessionID;
	SOCKET m_hClientSocket;
	OBJ_ID m_eObjId;
	OBJ_STATUS m_eObjStatus;
	PROTOCOL_INFO m_tInfo;
	PROTOCOL_FRAME m_tFrame;
};

