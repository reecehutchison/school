INCLUDE Irvine32.inc
TITLE Lab4part1_2
.data
smile BYTE "(: ", 0
row BYTE 0
col BYTE 0


.code
main PROC
call Clrscr

mov ecx, 100  ; for loop counter
mov eax, 100  ; for delay 


loop_start:
	call Clrscr
	
	mov dh, row
	mov dl, col
	call Gotoxy
	
	mov edx, OFFSET smile
	call WriteString
	call Delay
	
	inc col
	
	
	loop loop_start
	
	
call Crlf
call Crlf


call WaitMsg
call Clrscr
exit
main ENDP
END main
