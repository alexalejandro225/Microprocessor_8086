.model tiny

   ;----- Insert INCLUDE "filename" directives here
   ;----- Insert EQU and = equates here
   
   locals
   
.data
      
      msgGet 	DB  'Introduce the secrete 4 digits:',10,13,0
	  msgBoard 	DB  'Bulls: ',9,'Cows: ',9,'Guesses:',10,13,0
	  msgGuess	DB 	'Guess the 4 digit sequence',10,10,13,0
	  msgWin	DB 	'You win!',10,10,13,0
	  msgLoose	DB 	'You LOOSE!',10,10,13,0
	  done		DB 	'Done.',10,13,0
	  new_line	DB 	10,13,0
	  secrete  	DB  5 dup(0)
	  guess    	DB  5 dup(0)
	  count		DB  1 dup(0)

.code
             org 100h
	
;*************************************************************
;  Procedimiento principal
;*************************************************************	
	principal proc
            mov sp,0fffh	; inicializa SP (Stack Pointer)
		;	mov ax,@data  	; inicializar DS al la direccion
		;	mov ds,ax    	; del segmento de datos (.DATA)
			
			mov si, offset secrete 
			mov di, offset guess 
						
			mov dx, offset msgGet
			call puts
			mov dx,si
			call getDigits
			
			mov dx, offset done
			call puts
			mov dx, offset msgGuess
			call puts
			
			mov dx, offset msgBoard
			call puts

		@@nextGuess:
			mov ax,0
			mov dx,di
			call getDigits
			call evalGuess
			call printHint
			mov dx, offset new_line
			call puts
			cmp al,4
			je winner
			inc count
			cmp  byte ptr count,8
			je Lose_game
			jmp @@nextGuess
		; Add the following conditions:
		; 	The "game" end when Bulls equals 4 (You win)
		; 	or the number of guesses is greater then 8
winner:
			mov dx,offset msgWin
			call puts
			jmp @@sigue

Lose_game:	
			mov dx,offset msgLoose
			call puts
			jmp @@sigue

		@@sigue:
			jmp @@sigue
			
			ret						; nunca se llega aqu�
			endp

			
;***************************************************************
;  procedimientos
;***************************************************************            
    putchar	proc
			push ax
			push dx
			mov dl,al
			mov ah,2				; imprimir caracter DL
			int 21h					; usando servico 2 (ah=2)
			pop dx					; del int 21h
			pop ax
			ret
			endp
	
	getch	proc
			mov ah,8				; no echo
			int 21h				
			ret
			endp
	
	getche	proc
			mov ah,1				
			int 21h				
			ret
			endp
			
	puts	proc
			push ax
			push bx
			
			mov  bx,dx
		@@nxt: 
			mov  al,[bx]
			cmp  al,0
			je   @@end
			call putchar
			inc  bx
			jmp  @@nxt
			
		@@end: 
			pop  bx
			pop  ax
			ret
			endp
	
	getDigits proc
			push ax
			push bx
			push cx
			
			mov bx,dx
			mov cx,4
		@@gnxt: 
			call getch
			cmp al,'0'
			jb @@gnxt
			cmp al,'9'
			ja @@gnxt
			;-------------------------------------
			
			;----------------------------------------
			mov [bx],al
			inc bx
			loop  @@gnxt
			
			pop cx
			pop bx
			pop ax
			ret
			endp
	
	printHint proc
			push ax
			push dx
			
			add al,'0'
			call putchar ; print Bulls
			
			mov al,9
			call putchar ; tab
			
			mov al, ah
			add al,'0'
			call putchar ; print Cows
			
			mov al,9
			call putchar ; tab
			
			mov dx,di
			call puts
			
			pop dx
			pop ax
			ret
			endp

;***************************************************************
;  	Procedure that evaluates the Bulls (correct number in the correct place)
;  	and Cows (correct number but incorrect position) based on the two arrays
;	given by SI (secrete) and DI (guess).
;	Returns Bulls in AL, and Cows in AH	
;***************************************************************            
	evalGuess proc
			; place code here 
			mov cx,4
			mov bx,0
	bulls_cycle:
			mov dl,byte ptr [bx+di]
			cmp dl,byte ptr[bx+si]
			je bull_up
			jmp bull_out
	bull_up:
			inc al
			inc bx
			jmp bull_exit
	bull_out:
;--------------------------------------------------
			push bx
			push cx
			mov dl,byte ptr[bx+di]
			mov cx,0
			mov bx,0
;-------------------------------------------------
	cows_cycles:
			cmp cx,4	
			je cow_exit	
			cmp dl,byte ptr[bx+si]
			je cow_up
			jmp cow_reload
	cow_up:		
			inc ah
			jmp cow_exit
	cow_reload:
			inc cx
			inc bx
			jmp cows_cycles
	cow_exit:	
			pop cx
			pop bx	
			inc bx
;--------------------------------------------------			
	bull_exit:
			loop bulls_cycle
			ret
			endp
						
end   principal              ; End of program 