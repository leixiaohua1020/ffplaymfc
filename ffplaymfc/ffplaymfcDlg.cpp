/* 
 * FFplay for MFC
 *
 * 雷霄骅 Lei Xiaohua
 * leixiaohua1020@126.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 *
 * http://blog.csdn.net/leixiaohua1020
 * 
 * 本工程将ffmpeg项目中的ffplay播放器（ffplay.c）移植到了VC的环境下。
 * 并且使用MFC做了一套简单的界面。
 * This software transplant ffplay to Microsoft VC++ environment. 
 * And use MFC to build a simple Graphical User Interface. 
 */

#include "stdafx.h"
#include "ffplaymfc.h"
#include "ffplaymfcDlg.h"
#include "afxdialogex.h"

#include "ffplaycore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editconfig;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString configinfo;
#ifdef _UNICODE
	USES_CONVERSION;
	configinfo.Format(_T("%s"),A2W(avformat_configuration()));
#else
	configinfo.Format(_T("%s"),avformat_configuration());
#endif
	m_editconfig.SetWindowText(configinfo);
	return TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CONFIG, m_editconfig);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CffplaymfcDlg 对话框




CffplaymfcDlg::CffplaymfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CffplaymfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CffplaymfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODECA_CHANNELS, m_codecachannels);
	DDX_Control(pDX, IDC_CODECA_NAME, m_codecaname);
	DDX_Control(pDX, IDC_CODECA_SAMPLERATE, m_codecasamplerate);
	//  DDX_Control(pDX, IDC_CODECV_FRAMERATE, m_codecvframerate);
	DDX_Control(pDX, IDC_CODECV_NAME, m_codecvname);
	DDX_Control(pDX, IDC_CODECV_FRAMERATE, m_codecvframerate);
	DDX_Control(pDX, IDC_CODECV_PIXFMT, m_codecvpixfmt);
	//  DDX_Text(pDX, IDC_CODECV_SIZE, m_codecvsize);
	DDX_Control(pDX, IDC_CURRENT_CLOCK, m_currentclock);
	DDX_Control(pDX, IDC_DURATION, m_duration);
	DDX_Control(pDX, IDC_FORMAT_BITRATE, m_formatbitrate);
	DDX_Control(pDX, IDC_FORMAT_DURATION, m_formatduration);
	DDX_Control(pDX, IDC_FORMAT_INPUTFORMAT, m_formatinputformat);
	DDX_Control(pDX, IDC_FORMAT_METADATA, m_formatmetadata);
	DDX_Control(pDX, IDC_FORMAT_PROTOCOL, m_formatprotocol);
	DDX_Control(pDX, IDC_CODECV_RESOLUTION, m_codecvresolution);
	DDX_Control(pDX, IDC_PLAY_PROGRESS, m_playprogress);
	DDX_Control(pDX, IDC_INPUTURL, m_inputurl);
}

