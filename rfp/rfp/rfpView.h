
// rfpView.h : interface of the CrfpView class
//

#pragma once


class CrfpView : public CView
{
protected: // create from serialization only
	CrfpView() noexcept;
	DECLARE_DYNCREATE(CrfpView)

// Attributes
public:
	CrfpDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	unsigned char m_orgImg[256][256];
	virtual ~CrfpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenrawfileOpen();
};

#ifndef _DEBUG  // debug version in rfpView.cpp
inline CrfpDoc* CrfpView::GetDocument() const
   { return reinterpret_cast<CrfpDoc*>(m_pDocument); }
#endif

