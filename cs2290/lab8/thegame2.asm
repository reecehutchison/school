
; reece hutchison
; cs 2290
; assignment 8

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
    left BYTE 0
    right BYTE 79
    bounces DWORD 0

.code
main PROC
    call display_info  
    
    ; start ball 
    mov dh, 8
    mov dl, pos
    call Gotoxy
    mWrite "0"

    loop_game:

        ; display bounces
        mov dl, 15
        mov dh, 6
        call Gotoxy
        mov eax, bounces
        call WriteDec

        ; quick boundriy check
        mov al, pos
        cmp al, left
        je done           ; end game if out of bounds
        cmp al, right
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
        
         ; write boundry
        mov dl, left
        call Gotoxy
        mWrite "|"
        mov dl, right
        call Gotoxy
        mWrite "|"

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
        
        ; here  <-----
        cmp dir, 0
        je pause_key

        cmp al, 'a'
        jne l_key

        ; here
        mov dh, pos
        add dh, 1
        mov left, dh
        inc bounces
        ; here

        mov dir, -1       
        jmp skip_input

        ; check for l
        l_key:

        ; here <-----
        cmp dir, 1
        je pause_key

        cmp al, 'l'
        jne pause_key

        ; here
        mov dh, pos
        sub dh, 1
        mov right, dh
        inc bounces
        ; here

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

    mov dh, 6
    mov dl, 0
    call Gotoxy
    mWrite "bounces : "

    ret
display_info ENDP

END main
