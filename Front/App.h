#ifndef JBINTERNPROJECT_APP_H
#define JBINTERNPROJECT_APP_H


#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class App : public wxApp
{
public:
    bool OnInit() override;
};

#endif //JBINTERNPROJECT_APP_H
