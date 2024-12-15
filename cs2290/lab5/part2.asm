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
	
	mov edx, OFFSET first
	call WriteString
	call Crlf
	
	mov ecx, 38
	mov esi, OFFSET array   ; esi is pointer to array adress
	mov ebx, 1      ; ebx is counter this time
	
	mov DWORD PTR [esi], 1
	mov edx, OFFSET ans
	call WriteString
	mov eax, ebx
	call WriteDec
	mov edx, OFFSET equal
	call WriteString
	mov eax, [esi]
	call WriteDec
	inc ebx
	call Crlf
	
	add esi, 4
	mov DWORD PTR [esi], 1
	mov edx, OFFSET ans
	call WriteString
	mov eax, ebx
	call WriteDec
	mov edx, OFFSET equal
	call WriteString
	mov eax, [esi]
	call WriteDec
	inc ebx
	call Crlf
	
	l:
		sub esi, 4
		mov eax, [esi]
		add esi, 4
		add eax, [esi]
		add esi, 4
		mov DWORD PTR [esi], eax
		mov edx, OFFSET ans
		call WriteString
		mov eax, ebx
		call WriteDec
		mov edx, OFFSET equal
		call WriteString
		mov eax, [esi]
		call WriteDec
		inc ebx
		call Crlf
	loop l
	
	call Crlf
	
	invoke ExitProcess, 0
	
main ENDP
END main
