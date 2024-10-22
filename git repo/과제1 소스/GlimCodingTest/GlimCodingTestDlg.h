
// GlimCodingTestDlg.h: 헤더 파일
//

#pragma once
#include <opencv2/opencv.hpp>
#include <thread>

using namespace std;
using namespace cv;


// CGlimCodingTestDlg 대화 상자
class CGlimCodingTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimCodingTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	virtual ~CGlimCodingTestDlg();
	thread m_Thread;
	Mat image;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMCODINGTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	int LineFunc(Point2d start, Point2d end, double move_x);
	void ThradDrawFunc();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
	void FindCenter();
	CStatic m_View;
};
