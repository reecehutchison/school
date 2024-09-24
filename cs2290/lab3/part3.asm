INCLUDE Irvine32.inc
TITLE Lab2part3
.data
msg_one BYTE "Math Drill - Enter three values and get the following results: ", 0
msg_two BYTE "AX + BX + CX"
msg_three BYTE "Enter for AX : ", 0
msg_four BYTE "Enter for BX : ", 0
msg_five BYTE "Enter for CX : ", 0
msg_six BYTE "AX + BX + CX = ", 0
msg_seven BYTE "Hex value = ", 0
val_a WORD 0
val_b WORD 0
val_c WORD 0
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
mov val_a, ax
mov edx, OFFSET msg_four
call WriteString
call ReadDec
mov val_b, ax
mov edx, OFFSET msg_five
call WriteString
call ReadDec
mov val_c, ax
mov ax, val_a
add ax, val_b
add ax, val_c
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
