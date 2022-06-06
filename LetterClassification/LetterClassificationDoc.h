
// LetterClassificationDoc.h : CLetterClassificationDoc Ŭ������ �������̽�
//


#pragma once
#define MAXIM 64
#define HMAXIM 5
#include <math.h>
#include <malloc.h>
#pragma warning(disable: 4819)

class CLetterClassificationDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CLetterClassificationDoc();
	DECLARE_DYNCREATE(CLetterClassificationDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CLetterClassificationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
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
