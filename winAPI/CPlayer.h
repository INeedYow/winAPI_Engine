#pragma once
#include "CObject.h"

class CTexture;

#define ACT		ePLAYER_ACTION
enum class ePLAYER_ACTION
{
	IDLE,
	WALK,
	JUMP,
	FALL,
	ATTACK,
	HANG,

	LOOKUP,
	LOOKDOWN,
	DEATH,

	END
};

// # state
#define P_SPD			100;
#define P_JSPD			200;
#define P_GRAV			400
#define P_GRAVMAX		(P_GRAV * 3);

// 플레이어 상태
#define SP_DIR			0x0001			// 좌, 우 방향
#define SP_AIR			0x0002			// 공중에 뜸
#define SP_INVIN		0x0004			// 무적 (아마 둘 필요 없을 듯)
#define SP_GETDMG		0x0008			// 피격 등으로 무적

// item 보유
#define SP_ITEM1		0x0010
#define SP_ITEM2		0x0020

class CPlayer : public CObject
{
	ACT			m_eAction;
	UCHAR		m_ucState;				// 상태값 (무적, Item 보유상황)

	CTexture*	m_pTex;

	float		m_fSpd;
	float		m_fJumpSpd;
	float		m_fGravity;
	float		m_fTimer;
	int			m_iBottomCnt;

	//void createMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* clone();

	virtual void update();
	virtual void render(HDC hDC);

};