BEGIN_MESSAGE_MAP(CffplaymfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CffplaymfcDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_SEEK_B, &CffplaymfcDlg::OnBnClickedSeekB)
	ON_BN_CLICKED(IDC_PAUSE, &CffplaymfcDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_SEEK_F, &CffplaymfcDlg::OnBnClickedSeekF)
	ON_BN_CLICKED(IDC_STOP, &CffplaymfcDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_SEEK_STEP, &CffplaymfcDlg::OnBnClickedSeekStep)
	ON_BN_CLICKED(IDC_FULLSCREEN, &CffplaymfcDlg::OnBnClickedFullscreen)
	ON_BN_CLICKED(IDC_INPUTURL_BUTTON, &CffplaymfcDlg::OnBnClickedInputurlButton)
	ON_BN_CLICKED(IDC_VIDEODECODE, &CffplaymfcDlg::OnBnClickedVideodecode)
	ON_BN_CLICKED(IDC_AUDIODECODE, &CffplaymfcDlg::OnBnClickedAudiodecode)
	ON_WM_DROPFILES()
	ON_COMMAND(IDC_ABOUT, &CffplaymfcDlg::OnAbout)
	ON_COMMAND(IDC_SYSINFO, &CffplaymfcDlg::OnSysinfo)
	ON_COMMAND(IDC_SEEK_F_60, &CffplaymfcDlg::OnSeekF60)
	ON_COMMAND(IDC_SEEK_B_60, &CffplaymfcDlg::OnSeekB60)
	ON_COMMAND(IDC_SEEK_F_600, &CffplaymfcDlg::OnSeekF600)
	ON_COMMAND(IDC_SEEK_B_600, &CffplaymfcDlg::OnSeekB600)
	ON_COMMAND(ID_WINDOW_YUV, &CffplaymfcDlg::OnWindowYuv)
	ON_COMMAND(ID_WINDOW_WAVE, &CffplaymfcDlg::OnWindowWave)
	ON_COMMAND(ID_WINDOW_RDFT, &CffplaymfcDlg::OnWindowRdft)
	ON_COMMAND(ID_SIZE_50, &CffplaymfcDlg::OnSize50)
	ON_COMMAND(ID_SIZE_75, &CffplaymfcDlg::OnSize75)
	ON_COMMAND(ID_SIZE_100, &CffplaymfcDlg::OnSize100)
	ON_COMMAND(ID_SIZE_125, &CffplaymfcDlg::OnSize125)
	ON_COMMAND(ID_SIZE_150, &CffplaymfcDlg::OnSize150)
	ON_COMMAND(ID_SIZE_200, &CffplaymfcDlg::OnSize200)
	ON_COMMAND(ID_SIZE_400, &CffplaymfcDlg::OnSize400)
	ON_COMMAND(ID_ASPECT_1_1, &CffplaymfcDlg::OnAspect11)
	ON_COMMAND(ID_ASPECT_4_3, &CffplaymfcDlg::OnAspect43)
	ON_COMMAND(ID_ASPECT_16_9, &CffplaymfcDlg::OnAspect169)
	ON_COMMAND(ID_ASPECT_16_10, &CffplaymfcDlg::OnAspect1610)
	ON_COMMAND(ID_ASPECT_235_100, &CffplaymfcDlg::OnAspect235100)
	ON_COMMAND(ID_LANG_CN, &CffplaymfcDlg::OnLangCn)
	ON_COMMAND(ID_LANG_EN, &CffplaymfcDlg::OnLangEn)
	ON_WM_HSCROLL()
	ON_COMMAND(ID_WEBSITE, &CffplaymfcDlg::OnWebsite)
	ON_COMMAND(IDCANCEL, &CffplaymfcDlg::OnIdcancel)
	ON_COMMAND(ID_WINDOWSTRETCH_KEEPRATIO, &CffplaymfcDlg::OnWindowstretchKeepratio)
	ON_COMMAND(ID_WINDOWSTRETCH_RESIZE, &CffplaymfcDlg::OnWindowstretchResize)
END_MESSAGE_MAP()

UINT Thread_Play(LPVOID lpParam){
	CffplaymfcDlg *dlg=(CffplaymfcDlg *)lpParam;
	ffmfc_play(lpParam);
	return 0;
}

// CffplaymfcDlg 消息处理程序

BOOL CffplaymfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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


	//_CrtSetBreakAlloc(4985);
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CreateSubWindow();
	//
	//SliderControl
	m_playprogress.SetRange(0,1000);
	m_playprogress.SetTicFreq(50);

	ResetBtn();

	TCHAR* argvPath = __targv[1];


	if(argvPath != NULL){ 
		//设置路径
		m_inputurl.SetWindowText(argvPath);
		OnBnClickedStart();
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CffplaymfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CffplaymfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CffplaymfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CffplaymfcDlg::ResetBtn(){
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEEK_B)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEEK_F)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEEK_STEP)->EnableWindow(FALSE);
	GetDlgItem(IDC_FULLSCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_PLAY_PROGRESS)->EnableWindow(FALSE);
}

void CffplaymfcDlg::ActiveBtn(){
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEEK_B)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEEK_F)->EnableWindow(TRUE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEEK_STEP)->EnableWindow(TRUE);
	GetDlgItem(IDC_FULLSCREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_PLAY_PROGRESS)->EnableWindow(TRUE);
}

