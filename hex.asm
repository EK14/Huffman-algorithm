code_seg segment
assume  cs:code_seg, ds:code_seg, es:code_seg
org 100h
begin:
	mov cx, 4  ; because 4 digits
	mov ah, 01h; enter function
	F1:	
		rcl bx, 4; cyclic sdvig 4 bitov vlevo
		int 21h
		cmp al, '9'
		jle num
		sub al, 55
		add bl, al
		jmp n1
		num:
		sub al, '0';to get a number from ascii
		add bl, al
		n1:
		loop F1
	mov ah, 02h; for printing
	mov dl, 10 ; nEW lINE
	int 21h
	mov dl, 13 ; HOME
	int 21h
	mov cx, 4
	F2:	
		mov si, cx; si - for work with strings, to change the address automatically
		sub si, 1
		mov al, bl; copy the last byte from our number
		and al, 0Fh; cmp it to the F
		cmp al, 9; again whether the number or the letter 
		jle num1
		add al, 55 ; get ascii: +55, because letters start from 65 (A = 10) 
		mov msg[si], al; create a string of digits, si - increment 
		jmp n2
		num1:
		add al, '0' 
		mov msg[si], al; create a string of digits, si - increment
		n2:
		rcr bx, 4 ; right cyclic sdvig 4 bitov
		loop F2
	mov ah, 09h ; for a string print
	mov dx, offset msg; 
	int 21h
	int 20h
msg db 5 dup('$') ; fill with 5 $, to make 4 symbols and 1 $ for string
end begin
code_seg ends