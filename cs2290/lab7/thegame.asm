
; reece hutchison
; cs 2290
; assignment 7

; note: a = 61h
;       l = 6Ch
;     ' ' = 20h

INCLUDE Irvine32.inc
INCLUDE Macros.inc

.data
    pos BYTE 40        
    paused BYTE 0      ; 0 is NOT paused, 1 is paused
    dir BYTE 1         ; 1 is right, -1 is left
    speed DWORD 100

.code
main PROC
    call display_info  
    
    ; start ball 
    mov dh, 8
    mov dl, pos
    call Gotoxy
    mWrite "0"

    loop_game:
        
        ; quick boundriy check
        mov al, pos
        cmp al, 0
        je done           ; end game if pos is 0 or 79
        cmp al, 79
        je done           

        ; check for puased
        cmp paused, 1
        je input

        ; change ball dir
        update:
        mov bl, dir
        add pos, bl       

        ; erase old ball
        mov dl, pos
        sub dl, bl        
        mov dh, 8
        call Gotoxy
        mWrite " "        

        ; show the ball
        mov dl, pos       
        call Gotoxy
        mWrite "0"        

        ; add little delay
        mov eax, speed 
        call Delay
       
        ; read input
        input:
        call ReadKey      

        ; cherck for esc key
        cmp al, VK_ESCAPE
        je done          

        ; check for a
        cmp al, 'a'
        jne l_key
        mov dir, -1       
        jmp skip_input

        ; check for l
        l_key:
        cmp al, 'l'
        jne pause_key
        mov dir, 1        
        jmp skip_input

        ; check for space
        pause_key:
        cmp al, ' '
        jne skip_input
        xor paused, 1     ; switches to 1 if 0, and vice verse (xor)
        skip_input:


        jmp loop_game     

    done:
        mov dh, 10
        mov dl, 0
        call Gotoxy
        mWrite "GAME IS OVER THANKS FOR PLAYING THE GAME!!!!"

        exit
main ENDP

; show options at top of screen for player
display_info PROC
    mov dh, 0
    mov dl, 0
    call Gotoxy
    mWrite "--- THE GAME ---"
    
    mov dh, 1
    mov dl, 0
    call Gotoxy
    mWrite "'esc' key   : quit game"

    mov dh, 2
    call Gotoxy
    mWrite "'a' key     : move ball left"

    mov dh, 3
    call Gotoxy
    mWrite "'l' key     : move ball right"

    mov dh, 4
    call Gotoxy
    mWrite "'space' key : pause/resume game"

    ret
display_info ENDP

END main
