#pragma once
class CObj abstract
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;

public:
	inline const INFO& Get_INFO() const { return m_tInfo; }
	inline const RECT& Get_Rect() const { return m_tRect; }
	inline const float Get_Speed() const { return m_fSpeed; }
	inline const bool Get_Dead() const { return m_bDead; }
	inline const RECT& Get_Collider() const { return m_tColliderRect; }
	inline const INFO& Get_Collider_INFO() const { return m_tColliderInfo; }
	inline const int Get_ClientID() const { return m_iClientID; }
	inline const OBJ_STATUS Get_Obj_Cur_Status() const { return m_eObjCurStatus; }
	inline const OBJ_DIR Get_Obj_Dir() const { return m_eObjDir; }
	inline const FRAME Get_Frame() const { return m_tFrame; }

public:
	inline void Set_Scale(float _fCX, float _fCY) { m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY; }
	inline void Set_Pos(D3DXVECTOR3 _vPos) { m_tInfo.vPos = _vPos; }
	inline void Set_Look(D3DXVECTOR3 _vLook) { m_tInfo.vLook = _vLook; }
	inline void Set_Dead(bool _bDead) { m_bDead = _bDead; }
	inline void Set_ClinetID(int _iClientID) { m_iClientID = _iClientID; }
	inline void Set_Obj_Cur_Status(OBJ_STATUS _eObjStatus) { m_eObjCurStatus = _eObjStatus; }
	inline void Set_Obj_Dir(OBJ_DIR _eObjDir) { m_eObjDir = _eObjDir; }
	inline void Set_Frame(FRAME _tFrame) { m_tFrame = _tFrame; }
	inline void Set_Frame_Key(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }

// For Enemy Status
public:
	inline void Set_Frame_Start(int _iFrameStart) { m_tFrame.iFrameStart = _iFrameStart; }
	inline void Set_Frame_Motion(int _iMotion) { m_tFrame.iMotion = _iMotion; }
	inline void Set_Frame_End(int _iFrameEnd) { m_tFrame.iFrameEnd = _iFrameEnd; }
	
	

// Function For Collider
public:
	// 두 블록 사이에 있으면 부르르 떤다
	inline void Push_Left(float _pX)
	{
		m_tInfo.vPos.x -= _pX;
		m_tRect.left -= _pX;
		m_tRect.right -= _pX;

		m_tColliderInfo.fCX -= _pX;
		m_tColliderRect.left -= _pX;
		m_tColliderRect.right -= _pX;
		
	}

	inline void Push_Right(float _pX)
	{
		m_tInfo.vPos.x += _pX;
		m_tRect.left += _pX;
		m_tRect.right += _pX;

		m_tColliderInfo.fCX += _pX;
		m_tColliderRect.left += _pX;
		m_tColliderRect.right += _pX;
	}

	inline void Push_Top(float _pY)
	{
		m_tInfo.vPos.y -= _pY;
		m_tRect.top -= _pY;
		m_tRect.bottom -= _pY;

		m_tColliderInfo.fCY -= _pY;
		m_tColliderRect.top -= _pY;
		m_tColliderRect.bottom -= _pY;
	}

	inline void Push_Bottom(float _pY)
	{
		m_tInfo.vPos.y += _pY;
		m_tRect.top += _pY;
		m_tRect.bottom += _pY;

		m_tColliderInfo.fCY += _pY;
		m_tColliderRect.top += _pY;
		m_tColliderRect.bottom += _pY;
	}

public:
	void Update_Rect();
	void Update_Collider_Rect();
	void Update_Block_Collider_Rect();
	void Update_Water_Bomb_Collider();
	
	
	void Update_Player_Tile_Collider_Rect();

	void Move_Frame();
protected:
	FRAME m_tFrame;

	INFO m_tInfo;
	RECT m_tRect;

	INFO m_tColliderInfo;
	RECT m_tColliderRect;

	INFO m_tPlayerTileColliderInfo;
	RECT m_tPlayerTileColliderRect;

	OBJ_STATUS m_eObjPreStatus = OBJ_STATUS::OBJ_STATUS_END;
	OBJ_STATUS m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_END;
	
	OBJ_DIR m_eObjDir;

	int m_iClientID;
	float m_fSpeed;

	bool m_bDead = false;

	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vPrePos;

	D3DXMATRIX	m_matScale;
	D3DXMATRIX	m_matRotZ;
	D3DXMATRIX	m_matTrans;	

	TCHAR* m_pFrameKey;
};

