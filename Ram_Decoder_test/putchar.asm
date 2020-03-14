
.model small
.code 

    public _peek
    public _poke
    public _myputchar
    public _getch

    _peek  PROC
                push bp
                mov bp,sp
                mov cx,ds
                mov ds,[bp+4]
                mov bx,[bp+6] ;Ram offset 1 word size
                mov al,[bx]   ;return data from pointer
                mov ds,cx
                pop bp
                ret
    _peek ENDP

    _poke	proc
            push bp
            mov bp,sp
            mov cx,ds
            mov ds,[bp+4]
            mov bx,[bp+6]   ;Ram offset 1 word size
            mov al,[bp+8]   ;get byte of data from the stack
            mov byte ptr [bx],al ;move data to memory 
            mov ds,cx
            pop bp			
			ret
	_poke	ENDP

    _myputchar  PROC
                push bp
                mov bp,sp
                mov dl,[bp+4]
                mov ah,2
                int 21h

                pop bp
                ret
    _myputchar ENDP

    _getch	proc
            push bp
            mov bp,sp
			mov ah,8				
			int 21h	
            pop bp			
			ret
	_getch	ENDP

    END