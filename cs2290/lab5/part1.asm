INCLUDE Irvine32.inc
TITLE lab5_part1

.data
	array DWORD 40 DUP(?)  ; note: the max size of the array is 99
	msg BYTE "The Fibonacci sequence for the first 40 members is as follows:", 0
	ans BYTE "Fibonacci number ", 0
	equal BYTE " = ", 0
	first BYTE "Fibonacci number 0 = 0", 0
	
.code
main PROC

	call Clrscr
	 
	mov edx, OFFSET msg
	call WriteString
	call Crlf
	call Crlf
	
	mov ecx, 38
	mov [array], 1
	mov [array+4], 1
	
	mov esi, 0 ; use esi as index counter
	
	mov edx, OFFSET first
	call WriteString
	call Crlf
	
	mov edx, OFFSET ans
	call WriteString
	mov eax, esi
	add eax, 1
	call WriteDec
	mov edx, OFFSET equal
	call WriteString
	mov eax, [array]
	call WriteDec
	inc esi
	call Crlf
	
	mov edx, OFFSET ans
	call WriteString
	mov eax, esi
	add eax, 1
	call WriteDec
	mov edx, OFFSET equal
	call WriteString
	mov eax, [array+4]
	call WriteDec
	inc esi
	call Crlf
	
	l:
		mov eax, [array+((esi*4)-4)]
		add eax, [array+((esi*4)-8)]
		mov [array+(esi*4)], eax
		mov edx, OFFSET ans
		call WriteString
		mov eax, esi
		add eax, 1
		call WriteDec
		mov edx, OFFSET equal
		call WriteString
		mov eax, [array+esi*4]
		call WriteDec
		inc esi
		call Crlf
	loop l
	
	invoke ExitProcess, 0
	
main ENDP
END main
