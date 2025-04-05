#include "MainWindow.h"
#include <wx/filedlg.h> // ?
#include <wx/msgdlg.h> // ?
#include <fstream> // for reading and writing files 
#include <string>

// unique ids for menu items 
enum {
    ID_Open = wxID_HIGHEST + 1,
    ID_Save,
    ID_BuildRun
};



MainWindow::MainWindow(const wxString& title)
    :wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(1400,900))
{


    // --- MENU BAR --- >

    // menubar holds menus
    // menus hold menu items 

    wxMenuBar * menuBar = new wxMenuBar;
    wxMenu * fileMenu = new wxMenu;

    // Adding menu items to File menu

    fileMenu->Append(ID_Open,"&Open\tCtrl+O"); // Open button
    fileMenu->Append(ID_Save,"&Save\tCtrl+S"); // Save button
    fileMenu->Append(ID_BuildRun,"&Build and Run\tCtrl+Shift+B"); // Build and Run button 
    fileMenu->AppendSeparator(); // horizontal line that separates items
    fileMenu->Append(wxID_EXIT,"&Exit\tAlt+F4"); // Exit Button 


    // Add File menu to MenuBar
    menuBar->Append(fileMenu,"&File");
    SetMenuBar(menuBar);


    // TEXT SPACE FOR WRITING CODE ----->

    // creating a style text control (styled as in can support highlighting n stuff)
    editor = new wxStyledTextCtrl(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE|wxTE_RICH2|wxHSCROLL);


    // Create status bar at the bottom of the window
    CreateStatusBar();
    SetStatusText("Welcome To Harland's IDE");

    // Dynamic Event Binding

    // Binding menu items to handler methods
    // to handle wt to do when a button is clicked

    // we provide pointers to the functions(references)
    Bind(wxEVT_MENU,&MainWindow::OnOpen,this, ID_Open);
    Bind(wxEVT_MENU,&MainWindow::OnSave,this, ID_Save);
    Bind(wxEVT_MENU,&MainWindow::OnBuildAndRun,this, ID_BuildRun);
    Bind(wxEVT_MENU,&MainWindow::OnExit, this, wxID_EXIT);

}


void MainWindow::OnOpen(wxCommandEvent& event){

    // display file open dialog
    // search for cpp files

    wxFileDialog dlg(this, "Open File", "","","C++ files (*.cpp;*.h)|All files (*.*)|*.*",wxFD_OPEN);

    // if cancel button is clicked
    if(dlg.ShowModal() == wxID_CANCEL)
    {
        return;
    }



    // Reading data from file to put into editor --->

    // opening a file in input file stream-> to read from file
    std::ifstream file(dlg.GetPath().ToStdString());

    if(file)
    {
        // Template class istreambuf_iterator
        // Provides input iterator semantics for streambuf
        std::string content ((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // Write the content read from file to the text area 
        editor->SetText(content);
    }
}


void MainWindow::OnSave(wxCommandEvent& event){

    // show save-file ? dialog
    wxFileDialog dlg(this, "Save File", "", "", "C++ files (*.cpp;*.h)|*.cpp;*.h|All files (*.*)|*.*", wxFD_SAVE| wxFD_OVERWRITE_PROMPT);


    // if cancel button clicked
    if(dlg.ShowModal() == wxID_CANCEL)
        return; // then fun is terminated
    
    // write contents to a new file
    std::ofstream file(dlg.GetPath().ToStdString());
    
    // if file is valid then lets write it
    if(file)
    {
        file << editor->GetText().ToStdString(); // writing to the file
    }


}



void MainWindow::OnExit(wxCommandEvent& event){

    Close(true);
}


void MainWindow::OnBuildAndRun(wxCommandEvent& event){

    // message box

    wxMessageBox("Build and Run under development! :)", 
        "Stay Updated!", 
        wxOK|wxICON_INFORMATION);
}