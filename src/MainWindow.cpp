#include "MainWindow.h"
#include <wx/filedlg.h> // ?
#include <wx/msgdlg.h> // ?
#include <fstream> // for reading and writing files 
#include <string>
#include <sstream>

// unique ids for menu items 
enum {
    ID_Open = wxID_HIGHEST + 1,
    ID_Save,
    ID_BuildRun
};



MainWindow::MainWindow(const wxString& title)
    :wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(1400,900))
{

     CreateMenuBar(); // initializes menu bar
     CreateStatusBarAndNotebook(); // setup notebook(tabs) and status bar
     AddNewTab();  // start with one blank tab


     SetStatusText("Welcome to HSCode!");


     // dynamically connecting meny items to respective handlers
     Connect(ID_Open,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnOpen));
     Connect(ID_Save,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnSave));
     Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnExit));
     Connect(ID_BuildRun,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnBuildAndRun));


}


void MainWindow::CreateMenuBar(){

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
}



void MainWindow::CreateStatusBarAndNotebook(){
    // creates stock status bar 
    CreateStatusBar(); 

    // notebook with close button 

    notebook = new wxAuiNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,
        wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_CLOSE_ON_ALL_TABS);
}


void MainWindow::AddNewTab(const wxString& title){

    // create a new styled text control for code editing

    auto * editor = new wxStyledTextCtrl(notebook,wxID_ANY);

    // Add it to the notebook with given title
    notebook->AddPage(editor,title,true);
}


wxStyledTextCtrl * MainWindow::GetCurrentEditor(){

    // a notebook contains pages aka tabs or panels 
    // a page is a panel or a tab 
    // get current tab index
    
    int pageIndex = notebook->GetSelection();

    if(pageIndex == wxNOT_FOUND) return nullptr;

    // Return editor widget in the selected tab
    return dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(pageIndex));
}


void MainWindow::OnOpen(wxCommandEvent& event){

    // display file open dialog
    // search for cpp files

    wxFileDialog dlg(this, "Open File", "", "", "C++ source files (*.cpp)|*.cpp|Header files (*.h)|*.h|All files (*.*)|*.*", wxFD_OPEN);


    // if cancel button is clicked
    if(dlg.ShowModal() == wxID_CANCEL)
    {
        return;
    }



    // Reading data from file to put into editor --->

    // opening a file in input file stream-> to read from file
    std::ifstream file(dlg.GetPath().ToStdString());
    std::stringstream buffer; // make a buffer
    buffer << file.rdbuf(); // fill the buffer with file's content


    // create new tab with file name as title and set its text
    AddNewTab(dlg.GetFilename());
    GetCurrentEditor()->SetText(buffer.str());
}


void MainWindow::OnSave(wxCommandEvent& event){

    // show save-file ? dialog
    wxFileDialog dlg(this, "Save File", "", "", "C++ source files (*.cpp)|*.cpp|Header files (*.h)|*.h|All files (*.*)|*.*", 
        wxFD_SAVE| wxFD_OVERWRITE_PROMPT);


    // if cancel button clicked
    if(dlg.ShowModal() == wxID_CANCEL)
        return; // then fun is terminated

    
    // Get text from the current editor

    auto * editor = GetCurrentEditor();
    if(!editor) return; // if invalid editor then return
    
    // write contents to a new file
    std::ofstream file(dlg.GetPath().ToStdString());
    file << editor->GetText().ToStdString();


    // Update the tab title with saved file name

    notebook->SetPageText(notebook->GetSelection(),dlg.GetFilename());
    


}



void MainWindow::OnExit(wxCommandEvent& event){

    Close(true);
}


void MainWindow::OnBuildAndRun(wxCommandEvent& event){

    // message box

    wxMessageBox("Build and Run under development! :)", 
        "Notice", 
        wxOK|wxICON_INFORMATION);
}
