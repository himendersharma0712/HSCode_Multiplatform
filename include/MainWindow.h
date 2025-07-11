#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <wx/stc/stc.h> // styled text control
#include <wx/aui/aui.h> // AUI(Advanced User Interface) for notebook tabs

class MainWindow : public wxFrame
{

    public:

    MainWindow(const wxString & title);

    private:


    // status bar 
    wxStatusBar * statusBar;

    // Pointer to a tabbed notebook (each tab will have an editor)
    wxAuiNotebook * notebook;


    // HomePage when >> all tabs are closed 
    wxPanel* HomePage;
    void CreateHomePage();
    void UpdateHomePageVisibility();

    // UI Functions---->

    // creates the menu bar and items
    void CreateMenuBar();

    // creates the status bar at the bottom and notebook
    void CreateStatusBarAndNotebook();

    // creates a new tab
    void AddNewTab(const wxString& title = "Untitled");

    wxStyledTextCtrl * GetCurrentEditor();  // Returns editor in current tab


    // some functions like open, save, exit and "Build and Run"

    void OnNew(wxCommandEvent & event);
    void OnOpen(wxCommandEvent & event);
    void OnSave(wxCommandEvent & event);
    void OnExit(wxCommandEvent & event);
    void OnBuildAndRun(wxCommandEvent & event);

    // view menu function declarations
    void OnThemeLight(wxCommandEvent& event);
    void OnThemeDark(wxCommandEvent& event);

    // edit menu function declarations
    void OnUndo(wxCommandEvent & event);
    void OnRedo(wxCommandEvent & event);
    void OnCut(wxCommandEvent & event);
    void OnCopy(wxCommandEvent & event);
    void OnPaste(wxCommandEvent & event);

    // apply theme
    void ApplyTheme(bool darkMode);

    // tabs or editors
    void CloseCurrentTab(wxCommandEvent & event);

    // to resolve conflicts
    void CloseCurrentTab();

    // Close Editor event
    void OnControl_WKeyDown(wxKeyEvent & event);


    // About
    void OnAbout(wxCommandEvent & event);

    // Get started
    void OnGetStarted(wxCommandEvent & event);



};



#endif