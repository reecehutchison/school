
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
    left BYTE 1
    right BYTE 79
    bounces DWORD 0
    menu_loc BYTE 3
    points DWORD 300

.code
main PROC
    
call select_diff

call display_info  

    ; start ball 
    mov dh, 8
    mov dl, pos
    call Gotoxy
    mWrite "0"

    loop_game:

        ; check win 
        mov eax, bounces
        cmp eax, 10
        je win


        ; display bounces
        mov dl, 31
        mov dh, 6
        call Gotoxy
        mov eax, bounces
        call WriteDec
        
        ; display points
        mov dl, 60
        mov dh, 6
        call Gotoxy
        mWrite "                  "
        mov dl, 60
        mov dh, 6
        call Gotoxy
        mov eax, 0
        mov eax, points
        call WriteInt

        ; quick boundry check
        mov al, pos
        cmp al, left
        je done ; end game if out of bounds
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
        cmp dir, -1
        je l_key

        cmp al, 'a'
        jne l_key
 
        mov dh, pos
        add dh, 1

        ; points here <-----
        movzx eax, right
        movzx ebx, pos
        sub eax, ebx
        sub points, eax

        mov left, dh
        inc bounces

        mov dir, -1       
        jmp skip_input

        ; check for l
        l_key:

        
        cmp dir, 1
        je pause_key

        cmp al, 'l'
        jne pause_key

        mov dh, pos
        sub dh, 1

        ; points here <-----
        movzx eax, pos
        movzx ebx, left
        sub eax, ebx
        add points, eax
        

        mov right, dh
        inc bounces

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
        mWrite "GAME IS OVER, THANKS FOR PLAYING THE GAME!!!!"
        exit

    win: 

        mov dl, 31
        mov dh, 6
        call Gotoxy
        mov eax, 10
        call WriteDec

        mov dh, 10
        mov dl, 0
        call Gotoxy
        mWrite "YOU WON, THANKS FOR PLAYING THE GAME!!!!"
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
    mov dl, 20
    call Gotoxy
    mWrite "bounces : "

    mov dh, 6
    mov dl, 50
    call Gotoxy
    mWrite "points : "

    ret
display_info ENDP

select_diff PROC

    ; ah = 48h (up key)
    ; ah = 50h (down key)
    ; ah = 1Ch (enter key)
        
    mov dl, 15
    mov dh, 0
    call Gotoxy
    mWriteLn "--- Select Difficulty ---"
    mov dl, 0
    mov dh, 1
    call Gotoxy
    mWriteLn "Use up and down arrow to navigate, and enter to select."

    mov dl, 5
    mov dh, 3
    call Gotoxy
    mWriteLn "Easy"

    mov dl, 5
    mov dh, 4
    call Gotoxy
    mWriteLn "Medium"

    mov dl, 5
    mov dh, 5
    call Gotoxy
    mWriteLn "Hard"

    mov dl, 1
    mov dh, menu_loc
    call Gotoxy
    mWrite ">"
    
    mov  eax,50         
    call Delay          

    call ReadKey  
    
    loop1:       

    ; read input
        input:

        mov  eax,50          
        call Delay 

        call ReadKey      

        ; exit game
        cmp al, VK_ESCAPE
        je exit_game  

        ; up arrow ... ah = 48h (up key)
        up_arrow:
        cmp ah, 48h
        jne down_arrow
        cmp menu_loc, 3
        je down_arrow
        mov dh, menu_loc
        mov dl, 0
        call Gotoxy
        mWrite "   "
        dec menu_loc
        mov dl, 1
        mov dh, menu_loc
        call Gotoxy
        mWrite ">"

        ; down arrow ... ah = 50h (down key)
        down_arrow:
        cmp ah, 50h
        jne enter_key
        cmp menu_loc, 5
        je enter_key
        mov dh, menu_loc
        mov dl, 0
        call Gotoxy
        mWrite "   "
        inc menu_loc
        mov dl, 1
        mov dh, menu_loc
        call Gotoxy
        mWrite ">"
        
        ; enter ... ah = 1Ch
        enter_key: 
        cmp ah, 1Ch
        jne skip

        call Clrscr

        diff_easy:
        cmp menu_loc, 3
        jne diff_med
        mov eax, speed
        imul eax, 3
        mov speed, eax
        jmp done

        diff_med:
        cmp menu_loc, 4
        jne diff_hard
        mov eax, speed
        imul eax, 2
        mov speed, eax
        jmp done

        diff_hard:
        mov eax, speed
        imul eax, 1
        mov speed, eax
        jmp done


    skip:
    jmp loop1

    exit_game:
        exit

    done:


    ret
select_diff ENDP

END main