void CffplaymfcDlg::OnBnClickedStart()
{
	char url[MAX_URL_LENGTH]={0};
	m_inputurl.GetWindowText((LPTSTR)url,1000);
	if(strcmp(url,"")==0){
		CString resloader;
		resloader.LoadString(IDS_MSGBOX_NOURL);
		AfxMessageBox(resloader);
		return ;
	}

	pThreadPlay = AfxBeginThread(Thread_Play,this);//开启线程
	ActiveBtn();
}


void CffplaymfcDlg::OnBnClickedSeekB()
{
	ffmfc_seek(-60);
}


void CffplaymfcDlg::OnBnClickedPause()
{
	ffmfc_play_pause();
}


void CffplaymfcDlg::OnBnClickedSeekF()
{
	ffmfc_seek(60);
}


void CffplaymfcDlg::OnBnClickedStop()
{
	ffmfc_quit();
	SystemClear();
	ResetBtn();
}


void CffplaymfcDlg::OnBnClickedSeekStep()
{
	ffmfc_seek_step();
}


void CffplaymfcDlg::OnBnClickedFullscreen()
{
	ffmfc_play_fullcreen();
}


void CffplaymfcDlg::OnBnClickedInputurlButton()
{
	CString FilePathName;
	//文件过滤字符串。够长
	CString strfilter;
	strfilter.Append(_T("Common media formats|*.avi;*.wmv;*.wmp;*.wm;*.asf;*.rm;*.ram;*.rmvb;*.ra;*.mpg;*.mpeg;*.mpe;*.m1v;*.m2v;*.mpv2;"));
	strfilter.Append(_T("*.mp2v;*.dat;*.mp4;*.m4v;*.m4p;*.vob;*.ac3;*.dts;*.mov;*.qt;*.mr;*.3gp;*.3gpp;*.3g2;*.3gp2;*.swf;*.ogg;*.wma;*.wav;"));
	strfilter.Append(_T("*.mid;*.midi;*.mpa;*.mp2;*.mp3;*.m1a;*.m2a;*.m4a;*.aac;*.mkv;*.ogm;*.m4b;*.tp;*.ts;*.tpr;*.pva;*.pss;*.wv;*.m2ts;*.evo;"));
	strfilter.Append(_T("*.rpm;*.realpix;*.rt;*.smi;*.smil;*.scm;*.aif;*.aiff;*.aifc;*.amr;*.amv;*.au;*.acc;*.dsa;*.dsm;*.dsv;*.dss;*.pmp;*.smk;*.flic|"));
	strfilter.Append(_T("Windows Media Video(*.avi;*wmv;*wmp;*wm;*asf)|*.avi;*.wmv;*.wmp;*.wm;*.asf|"));
	strfilter.Append(_T("Windows Media Audio(*.wma;*wav;*aif;*aifc;*aiff;*mid;*midi;*rmi)|*.wma;*.wav;*.aif;*.aifc;*.aiff;*.mid;*.midi;*.rmi|"));
	strfilter.Append(_T("Real(*.rm;*ram;*rmvb;*rpm;*ra;*rt;*rp;*smi;*smil;*.scm)|*.rm;*.ram;*.rmvb;*.rpm;*.ra;*.rt;*.rp;*.smi;*.smil;*.scm|"));
	strfilter.Append(_T("MPEG Video(*.mpg;*mpeg;*mpe;*m1v;*m2v;*mpv2;*mp2v;*dat;*mp4;*m4v;*m4p;*m4b;*ts;*tp;*tpr;*pva;*pss;*.wv;)|"));
	strfilter.Append(_T("*.mpg;*.mpeg;*.mpe;*.m1v;*.m2v;*.mpv2;*.mp2v;*.dat;*.mp4;*.m4v;*.m4p;*.m4b;*.ts;*.tp;*.tpr;*.pva;*.pss;*.wv;|"));
	strfilter.Append(_T("MPEG Audio(*.mpa;*mp2;*m1a;*m2a;*m4a;*aac;*.m2ts;*.evo)|*.mpa;*.mp2;*.m1a;*.m2a;*.m4a;*.aac;*.m2ts;*.evo|"));
	strfilter.Append(_T("DVD(*.vob;*ifo;*ac3;*dts)|*.vob;*.ifo;*.ac3;*.dts|MP3(*.mp3)|*.mp3|CD Tracks(*.cda)|*.cda|"));
	strfilter.Append(_T("Quicktime(*.mov;*qt;*mr;*3gp;*3gpp;*3g2;*3gp2)|*.mov;*.qt;*.mr;*.3gp;*.3gpp;*.3g2;*.3gp2|"));
	strfilter.Append(_T("Flash Files(*.flv;*swf;*.f4v)|*.flv;*.swf;*.f4v|Playlist(*.smpl;*.asx;*m3u;*pls;*wvx;*wax;*wmx;*mpcpl)|*.smpl;*.asx;*.m3u;*.pls;*.wvx;*.wax;*.wmx;*.mpcpl|"));
	strfilter.Append(_T("Others(*.ivf;*au;*snd;*ogm;*ogg;*fli;*flc;*flic;*d2v;*mkv;*pmp;*mka;*smk;*bik;*ratdvd;*roq;*drc;*dsm;*dsv;*dsa;*dss;*mpc;*divx;*vp6;*.ape;*.flac;*.tta;*.csf)"));
	strfilter.Append(_T("|*.ivf;*.au;*.snd;*.ogm;*.ogg;*.fli;*.flc;*.flic;*.d2v;*.mkv;*.pmp;*.mka;*.smk;*.bik;*.ratdvd;*.roq;*.drc;*.dsm;*.dsv;*.dsa;*.dss;*.mpc;*.divx;*.vp6;*.ape;*.amr;*.flac;*.tta;*.csf|"));
	strfilter.Append(_T("All Files(*.*)|*.*||"));


	LPCTSTR lpszfilter=strfilter;
	CFileDialog dlg(TRUE,NULL,NULL,NULL,lpszfilter);///TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if(dlg.DoModal()==IDOK) {
		FilePathName=dlg.GetPathName();
		m_inputurl.SetWindowText(FilePathName);
	}
}

