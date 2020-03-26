
.model small
.code 

    
    public _myputchar
    public _getch
    public _outportb
    public _inportb

    _inportb    PROC
                push bp
                mov bp,sp
                mov dx,[bp+4]
                in  al,dx
                pop bp
                ret
    _inportb    ENDP

    _outportb   PROC
                push bp
                mov bp,sp
                mov dx,[bp+4]
                mov al,[bp+6]
                out dx,al
                pop bp
                ret
    _outportb   ENDP

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