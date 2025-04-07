# OOPS_Project
a GUI program built using wxWidgets 


HSCode IDE - Version 1.0.3 (WIP)

Core Features Implemented:

1. Main Window:

wxFrame-based main window (MainWindow class).

Window size set to 1400x900.



2. Menu Bar:

File Menu:

Open (Ctrl+O)

Save (Ctrl+S)

Build and Run (Ctrl+Shift+B)

Exit (Alt+F4)


View Menu:

Theme submenu with two radio items:

Dark Theme

Light Theme





3. Status Bar and Notebook:

Default status bar created.

wxAuiNotebook used for managing editor tabs.

Tabs support close buttons.



4. Tab & Editor Management:

Each tab contains a wxStyledTextCtrl as the code editor.

Editor uses C++ lexer and syntax highlighting.

Keywords, comments, numbers, strings, operators, and preprocessors are color-coded.

Fonts and colors are customizable.



5. File Operations:

Open:

Displays a file dialog.

Opens .cpp, .h, or any file.

Loads content into a new tab.


Save:

Displays save file dialog.

Saves current tab's content.

Updates tab title to filename.




6. Build and Run:

Currently shows a message box saying "under development".



7. Theme Support (Partially Implemented):

Theme switching via ApplyTheme(bool darkMode) method.

Uses StyleSetBackground and StyleSetForeground.

However, currently commented out (temporarily inactive as of latest update).




Notes:

Theme switching buttons exist but are non-functional until re-enabled.

Syntax highlighting, tab system, and file I/O are all functional.

Build system and advanced editing features to be added in future versions.


Next Steps:

Re-enable and polish theme switching.

Implement a real build and run system.

Add settings and tab persistence.

Improve UI with custom icons or layouts.


End of HSCode IDE v1.0.3 documentation.
