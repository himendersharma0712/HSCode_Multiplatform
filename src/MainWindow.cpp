#include "MainWindow.h"
#include <wx/filedlg.h> // file dialog asks which file to open or save 
#include <wx/msgdlg.h> // message dialog for a notice or a simple message with an ok button 
#include <fstream> // for reading and writing files 
#include <string>
#include <sstream>



// unique ids for menu items 
enum {
    ID_Open = wxID_HIGHEST + 1,
    ID_Save,
    ID_BuildRun,
    ID_THEME_LIGHT,
    ID_THEME_DARK
};



MainWindow::MainWindow(const wxString& title)
    :wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(1400,900))
{

     CreateMenuBar(); // initializes menu bar
     CreateStatusBarAndNotebook(); // setup notebook(tabs) and status bar
     AddNewTab();  // start with one blank tab


     SetStatusText("Welcome to HSCode!");


     // dynamically connecting menu items to respective handlers
     Connect(ID_Open,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnOpen));
     Connect(ID_Save,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnSave));
     Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnExit));
     Connect(ID_BuildRun,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnBuildAndRun));

     // View Menu functions
     Connect(ID_THEME_DARK,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnThemeDark));
     Connect(ID_THEME_LIGHT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnThemeLight));


}


void MainWindow::CreateMenuBar(){

     // --- MENU BAR --- >

    // menubar holds menus
    // menus hold menu items 

    wxMenuBar * menuBar = new wxMenuBar;

    // File Menu
    wxMenu * fileMenu = new wxMenu;

    // Adding menu items to File menu

    fileMenu->Append(ID_Open,"&Open\tCtrl+O"); // Open button
    fileMenu->Append(ID_Save,"&Save\tCtrl+S"); // Save button
    fileMenu->Append(ID_BuildRun,"&Build and Run\tCtrl+Shift+B"); // Build and Run button 
    fileMenu->AppendSeparator(); // horizontal line that separates items
    fileMenu->Append(wxID_EXIT,"&Exit\tAlt+F4"); // Exit Button 

    // View Menu
    wxMenu * viewMenu = new wxMenu;
    wxMenu * themeMenu = new wxMenu;

    // add radio buttons to theme menu
    themeMenu->AppendRadioItem(ID_THEME_DARK,"Dark");
    themeMenu->AppendRadioItem(ID_THEME_LIGHT,"Light");

    // make themeMenu a submenu of view menu
    viewMenu->AppendSubMenu(themeMenu,"Theme");
    

    // Add File menu to MenuBar
    menuBar->Append(fileMenu,"&File");
    menuBar->Append(viewMenu,"&View");
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

    // set margins to zero
    editor->SetMargins(0,0);
    editor->SetMarginWidth(0,0);


    // background color 
    editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(30, 30, 30));   // Dark gray background

    // normal text color 
    editor->StyleSetForeground(wxSTC_STYLE_DEFAULT,wxColour(220,220,220));

    // lexer fot C++
    editor->SetLexer(wxSTC_LEX_CPP);

    // Set keywords for C++
    editor->SetKeyWords(0,
        "int float double char void short long signed unsigned bool "
        "if else switch case default break continue return for while do "
        "class struct union enum typedef const static extern inline "
        "new delete try catch throw this namespace using template typename ");

    // string concatenation by adding a space in between em 

    // set remaining keywords 
    editor->SetKeyWords(1,
    "auto register asm dynamic_cast reinterpret_cast static_cast const_cast mutable explicit friend operator" 
    "typeid volatile export alignas alignof noexcept decltype concept requires co_await co_yield co_return import module"
    "public private protected virtual override final nullptr true false sizeof "
    "include define undef ifdef ifndef endif pragma ");

    // setting font
    editor->StyleSetFont(wxSTC_STYLE_DEFAULT,wxFont(12,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
    editor->StyleClearAll();
    
    // Style numbers, string, comments and keywords
    editor->StyleSetForeground(wxSTC_C_NUMBER,wxColour(0,128,0)); // green for numbers
    editor->StyleSetForeground(wxSTC_C_STRING,wxColour(255,255,51)); // for string
    editor->StyleSetForeground(wxSTC_C_COMMENT,wxColour(0,0,240)); // teal for comments
    editor->StyleSetForeground(wxSTC_C_COMMENTLINE,wxColour(0,0,240)); // for multiline comments
    editor->StyleSetForeground(wxSTC_C_WORD,wxColour(0,255,255)); // blue for keywords set 0
    editor->StyleSetForeground(wxSTC_C_WORD2,wxColour(255,0,127)); // pink for keywords set 1
    editor->StyleSetBold(wxSTC_C_WORD,true); // set bold font for set 0 
    editor->StyleSetBold(wxSTC_C_WORD,true); // set bold font for set 1



    // styling operators 
    editor->StyleSetForeground(wxSTC_C_OPERATOR,wxColour(255,140,0));
    editor->StyleSetBold(wxSTC_C_OPERATOR,true);


    

    // preprocessors highlighting
    editor->StyleSetForeground(wxSTC_C_PREPROCESSOR,wxColour(128,0,128)); // purple
    editor->StyleSetBold(wxSTC_C_PREPROCESSOR,true);


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


void MainWindow::OnThemeDark(wxCommandEvent &)
{
    ApplyTheme(false); // false = light
}


void MainWindow::OnThemeLight(wxCommandEvent&)
{
    ApplyTheme(true);
}


void MainWindow::ApplyTheme(bool darkMode){

    for(size_t i = 0; i < notebook->GetPageCount(); ++i)
    {
        // takes a ptr to a notebook page(a tab which is wxwindow* or textctrl*)
        // and casts it to wxStyledTextCtrl* dynamically
        auto * editor = dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(i));

        if(editor)
        {
            if(darkMode){
                // editor->StyleSetBackground(wxSTC_STYLE_DEFAULT,wxColour(30, 30, 30));
                // editor->StyleSetForeground(wxSTC_STYLE_DEFAULT,wxColour(220, 220, 220));
            }
            else{
                // editor->StyleSetBackground(wxSTC_STYLE_DEFAULT,*wxWHITE);
                // editor->StyleSetForeground(wxSTC_STYLE_DEFAULT,*wxBLACK);
            }

            // editor->Refresh();
        }
    }
}