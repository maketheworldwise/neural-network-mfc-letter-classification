
// LetterClassificationView.cpp : CLetterClassificationView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "LetterClassification.h"
#endif

#include "LetterClassificationDoc.h"
#include "LetterClassificationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLetterClassificationView

IMPLEMENT_DYNCREATE(CLetterClassificationView, CView)

BEGIN_MESSAGE_MAP(CLetterClassificationView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLetterClassificationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Learn, &CLetterClassificationView::OnLearn)
	ON_COMMAND(ID_Recall, &CLetterClassificationView::OnRecall)
	ON_COMMAND(ID_TextLearn, &CLetterClassificationView::OnTextlearn)
	ON_COMMAND(ID_TextureRecall, &CLetterClassificationView::OnTexturerecall)
END_MESSAGE_MAP()

// CLetterClassificationView 생성/소멸

CLetterClassificationView::CLetterClassificationView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CLetterClassificationView::~CLetterClassificationView()
{
}

BOOL CLetterClassificationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CLetterClassificationView 그리기

void CLetterClassificationView::OnDraw(CDC* /*pDC*/)
{
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CLetterClassificationView 인쇄


void CLetterClassificationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLetterClassificationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLetterClassificationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLetterClassificationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CLetterClassificationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLetterClassificationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLetterClassificationView 진단

#ifdef _DEBUG
void CLetterClassificationView::AssertValid() const
{
	CView::AssertValid();
}

void CLetterClassificationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLetterClassificationDoc* CLetterClassificationView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLetterClassificationDoc)));
	return (CLetterClassificationDoc*)m_pDocument;
}
#endif //_DEBUG


// CLetterClassificationView 메시지 처리기


void CLetterClassificationView::MakeOneInput(int filecount)
{
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	int y, x, c = 0;
	
	sprintf(file_name, "%s%d%s", "C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/ㄱ 이미지/ㄱ이미지 8x8/", filecount, ".png");
	image = cvLoadImage(file_name, CV_LOAD_IMAGE_GRAYSCALE);		//original
	int iw = image->width;
	int ih = image->height;
	
	for (y = 0; y < ih; y++) {
		for (x = 0; x < iw; x++) {
			pDoc->InputPattern[c] = cvGetReal2D(image, y, x);
			
			if (pDoc->InputPattern[c] > 128)
				pDoc->InputPattern[c] = 0;
			else
				pDoc->InputPattern[c] = 1;
			//printf(" %d ", (int)pDoc->InputPattern[c]);
			
			c = c + 1;
		}
		//printf("\n\n");
	}
}

void CLetterClassificationView::MakeZeroInput(int filecount)
{
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int y, x, c = 0;

	sprintf(file_name, "%s%d%s", "C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/ㄱ 아닌 이미지/ㄱ 이 아닌 8x8/", filecount, ".png");
	image = cvLoadImage(file_name, CV_LOAD_IMAGE_GRAYSCALE);		//original
	int iw = image->width;
	int ih = image->height;

	for (y = 0; y < ih; y++) {
		for (x = 0; x < iw; x++) {
			pDoc->InputPattern[c] = cvGetReal2D(image, y, x);
			
			if (pDoc->InputPattern[c] > 128)
				pDoc->InputPattern[c] = 0;
			else
				pDoc->InputPattern[c] = 1;
			//printf(" %d ", (int)pDoc->InputPattern[c]);			
			c = c + 1;
		}
		//printf("\n\n");
	}
}


void CLetterClassificationView::OnLearn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	int count, num = 0;;
	
	pDoc->E = 0.0;

	do {
		//ㄱ
		for (count = 1; count < 51; count++) {
			MakeOneInput(count);
			pDoc->TargetOutput = 1;
			pDoc->Propagation(pDoc->InputPattern);
		}

		//ㄱx
		for (count = 1; count < 51; count++) {
			MakeZeroInput(count);
			pDoc->TargetOutput = 0;
			pDoc->Propagation(pDoc->InputPattern);
		}
		num++;
	} while (pDoc->E > 0.00005 && num < 3000000);
}


void CLetterClassificationView::OnRecall()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//비교 영상 불러와 재생을 통해 인식 확인
	MakeOneInput(10);
	pDoc->Recall();

	MakeZeroInput(7);
	pDoc->Recall();

}


void CLetterClassificationView::TextureReadInputO(int filecount)
{
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	FILE *fp;
	int y, x, c, ImageSize;

	c = 0;
	ImageSize = 8;

	sprintf(file_name, "%s%d%s", "C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/ㄱ 이미지 텍스트/Binary/8x8/B_", filecount, ".txt");
	fp = fopen(file_name, "r");

	for (y = 0; y < ImageSize; y++) {
		for (x = 0; x < ImageSize; x++) {
			fprintf(fp, "%lf\n", pDoc->InputPattern[c++]);
		}
	}
}


void CLetterClassificationView::TextureReadInputZ(int filecount)
{
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	FILE *fp;
	int y, x, c, ImageSize;

	c = 0;
	ImageSize = 8;

	sprintf(file_name, "%s%d%s", "C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/ㄱ 아닌 이미지 텍스트/Binary/8x8/B_", filecount, ".txt");
	fp = fopen(file_name, "r");

	for (y = 0; y < ImageSize; y++) {
		for (x = 0; x < ImageSize; x++) {
			fprintf(fp, "%lf\n", pDoc->InputPattern[c++]);
		}
	}
}


void CLetterClassificationView::OnTextlearn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int count;

	//ㄱ
	for (count = 1; count < 51; count++) {
		TextureReadInputO(count);
		pDoc->TargetOutput = 1;
		pDoc->Propagation(pDoc->InputPattern);
	}
	//ㄱx
	for (count = 1; count < 51; count++) {
		TextureReadInputZ(count);
		pDoc->TargetOutput = 0;
		pDoc->Propagation(pDoc->InputPattern);
	}
	
}


void CLetterClassificationView::OnTexturerecall()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	TextureReadInputO(1);
	pDoc->Recall();

	TextureReadInputZ(1);
	pDoc->Recall();

}

void CLetterClassificationView::Instruction()
{
	/*
	//목표 출력값
	ㄱ : 1
	ㄱx: 0

	//이미지(.png)
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification\image/ㄱ 아닌 이미지/ㄱ 이 아닌 8x8
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification\image/ㄱ 이미지/ㄱ이미지 8x8

	//텍스트(.txt)
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/ㄱ 이미지 텍스트/Binary/8x8/B_
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/ㄱ 이미지 텍스트/origin/8x8/O_

	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/ㄱ 아닌 이미지 텍스트/Binary/8x8/B_
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/ㄱ 아닌 이미지 텍스트/origin/8x8/O_

	텍스트파일은 학습이 잘 안되므로 이미지만으로 학습시키는 것이 좋음
	*/
}
