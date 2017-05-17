// ProiectDlg.cpp : implementation file

#include "stdafx.h"
#include "Proiect.h"
#include "ProiectDlg.h"
#include "pkfuncs.h"
#include "tlhelp32.h"
#include "Windows.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_PROCESSES 50

BOOL state = TRUE;

//Timer definition
#define  IDT_TIMER  WM_USER + 400


PROCESSENTRY32 Process[100];


struct thread_proc
{
	DWORD ProcessID;
	double thread_time;
} CPU[300];

double CPU_old[100];
double CPU_new[100];
double CPU_med[100];

// Number of all threads
int thread_num=0;

CEdit my_edit;
CListCtrl my_list;
CString str;

DWORD GetRunningProcesses( PROCESSENTRY32 *pProcess )
{
	__int64 creation = 0, exit= 0, kernel= 0, user= 0;

	DWORD index = 0;

	HANDLE hSnapShotProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	//Do a little error handling, just in case.
	if(hSnapShotProcess == (HANDLE)-1)
	{
		RETAILMSG( 1,(TEXT("GetRunningProcesses: Failed CreateToolhelp32Snapshot Error: %d\n"), GetLastError()));
		return 0;
	}
	
	// Pointer creation to a process
	memset(pProcess,0,sizeof(PROCESSENTRY32));

	index = 0;
	thread_num = 0;
	
	pProcess->dwSize = sizeof(PROCESSENTRY32);
	
	if(Process32First(hSnapShotProcess, pProcess))
	{
		HANDLE hSnapShotThread = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		THREADENTRY32 entry;
		entry.dwSize = sizeof(entry);

		// Permission to access informations about the threads of current process
		DWORD permissions =0;
		
		permissions = GetCurrentPermissions(); 
		DWORD a=SetProcPermissions(0xFFFFFFFF);
		permissions = GetCurrentPermissions(); 

		if(Thread32First(hSnapShotThread, &entry))
		{
			do
			{		
				HANDLE threadH = (HANDLE)entry.th32ThreadID; 
				
				if (!GetThreadTimes( (HANDLE)threadH,
									 (FILETIME*)&creation,
									 (FILETIME*)&exit,
									 (FILETIME*)&kernel, 
									 (FILETIME*)&user ) )
				{
					AfxMessageBox (_T("Can't get thread time!"));
				}
				else
				{	
					CPU[thread_num].ProcessID = entry.th32OwnerProcessID;
					CPU[thread_num].thread_time = (double)(kernel + user)/1000;
				}
				thread_num++;
			}
			while(Thread32Next(hSnapShotThread, &entry));
		}
		CloseToolhelp32Snapshot(hSnapShotThread);

		while(TRUE)
		{
			index += 1;
			if( index < MAX_PROCESSES )
			{
				memcpy( pProcess + 1 , pProcess, sizeof(PROCESSENTRY32));
				pProcess++;
				if(!Process32Next(hSnapShotProcess, pProcess))
				{
					break;
				}	
			}
			else
			{
				index = MAX_PROCESSES;
				break;
			}
		} 
	}
	CloseToolhelp32Snapshot (hSnapShotProcess);
return index ;
}


CProiectDlg::CProiectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProiectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProiectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, my_edit);
	DDX_Control(pDX, IDC_LIST1, my_list);
	DDX_Control(pDX, IDC_BUTTON1, ShowButton);
}

BEGIN_MESSAGE_MAP(CProiectDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CProiectDlg::OnBnClickedShow)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CProiectDlg::OnLvnItemchangedList1)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CProiectDlg message handlers

BOOL CProiectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
     my_list.InsertColumn(0, _T("Nr"), LVCFMT_CENTER, 23); 
	 my_list.InsertColumn(1,_T("Process Name"), LVCFMT_LEFT,  60);
	 my_list.InsertColumn(2, _T("CPU %"), LVCFMT_LEFT, 80);
     my_list.InsertColumn(3, _T("Cnt Threads"), LVCFMT_LEFT, 72);
     my_list.InsertColumn(4, _T("PID"), LVCFMT_LEFT, 70);
	 my_list.InsertColumn(5, _T("Cnt Usage"), LVCFMT_LEFT, 62);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CProiectDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_PROIECT_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_PROIECT_DIALOG));
	}
}
#endif


void CProiectDlg::OnBnClickedShow()
{
	if(state)
	{
		UINT_PTR TimerVal;
		TimerVal = SetTimer (IDT_TIMER, 1000, NULL);
		ShowButton.SetWindowTextW(_T("STOP"));
		state = FALSE;
	}
	else 
	{
		UINT_PTR TimerVal;
		TimerVal = KillTimer (IDT_TIMER);
		ShowButton.SetButtonStyle(0,1);
		ShowButton.SetWindowTextW(_T("SHOW"));
		state = TRUE;
	}
}

void CProiectDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CProiectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int ProcessCount;
	int index, nindex ;
	DWORD nr = 0;
	double percent = 0, total_percent = 0;
	int i,j;
	static int contor = 0;
	static int value = 0;

	// Get the list of running processes
	ProcessCount = GetRunningProcesses( Process );
	

	// Array inversion
	for(i=0; i<ProcessCount; i++)
	{
		CPU_old[i]=CPU_new[i];
	}

	// Process times calculation, with which thread ID verification
	for(i=0; i<ProcessCount; i++)
	{
		CPU_new[i]=0;
		for(j=0; j<thread_num; j++)
		{
			if( Process[i].th32ProcessID == CPU[j].ProcessID )
			{
				// loading 
				CPU_new[i] = CPU_new[i]+ CPU[j].thread_time;
			}
		}
	}
	
	if(value)
		for( i = 0; i < ProcessCount; i++)
		CPU_med[i] += ( CPU_new[i]-CPU_old[i])/ 100;
	value=1;

	if(contor==2)
	{
		
		contor = 0;
		// Clear ListControl
		my_list.DeleteAllItems();

	// Output information for each running process
	for( index = 0; index < ProcessCount; index++ )
	{
		str.Format(_T("%d"), index+1);
		nr+=Process[index].cntThreads;
	
		nindex = my_list.InsertItem(index, str);

		str.Format(_T("%s"), Process[index].szExeFile); 
		my_list.SetItemText(nindex,1,str);

		total_percent = total_percent + CPU_med[index]/2;
		str.Format(_T("%0.3f"),CPU_med[index]/2);
		my_list.SetItemText(nindex,2,str);

		str.Format(_T("%d"), Process[index].cntThreads);
		my_list.SetItemText(nindex,3,str);
     
		str.Format(_T("%X"), Process[index].th32ProcessID);
		my_list.SetItemText(nindex,4,str);

		str.Format(_T("%d"), Process[index].cntUsage);
		my_list.SetItemText(nindex,5,str);	
	}
		str.Format(_T("%0.3f"), total_percent);
		my_edit.SetWindowTextW(str);

		CDialog::OnTimer(nIDEvent);

		for(i = 0; i < ProcessCount; i++)
			CPU_med[i] = 0;
	}
	contor++;
}