void CffplaymfcDlg::SystemClear()
{
	vddlg->m_videodecodelist.DeleteAllItems();
	addlg->m_audiodecodelist.DeleteAllItems();
}

void CffplaymfcDlg::OnBnClickedVideodecode()
{
	vddlg->ShowWindow(TRUE);
}


void CffplaymfcDlg::OnBnClickedAudiodecode()
{
	addlg->ShowWindow(TRUE);
}

void CffplaymfcDlg::CreateSubWindow(){
	vddlg=new VideodecodeDlg;
	vddlg->Create(IDD_VIDEODECODE_DIALOG);
	addlg=new AudiodecodeDlg;
	addlg->Create(IDD_AUDIODECODE_DIALOG);
	sidlg=new SysinfoDlg;
	sidlg->Create(IDD_SYSINFO_DIALOG);
}

void CffplaymfcDlg::FreeSubWindow(){
	vddlg->DestroyWindow();
	addlg->DestroyWindow();
	sidlg->DestroyWindow();
	delete vddlg;
	delete addlg;
	delete sidlg;
}


void CffplaymfcDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);
	LPTSTR pFilePathName =(LPTSTR)malloc(MAX_URL_LENGTH);
	::DragQueryFile(hDropInfo, 0, pFilePathName,MAX_URL_LENGTH);  // 获取拖放文件的完整文件名，最关键！

	m_inputurl.SetWindowText(pFilePathName);

	::DragFinish(hDropInfo);   // 注意这个不能少，它用于释放Windows 为处理文件拖放而分配的内存
	free(pFilePathName);
}


void CffplaymfcDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


void CffplaymfcDlg::OnSysinfo()
{
	sidlg->ShowWindow(TRUE);
}


void CffplaymfcDlg::OnSeekF60()
{
	ffmfc_seek(60);
}


void CffplaymfcDlg::OnSeekB60()
{
	ffmfc_seek(-60);
}


void CffplaymfcDlg::OnSeekF600()
{
	ffmfc_seek(600);
}


void CffplaymfcDlg::OnSeekB600()
{
	ffmfc_seek(-600);
}


void CffplaymfcDlg::OnWindowYuv()
{
	ffmfc_audio_display(0);
}


void CffplaymfcDlg::OnWindowWave()
{
	ffmfc_audio_display(1);
}


