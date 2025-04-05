#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <wx/stc/stc.h> // styled text control

class MainWindow : public wxFrame
{

    public:

    MainWindow(const wxString & title);

    private:

    // some functions like open, save, exit and "Build and Run"
    void OnOpen(wxCommandEvent & event);
    void OnSave(wxCommandEvent & event);
    void OnExit(wxCommandEvent & event);
    void OnBuildAndRun(wxCommandEvent & event);

    wxStyledTextCtrl * editor;  // typing area for text


};



#endif