INCLUDE Irvine32.inc
TITLE Lab4part1_1
.data
smile BYTE "(: ", 0


.code
main PROC
call Clrscr

mov edx, OFFSET smile
mov ecx, 40  ; ecx is loop counter register
mov eax, 50

; loop syntax 
loop_start: 
	call WriteString
	call Delay
	loop loop_start
	
call Crlf
call Crlf


call WaitMsg
call Clrscr
exit
main ENDP
END main
