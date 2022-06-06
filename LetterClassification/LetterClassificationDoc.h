
// LetterClassificationDoc.h : CLetterClassificationDoc 클래스의 인터페이스
//


#pragma once
#define MAXIM 64
#define HMAXIM 5
#include <math.h>
#include <malloc.h>
#pragma warning(disable: 4819)

class CLetterClassificationDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CLetterClassificationDoc();
	DECLARE_DYNCREATE(CLetterClassificationDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CLetterClassificationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:

	double* InputPattern;
	double* HiddenI;
	double* HiddenO;
	double OutputI;
	double OutputO;
	double TargetOutput;

	double** w1;
	double* w2;
	double Bias1;
	double Bias2;

	double E;
	double EO;
	double EH;

	double* Woh;
	double* Whi;

	int i, j;

	double Sigmoid(double p);
	void Initialization();
	void Propagation(double *input);
	void Recall();
	void Print(double** w1, double* w2, double OutputO, double E);
};
