#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	m_pTex = loadTex(L"PlayerTex", L"texture\\Player\\test.bmp");

	setName(OBJNAME::PLAYER);
	setSize(fPoint(100.f, 100.f));
	
	m_eAction = ACT::IDLE;
	m_ucState = 0;
	m_fSpd = P_SPD;
	m_fJumpSpd = P_JSPD;
	m_fGravity = P_GRAV;
	m_fTimer = 0.f;
	m_iBottomCnt = 0;

	createCollider();
	getCollider()->setSize(fPoint(40.f, 40.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));

	createAnimator();

	createAnim(L"Idle_L",	m_pTex, fPoint(0.f, 127.f),		fPoint(60.f, 127.f), fPoint(60.f, 0.f),	0.25f,	6);
	createAnim(L"Idle_R",	m_pTex, fPoint(0.f, 0.f),		fPoint(60.f, 127.f), fPoint(60.f, 0.f),	0.25f,	6);
	
	createAnim(L"Walk_L",	m_pTex, fPoint(0.f, 381.f),		fPoint(60.f, 127.f), fPoint(60.f, 0.f),	0.25f,	7);
	createAnim(L"Walk_R",	m_pTex, fPoint(0.f, 254.f),		fPoint(60.f, 127.f), fPoint(60.f, 0.f),	0.25f,	7);
	
	createAnim(L"Run_L",	m_pTex, fPoint(0.f, 635.f),		fPoint(82.f, 127.f), fPoint(82.f, 0.f),	0.2f,	12);
	createAnim(L"Run_R",	m_pTex, fPoint(0.f, 508.f),		fPoint(82.f, 127.f), fPoint(82.f, 0.f),	0.2f,	12);
	
	PLAY(L"Idle_R");

	//CAnimation* pAni;
	//pAni = getAnimator()->findAnimation(L"LeftMove");
	//pAni->getFrame(1).fpOffset = fPoint(0.f, -20.f);
	//pAni = getAnimator()->findAnimation(L"RightMove");
	//pAni->getFrame(1).fpOffset = fPoint(0.f, -20.f);
}

CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	fPoint pos = getPos();

	if (m_ucState & SP_DIR)
		PLAY(L"Idle_R");
	else
		PLAY(L"Idle_L");

	if (KEY_HOLD(VK_LEFT))
	{
		m_ucState &= ~(SP_DIR);

		if (KEY_NONE(VK_CONTROL))
		{
			pos.x -= m_fSpd * fDT;
			PLAY(L"Walk_L");
		}
		else
		{
			pos.x -= 2 * m_fSpd * fDT;
			PLAY(L"Run_L");
		}
	}
	if (KEY_HOLD(VK_RIGHT))
	{
		m_ucState |= SP_DIR;

		if (KEY_NONE(VK_CONTROL))
		{
			pos.x += m_fSpd * fDT;
			PLAY(L"Walk_R");
		}
		else
		{
			pos.x += 2 * m_fSpd * fDT;
			PLAY(L"Run_R");
		}
	}

	setPos(pos);
	getAnimator()->update();
}

void CPlayer::render(HDC hDC)
{
	componentRender(hDC);
}

//void CPlayer::createMissile()
//{
//	fPoint fpMissilePos = getPos();
//	fpMissilePos.x += getSize().x / 2.f;
//
//	// Misiile Object
//	CMissile* pMissile = new CMissile;
//	pMissile->setPos(fpMissilePos);
//	pMissile->setDir(fVec2(1, 0));
//
//	createObj(pMissile, OBJ::MISSILE_PLAYER);
//}
