﻿
// MFCApplication5Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"
#include "Functions.h"
#include "Constants.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <CString>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication5Dlg 对话框



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication5Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication5Dlg 消息处理程序

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication5Dlg::OnPaint()
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
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication5Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码


	//=======================================================================================================================
	//GLOBAL VARS TO BE DEFINED=
	//=======================================================================================================================

	const int       maxr = 146, maxc = 177;
	const double    xll = 799600.000120;
	const double    yll = 2647174.387550;
	const double    cellsize = 200;
	const float     NODATA_value = -9999;

	// define the simulation year, month and day
	CString strFileName = _T("c:\\file1.txt");
	if (!PathFileExists(strFileName))
	{
		MessageBox(TEXT("Nothing!"));
	}
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeRead))
	{
		MessageBox(TEXT("Nothing!"));
	}
	std::vector<CString> vecResult;
	CString strValue = _T("");
	while (file.ReadString(strValue))
	{
		vecResult.push_back(strValue);
	}

	
	file.Close();
	
	int start_year;
	int end_year;
	int output_start_year;
	int output_end_year;
	int spin_years;
	int spin_interval;
	int Check1 = 0;
	int Check2 = 0;
	int Check3 = 0;
	int Check4 = 0;
	int Check5 = 0;
	int Check6 = 0;

	start_year = _ttoi(vecResult[0]);
	end_year = _ttoi(vecResult[1]);
	output_start_year = _ttoi(vecResult[2]);
	output_end_year = _ttoi(vecResult[3]);
	spin_years = _ttoi(vecResult[4]);
	spin_interval = _ttoi(vecResult[5]);
	
	Check1 = _ttoi(vecResult[6]);
	Check2 = _ttoi(vecResult[7]);
	Check3 = _ttoi(vecResult[8]);
	Check4 = _ttoi(vecResult[9]);
	Check5 = _ttoi(vecResult[10]);
	Check6 = _ttoi(vecResult[11]);

	const int start_month = 1, end_month = 12, start_day = 1, end_day = 31;
	const int start_hour = 1, end_hour = 24;
	//int       end_day; //The end of date in February varies between normal and leap year

	// define the time period for outputting simulation results
	// out_date_range outdate={first_year, last_year, first_month, last_month, first_day, last_day, first_hour, last_hour};
	struct out_date_range out_date = { output_start_year, output_end_year, 1, 12, 1, 31, 1, 24 };

	// define the number of spin years required for vegetation and soil carbon to reach the stable state with long-term
	// climatology. Spin interval is the period of input climate data used for spin-up simulations
	//const int spin_years = 0, spin_interval = 6;
	bool      spin_flag = true;

	// define the input file prefix and paths for model forcing data
	CString strText;
	CString strText_img;
	CString strText_clim;
	CString strText_out;
	const char* filename = "c:\\file2.txt";
	FILE* fp2 = NULL;
	errno_t err = 0;
	err = fopen_s(&fp2, filename, "rb");


	char inDefFile_t[120];
    char inImgFile_t[120];
	char inFlowFile_t[120];
	char inClimPath_t[120];
	char outPutPath_t[120];

	char inDefFile[120] = { 0 };
	char inImgFile[120] = { 0 };
	char inFlowFile[120] = { 0 };
	char inClimPath[120] = { 0 };
	char outPutPath[120] = { 0 };



	int n = fread(inDefFile_t, 1, 120, fp2);
	//int n2 = fread(inImgFile_t, 1, 120, fp2);

	::wsprintfA(inDefFile, "%ls", (LPCTSTR)inDefFile_t);

	strText = inDefFile;
	//strText_img = inImgFile;
	//MessageBox(strText);
	strText = strText.Left(strText.ReverseFind('\\'));
	strText = strText.Left(strText.ReverseFind('\\'));
	//strText_clim = strText.Left(strText.ReverseFind('\\'));
	strText += _T("\\");
	strText_clim = strText+_T("clim");
	strText_out = strText+_T("out");
	strText += _T("geo");
	
	//MessageBox(strText_out);
	

	char  prefix[20] = "xf_ws";

	//char  inDefFile[120] = { "I://方老师//模型//Data//xf_ws//defs//" };
	//char  inImgFile[120] = { "I://方老师//模型//Data//xf_ws//geo//" };
	::wsprintfA(inImgFile, "%ls", (LPCTSTR)strText);
	::wsprintfA(inFlowFile, "%ls", (LPCTSTR)strText);
	::wsprintfA(inClimPath, "%ls", (LPCTSTR)strText_clim);
	::wsprintfA(outPutPath, "%ls", (LPCTSTR)strText_out);
	//char  inFlowFile[120] = { "I://方老师//模型//Data//xf_ws//geo//" };
	//char  inClimPath[120] = { "I://方老师//模型//Data//xf_ws//clim//" };
	//char  outPutPath[120] = { "I://方老师//模型//Data//xf_ws//out//" };

	strcat_s(inDefFile, "\\");
	strcat_s(inImgFile, "\\");
	strcat_s(inFlowFile, "\\");
	strcat_s(inClimPath, "\\");
	strcat_s(outPutPath, "\\");

	// multiple choice of routing algorithms
	char  FlowTableName[40] = "xf_ws_flow_table_D8.dat";

	// parallel attribute
	int	climate_num = 1;
	int thread_num = 4;
	int patch_num = 13513;

	//=======================================================================================================================
	//xu. LOCAL VARS FOR SIMULATION
	//=======================================================================================================================

	struct  date current_date {};
	struct  output_hydro_plant DM_outfiles {};
	struct  input_Clim_Files   inClimFiles {};
	struct  reservoir_object   reservoir = { 10072, 2284.5, 50, 338.6, 100, 1514.4, 2351.55, 0., 4. };
	struct command_line_object *command_line = new struct command_line_object;
	struct OutArray_object *OutArray = new struct OutArray_object;

	//xu. for lower use memory we use patch_num instead of cols*rows
	//only 1/4 memory are needed now
	struct patch_object *patch = new struct patch_object[patch_num]{};
	struct  daily_clim_object *daily_clim = new struct daily_clim_object[climate_num]{};//change it as a pointer

	//xu. parallel
	int **patch_pch = new int* [thread_num] {};
	for (int inx = 0; inx != thread_num; inx++)
		patch_pch[inx] = new int[patch_num] {};

	//storage of pch to each thread
	int *thread_patch_num = new int[thread_num] {};//number of pches in each thread

	//gauge_lists of patchID for output
	int		*gauge_list = new int [GAUGE_NUM] {};

	int     num_patches{}, kk = 0;
	int     f_flag = 1, arc_flag = 1, CO2_flag = 1, out_flag = 0;
	int     i = 0, j = 0, endyear = 0, spin_yrs = 0;
	int     firstmonth, lastmonth, firstday, lastday;
	clock_t  t, t1, t2, t3;
	double land_time{}, channel_time{};


	char **command_argv = new char*[2];
	for (int inx = 0; inx != 2; inx++) {

		command_argv[inx] = new char[120];
	}
	/*command_argv[1] = "-b";
	command_argv[2] = "-g";
	int command_argc = 3;*/
	//=======================================================================================================================
	//xu. BUILD AND INITIAL THE ENDVIRONMENT FOR SIMULATION
	//=======================================================================================================================
	//printf("Starting initialization:: \n");

	//construct and assign command line arguments
	//construct_command_line(command_argc, command_argv, command_line);
	construct_command_line(command_line);
	//-b 启动
	if (Check1==1)
	{
		command_line->b = 1;
	}

	//-g启动
	if (Check2==1)
	{
		command_line->gg = 1;
	}

	//-cf启动
	if (Check3==1)
	{
		command_line->cf = 1;
	}

	//-re启动
	if (Check4==1)
	{
		command_line->re = 1;
	}

	//-pmon启动
	if (Check5==1)
	{
		command_line->pmon = 1;
	}

	//-pday启动
	if (Check6==1)
	{
		command_line->pday = 1;
	}

	//////////////////////////////////////////////////////////////////////////////////////////

	//xu. I sugguest should 1\ flow table then  2\construct patch and read images
	num_patches = construct_routing_topology(patch, inFlowFile, FlowTableName, maxr, maxc);

	//reading GRASS- or ArcInfo-based input images such as DEM,slope,aspect....stream,roads, gauge_lists
	read_geo_images(patch, command_line, maxr, maxc, cellsize, xll, yll, inImgFile, prefix, f_flag, arc_flag, num_patches, gauge_list, thread_num);

	//Initialize the default values of patch fields/members
	construct_patch(patch, command_line, maxr, maxc, inDefFile, prefix, num_patches);

	//open input climate files (daily precipitation, minimum temperature and maximum temperature)
	inClimFiles = open_Clim_Files(inClimPath, prefix);

	//distribute parallel threads of each basins
	parallel_basins_pches(patch, patch_pch, patch_num, thread_patch_num);

	//xu. 11 minute process of initialization are now shorter to 40 second

	//=======================================================================================================================
	//xu. SPIN UP and CHESS SIMULATION
	//=======================================================================================================================

	printf("\n Starting simulation:: \n");
	do {
		t1 = clock();
		if (spin_yrs < spin_years) { //&& command_line->grow_flag>0
			endyear = start_year + spin_interval - 1;
			spin_flag = true;

			//spin_up needs routing_flag now for channel flow
			command_line->routing_flag = 1;
		}
		else {
			endyear = end_year;
			spin_flag = false;
			command_line->routing_flag = 1;
		}

		//contruct daily output files
		if (!spin_flag && out_flag == 0) {

			//basin-level
			if (!spin_flag && command_line->b != NULL) {
				construct_basin_output_files(outPutPath, &DM_outfiles, command_line);
			}
			//xu. gauge-level
			if (!spin_flag && command_line->gg != NULL) {
				construct_gauge_output_files(patch, outPutPath, &DM_outfiles, command_line, gauge_list);
			}
			out_flag = 1;
		}

		//=======================================================================================================================
		//xu. STARTING CHESS SIMULATION by YEAR, MON and DAY
		//=======================================================================================================================


		for (current_date.year = start_year; current_date.year <= endyear; current_date.year++) {


			t1 = clock();

			if (current_date.year == start_year + 10)
				cout << "\n\n" << land_time << "\t" << channel_time << endl;;


			if (current_date.year == start_year)
				firstmonth = start_month;
			else
				firstmonth = 1;

			if (current_date.year == end_year)
				lastmonth = end_month;
			else
				lastmonth = 12;

			init_phenology_object(patch, num_patches);

			for (current_date.month = firstmonth; current_date.month <= lastmonth; current_date.month++) {

				//construct patch-level daily output files for a month
				if (!spin_flag && command_line->p != NULL) {
					construct_patch_output_files(current_date, out_date, outPutPath, patch_num, &DM_outfiles, OutArray, command_line);
				}

				if (current_date.year == start_year && current_date.month == start_month)
					firstday = start_day;
				else
					firstday = 1;

				if (current_date.year == end_year && current_date.month == end_month)
					lastday = end_day;
				else
					lastday = end_day_norm_leap(current_date.year, current_date.month - 1);

				//determine if the year is leap year and thus the end day of February can be different
				//end_day=end_day_norm_leap(current_date.year,=current_date.month-1);


				//=======================================================================================================================
				//xu. DAILY SIMULATION (THREE KEY PROCESSES)
				//=======================================================================================================================
				for (current_date.day = firstday; current_date.day <= lastday; current_date.day++) {

					//-----------------------------------------------------------------------------------------------------------------------
					//xu. CLIMATE.. Read input climate data Precipitation, Tmin, Tmax and annual CO2
					//---------------------------------------------------------------------------------------------------------------------------
					chess_climate_daily(inClimFiles, current_date, daily_clim, climate_num, start_year, start_month, start_day, &CO2_flag);



					//---------------------------------------------------------------------------------------------------------------------------
					//xu. PATCH.. Initial and run parallel CHESS daily Ecohydrological process and Transport of water and nutrients
					//---------------------------------------------------------------------------------------------------------------------------
					chess_patch_daily(patch, command_line, current_date, daily_clim, num_patches, patch_pch, thread_num, thread_patch_num);//daily_clim is a pointer now, the changes through out chess land daily



					//---------------------------------------------------------------------------------------------------------------------------
					//xu. CHANNEL.. Channel flow routing process the route out the water
					//---------------------------------------------------------------------------------------------------------------------------
					chess_channel_daily(patch, reservoir, command_line, current_date, num_patches, cellsize);


					//output daily-step variables
					if (!spin_flag) {
						if (command_line->b != NULL)
							out_basin_level_daily(num_patches, patch, current_date, out_date, &DM_outfiles, command_line);
						if (command_line->p != NULL)
							out_patch_level_daily(num_patches, patch, current_date, out_date, &DM_outfiles, OutArray, command_line);
						if (command_line->gg != NULL)
							out_gauge_level_daily(num_patches, patch, current_date, out_date, &DM_outfiles, command_line, gauge_list, cellsize);
					}

				}
				//=======================================================================================================================
				//END OF DAILY SIMULATION
				//=======================================================================================================================

				//close patch_level_output_files
				if (!spin_flag && command_line->p == true)
					close_patch_output_files(&DM_outfiles, OutArray);

			} //end of months

			CO2_flag = 1;

			t3 = clock();
			channel_time = (float)(t3 - t1) / CLOCKS_PER_SEC / 60.0;


			if (!spin_flag)
				printf("year, month and day:: %d %d %d %lf\n", current_date.year, current_date.month - 1, current_date.day - 1, channel_time);

			spin_yrs += 1;
			if (spin_yrs == spin_years && spin_flag) break;
		}

		//=======================================================================================================================
		//END OF YEARS
		//=======================================================================================================================

		if (spin_flag) {
			rewind_daily_clim(inClimFiles);
			//printf("Spin-up to %d years takes %f minutes \n", spin_yrs, ((float)(clock() - t) / CLOCKS_PER_SEC / 60.));
		}

	} while (spin_flag);

	if (command_line->b != NULL)
	{
		fclose(DM_outfiles.fBasinDailyHydro);
		fclose(DM_outfiles.fBasinDailyPlant);
	}


	delete[] patch;
	delete[] daily_clim;
	for (int inx = 0; inx != thread_num; inx++)
		delete[] patch_pch[inx];
	delete[] patch_pch;
	delete[] thread_patch_num;
	delete command_line;


	//=======================================================================================================================
	//END OF SIMULATION
	//=======================================================================================================================

	//return (0);
} //end of main programs
//================================================================================================================
	



void CMFCApplication5Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);

}
