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
    ID_THEME_DARK,
    ID_New,
    ID_Undo,
    ID_Redo,
    ID_Cut,
    ID_Copy,
    ID_Paste,
    ID_CloseEditor,
    ID_About,
    ID_Guide
};



MainWindow::MainWindow(const wxString& title)
    :wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(1400,900))
{

     CreateMenuBar(); // initializes menu bar
     CreateStatusBarAndNotebook(); // setup notebook(tabs) and status bar
     AddNewTab();  // start with one blank tab


     SetStatusText("Welcome to HSCode!");

    


     // dynamically connecting menu items to respective handlers

     // File Menu event bindings
     Connect(ID_Open,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnOpen));
     Connect(ID_Save,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnSave));
     Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnExit));
     Connect(ID_BuildRun,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnBuildAndRun));
     Connect(ID_New,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnNew));

     // View Menu event bindings
     Connect(ID_THEME_DARK,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnThemeDark));
     Connect(ID_THEME_LIGHT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnThemeLight));

     // Edit Menu event bindings
     Connect(ID_Undo,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnUndo));
     Connect(ID_Redo,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnRedo));
     Connect(ID_Cut,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnCut));
     Connect(ID_Copy,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnCopy));
     Connect(ID_Paste,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnPaste));


     // Close tab menu event
     Connect(ID_CloseEditor,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::CloseCurrentTab));
     

     // Close tab key down
     Connect(wxID_ANY,wxEVT_CHAR_HOOK,wxKeyEventHandler(MainWindow::OnControl_WKeyDown));
     



}


void MainWindow::CreateMenuBar(){

     // --- MENU BAR --- >

    // menubar holds menus
    // menus hold menu items 

    wxMenuBar * menuBar = new wxMenuBar;

    // File Menu
    wxMenu * fileMenu = new wxMenu;

    // Adding menu items to File menu

    fileMenu->Append(ID_New,"&New File\tCtrl+N"); // New file button 
    fileMenu->Append(ID_Open,"&Open File\tCtrl+O"); // Open button
    fileMenu->Append(ID_Save,"&Save File\tCtrl+S"); // Save button
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_BuildRun,"&Build and Run Current File\tCtrl+Shift+B"); // Build and Run button 
    fileMenu->AppendSeparator(); // horizontal line that separates items
    fileMenu->Append(ID_CloseEditor,"&Close Editor\tCtrl+W");
    fileMenu->Append(wxID_EXIT,"&Exit\tCtrl+Q"); // Exit Button 

    // View Menu
    wxMenu * viewMenu = new wxMenu;
    wxMenu * themeMenu = new wxMenu;

    // Edit Menu                    
    wxMenu * editMenu = new wxMenu;

    // Edit Menu items 
    editMenu->Append(ID_Undo,"&Undo Action\tCtrl+Z");
    editMenu->Append(ID_Redo,"&Redo Action\tCtrl+Y");
    editMenu->AppendSeparator();
    editMenu->Append(ID_Cut,"&Cut Selected\t\tCtrl+X");
    editMenu->Append(ID_Copy,"&Copy Selected\t\tCtrl+C");
    editMenu->Append(ID_Paste,"&Paste\t\tCtrl+V");


    // Help Menu
    wxMenu * helpMenu = new wxMenu;

    // Help Menu items
    helpMenu->Append(ID_Guide,"&Get Started");
    helpMenu->AppendSeparator();
    helpMenu->Append(ID_About,"&About");
    


    // add radio buttons to theme menu
    themeMenu->AppendRadioItem(ID_THEME_DARK,"Dark");
    themeMenu->AppendRadioItem(ID_THEME_LIGHT,"Light");

    // make themeMenu a submenu of view menu
    viewMenu->AppendSubMenu(themeMenu,"Theme");
    

    // Add File menu to MenuBar
    menuBar->Append(fileMenu,"&File");
    menuBar->Append(editMenu,"&Edit");
    menuBar->Append(viewMenu,"&View");
    menuBar->Append(helpMenu,"&Help");
    SetMenuBar(menuBar);
}



void MainWindow::CreateStatusBarAndNotebook(){
    // creates stock status bar 
    CreateStatusBar(); 

    // notebook with close button 

    notebook = new wxAuiNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,
        wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_CLOSE_ON_ALL_TABS);

    notebook->SetBackgroundColour(wxColour(30,30,30));
    
}


