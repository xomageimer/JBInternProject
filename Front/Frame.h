#ifndef JBINTERNPROJECT_FRAME_H
#define JBINTERNPROJECT_FRAME_H

#include "App.h"

#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/valgen.h>

class Frame : public wxFrame
{
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size);

public:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnInput(wxCommandEvent& event);
    void OnOut(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);
private:
    wxTextCtrl *m_txt_input;
    wxTextCtrl *m_txt_output;
    wxCheckBox *m_chkBox;

wxDECLARE_EVENT_TABLE();
};

enum { ID_BUTTON_OUT = 1, ID_BUTTON_INPUT };


#endif //JBINTERNPROJECT_FRAME_H
