#ifndef JBINTERNPROJECT_FRAME_H
#define JBINTERNPROJECT_FRAME_H

#include "App.h"

#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/valgen.h>

#include "../Back/ThreadPool.h"
#include "../Back/Searcher.h"

class Frame : public wxFrame
{
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size);

public:
    void OnExit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnInput(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);
private:
    wxTextCtrl *m_txt_input;
    wxTextCtrl *m_txt_output;
    wxCheckBox *m_chkBox;

    ThreadPool tp;
    std::shared_ptr<Searcher> searcher;

wxDECLARE_EVENT_TABLE();
};

enum { ID_BUTTON_INPUT = 1};


#endif //JBINTERNPROJECT_FRAME_H