void MainWindow::AddNewTab(const wxString& title){

    // create a new styled text control for code editing

    auto * editor = new wxStyledTextCtrl(notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);

    // set margins to zero
    editor->SetMargins(5,0);

    // set all margins to zero except 0th
    editor->SetMarginWidth(1,0);
    editor->SetMarginWidth(2,0);
    editor->SetMarginWidth(3,0);
    editor->SetMarginWidth(4,0);

    // AA enabled for windows
    editor->SetUseAntiAliasing(true);


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


    // Left margin line numbers 
    editor->SetMarginType(0,wxSTC_MARGIN_NUMBER);
    editor->SetMarginWidth(0,40);

    editor->StyleSetForeground(wxSTC_STYLE_LINENUMBER,wxColour(128,128,128));
    editor->StyleSetBackground(wxSTC_STYLE_LINENUMBER,wxColour(30,30,30));

    // set background color for notebook 
    editor->GetParent()->SetBackgroundColour(wxColour(30,30,30));

    // setting caret (cursor) color 
    editor->SetCaretForeground(wxColour(255,255,255));
    editor->SetCaretWidth(2);

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

    // get current editor from notebook 
    wxStyledTextCtrl * editor = dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(notebook->GetSelection()));
    if(!editor)
    {
        wxMessageBox("No active editor found!", "Fatal error",wxICON_ERROR);
        return;
    }

    // get the code from editor
    wxString code = editor->GetText();

    // names for the code file and output file
    wxString sourceFile = "temp.cpp";

    #ifdef _WIN32
        wxString outputFile = "temp_output.exe";
    #else
        wxString outputFile = "temp_output";
    #endif


    // save the code to source file

    std::ofstream outFile(sourceFile.ToStdString()); // open the file for writing

    if(!outFile)
    {
        wxMessageBox("Unable to open file for writing!","Error",wxICON_ERROR);
        return;
    }

    outFile << code.ToStdString(); // write code to file
    outFile.close(); // flush the buffer 


    // Complie the file according to system

    /* The 2> in the command is a shell redirection operator. In Unix-like systems (and in Windows command shells that support similar syntax), file descriptors are used to represent streams:

       0 is for standard input (stdin).

       1 is for standard output (stdout).

       2 is for standard error (stderr)*/


    #ifdef _WIN32
        wxString compileCmd = "g++ temp.cpp -o temp_output.exe 2> compile_errors.txt";
        wxString runCmd = "temp_output.exe";
    #else 
        wxString compileCmd = "g++ temp.cpp -o temp_output 2> compile_errors.txt";
        wxString runCmd = "./temp_output";
    #endif


    // int system(const char *__command) => Execute the given line as a shell command
    int compileResult = std::system(compileCmd.ToStdString().c_str());

    if(compileResult == 0)
    {
        std::system(runCmd.ToStdString().c_str());

        #ifdef _WIN32
        wxString terminalCmd = "start cmd /k temp_output.exe";
        #else
        wxString terminalCmd = "gnome-terminal -- bash -c './temp_output; echo; echo Press enter to exit...; read'";
        #endif

        std::system(terminalCmd.ToStdString().c_str());
    }


    else
    {
        wxMessageBox("Compilation failed. Refer to compile_errors.txt for details.", "Build error", wxICON_ERROR);
    }

}


void MainWindow::OnThemeDark(wxCommandEvent &)
{
    ApplyTheme(true); // true = dark theme
}

void MainWindow::OnThemeLight(wxCommandEvent &)
{
    ApplyTheme(false); // false = light theme
}

void MainWindow::ApplyTheme(bool darkMode)
{
    wxMessageBox("Themes are available only for normal text editing! They break the code for code highlighting.", 
        "Warning", 
        wxOK|wxICON_INFORMATION);
    

    for (size_t i = 0; i < notebook->GetPageCount(); ++i)
    {
        // Get the i-th tab and dynamically cast to wxStyledTextCtrl*
        auto * editor = dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(i));
        if (editor)
        {
            if(darkMode)
            {
                // Set dark theme: dark background, light text
                editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(30, 30, 30));
                editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColour(220, 220, 220));
            }
            else
            {
                // Set light theme: white background, dark text
                editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, *wxWHITE);
                editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, *wxBLACK);
            }

            // Reapply the style changes to all styles using the current default:
            editor->StyleClearAll();
            // Refresh so the changes take effect immediately:
            editor->Refresh();
        }
    }
}

void MainWindow::CloseCurrentTab(wxCommandEvent &event)
{
    CloseCurrentTab();
}

void MainWindow::CloseCurrentTab()
{
    int selected = notebook->GetSelection();
    if(selected != wxNOT_FOUND)
    {
        notebook->DeletePage(selected);
    }
}

void MainWindow::OnControl_WKeyDown(wxKeyEvent &event)
{
    if(event.GetKeyCode() == 'W' && event.ControlDown())
    {
        CloseCurrentTab();
        return;
    }

    event.Skip();
}

void MainWindow::OnNew(wxCommandEvent & event)
{
    static int tabCount = 1;
    wxString tabTitle = "Untitled " + std::to_string(tabCount++);
    AddNewTab(tabTitle);
}

void MainWindow::OnUndo(wxCommandEvent &event)
{
    auto * editor = dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(notebook->GetSelection()));

    if(editor){
        editor->Undo();
    }
}

void MainWindow::OnRedo(wxCommandEvent &event)
{
    auto * editor = dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(notebook->GetSelection()));

    if(editor){
        editor->Redo();
    }
}

void MainWindow::OnCut(wxCommandEvent &event)
{
    auto * editor = dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(notebook->GetSelection()));

    if(editor){
        editor->Cut();
    }
}

void MainWindow::OnCopy(wxCommandEvent &event)
{
    auto * editor = dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(notebook->GetSelection()));

    if(editor){
        editor->Copy();
    }
}

void MainWindow::OnPaste(wxCommandEvent &event)
{
    auto * editor = dynamic_cast<wxStyledTextCtrl*>(notebook->GetPage(notebook->GetSelection()));

    if(editor){
        editor->Paste();
    }
}
