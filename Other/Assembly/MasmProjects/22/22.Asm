.386
.model flat,stdcall
option casemap:none

include 22.inc

.code

start:

	invoke GetModuleHandle,NULL
	mov    hInstance,eax
	invoke GetCommandLine
	invoke InitCommonControls
	mov		CommandLine,eax
	invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	invoke ExitProcess,eax

WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
	LOCAL	wc:WNDCLASSEX
	LOCAL	msg:MSG

	mov		wc.cbSize,sizeof WNDCLASSEX
	mov		wc.style,CS_HREDRAW or CS_VREDRAW
	mov		wc.lpfnWndProc,offset WndProc
	mov		wc.cbClsExtra,NULL
	mov		wc.cbWndExtra,DLGWINDOWEXTRA
	push	hInst
	pop		wc.hInstance
	mov		wc.hbrBackground,COLOR_BTNFACE+1
	mov		wc.lpszMenuName,IDM_MENU
	mov		wc.lpszClassName,offset ClassName
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov		wc.hIcon,eax
	mov		wc.hIconSm,eax
	invoke LoadCursor,NULL,IDC_ARROW
	mov		wc.hCursor,eax
	invoke RegisterClassEx,addr wc
	invoke CreateDialogParam,hInstance,IDD_DIALOG,NULL,addr WndProc,NULL
	invoke ShowWindow,hWnd,SW_SHOWNORMAL
	invoke UpdateWindow,hWnd
	.while TRUE
		invoke GetMessage,addr msg,NULL,0,0
	  .BREAK .if !eax
		invoke TranslateMessage,addr msg
		invoke DispatchMessage,addr msg
	.endw
	mov		eax,msg.wParam
	ret

WinMain endp


ReadNumber1 proc hDlg:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

    mov eax, uMsg
    .if eax==WM_INITDIALOG
        ret
    .elseif eax==WM_COMMAND
        mov eax,wParam
        and eax,0FFFFh
        .if eax==IDC_BTN3
            invoke GetDlgItemText, hDlg, IDC_EDT2, addr buf, 100
            xor ebx, ebx
            .if (buf[ebx] == 0)
                invoke EndDialog, hDlg, -1
                ret
            .endif
            invoke GetDlgItemInt, hDlg, IDC_EDT2, NULL, FALSE
            mov num1, eax
            .if num1==0
                invoke EndDialog, hDlg, -1
            .elseif
                dec num1
                invoke EndDialog, hDlg, num1
            .endif
            ret
        .elseif eax==IDC_BTN4
            invoke EndDialog, hDlg, -100
            ret
        .endif 
    .elseif eax==WM_CLOSE
        invoke EndDialog, hDlg, -100
        ret       
    .endif
    xor eax, eax
    ret
ReadNumber1 endp

ReadNumber2 proc hDlg:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

    mov eax, uMsg
    .if eax==WM_INITDIALOG
        ret
    .elseif eax==WM_COMMAND
        mov eax, wParam
        and eax,0FFFFh
        .if eax==IDC_BTN5
            invoke GetDlgItemText, hDlg, IDC_EDT3, addr buf, 100
            xor ebx, ebx
            .if (buf[ebx] == 0)
                invoke EndDialog, hDlg, -1
                ret
            .endif
            invoke GetDlgItemInt, hDlg, IDC_EDT3, NULL, FALSE
            mov num2, eax
            .if num2==0
                invoke EndDialog, hDlg, -1
            .elseif
                invoke EndDialog, hDlg, num2
            .endif
            ret
        .elseif eax==IDC_BTN6
            invoke EndDialog, hDlg, -100
            ret
        .endif 
    .elseif eax==WM_CLOSE
        invoke EndDialog, hDlg, -100
        ret       
    .endif
    xor eax, eax
    ret
ReadNumber2 endp


WndProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

	mov		eax,uMsg
	.if eax==WM_INITDIALOG
		push	hWin
		pop		hWnd
	.elseif eax==WM_COMMAND
		mov		eax,wParam
		and		eax,0FFFFh
		.if eax==IDM_FILE_EXIT
			invoke SendMessage, hWin, WM_CLOSE, 0, 0
		.elseif eax==IDM_ADD
		invoke GetDlgItemText, hWin, IDC_EDT1, addr buf, 100
		    xor ebx, ebx
		    .if buf[ebx]==0
		    .elseif
		        invoke GetDlgItem, hWin, IDC_LST1
		        mov hList, eax
		        invoke SendMessage, hList, LB_ADDSTRING, 0, addr buf
		        mov buf[ebx], 0
		        invoke SetDlgItemText, hWin, IDC_EDT1, addr buf
		    .endif
		.elseif eax==IDM_DELETE
		    invoke DialogBoxParam, hInstance, IDD_DLG1, NULL, addr ReadNumber1, NULL
		    mov num1, eax
		    cmp eax, -1
		    jne gogogo
		    invoke MessageBox, hWin, addr Err2, addr Err, 0
		    jmp finn
		   gogogo:
		    invoke GetDlgItem, hWin, IDC_LST1
		    mov hList, eax
		    invoke SendMessage, hList, LB_GETCOUNT, 0, 0
		    dec eax
		    cmp num1, eax
		    jg fin
		    invoke SendMessage, hList, LB_DELETESTRING, num1, 0
		    jmp finn
		   fin:
		    invoke MessageBox, 0, addr Err1, addr Err, 0 
		   finn:
		.elseif eax==IDC_BTN1
		    invoke DialogBoxParam, hInstance, IDD_DLG2, NULL, addr ReadNumber2, NULL
		    mov num2, eax
		    cmp eax, -1
		    jne ggo
		    invoke MessageBox, 0, addr Err2, addr Err, 0
		    jmp endd
		   ggo:
		    invoke GetDlgItem, hWin, IDC_LST1
		    mov hList, eax
		    invoke SendMessage, hList, LB_GETCOUNT, 0, 0
		    dec eax
		    mov esi, eax
		   gogo:
		    invoke SendMessage, hList, LB_GETTEXTLEN, esi, 0
		    cmp eax, num2
		    je gogo1
		    dec esi
		    cmp esi, 0
		    jnl gogo
		    jl endd
		   gogo1:
		    invoke SendMessage, hList, LB_DELETESTRING, esi, 0
		    dec esi
		    cmp esi, 0
		    jnl gogo
		   endd:
		.elseif eax==IDM_HELP_ABOUT
			invoke ShellAbout,hWin,addr AppName,addr AboutMsg,NULL
		.endif
;	.elseif eax==WM_SIZE
	.elseif eax==WM_CLOSE
		invoke DestroyWindow,hWin
	.elseif uMsg==WM_DESTROY
		invoke PostQuitMessage,NULL
	.else
		invoke DefWindowProc,hWin,uMsg,wParam,lParam
		ret
	.endif
	xor eax, eax
	ret

WndProc endp

end start
