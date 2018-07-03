.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include gdi32.inc
   includelib user32.lib
   includelib kernel32.lib
   includelib gdi32.lib

WinMain proto :DWORD,:DWORD,:DWORD,:DWORD


.data
   ClassName db "MainWinClass",0
   AppName  db "Main Window",0
   time     dd  0
    
.data?
   hInstance HINSTANCE ?
   CommandLine LPSTR ?
   hDC          HDC         ?
   ps           PAINTSTRUCT <>
   rect         RECT        <>
   
   hbrY     dd  2   dup(?)
   hbrG     dd  2   dup(?)
   hbrR     dd  2   dup(?)
   hpnY     dd  2   dup(?)
   hpnG     dd  2   dup(?)
   hpnR     dd  2   dup(?)
   div3     dd  ?
   _div3    dd  ?
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
	mov   wc.lpszMenuName,NULL
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
	    xor ebx, ebx
	    invoke DeleteObject, hpnR[ebx]
	    invoke DeleteObject, hpnY[ebx]
	    invoke DeleteObject, hpnG[ebx]
	    invoke DeleteObject, hbrR[ebx]
	    invoke DeleteObject, hbrY[ebx]
	    invoke DeleteObject, hbrG[ebx]
	    add ebx, 4
	    invoke DeleteObject, hpnR[ebx]
	    invoke DeleteObject, hpnY[ebx]
	    invoke DeleteObject, hpnG[ebx]
	    invoke DeleteObject, hbrR[ebx]
	    invoke DeleteObject, hbrY[ebx]
	    invoke DeleteObject, hbrG[ebx]
	    invoke KillTimer,hWnd,1
		invoke PostQuitMessage,NULL
	.ELSEIF uMsg==WM_CREATE
	    invoke MoveWindow, hWnd, 300, 100, 200, 600, TRUE
	    xor ebx, ebx
	    invoke CreatePen,PS_SOLID,0,00000FFh
		mov hpnR[ebx*4], eax
	    invoke CreateSolidBrush,00000FFh
		mov hbrR[ebx*4], eax
		invoke CreateSolidBrush,000FFFFh
		mov hbrY[ebx*4], eax
		invoke CreatePen,PS_SOLID,0,000FFFFh
		mov hpnY[ebx*4], eax
		invoke CreateSolidBrush,000FF00h
		mov hbrG[ebx*4], eax
		invoke CreatePen,PS_SOLID,0,000FF00h
		mov hpnG[ebx*4], eax
		inc ebx
		invoke CreateSolidBrush,0000080h
		mov hbrR[ebx*4], eax
		invoke CreatePen,PS_SOLID,0,0000080h
		mov hpnR[ebx*4], eax
		invoke CreateSolidBrush,000A5FFh
		mov hbrY[ebx*4], eax
		invoke CreatePen,PS_SOLID,0,000A5FFh
		mov hpnY[ebx*4], eax
		invoke CreateSolidBrush,0006600h
		mov hbrG[ebx*4], eax
		invoke CreatePen,PS_SOLID,0,0006600h
		mov hpnG[ebx*4], eax
        invoke SetTimer,hWnd,1,1000,0
    .ELSEIF uMsg==WM_TIMER
        inc time
        invoke InvalidateRect, hWnd, NULL, TRUE
    .ELSEIF uMsg==WM_PAINT
        invoke BeginPaint,hWnd,addr ps
        mov hDC, eax
        mov esi, 1 
        invoke GetClientRect, hWnd, addr rect
        invoke SelectObject, hDC, hpnR[esi*4]
        invoke SelectObject, hDC, hbrR[esi*4]
        mov eax, rect.bottom
        mov ebx, 3
        cdq
        idiv ebx
        mov div3, eax
        invoke Rectangle, hDC, rect.left, rect.top, rect.right, div3
        invoke SelectObject, hDC, hpnY[esi*4]
        invoke SelectObject, hDC, hbrY[esi*4]
        mov eax, div3
        mov ebx, 2
        imul ebx
        mov _div3, eax
        invoke Rectangle, hDC, rect.left, div3, rect.right, _div3
        invoke SelectObject, hDC, hpnG[esi*4]
        invoke SelectObject, hDC, hbrG[esi*4]
        invoke Rectangle, hDC, rect.left, _div3, rect.right, rect.bottom
        dec esi
        mov eax, time
        mov ebx, 6
        cdq
        idiv ebx
        cmp edx, 0
        je zer
        cmp edx, 1
        je one
        cmp edx, 2
        je two
        cmp edx, 3
        je fin
        cmp edx, 4
        je two
        invoke SelectObject, hDC, hpnY[esi*4]
        invoke SelectObject, hDC, hbrY[esi*4]
        invoke Rectangle, hDC, rect.left, div3, rect.right, _div3
        jmp fin
        zer:
        invoke SelectObject, hDC, hpnR[esi*4]
        invoke SelectObject, hDC, hbrR[esi*4]
        invoke Rectangle, hDC, rect.left, rect.top, rect.right, div3
        jmp fin
        one:
        invoke SelectObject, hDC, hpnY[esi*4]
        invoke SelectObject, hDC, hbrY[esi*4]
        invoke Rectangle, hDC, rect.left, div3, rect.right, _div3
        invoke SelectObject, hDC, hpnR[esi*4]
        invoke SelectObject, hDC, hbrR[esi*4]
        invoke Rectangle, hDC, rect.left, rect.top, rect.right, div3
        jmp fin
        two:
        invoke SelectObject, hDC, hpnG[esi*4]
        invoke SelectObject, hDC, hbrG[esi*4]
        invoke Rectangle, hDC, rect.left, _div3, rect.right, rect.bottom
        fin:
        invoke EndPaint,hDC,addr ps     
	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.ENDIF

	xor eax,eax
	ret
WndProc endp


end start
