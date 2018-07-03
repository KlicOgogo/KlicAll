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
ReadNumDlgProc  proto :DWORD, :DWORD, :DWORD, :DWORD
IDD_DLG1    equ 1000
IDC_EDT1    equ 1001
IDC_OK      equ 1002
IDC_CANCEL  equ 1003

.data
   ClassName db "MainWinClass",0
   AppName  db "Main Window",0
   x1       dd  0
   x2       dd  0

.data?
   hInstance HINSTANCE ?
   CommandLine LPSTR ?
   ps           PAINTSTRUCT <>
   hEdit   dd   ?
   ans     dd   ?
   hDC     dd   ?
   nums    dd   20  dup(?)
   numsInv  dd  20  dup(?) 
   val     dd   ?
   hbr     dd   ?
   rect     RECT     <>
   wdth     dd  ?
   hith     dd  ?
   hor      dd  ?
   max      dd  ?
   vert     dd  ?
   y2       dd  ?
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
	    invoke DeleteObject, hbr
		invoke PostQuitMessage,NULL
	.ELSEIF uMsg==WM_CREATE
	    invoke DialogBoxParam, hInstance, IDD_DLG1, NULL, addr ReadNumDlgProc, NULL
		mov ans, eax
		cmp eax, -1
		jne norm
	    invoke DestroyWindow, hWnd
	    jmp notok
norm:
        invoke CreateSolidBrush, 0FF0000h
	    mov hbr, eax
	    mov eax, ans
        xor ebx, ebx
        mov edi, 10
       _nums:
        cdq
        idiv edi
        mov nums[ebx*4], edx
        inc ebx
        cmp eax, 0
        jg _nums
        mov val, ebx
        mov ecx, val
        xor edi, edi
    inverse:
        mov eax, nums[edi*4]
        mov numsInv[ecx*4-4], eax
        inc edi        
        loop inverse
        mov ecx, val
        xor ebx, ebx
        xor edi, edi
    maxval:
        mov eax, numsInv[ebx*4]
        cmp eax, edi
        jng nogr
        mov edi, eax
        nogr:
        inc ebx
        loop maxval
        mov max, edi
notok:
    .ELSEIF uMsg==WM_PAINT
        invoke BeginPaint,hWnd,addr ps
        mov hDC, eax
        invoke GetClientRect, hWnd, addr rect
        mov eax, rect.right
        sub eax, rect.left
        mov wdth, eax
        mov eax, rect.bottom
        sub eax, rect.top
        mov hith, eax
        mov eax, wdth
        mov ebx, val
        cdq
        idiv ebx
        mov hor, eax
        mov eax, hith
        mov ebx, max
        cdq
        idiv ebx
        mov vert, eax
        invoke SelectObject, hDC, hbr
        xor ebx, ebx
        mov esi, val
     draw:
        mov eax, hor
        add x2, eax
        mov eax, numsInv[ebx*4]
        mov edi, hith
        imul edi
        cdq
        idiv max
        sub edi, eax
        mov y2, edi       
        invoke Rectangle, hDC, x1, rect.bottom, x2, y2
        mov eax, x1
        add eax, hor
        mov x1, eax
        inc ebx
        dec esi
        cmp esi, 0
        jg draw
        xor eax, eax
        mov x1, eax
        mov x2, eax
        invoke EndPaint, hWnd, addr ps
	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.ENDIF
	
	xor eax,eax
	ret
WndProc endp

ReadNumDlgProc proc hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM 
    mov eax, uMsg
    .if eax==WM_INITDIALOG
        ret
    .elseif eax==WM_COMMAND
        mov eax, wParam
        and eax,0FFFFh
        .if eax==IDC_OK
            invoke GetDlgItemInt, hDlg, IDC_EDT1, NULL, FALSE
            cmp eax, 0
            jne ye_
            invoke EndDialog, hDlg, -1
            jmp end_
           ye_:   
            mov ans, eax
            invoke EndDialog, hDlg, ans
           end_:
           ret
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

ReadNumDlgProc endp

end start
