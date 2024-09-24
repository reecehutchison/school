INCLUDE Irvine32.inc
TITLE Lab2part2
.data
msg_one BYTE "Math Drill - Enter three values and get the following results: ", 0
msg_two BYTE "EAX + EBX + ECX"
msg_three BYTE "Enter for EAX : ", 0
msg_four BYTE "Enter for EBX : ", 0
msg_five BYTE "Enter for ECX : ", 0
msg_six BYTE "EAX + EBX + ECX = ", 0
msg_seven BYTE "Hex value = ", 0
.code
main PROC
call Clrscr
mov edx, OFFSET msg_one
call WriteString
call Crlf
mov edx, OFFSET msg_two
call WriteString
call Crlf
call Crlf
mov edx, OFFSET msg_three
call WriteString
call ReadDec
mov ebx, eax
mov edx, OFFSET msg_four
call WriteString
call ReadDec
mov ecx, eax
mov edx, OFFSET msg_five
call WriteString
call ReadDec
add eax, ebx
add eax, ecx
call Crlf
mov edx, OFFSET msg_six
call WriteString
call WriteDec
mov edx, OFFSET msg_seven
call Crlf
call WriteString
call WriteHex
call Crlf
call Crlf
call WaitMsg
call Clrscr
exit
main ENDP
END main
