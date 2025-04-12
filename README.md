# OOPS_Project
*a GUI program built using wxWidgets*


HSCode IDE Development Log
==========================

Date: 2025-04-12

Summary:
--------
This document tracks the development of the HSCode IDE, focusing on integrating build and run functionality for both Windows and Linux platforms, syntax highlighting, editor customization, and user interface enhancements using wxWidgets and wxStyledTextCtrl.

Progress Log:
-------------
1. Integrated `wxStyledTextCtrl` for syntax highlighting.
   - Set dark theme background and custom colors for keywords, strings, comments, numbers, etc.
   - Used SetLexer(wxSTC_LEX_CPP) for C++ code parsing.
   - Implemented keyword sets (SetKeyWords 0 and 1).
   - Configured line numbers and caret customization.

2. Created logic for "Build and Run" functionality.
   - Extracted current editor text and wrote it to temp.cpp.
   - Used `std::ofstream` to write file contents.
   - Platform-specific handling:
     - On Windows: `g++ temp.cpp -o temp_output.exe 2> compile_errors.txt`
     - On Linux: `g++ temp.cpp -o temp_output 2> compile_errors.txt`
   - On successful compilation, executed the output binary.

3. Handled runtime terminal issues:
   - On Linux Mint Cinnamon, used `x-terminal-emulator -e ./temp_output` to launch the output in a new terminal window.
   - Verified functionality on Linux.
   - Testing confirmed working execution behavior across platforms.

4. UI Enhancements:
   - Added edit menu with full functionality (cut, copy, paste, undo, redo).
   - Added "New File" and "Close Tab" functionality.
   - Implemented keyboard shortcut for closing tabs (Ctrl+W) using key event handling.
   - Introduced static counter for untitled files.
   - Developed homepage panel (formerly "void panel") to display when no tabs are open.

5. General Improvements:
   - Menu bar and status bar fully implemented.
   - Working tab system with the ability to add new editors dynamically.
   - Display versioning and future placeholder for about info.
   - Verified and minimized app size (598 KB binary).
   
Next Steps:
-----------
- Implement a sidebar for file directory navigation with toggle visibility button in the status bar.
- Refine execution handling on Windows.
- Provide clear compiler error output to users via interface.
- Clean temp files post execution.
- Polish UI/UX with icon, logo, theme switching, and optional Gemini API integration.

Notes:
------
- Redirection `2>` used to capture compile-time errors.
- Execution method uses `std::system()` for shell commands.
- IDE functions as a lightweight and fast C++ development environment.


