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

#pragma once


// AudiodecodeDlg 对话框

class AudiodecodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AudiodecodeDlg)

public:
	AudiodecodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AudiodecodeDlg();

// 对话框数据
	enum { IDD = IDD_AUDIODECODE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_audiodecodelist;

};
