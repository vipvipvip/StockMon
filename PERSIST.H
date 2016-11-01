/***************************** Defines/Macros ******************************/
#define FRM_SUBKEY_HEADING	_T("Settings\\Main Window")
#define FRM_LHV_RECT			_T("Rect")
#define FRM_LHV_ICON			_T("Icon")
#define FRM_LHV_MAX			_T("Max")
#define FRM_LHV_TOOL		_T("Tool")
#define FRM_LHV_STATUS		_T("Status")
#define FRM_LHV_COLWIDTH	_T("Column Width")

/************************** Forward Declarations ***************************/
/* None */

/**************************** Typedefs/Classes *****************************/

class UPersistentFrame : public CFrameWnd
{ 
    DECLARE_DYNAMIC(UPersistentFrame)
public:
     UPersistentFrame() {};
    ~UPersistentFrame() {};

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(UPersistentFrame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

protected: // create from serialization only
    //{{AFX_MSG(UPersistentFrame)
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
