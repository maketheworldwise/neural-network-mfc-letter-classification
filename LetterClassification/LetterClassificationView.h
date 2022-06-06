
// LetterClassificationView.h : CLetterClassificationView 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CLetterClassificationView();
	DECLARE_DYNCREATE(CLetterClassificationView)

// 특성입니다.
public:
	CLetterClassificationDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CLetterClassificationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // LetterClassificationView.cpp의 디버그 버전
inline CLetterClassificationDoc* CLetterClassificationView::GetDocument() const
   { return reinterpret_cast<CLetterClassificationDoc*>(m_pDocument); }
#endif

