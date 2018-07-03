include windows.inc
include user32.inc
include kernel32.inc
include shell32.inc
include comctl32.inc
include comdlg32.inc

includelib user32.lib
includelib kernel32.lib
includelib shell32.lib
includelib comctl32.lib
includelib comdlg32.lib

WinMain				PROTO :DWORD,:DWORD,:DWORD,:DWORD
WndProc				PROTO :DWORD,:DWORD,:DWORD,:DWORD

IDD_DIALOG			equ 1000
IDC_EDT1            equ 1001
IDC_LST1            equ 1002
IDC_BTN1            equ 1003
IDC_EDT2            equ 1004
IDD_DLG1            equ 1005
IDC_BTN3            equ 1006
IDC_BTN4            equ 1007
IDD_DLG2            equ 1010
IDC_EDT3            equ 1011
IDC_BTN5            equ 1012
IDC_BTN6            equ 1013
IDM_MENU			equ 10000
IDM_FILE_EXIT		equ 10001
IDM_ADD             equ 10002
IDM_DELETE          equ 10003
IDM_HELP_ABOUT		equ 10101

.const

ClassName			db 'DLGCLASS',0
AppName				db 'Dialog as main',0
AboutMsg			db 'MASM32 RadASM Dialog as main',13,10,'Copyright © MASM32 2001',0
Err                 db  "Ooops...", 0
Err1                db  "You are trying to delete the string which doesn't exist", 0
Err2                db  "Please, enter correctly", 0

.data?

hInstance			dd  ?
CommandLine			dd  ?
hWnd				dd  ?
hEdit               dd  ?
hList               dd  ?
num1                dd  ?
num2                dd  ?
buf                 db  100 dup(?)