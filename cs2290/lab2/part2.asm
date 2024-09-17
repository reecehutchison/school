INCLUDE Irvine32.inc
.data
one_msg BYTE "Enter a value for EAX:", 0
two_msg BYTE "EAX=", 0
three_msg BYTE "AX=", 0
four_msg BYTE "AL=", 0
val DWORD 0
.code
main PROC
call Clrscr 
mov edx, OFFSET one_msg
call WriteString
call ReadDec
mov val, eax
call Crlf
mov edx, OFFSET two_msg
call WriteString
call WriteHexB
call Crlf
mov edx, OFFSET three_msg
call WriteString
mov ebx, 2
call WriteHexB
call Crlf
mov edx, OFFSET four_msg
call WriteString
mov ebx, 1
call WriteHexB
call Crlf
call Crlf
call WaitMsg
call Clrscr
exit
main ENDP
END main
