/**
 * @file findinfilesview.cpp
 * @brief Find In Files View
 * @author Simon Steele
 * @note Copyright (c) 2005 Simon Steele <s.steele@pnotepad.org>
 *
 * Programmers Notepad 2 : The license file (license.[txt|html]) describes 
 * the conditions under which this source may be modified / distributed.
 */

#ifndef findinfilesview_h__included_33B3B680_2120_4038_97EA_A109AAE08AB0
#define findinfilesview_h__included_33B3B680_2120_4038_97EA_A109AAE08AB0

#define PN_FIFFINISH	(PN_FIFMATCH+1)

class CFindInFilesView : public CWindowImpl<CFindInFilesView>, public FIFSink
{
public:
	CFindInFilesView();

	enum {
		IDC_FIF_LIST = 100,
	};

	BEGIN_MSG_MAP(CFindInFilesView)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(PN_FIFMATCH, OnFIFMatch)
		MESSAGE_HANDLER(PN_FIFFINISH, OnFIFFinish)
		NOTIFY_HANDLER(IDC_FIF_LIST, NM_DBLCLK, OnListDblClk)
	END_MSG_MAP()

	void AddResult(LPCTSTR file, int line, LPCTSTR str);
	void Clear();

// Implement FIFSink
public:
	virtual void OnBeginSearch(LPCTSTR stringLookingFor, bool bIsRegex);
	virtual void OnEndSearch(int nFound, int nFiles);
	virtual void OnFoundString(LPCTSTR stringFound, LPCTSTR szFilename, int line, LPCTSTR buf);

protected:
	class FIFMatch
	{
	public:
		FIFMatch(LPCTSTR szFileName, int line, LPCTSTR szBuf);
		~FIFMatch();

		TCHAR*	FileName;
		int		Line;
		TCHAR*	Buf;
	};

protected:
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFIFMatch(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFIFFinish(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnListDblClk(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);

protected:
	CListViewCtrl	m_list;
	int				m_nItems;
	DWORD			m_dwStartTicks;
	TCHAR			m_NCBuf[40];
};

#endif //#ifndef findinfilesview_h__included_33B3B680_2120_4038_97EA_A109AAE08AB0