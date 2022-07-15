//---------------------------------------------------------------------------

#ifndef helpH
#define helpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmHelp : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmHelp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmHelp *frmHelp;
//---------------------------------------------------------------------------
#endif
