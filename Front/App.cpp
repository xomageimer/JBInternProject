#include "App.h"
#include "Frame.h"

#include <thread>
#include <iostream>

IMPLEMENT_APP(App)

bool App::OnInit() {
    Frame* frame = new Frame("Dictionary", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);

    return true;
}
