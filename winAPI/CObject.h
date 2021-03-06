#pragma once

class CCollider;
class CAnimator;

class CObject
{
	friend class CEventManager;
private:

	OBJNAME		m_eName;			// 충돌 대상의 종류를 알려면 필요함

	fPoint		m_fptPos;
	fPoint		m_fptSize;

	// 컴포넌트
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool		m_bDead;			// 1프레임 유예
	void		setDead();			// 이벤트 매니저만 호출할 수 있도록 friend, private;

public:
	CObject();
	CObject(const CObject& other);
	virtual ~CObject();
	virtual CObject* clone() = 0;

	void setPos(fPoint pos);
	void setSize(fPoint size);
	void setName(OBJNAME name);

	fPoint	getPos();
	fPoint	getSize();
	OBJNAME	getName();

	bool isDead();

	virtual void update() = 0;
	virtual void finalUpdate() final;	// 오버라이딩 막음
	virtual void render(HDC hDC);
	virtual void componentRender(HDC hDC);

	CCollider* getCollider();
	void createCollider();				// 

	CAnimator* getAnimator();
	void createAnimator();

	virtual void collisionKeep(CCollider* pOther) {}
	virtual void collisionEnter(CCollider* pOther) {}
	virtual void collisionExit(CCollider* pOther) {}

};

