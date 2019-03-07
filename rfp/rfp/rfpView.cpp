
// rfpView.cpp : implementation of the CrfpView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "rfp.h"
#endif

#include "rfpDoc.h"
#include "rfpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CrfpView

IMPLEMENT_DYNCREATE(CrfpView, CView)

BEGIN_MESSAGE_MAP(CrfpView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_OPENRAWFILE_OPEN, &CrfpView::OnOpenrawfileOpen)
END_MESSAGE_MAP()

// CrfpView construction/destruction

CrfpView::CrfpView() noexcept
{
	// TODO: add construction code here

}

CrfpView::~CrfpView()
{
}

BOOL CrfpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CrfpView drawing

void CrfpView::OnDraw(CDC* pDC)
{
	CrfpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: add draw code for native data here
	for (int i = 0; i < 256; ++i) {
		for (int j = 0; j < 256; ++j) {
			pDC->SetPixel(j, i, RGB(m_orgImg[i][j], m_orgImg[i][j], m_orgImg[i][j]));
		}
	}
}


// CrfpView printing

BOOL CrfpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CrfpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CrfpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CrfpView diagnostics

#ifdef _DEBUG
void CrfpView::AssertValid() const
{
	CView::AssertValid();
}

void CrfpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CrfpDoc* CrfpView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CrfpDoc)));
	return (CrfpDoc*)m_pDocument;
}
#endif //_DEBUG


// CrfpView message handlers


void CrfpView::OnOpenrawfileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, _T("raw"), _T("*.raw"), OFN_OVERWRITEPROMPT, _T("RAW(*.raw)|(*.raw)}"));
	if (dlg.DoModal() == IDOK)
	{
		CString pathname;
		pathname = dlg.GetPathName();

		FILE *fp;
		_tfopen_s(&fp, pathname, _T("rb"));
		fread(m_orgImg, sizeof(char), 256 * 256, fp);
		fclose(fp);

		Invalidate();
	}
}
