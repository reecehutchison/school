INCLUDE Irvine32.inc
TITLE Lab2part1
.data
msg_one BYTE "Math Drill - Enter two values and get the following results: ", 0
msg_two BYTE "+ Addition", 0
msg_three BYTE "- Subtraction", 0
msg_four BYTE "Enter Value for X : ", 0
msg_five BYTE "Enter Value for Y : ", 0
msg_six BYTE "X = ", 0
msg_seven BYTE "Hex value = ", 0
msg_eight BYTE "         ", 0
msg_nine BYTE "Y = ", 0
msg_ten BYTE "X + Y = ", 0
msg_eleven BYTE "     ", 0
msg_twelve BYTE "X - Y = ", 0
val_y DWORD 0
val_x DWORD 0
.code
main PROC
call Clrscr
mov edx, OFFSET msg_one
call WriteString
call Crlf
call Crlf
mov edx, OFFSET msg_two
call WriteString
call Crlf
mov edx, OFFSET msg_three
call WriteString
call Crlf
call Crlf
mov edx, OFFSET msg_four
call WriteString
call ReadDec
mov val_x, eax
mov edx, OFFSET msg_five
call WriteString
call ReadDec
mov val_y, eax
call Crlf
mov edx, OFFSET msg_six
call WriteString
mov eax, val_x
call WriteDec
mov edx, OFFSET msg_eight
call WriteString
mov edx, OFFSET msg_seven
call WriteString
call WriteHex
call Crlf 
mov edx, OFFSET msg_nine
call WriteString
mov eax, val_y
call WriteDec
mov edx, OFFSET msg_eight
call WriteString
mov edx, OFFSET msg_seven
call WriteString
call WriteHex
call Crlf
call Crlf
add eax,val_x
mov edx, OFFSET msg_ten
call WriteString
call WriteDec
mov edx, OFFSET msg_eleven
call WriteString
mov edx, OFFSET msg_seven
call WriteString
call WriteHex
call Crlf
mov edx, OFFSET msg_twelve
call WriteString
mov eax, val_x
sub eax, val_y
call WriteDec
mov edx, OFFSET msg_eleven
call WriteString
mov edx, OFFSET msg_seven
call WriteString
call WriteHex




call Crlf
call Crlf
call WaitMsg
call Clrscr
exit
main ENDP
END main
