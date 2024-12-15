
INCLUDE Irvine32.inc

.data
	sequence BYTE 2,5,9,11,23,41,57,68,71,82,85
	seq_len DWORD LENGTHOF sequence
	seq_type DWORD TYPE sequence
	msg1 BYTE "The array is as follows: ", 0
	msg2 BYTE " ", 0
	msg3 BYTE "The array after the change: ", 0
	msg4 BYTE "Which location do you wish to change: "
	msg5 BYTE "location", 0
	msg6 BYTE "=", 0

.code
main proc
	
	mov edx, OFFSET msg1
	call WriteString
	call Crlf

	; prints first sequence
	mov esi, 0
	mov ecx, seq_len
	mov ebx, seq_type
	call print_seq
	call Crlf
	call Crlf

	mov edx, OFFSET msg4
	call WriteString
	call ReadDec
	call Crlf


	; shift routine
	mov esi, eax
	mov ecx, seq_len
	mov ebx, seq_type
	call shift_routine

	mov edx, OFFSET msg3
	call WriteString
	call Crlf

	; prints result sequence
	mov esi, OFFSET [sequence+eax]
	mov ecx, seq_len
	mov ebx, seq_type
	call print_seq

	call Crlf

	exit
main endp

; print_seq
; goal           --> print the sequence
; parameters     --> esi=0
;                    ecx=loop counter / size of array
;					 ebx=type of sequence
; postconditions --> the sequence will be printed
; preconditions  --> none
print_seq PROC
	l1: mov edi, 0
	mov edx, OFFSET msg5
	call WriteString
	mov edx, OFFSET msg2
	call WriteString
	mov eax, edi
	call WriteDec
	mov edx, OFFSET msg2
	call WriteString
	mov edx, OFFSET msg6
	call WriteString
	mov edx, OFFSET msg2
	call WriteString
	movzx eax, sequence[esi]
	call WriteDec
	mov edx, OFFSET msg2
	call WriteString
	add esi, ebx
	call Crlf

	loop l1
	
	
	ret
print_seq ENDP

; shift_routine
; goal           --> shift the values to the right from the specified value
; parameters     --> esi=position to start at
;					 ecx=size of arr / loop counter (make sure to subtract esi)
;					 ebx=type of sequence
; postconditions --> the sequence will be shifted to the right by 1 starting at the specified position
; preconditions  --> none
shift_routine PROC

	push esi
	sub ecx, esi
	dec ecx
	

	mov al, [esi]

	l1: add esi, ebx
	mov dl, [esi]
	mov [esi], al
	mov al, dl

	loop l1

	pop esi
	mov sequence[esi], 0 
	


	ret
shift_routine ENDP

end main
