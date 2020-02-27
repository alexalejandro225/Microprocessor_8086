
.model small
.code 

    public _peek
    public _poke
    public _myputchar
    public _getch

    _peek  PROC
                push bp
                mov bp,sp
                mov bx,[bp+4]
                
                mov al,[bx]
                pop bp
                ret
    _peek ENDP

    _poke	proc
            push bp
            mov bp,sp
            
            mov bx,[bp+4]
            mov al,[bp+6]
            mov byte ptr [bx],al
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