
// testView.cpp : CtestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "test.h"
#endif
#include "testDoc.h"
#include "testView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Round(d) int(floor(d+0.5))//��������궨��

// CtestView

IMPLEMENT_DYNCREATE(CtestView, CView)

BEGIN_MESSAGE_MAP(CtestView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CtestView ����/����

CtestView::CtestView()
{
	// TODO: �ڴ˴���ӹ������

}

CtestView::~CtestView()
{
}

BOOL CtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CtestView ����

void CtestView::OnDraw(CDC* /*pDC*/)
{
	CtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	GetClientRect(&rect);
}


// CtestView ��ӡ


void CtestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CtestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CtestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CtestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CtestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CtestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CtestView ���

#ifdef _DEBUG
void CtestView::AssertValid() const
{
	CView::AssertValid();
}

void CtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestDoc* CtestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestDoc)));
	return (CtestDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestView ��Ϣ�������


void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	                                               //������ֵ����Ļ������Ϊԭ����ʾ����ֵ
	P0.x=point.x-rect.Width()/2;
	P0.y=rect.Height()/2-point.y;

	CView::OnLButtonDown(nFlags, point);
}


void CtestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		   
		                                           //ת������ϵ��������Ļ����Ϊԭ��
		   CDC* pDC=GetDC();
		   pDC->SetMapMode(MM_ANISOTROPIC);
		   pDC->SetWindowExt(rect.Width(),rect.Height());
		   pDC->SetViewportExt(rect.Width(),-rect.Height());
		   pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);

		 P1.x=point.x-rect.Width()/2;;
		 P1.y=rect.Height()/2-point.y;



		 double k,d;
		 CP2 p1;                                    //����p1����
		 CP2 p, t;                                  //����p,t����
		 

		 COLORREF clr = RGB(0, 0, 0);                  
		 if (fabs(P0.x - P1.x) < 1e-6)                //������
		 {
			 if (P0.y > P1.y)
			 {
				 t = P0; P0 = P1; P1 = t;
			 }
			 for (p = P0; p.y < P1.y; p.y++)
			 {
				 pDC->SetPixelV(Round(p.x), Round(p.y), clr);
			 }
		 }
		 else
		 {			 
			k=(P1.y-P0.y)/(P1.x-P0.x);              
				if (k > 1.0)                       //��б��k>1��ֱ��
				{
					if (P0.y > P1.y)
					{
						t = P0; P0 = P1; P1 = t;
					}
					d = 1 - 0.5*k;
					for (p = P0; p.y < P1.y; p.y++)
					{
						pDC->SetPixelV(Round(p.x), Round(p.y), clr);
						if (d >= 0)
						{
							p.x++;
							d += 1 - k;
						}
						else
							d += 1;
					}
				}

			if (0.0<=k&&k<=1.0)                     //��б��0<=k<=1��ֱ��
			{
				if (P0.x > P1.x)
				{
					t = P0; P0 = P1; P1 = t;
				}
				d =0.5-k;
				for (p = P0; p.x < P1.x; p.x++)
				{
					pDC->SetPixelV(Round(p.x), Round(p.y), clr);
					if (d<0)
					{
						p.y++;
						d+=1-k;
					}
					else
						d-=k;
				}
			}

			if (k>=-1.0&&k<0.0)                    //��-1<=k<0.0��ֱ��
			{
				if (P0.x > P1.x)
				{
					t = P0; P0 = P1; P1 = t;
				}
				d = -0.5 - k;
				for (p = P0; p.x < P1.x; p.x++)
				{
					pDC->SetPixelV(Round(p.x), Round(p.y), clr);
					if (d>0)
					{
						p.y--;
						d -= 1 + k;
					}
					else
						d -= k;
				}
			}

			if (k<-1.0)                         //��б��k<-1.0��ֱ��
			{
				if (P0.y < P1.y)
				{
					t = P0; P0 = P1; P1 = t;
				}
				d = -1-0.5*k;
				for (p = P0; p.y > P1.y; p.y--)
				{
					pDC->SetPixelV(Round(p.x), Round(p.y), clr);
					if (d<0)
					{
						p.x++;
						d -= 1 + k;
					}
					else
						d -= 1;
				}
			}
		 }
		 P0 = p1;

	CView::OnLButtonUp(nFlags, point);
}
