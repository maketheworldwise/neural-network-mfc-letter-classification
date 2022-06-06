
// LetterClassificationView.h : CLetterClassificationView Ŭ������ �������̽�
//

#pragma once
#include "LetterClassificationDoc.h"
#include "LetterClassificationView.h"

#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include "TCHAR.h"
#include "math.h" 

using namespace cv;

class CLetterClassificationView : public CView
{
protected: // serialization������ ��������ϴ�.
	CLetterClassificationView();
	DECLARE_DYNCREATE(CLetterClassificationView)

// Ư���Դϴ�.
public:
	CLetterClassificationDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CLetterClassificationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	IplImage* image;
	char file_name[250];
	
	afx_msg void OnLearn();
	afx_msg void OnRecall();
	void MakeOneInput(int filecount);
	void MakeZeroInput(int filecount);

	afx_msg void OnTextlearn();
	void TextureReadInputZ(int filecount);

	afx_msg void OnTexturerecall();
	void TextureReadInputO(int filecount);

	void Instruction();
};

#ifndef _DEBUG  // LetterClassificationView.cpp�� ����� ����
inline CLetterClassificationDoc* CLetterClassificationView::GetDocument() const
   { return reinterpret_cast<CLetterClassificationDoc*>(m_pDocument); }
#endif

