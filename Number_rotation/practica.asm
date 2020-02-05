.model tiny
;----- Insert INCLUDE "filename" directives here
;----- Insert EQU and = equates here

locals

.data
Mens DB 'Hola Mundo',10,13,0
.code
org 100h
;*************************************************************
; Procedimiento principal
;*************************************************************
 principal proc
 mov sp,0fffh ; inicializar SP (Stack Pointer)
 @@redo: mov ax,10
 
 jmp @@redo
 ret ; nunca se llega aquí
 endp
;***************************************************************
; procedimientos
;***************************************************************
 putchar proc
 push ax
push dx
mov dl,al
mov ah,2 ; imprimir caracter DL
int 21h ; usando servicio 2 (ah=2)
pop dx ; del int 21h
pop ax
ret
endp
end principal ; fin de programa (file)