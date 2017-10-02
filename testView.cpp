
// testView.cpp : CtestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "test.h"
#endif
#include "testDoc.h"
#include "testView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Round(d) int(floor(d+0.5))//四舍五入宏定义

// CtestView

IMPLEMENT_DYNCREATE(CtestView, CView)

BEGIN_MESSAGE_MAP(CtestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CtestView 构造/析构

CtestView::CtestView()
{
	// TODO: 在此处添加构造代码

}

CtestView::~CtestView()
{
}

BOOL CtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CtestView 绘制

void CtestView::OnDraw(CDC* /*pDC*/)
{
	CtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: 在此处为本机数据添加绘制代码
	GetClientRect(&rect);
}


// CtestView 打印


void CtestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CtestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CtestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CtestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CtestView 诊断

#ifdef _DEBUG
void CtestView::AssertValid() const
{
	CView::AssertValid();
}

void CtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestDoc* CtestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestDoc)));
	return (CtestDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestView 消息处理程序


void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	                                               //将坐标值以屏幕中心作为原点显示坐标值
	P0.x=point.x-rect.Width()/2;
	P0.y=rect.Height()/2-point.y;

	CView::OnLButtonDown(nFlags, point);
}


/******************************************************************************************/
/*******************************直线算法实现************************************************/
/******************************************************************************************/
void CtestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		   
		                                           //转换坐标系，设置屏幕中心为原点
		   CDC* pDC=GetDC();
		   pDC->SetMapMode(MM_ANISOTROPIC);
		   pDC->SetWindowExt(rect.Width(),rect.Height());
		   pDC->SetViewportExt(rect.Width(),-rect.Height());
		   pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);

		 P1.x=point.x-rect.Width()/2;;
		 P1.y=rect.Height()/2-point.y;



		 double k,d;
		 CP2 p1;                                    //声明p1坐标
		 CP2 p, t;                                  //声明p,t坐标
		 

		 COLORREF clr = RGB(0, 0, 0);                  
		 if (fabs(P0.x - P1.x) < 1e-6)                //画垂线
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
				if (k > 1.0)                       //画斜率k>1的直线
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

			if (0.0<=k&&k<=1.0)                     //画斜率0<=k<=1的直线
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

			if (k>=-1.0&&k<0.0)                    //画-1<=k<0.0的直线
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

			if (k<-1.0)                         //画斜率k<-1.0的直线
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
