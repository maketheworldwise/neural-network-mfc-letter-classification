
// LetterClassificationView.cpp : CLetterClassificationView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CLetterClassificationView ����/�Ҹ�

CLetterClassificationView::CLetterClassificationView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CLetterClassificationView::~CLetterClassificationView()
{
}

BOOL CLetterClassificationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CLetterClassificationView �׸���

void CLetterClassificationView::OnDraw(CDC* /*pDC*/)
{
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CLetterClassificationView �μ�


void CLetterClassificationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLetterClassificationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CLetterClassificationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CLetterClassificationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CLetterClassificationView ����

#ifdef _DEBUG
void CLetterClassificationView::AssertValid() const
{
	CView::AssertValid();
}

void CLetterClassificationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLetterClassificationDoc* CLetterClassificationView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLetterClassificationDoc)));
	return (CLetterClassificationDoc*)m_pDocument;
}
#endif //_DEBUG


// CLetterClassificationView �޽��� ó����


void CLetterClassificationView::MakeOneInput(int filecount)
{
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	int y, x, c = 0;
	
	sprintf(file_name, "%s%d%s", "C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/�� �̹���/���̹��� 8x8/", filecount, ".png");
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

	sprintf(file_name, "%s%d%s", "C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/�� �ƴ� �̹���/�� �� �ƴ� 8x8/", filecount, ".png");
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	int count, num = 0;;
	
	pDoc->E = 0.0;

	do {
		//��
		for (count = 1; count < 51; count++) {
			MakeOneInput(count);
			pDoc->TargetOutput = 1;
			pDoc->Propagation(pDoc->InputPattern);
		}

		//��x
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//�� ���� �ҷ��� ����� ���� �ν� Ȯ��
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

	sprintf(file_name, "%s%d%s", "C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/�� �̹��� �ؽ�Ʈ/Binary/8x8/B_", filecount, ".txt");
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

	sprintf(file_name, "%s%d%s", "C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/�� �ƴ� �̹��� �ؽ�Ʈ/Binary/8x8/B_", filecount, ".txt");
	fp = fopen(file_name, "r");

	for (y = 0; y < ImageSize; y++) {
		for (x = 0; x < ImageSize; x++) {
			fprintf(fp, "%lf\n", pDoc->InputPattern[c++]);
		}
	}
}


void CLetterClassificationView::OnTextlearn()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CLetterClassificationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int count;

	//��
	for (count = 1; count < 51; count++) {
		TextureReadInputO(count);
		pDoc->TargetOutput = 1;
		pDoc->Propagation(pDoc->InputPattern);
	}
	//��x
	for (count = 1; count < 51; count++) {
		TextureReadInputZ(count);
		pDoc->TargetOutput = 0;
		pDoc->Propagation(pDoc->InputPattern);
	}
	
}


void CLetterClassificationView::OnTexturerecall()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	//��ǥ ��°�
	�� : 1
	��x: 0

	//�̹���(.png)
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification\image/�� �ƴ� �̹���/�� �� �ƴ� 8x8
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification\image/�� �̹���/���̹��� 8x8

	//�ؽ�Ʈ(.txt)
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/�� �̹��� �ؽ�Ʈ/Binary/8x8/B_
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/�� �̹��� �ؽ�Ʈ/origin/8x8/O_

	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/�� �ƴ� �̹��� �ؽ�Ʈ/Binary/8x8/B_
	C:/Users/AhnSeungSeop/Documents/Visual Studio 2015/Projects/LetterClassification/image/�� �ƴ� �̹��� �ؽ�Ʈ/origin/8x8/O_

	�ؽ�Ʈ������ �н��� �� �ȵǹǷ� �̹��������� �н���Ű�� ���� ����
	*/
}
