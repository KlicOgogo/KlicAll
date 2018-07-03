.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include comdlg32.inc
   include gdi32.inc
   
   includelib user32.lib
   includelib kernel32.lib
   includelib comdlg32.lib
   includelib gdi32.lib

WinMain         proto :DWORD, :DWORD, :DWORD, :DWORD
MoveWindDlgProc proto :DWORD, :DWORD, :DWORD, :DWORD 

IDR_MENU    equ 10000
IDM_OPEN    equ 10002
IDM_NEWCOLOR    equ 10003
IDM_MOVE_VERT   equ 10004
IDM_MOVE_HOR    equ 10005

IDC_LST1    equ 1001
IDD_DLG1    equ 1000
IDC_OK      equ 1002
IDC_CANCEL  equ 1003

.data
   ClassName db "MainWinClass",0
   AppName  db "Main Window",0
   moveCh0  db  "50", 0
   moveCh1  db  "100", 0
   moveCh2  db  "-50", 0
   move     dd  50, 100, -50
.data?
   hInstance HINSTANCE ?
   CommandLine LPSTR ?
   file     OPENFILENAME    <>
   color    CHOOSECOLOR     <>
   ps       PAINTSTRUCT     <>
   rect     RECT            <>
   colors   dd  16      dup(?)
   buf      db  300     dup(0)
   hbrush   dd  ? 
   hDC      dd  ?
   hList    dd  ?
   vert     dd  ?
   hor      dd  ?
   dragH    dd  ?
   dragV    dd  ?
.code


; ---------------------------------------------------------------------------


start:
	invoke GetModuleHandle, NULL
	mov    hInstance,eax
	
	invoke GetCommandLine
	mov    CommandLine,eax
	
	invoke WinMain, hInstance,NULL,CommandLine, SW_SHOWDEFAULT
	invoke ExitProcess,eax

WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	LOCAL hwnd:HWND
	
	mov   wc.cbSize,SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, OFFSET WndProc
	mov   wc.cbClsExtra,NULL
	mov   wc.cbWndExtra,NULL
	push  hInstance
	pop   wc.hInstance
	mov   wc.hbrBackground,COLOR_BTNFACE+1
	mov   wc.lpszMenuName,IDR_MENU
	mov   wc.lpszClassName,OFFSET ClassName
	
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov   wc.hIcon,eax
	mov   wc.hIconSm,eax
	
	invoke LoadCursor,NULL,IDC_ARROW
	mov   wc.hCursor,eax
	
	invoke RegisterClassEx, addr wc
	INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,\
           WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
           CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
           hInst,NULL
	mov   hwnd,eax
	
	invoke ShowWindow, hwnd,SW_SHOWNORMAL
	invoke UpdateWindow, hwnd
	
	.WHILE TRUE
		invoke GetMessage, ADDR msg,NULL,0,0
		.BREAK .IF (!eax)
		invoke TranslateMessage, ADDR msg
		invoke DispatchMessage, ADDR msg
	.ENDW
	
	mov     eax,msg.wParam
	ret
WinMain endp


WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	
	.IF uMsg==WM_DESTROY
	    invoke DeleteObject, hbrush
		invoke PostQuitMessage,NULL
	.ELSEIF uMsg==WM_COMMAND
	    mov eax, wParam
	    and eax, 0FFFFh
	    .if eax==IDM_OPEN
	    mov file.lStructSize, sizeof file    
	        mov file.lpstrFile, offset buf
	        mov file.nMaxFile, MAX_PATH
	        invoke GetOpenFileName, addr file
	        .if eax==TRUE
	            invoke SetWindowText,hWnd,file.lpstrFile
	        .endif
	    .elseif eax==IDM_NEWCOLOR
	        mov color.lStructSize, sizeof color
	        mov color.lpCustColors, offset colors
	        mov color.Flags, CC_RGBINIT or CC_PREVENTFULLOPEN
	        invoke ChooseColor,addr color
	        .if eax==TRUE
	            invoke DeleteObject,hbrush
	            invoke CreateSolidBrush,color.rgbResult
	            mov hbrush, eax
	            invoke SetClassLong, hWnd, GCL_HBRBACKGROUND, hbrush 
	            invoke InvalidateRect,hWnd,NULL,TRUE
	        .endif
	    .elseif eax==IDM_MOVE_VERT
	        invoke DialogBoxParam, hInstance, IDD_DLG1, NULL, MoveWindDlgProc, NULL
	        cmp eax, -1
	        je no
	        mov edi, eax
	        invoke GetWindowRect, hWnd, addr rect
	        mov eax, rect.right
	        sub eax, rect.left
	        mov hor, eax
	        mov eax, rect.bottom
	        sub eax, rect.top
	        mov vert, eax
	        mov eax, rect.left
	        mov dragH, eax
	        mov eax, rect.top
	        add eax, edi
	        mov dragV, eax
	        invoke MoveWindow, hWnd, dragH, dragV, hor, vert, TRUE 
	        no:
	    .elseif eax==IDM_MOVE_HOR
	        invoke DialogBoxParam, hInstance, IDD_DLG1, NULL, MoveWindDlgProc, NULL
	        cmp eax, -1
	        je noo
	        mov edi, eax
	        invoke GetWindowRect, hWnd, addr rect
	        mov eax, rect.right
	        sub eax, rect.left
	        mov hor, eax
	        mov eax, rect.bottom
	        sub eax, rect.top
	        mov vert, eax
	        mov eax, rect.top
	        mov dragV, eax
	        mov eax, rect.left
	        add eax, edi
	        mov dragH, eax
	        invoke MoveWindow, hWnd, dragH, dragV, hor, vert, TRUE
	        noo:
	   .endif
	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.ENDIF
	
	xor eax,eax
	ret
WndProc endp


MoveWindDlgProc proc    hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM 
    
    mov eax, uMsg
    .if eax==WM_INITDIALOG
        invoke GetDlgItem,hDlg,IDC_LST1
        mov hList, eax
        invoke SendMessage,hList,LB_ADDSTRING,0,addr moveCh0
        invoke SendMessage,hList,LB_ADDSTRING,0,addr moveCh1
        invoke SendMessage,hList,LB_ADDSTRING,0,addr moveCh2
        invoke SendMessage,hList,LB_SETCURSEL,0,0
        ret
    .elseif eax==WM_COMMAND
        mov eax, wParam
        and eax, 0FFFFh
        .if eax==IDC_OK
            invoke SendMessage,hList,LB_GETCURSEL,0,0
            .if eax==LB_ERR
                    invoke EndDialog,hDlg,-1
            .elseif
                    invoke EndDialog,hDlg,move[eax*4]
            .endif
        .elseif eax==IDC_CANCEL
            invoke EndDialog,hDlg,-1
        .endif
        ret
    .elseif eax==WM_CLOSE
        invoke EndDialog,hDlg,-1
        ret
    .endif
 
    xor eax, eax
    ret

MoveWindDlgProc endp

end start

            ; invoke SetBkColor, 
             ;hbmf=(HBITMAP)LoadImage((HINSTANCE)(GetWindowLong(hwnd,GWL_HINSTANCE)),szFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			; bkBrush=CreatePatternBrush(hbmf);
			; SetClassLong(hwnd,GCL_HBRBACKGROUND,(LONG)bkBrush);
			; InvalidateRect(hwnd, NULL, true);