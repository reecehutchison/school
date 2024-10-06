INCLUDE Irvine32.inc
TITLE Lab4part2

.data
	prompt BYTE "Which Fibonacci number do you wish: ", 0
	message BYTE "Fibonacci value = ", 0
	space Byte " ", 0

.code
main PROC
	call Clrscr

	; prompt
	mov edx, OFFSET prompt
	call WriteString
	call readDec ; going into ecx, for loop counter
	mov ebx, 2
	sub eax, ebx ; this part is because first two will be printed always
	             ; also assumption is input is greater then 2
	mov ecx, eax
	call Crlf
	
	
	; setup
	mov eax, 1
	call WriteDec
	mov edx, OFFSET space
	call WriteString
	call WriteDec
	
	mov ebx, 1
	mov edx, 1
	
	loop_start: 
		
		mov eax, ebx
		add eax, edx
		
		mov edx, OFFSET space
		call WriteString
		call WriteDec
		
		mov edx, ebx
		mov ebx, eax
		
		
	loop loop_start
	
	call Crlf
	call Crlf
	
	mov edx, OFFSET message
	call WriteString
	call WriteDec
	


	call Crlf
	call Crlf
	
	
	call WaitMsg
	call Clrscr
	
	exit
	main ENDP
END main
