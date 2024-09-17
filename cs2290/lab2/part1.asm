INCLUDE Irvine32.inc
.data
one_msg BYTE "Enter Value for X:", 0
two_msg BYTE "Enter Value for Y:", 0
three_msg BYTE "X=", 0
four_msg BYTE "Y=", 0
five_msg BYTE "Hex X=", 0
six_msg BYTE "Hex Y=", 0
seven_msg BYTE "Binary X=", 0
eight_msg BYTE "Binary Y=", 0
val_y DWORD 0
val_x DWORD 0
.code
main PROC
call Clrscr
mov edx, OFFSET one_msg
call WriteString
call ReadDec
mov val_x, eax
mov edx, OFFSET two_msg
call WriteString
call ReadDec
mov val_y, eax
call Crlf
mov edx, OFFSET three_msg
call WriteString
mov eax, val_x
call WriteDec
call Crlf
mov edx, OFFSET four_msg
call WriteString
mov eax, val_y
call WriteDec
call Crlf
call Crlf
mov eax, val_x
mov edx, OFFSET five_msg
call WriteString
call WriteHex
call Crlf
mov eax, val_y
mov edx, OFFSET six_msg
call WriteString
call WriteHex
call Crlf
call Crlf
mov eax, val_x
mov edx, OFFSET seven_msg
call WriteString
call WriteBin
call Crlf
mov eax, val_y
mov edx, OFFSET seven_msg
call WriteString
call WriteBin
call Crlf
call Crlf
call WaitMsg
call Clrscr
exit
main ENDP
END main