void CffplaymfcDlg::OnWindowRdft()
{
	ffmfc_audio_display(2);
}


void CffplaymfcDlg::OnSize50()
{
	ffmfc_size(50);
}


void CffplaymfcDlg::OnSize75()
{
	ffmfc_size(75);
}


void CffplaymfcDlg::OnSize100()
{
	ffmfc_size(100);
}


void CffplaymfcDlg::OnSize125()
{
	ffmfc_size(125);
}


void CffplaymfcDlg::OnSize150()
{
	ffmfc_size(150);
}


void CffplaymfcDlg::OnSize200()
{
	ffmfc_size(200);
}


void CffplaymfcDlg::OnSize400()
{
	ffmfc_size(400);
}


void CffplaymfcDlg::OnAspect11()
{
	ffmfc_aspectratio(1,1);
}


void CffplaymfcDlg::OnAspect43()
{
	ffmfc_aspectratio(4,3);
}


void CffplaymfcDlg::OnAspect169()
{
	ffmfc_aspectratio(16,9);
}


void CffplaymfcDlg::OnAspect1610()
{
	ffmfc_aspectratio(16,10);
}


void CffplaymfcDlg::OnAspect235100()
{
	ffmfc_aspectratio(235,100);
}


void CffplaymfcDlg::OnLangCn()
{
	//配置文件路径
	char conf_path[300]={0};
	//获得exe绝对路径
	GetModuleFileNameA(NULL,(LPSTR)conf_path,300);//
	//获得exe文家夹路径
	strrchr( conf_path, '\\')[0]= '\0';//
	//_getcwd(realpath,MYSQL_S_LENGTH);
	printf("%s",conf_path);
	strcat(conf_path,"\\configure.ini");
	//写入配置文件
	WritePrivateProfileStringA("Settings","language","Chinese",conf_path);

	//重启软件
	char exe_path[300]={0};
	//获得exe绝对路径
	GetModuleFileNameA(NULL,(LPSTR)exe_path,300);
	ShellExecuteA( NULL,"open",exe_path,NULL,NULL,SW_SHOWNORMAL);

	//先点一下暂停
	OnBnClickedStop();
	//释放子窗口
	FreeSubWindow();
	CDialogEx::OnCancel();
}


void CffplaymfcDlg::OnLangEn()
{
	//配置文件路径
	char conf_path[300]={0};
	//获得exe绝对路径
	GetModuleFileNameA(NULL,(LPSTR)conf_path,300);//
	//获得exe文家夹路径
	strrchr( conf_path, '\\')[0]= '\0';//
	//_getcwd(realpath,MYSQL_S_LENGTH);
	printf("%s",conf_path);
	strcat(conf_path,"\\configure.ini");
	//写入配置文件
	WritePrivateProfileStringA("Settings","language","English",conf_path);

	//重启软件
	char exe_path[300]={0};
	//获得exe绝对路径
	GetModuleFileNameA(NULL,(LPSTR)exe_path,300);
	ShellExecuteA( NULL,"open",exe_path,NULL,NULL,SW_SHOWNORMAL);

	//先点一下暂停
	OnBnClickedStop();
	//释放子窗口
	FreeSubWindow();
	CDialogEx::OnCancel();
}


void CffplaymfcDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//调整播放进度条
	if(nSBCode==SB_THUMBPOSITION){
		ffmfc_seek_bar(nPos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CffplaymfcDlg::OnWebsite()
{
	ShellExecuteA( NULL,"open","http://blog.csdn.net/leixiaohua1020",NULL,NULL,SW_SHOWNORMAL);
}




void CffplaymfcDlg::OnIdcancel()
{
	CString resloader;
	resloader.LoadString(IDS_MSGBOX_EXIT);
	if(IDOK==AfxMessageBox(resloader,MB_OKCANCEL|MB_ICONINFORMATION)){
		//先点一下暂停
		OnBnClickedStop();
		//释放子窗口
		FreeSubWindow();
		CDialogEx::OnCancel();
	}
}


void CffplaymfcDlg::OnWindowstretchKeepratio()
{
	ffmfc_stretch(0);
}


void CffplaymfcDlg::OnWindowstretchResize()
{
	ffmfc_stretch(1);
}
