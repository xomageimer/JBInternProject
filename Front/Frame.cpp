#include "Frame.h"

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
                EVT_MENU(wxID_EXIT, Frame::OnExit)
                EVT_MENU(wxID_ABOUT, Frame::OnAbout)
                EVT_BUTTON(ID_BUTTON_INPUT,  Frame::OnInput)
                EVT_SIZE(Frame::OnSize)
                EVT_TEXT(1, Frame::OnInput)
                EVT_CLOSE(Frame::OnClose)
wxEND_EVENT_TABLE()

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), tp(std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() - 1 : 1)
{
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu();
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    int bar_tmp[2];
    bar_tmp[0] = -1;
    bar_tmp[1] = 250;
    CreateStatusBar(2);
    SetStatusWidths(2, bar_tmp);
    SetStatusText(_T("Ready!"), 0);
    bar_tmp[0] = wxSB_FLAT;
    bar_tmp[1] = wxSB_NORMAL;
    wxStatusBar *barStatus = GetStatusBar();
    m_chkBox = new wxCheckBox(barStatus, wxID_ANY, _T("Search by consecutive characters"));

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *InputSizer = new wxBoxSizer(wxHORIZONTAL);

    m_txt_input= new wxTextCtrl(this, 1);
    InputSizer->Add(m_txt_input, 1);

 //  InputSizer->Add(10, 0);

 //   wxButton *butSearch = new wxButton(this, ID_BUTTON_INPUT, _T("Search"));

 //   InputSizer->Add(butSearch, 0, wxALL | wxALIGN_LEFT, 1);

    mainSizer->Add(InputSizer, 0, wxEXPAND | wxALL, 5);

    m_txt_output = new wxTextCtrl(this, wxID_ANY, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

    mainSizer->Add(m_txt_output, 1,  wxEXPAND | wxLEFT | wxTOP | wxRIGHT | wxBOTTOM, 5);

    SetSizer(mainSizer);

    searcher = std::make_shared<Searcher>("words.txt", m_txt_output, GetStatusBar());
}

void Frame::OnSize(wxSizeEvent &event) {
    wxRect rect;
    wxStatusBar *barStatus = GetStatusBar();
    event.Skip();
    if(NULL == barStatus)
        return;
    barStatus->GetFieldRect(1, rect);
    m_chkBox->SetSize(rect.x + 5, rect.y + 2, rect.width - 4, rect.height - 4);
}

void Frame::OnExit(wxCommandEvent& event)
{
    searcher->BrokeIt();
    tp.Reset();
    tp.AddTask([this] {
        while (tp.WorkersCount() != 1) {
            std::this_thread::yield();
        }
        Close(true);
    });
}

void Frame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is an application for searching for words that contain a string entered by the user", "About Dictionary",
                 wxOK | wxICON_INFORMATION);
}

void Frame::OnInput(wxCommandEvent &event) {
    //std::cout << "call" << std::endl;
    searcher->BrokeIt();
    tp.Reset();
    if (!m_txt_output->IsEmpty())
        m_txt_output->Clear();

    std::string word = m_txt_input->GetValue().ToStdString();
    if (word.empty())
        return;

    std::shared_ptr<SearchPredicate> predicate;
    if (m_chkBox->GetValue())
        predicate = std::make_shared<ConsecutiveSearch>(word);
    else
        predicate = std::make_shared<DefaultSearch>(word);

    searcher->PrepareSource(tp, predicate);
}

void Frame::OnClose(wxCloseEvent& event) {
    searcher->BrokeIt();
    tp.Reset();
    tp.AddTask([this] {
        while (tp.WorkersCount() != 1) {
            std::this_thread::yield();
        }
        Destroy();
    });
}
