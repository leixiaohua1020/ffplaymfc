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
#include "AudiodecodeDlg.h"
#include "afxdialogex.h"


// AudiodecodeDlg 对话框

IMPLEMENT_DYNAMIC(AudiodecodeDlg, CDialogEx)

AudiodecodeDlg::AudiodecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AudiodecodeDlg::IDD, pParent)
{

}

AudiodecodeDlg::~AudiodecodeDlg()
{
}

void AudiodecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUDIODECODE_LIST, m_audiodecodelist);
}


BEGIN_MESSAGE_MAP(AudiodecodeDlg, CDialogEx)

END_MESSAGE_MAP()


BOOL AudiodecodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//整行选择；有表格线；表头；单击激活
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE;
	
	//多国语言支持
	CString resloader;
	resloader.LoadString(IDS_AUDIODECODE);
	SetWindowText(resloader);
	
	m_audiodecodelist.ModifyStyle(0,LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
	m_audiodecodelist.SetExtendedStyle(dwExStyle);

	resloader.LoadString(IDS_AUDIODECODE_NUM);
	m_audiodecodelist.InsertColumn(0,resloader,LVCFMT_CENTER,50,0);
	resloader.LoadString(IDS_AUDIODECODE_SIZE);
	m_audiodecodelist.InsertColumn(1,resloader,LVCFMT_CENTER,50,0);
	resloader.LoadString(IDS_AUDIODECODE_PTS);
	m_audiodecodelist.InsertColumn(2,resloader,LVCFMT_CENTER,50,0);
	resloader.LoadString(IDS_AUDIODECODE_DTS);
	m_audiodecodelist.InsertColumn(3,resloader,LVCFMT_CENTER,50,0);

	return TRUE;
}




