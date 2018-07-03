.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include gdi32.inc
   include comdlg32.inc
   
   includelib user32.lib
   includelib kernel32.lib
   includelib gdi32.lib
   includelib comdlg32.lib

WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
DlgProc proto :DWORD,:DWORD,:DWORD,:DWORD 

IDD_DLG1    equ 1000
IDC_EDT1    equ 1001
IDC_OK      equ 1002
IDC_CANCEL  equ 1003


IDR_MENU    equ 10000
IDM_OPEN    equ 10002
IDM_COLOR   equ 10003
IDM_ENTER   equ 10004

.data
   ClassName db "MainWinClass",0
   AppName  db "Main Window",0
   x1       dd  0
   y1       dd  100
   letter   db  'e'

.data?
   hInstance HINSTANCE ?
   CommandLine LPSTR ?
   buf     db   300 dup(0)
   file     OPENFILENAME    <>
   color    CHOOSECOLOR     <>
   ps       PAINTSTRUCT <>
   colors  dd   16 dup(?)
   hEdit   dd   ?
   ans     dd   ?
   hDC     dd   ?
   nums    dd   20  dup(?)
   numsInv dd   20  dup(?) 
   val     dd   ?
   hbrush     dd   ?
   rect     RECT     <>
   buf1   db  300 dup(0)
   wth      dd  ?
   hth      dd  ?
   hor      dd  ?
   max      dd  ?
   vert     dd  ?
   _word    db  100 dup(0)  
   
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
		invoke PostQuitMessage,NULL
	.ELSEIF uMsg==WM_CREATE
		;
    .ELSEIF uMsg==WM_COMMAND
        mov eax, wParam
	    and eax, 0FFFFh
	    .if eax==IDM_OPEN
	        mov ecx, 300
	        xor ebx, ebx
	       clean:
	        mov buf[ebx], 0
	        inc ebx
	        loop clean
	        mov file.lStructSize, sizeof file    
	        mov file.lpstrFile, offset buf
	        mov file.nMaxFile, MAX_PATH
	        invoke GetOpenFileName, addr file
	        .if eax==TRUE
	            invoke InvalidateRect, hWnd, NULL, TRUE
	        .endif
	    .elseif eax==IDM_COLOR
	        mov color.lStructSize, sizeof color
	        mov color.lpCustColors, offset colors
	        mov color.Flags, CC_RGBINIT or CC_PREVENTFULLOPEN
	        invoke ChooseColor,addr color
	        .if eax==TRUE
	            invoke DeleteObject,hbrush
	            invoke CreateSolidBrush,color.rgbResult
	            mov hbrush, eax
	            invoke InvalidateRect,hWnd,NULL,TRUE
	        .endif
	     .elseif eax==IDM_ENTER
	         invoke DialogBoxParam, hInstance, IDD_DLG1, NULL, addr DlgProc, NULL
	         invoke InvalidateRect, hWnd, NULL, TRUE
	     .endif 
	 .ELSEIF uMsg==WM_PAINT
	     invoke BeginPaint, hWnd, addr ps
	     mov hDC, eax
	     invoke TextOut, hDC, 0, 0,addr buf, 300
	     xor ebx, ebx
	     xor esi, esi
	    cutword:
	     cmp buf[ebx], 0
	     je endd
	     cmp buf[ebx], '\'
	     je wordd 
	     mov al, buf[ebx]
	     mov _word[esi], al
	     inc ebx
	     inc esi
	     jmp cutword
	    wordd: 
	        mov _word[esi], 0
	        inc ebx
	        xor esi, esi
	        xor edi, edi
	    findlett:
	        mov dl, _word[edi]
	        cmp dl, letter
	        je yes
	        cmp _word[edi], 0
	        je no
	        inc edi
	        jmp findlett
	       yes:
	        
	        invoke TextOut, hDC, x1, y1, addr _word, 100
	        mov eax, 15
	        add y1, eax
	        no:
	        jmp cutword
	    endd:
	        mov _word[esi], 0
	        inc ebx
	        xor esi, esi
	        xor edi, edi
	    findlett1:
	        mov dl, _word[edi]
	        cmp dl, letter
	        je yes1
	        cmp _word[edi], 0
	        je no1
	        inc edi
	        jmp findlett1
	       yes1:
	        invoke TextOut, hDC, x1, y1, addr _word, 100
	        mov eax, 10
	        add y1, eax
	        no1:
	     invoke SelectObject, hDC, hbrush
	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.ENDIF
	
	xor eax,eax
	ret
WndProc endp

DlgProc proc hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM 
    mov eax, uMsg
    .if eax==WM_INITDIALOG
        ret
    .elseif eax==WM_COMMAND
        mov eax, wParam
        and eax,0FFFFh
        .if eax==IDC_OK
            invoke GetDlgItemText, hDlg, IDC_EDT1, addr buf1, 100
		    xor ebx, ebx
		    .if buf1[ebx]==0
		        invoke EndDialog, hDlg, -1
		        ret
		    .elseif
		        mov al, buf1[ebx]
		        mov letter, al
		        invoke EndDialog, hDlg, 1
                ret
             .endif
       .elseif eax==IDC_CANCEL
           invoke EndDialog, hDlg, -1
           ret
       .endif   
    .elseif eax==WM_CLOSE
           invoke EndDialog, hDlg, -1
           ret
     .endif
     xor eax, eax    
    ret
DlgProc endp

end start