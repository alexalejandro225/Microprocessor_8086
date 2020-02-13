
.model small
.code 

    public _myputchar
    public _getch

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