//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TListBox *ListBox1;
    TPanel *Panel2;
    TLabel *Label2;
    TLabel *lblRecent;
    TLabel *Label3;
    TLabel *Label1;
    TLabel *Label5;
    TButton *cmdOpen;
    TButton *cmdCancel;
    void __fastcall cmdOpenClick(TObject *Sender);
    void __fastcall cmdCancelClick(TObject *Sender);
    void __fastcall ListBox1Click(TObject *Sender);
    void __fastcall ListBox1DblClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ListBox1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
    void __fastcall PopulateListbox( void );
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
