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
 mov ax,1230
 ;--------------------------------------------------------------- 

 ;---------------------------------------------------------------
 cmp ax,8000h
 ja @@negative 
 jmp @@positive

 @@negative:
;===============================================================
    not ax
    add ax,1
    cmp ax,1270
    jbe @@negative_run
    call Overflow_test
    jmp @@out
    @@negative_run:
    push ax
 ;---------------------------------------------------------------
    mov al,'A'
    call putchar
    mov al,'X'
    call putchar
    mov al,'-'
    call putchar
    mov al,'>'
    call putchar
    mov al,'-'
    call putchar
    pop ax
    push ax
    xor cx,cx
    mov bl,10
@@redo_pos_neg:
    div bl
    push ax
    cbw
    inc cl
    cmp al,0
    jne @@redo_pos_neg
@@print_ax_neg:
    pop ax
    xchg ah,al
    add al,'0'
    call putchar
    dec cl
    cmp cl,0
    jne @@print_ax_neg
;***********************************************
 pop ax
;***********************************************
 push ax
 ;---------------------------------------------------------------
 mov al,' '
 call putchar
 mov al,13
 call putchar
 mov al,10
 call putchar
 mov al,'D'
 call putchar
 mov al,'X'
 call putchar
 mov al,'-'
 call putchar
 mov al,'>'
 call putchar
 mov al,'-'
call putchar
 pop ax
 ;--------------------------------------------------------------- 
 xor cx,cx
 mov bl,10
 ;------------------------------------------------------------
    xor dx,dx
 @@invert_ax_neg:
    div bl
    push ax    
    xchg al,ah
    cbw 
    ;------------------------------------
    xchg ax,dx
    mul bl
    xchg ax,dx
    add dx,ax
    pop ax
    cbw
    cmp al,0
    jne @@invert_ax_neg
;====================================================
    xor cx,cx
    mov bl,10
    mov ax,dx
@@redo_pos_dx_neg:
    div bl
    push ax
    cbw
    inc cl
    cmp al,0
    jne @@redo_pos_dx_neg
@@print_dx_neg:
    pop ax
    xchg ah,al
    add al,'0'
    call putchar
    dec cl
    cmp cl,0
    jne @@print_dx_neg
    not dx
    add dx,1
    jmp @@out

;===========================================

;*********************************************
 @@positive:
    cmp ax,1270
    jbe @@positive_run
    call Overflow_test
    jmp @@out
    @@positive_run:
    push ax
 ;---------------------------------------------------------------
    mov al,'A'
    call putchar
    mov al,'X'
    call putchar
    mov al,'-'
    call putchar
    mov al,'>'
    call putchar
    pop ax
    push ax
    xor cx,cx
    mov bl,10
@@redo_pos:
    div bl
    push ax
    cbw
    inc cl
    cmp al,0
    jne @@redo_pos
@@print_ax:
    pop ax
    xchg ah,al
    add al,'0'
    call putchar
    dec cl
    cmp cl,0
    jne @@print_ax
;***********************************************
 pop ax
;***********************************************
 push ax
 ;---------------------------------------------------------------
 mov al,' '
 call putchar
 mov al,13
 call putchar
 mov al,10
 call putchar
 mov al,'D'
 call putchar
 mov al,'X'
 call putchar
 mov al,'-'
 call putchar
 mov al,'>'
 call putchar
 pop ax
 ;--------------------------------------------------------------- 
 xor cx,cx
 mov bl,10
 ;------------------------------------------------------------
    xor dx,dx
 @@invert_ax:
    div bl
    push ax    
    xchg al,ah
    cbw 
    ;------------------------------------
    xchg ax,dx
    mul bl
    xchg ax,dx
    add dx,ax
    pop ax
    cbw
    cmp al,0
    jne @@invert_ax
;====================================================
    xor cx,cx
    mov bl,10
    mov ax,dx
@@redo_pos_dx:
    div bl
    push ax
    cbw
    inc cl
    cmp al,0
    jne @@redo_pos_dx
@@print_dx:
    pop ax
    xchg ah,al
    add al,'0'
    call putchar
    dec cl
    cmp cl,0
    jne @@print_dx
 @@out:
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
;*****************************************************************
;procedimiento
;*****************************************************************
Overflow_test proc
    push ax
    push bx
    mov al,'A'
    call putchar
    mov al,'X'
    call putchar
    mov al,'-'
    call putchar
    mov al,'>'
    call putchar
    mov al,'-'
    call putchar
    mov al,' '
    call putchar
    mov al,13
    call putchar
    mov al,10
    call putchar
    mov al,'D'
    call putchar
    mov al,'X'
    call putchar
    mov al,'-'
    call putchar
    mov al,'>'
    call putchar
    mov al,'0'
    call putchar
    pop bx
    pop ax
    ret
    endp
 end principal ; fin de programa (file)