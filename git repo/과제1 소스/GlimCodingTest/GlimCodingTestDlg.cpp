
// GlimCodingTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimCodingTest.h"
#include "GlimCodingTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGlimCodingTestDlg 대화 상자



CGlimCodingTestDlg::CGlimCodingTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMCODINGTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGlimCodingTestDlg::~CGlimCodingTestDlg()
{
	if (m_Thread.joinable()) m_Thread.join();
}

void CGlimCodingTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_View);
}

BEGIN_MESSAGE_MAP(CGlimCodingTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGlimCodingTestDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGlimCodingTestDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CGlimCodingTestDlg 메시지 처리기

BOOL CGlimCodingTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimCodingTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimCodingTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimCodingTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin)
{
	assert(bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));
	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);
	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = width;
	bmih->biHeight = origin ? abs(height) : -abs(height);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bpp;
	bmih->biCompression = BI_RGB;
	if (bpp == 8) {
		RGBQUAD* palette = bmi->bmiColors;
		for (int i = 0; i < 256; i++) {
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}


void DisplayImage(CDC* pDC, CRect rect, Mat& srcimg)
{

	if (!srcimg.data) return;
	Mat img;
	int step = ((int)(rect.Width() / 4)) * 4;
	uchar buffer[sizeof(BITMAPINFOHEADER) * 1024];

	resize(srcimg, img, Size(step, rect.Height()));
	int bmp_w = img.cols;
	int bmp_h = img.rows;
	int depth = img.depth();
	int channels = img.channels();
	int bpp = 8 * channels;

	BITMAPINFO* bmi = (BITMAPINFO*)buffer;
	FillBitmapInfo(bmi, bmp_w, bmp_h, bpp, 0);
	int from_x = MIN(0, bmp_w - 1);
	int from_y = MIN(0, bmp_h - 1);
	int sw = MAX(MIN(bmp_w - from_x, rect.Width()), 0);
	int sh = MAX(MIN(bmp_h - from_y, rect.Height()), 0);

	SetDIBitsToDevice(pDC->m_hDC, 0, 0, sw, sh, from_x, from_y, 0, sh, img.data + from_y * img.step, bmi, 0);
	img.release();
}

int CGlimCodingTestDlg::LineFunc(Point2d start, Point2d end, double move_x) {  //원 이동 시 y좌표 구하는 함수
	double move_y; // 이동할 y좌표

	move_y = ((end.y - start.y) / (end.x - start.x)) * (move_x - start.x) + start.y;  // 직.방 이용해 이동할 y좌표 구함

	return move_y;
}

void CGlimCodingTestDlg::ThradDrawFunc() {

	CRect rect;
	Point2d start(0, 0), end(0, 0), move(0, 0);  // start, end == 시작/종료 좌표
	int r, cnt = 0; // r == 반지름

	GetWindowRect(&rect);
	CDC* pDC = m_View.GetWindowDC();
	m_View.GetWindowRect(&rect);

	ScreenToClient(&rect);

	// Edit에서 시작/종료 좌표 읽어오기
	start.x = double(GetDlgItemInt(IDC_START_X)), start.y = double(GetDlgItemInt(IDC_START_Y));
	end.x = double(GetDlgItemInt(IDC_END_X)), end.y = double(GetDlgItemInt(IDC_END_Y));

	move = start;

	srand(time(0));
	r = rand() % 91 + 10;

	while (true) {  // 원 그리기
		image = Mat(rect.Height(), rect.Width(), CV_8UC3, Scalar(255, 255, 255));

		circle(image, move, r, Scalar(0, 0, 0), -1);

		DisplayImage(pDC, rect, image); // 그린 원 띄움

		String fname = format("D:/취업/git repo/과제1 소스/GlimCodingTest/image/circle_%d.jpg", cnt);
		imwrite(fname, image); // 그린 이미지 저장
		cnt++;

		if ((move.x == end.x) && (move.y == end.y)) break;

		// 이동할 x좌표 설정
		if (start.x < end.x) move.x++;
		else if (start.x > end.x) move.x--;
		else {  // 시작/종료 x좌표 같을 시 이동할 y좌표 설정
			move.y++;
			continue;
		}

		move.y = LineFunc(start, end, move.x);  // 이동할 y좌표 구함
	}
}


void CGlimCodingTestDlg::OnBnClickedBtnAction()
{
	m_Thread = thread(&CGlimCodingTestDlg::ThradDrawFunc, this);
}


void CGlimCodingTestDlg::OnBnClickedBtnOpen()
{
	char szFilter[] = "JPEG Files (*.jpg;*.jpeg)|*.jpg;*.jpeg|BMP Files (*.bmp)|*.bmp|";  // 선택 파일 필터

	// 파일 다이얼로그 생성
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);

	if (IDOK == dlg.DoModal()) { // 다이얼로그 표시
		CString cstrImgPath = dlg.GetPathName();
		image = imread(string(CT2A(cstrImgPath)));

		if (image.empty()) {  // 이미지 로드 실패할 경우
			AfxMessageBox(_T("이미지를 열 수 없습니다."), MB_OK | MB_ICONERROR);
			return;
		}
	}

	FindCenter();
}


void CGlimCodingTestDlg::FindCenter() {
	Mat gray_image, canny_image;  // canny_image == 캐니 에지 검출 이미지
	Point2f center;
	vector<Point> pt;
	float r;

	cvtColor(image, gray_image, COLOR_BGR2GRAY);
	Canny(gray_image, canny_image, 0, 255);

	// 에지 좌표 저장
	for (int row = 0; row < canny_image.rows; row++)
		for (int col = 0; col < canny_image.cols; col++)
			if (canny_image.at<uchar>(row, col) > 0) pt.push_back(Point(col, row));

	if (pt.size() > 0) {
		minEnclosingCircle(pt, center, r);
		string str = "(" + to_string(center.x) + ", " + to_string(center.y) + ")"; // 좌표 문자열

		line(image, Point(center.x - 10, center.y - 10), Point(center.x + 10, center.y + 10), Scalar(0, 0, 255), 1);
		line(image, Point(center.x + 10, center.y - 10), Point(center.x - 10, center.y + 10), Scalar(0, 0, 255), 1);
		putText(image, str, Point(center.x + 10, center.y + 10), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255));

		CRect rect;
		CDC* pDC = m_View.GetDC();

		m_View.GetClientRect(rect);
		DisplayImage(pDC, rect, image);
	}
	else AfxMessageBox(_T("원 그림이 존재하지 않습니다."), MB_OK | MB_ICONERROR);
}