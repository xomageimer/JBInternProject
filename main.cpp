#include <iostream>

// git submodule update --init --recursive
// C:\TDM-GCC-64\bin\mingw32-make -j4 -f makefile.gcc BUILD=release SHARED=0 UNICODE=1 setup_h
// C:\TDM-GCC-64\bin\mingw32-make -j4 -f makefile.gcc BUILD=release SHARED=0 UNICODE=1

#include <wx/wxprec.h>

#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/valgen.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class App : public wxApp
{
public:
    bool OnInit();
};

class Frame : public wxFrame
{
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);

wxDECLARE_EVENT_TABLE();
};

enum { ID_Hello = 1 };

// clang-format off
wxBEGIN_EVENT_TABLE(Frame, wxFrame)
                EVT_MENU(ID_Hello, Frame::OnHello)
                EVT_MENU(wxID_EXIT, Frame::OnExit)
                EVT_MENU(wxID_ABOUT, Frame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(App);
// clang-format on

#include <iostream>
#include <thread>

bool App::OnInit()
{
    Frame* frame = new Frame("Finder", wxPoint(50, 50), wxSize(450, 340));
    std::thread t1 ([]{
        while (true)
            std::cout << "hi\n";
    });
    t1.detach();
    frame->Show(true);

    return true;
}

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string show in status bar");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu();
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *firstNameSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *firstNameLabel = new wxStaticText(this, wxID_ANY, _("NIGGA:"));
    firstNameSizer->Add(firstNameLabel);

    firstNameSizer->Add(10, 0);

    wxTextCtrl *firstNameBox = new wxTextCtrl(this, wxID_ANY);
    firstNameSizer->Add(firstNameBox, 1);

    mainSizer->Add(firstNameSizer, 0, wxEXPAND | wxALL, 5);
    SetSizer(mainSizer);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}

void Frame::OnExit(wxCommandEvent& event) { Close(true); }

void Frame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets' Hello world example", "About Hello World",
                 wxOK | wxICON_INFORMATION);
}

void Frame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello World from wxWidgets!");
}