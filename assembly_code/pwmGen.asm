;6.115 Final Project
;Serial Receiving Program
;Albert Wu

.org 00h					;power up and reset vector
    ljmp start				;jump to the beginning of the program (start)
							;which is stored in 100h
.org 100h					;set vector to 100h
start:						
    lcall init				;call subroutine "init" to start serial port
loop:					;loop over
    lcall getchr			;call subroutine "getchr" to get character from PSoC
    mov r2, 70h               ;store first char (direction) in r2
	lcall readnum			;reads number and store to r3
;set direction
    mov a, r2
    anl a, #000000001b      ;keep only 1 bit
    cjne a, #01h, cw
;1: counterclockwise
    setb p3.2
    sjmp setPWM
cw:
;0: counterclockwise
    clr p3.2  
;set PWM
setPWM:
    mov P1, r3             ;display pwm value in r3
    lcall set8254           ;reflect change in 8254
	sjmp loop
	
init:
;set up serial port with 11.0592 MHz crystal
;use timer 1 for 9600 baud serial communication
	mov tmod, #20h			;MCS-51 Programmer's Guide P2-16: set timer 1 for auto reload-mode2
	mov tcon, #40h			;run timer 1
	mov th1, #0fdh			;set 9600 baud with xtal=11.059MHz, SMOD = 0
	mov scon, #50h			;set to 8 bit mode 1
        
;set up 8254 counter 0
	mov dptr, #0FE03h		;set dptr to command word register
	mov A, #24h				;set to mode 2, MSB only 
	movx @dptr, A			;send command word

	mov dptr, #0FE00h		;set dptr to timer 0 register
	mov A, #01h				;start scanning at #0B0h(~50kHz)
	movx @dptr, A			;set low byte to #B0h
    
    mov r3, #00h
;set up 8254 counter 1 using the value in r3
set8254:
;inverse command such that 01 corresponds to low pwm
    clr c
    mov A, #00h
    subb A, r3
    mov r3, A
    
	mov dptr, #0FE03h		;set dptr to command word register
	mov A, #52h				;set to mode 1, LSB only
	movx @dptr, A			;send command word

	mov dptr, #0FE01h		;set dptr to timer 1 register
	mov A, r3				;set duty cycle
	movx @dptr, A			;
	ret						;return from subroutine
	
getchr:
;gets a character from PC using serial. RI is SCON.0. ASCII code is returned in 70h
	jnb ri, getchr			;if ri is not set, jump to getchr 
	mov 70h, sbuf				;get character from serial data buffer to 70h
	anl 70h, #7fh				;mask off 8th bit
	clr ri					;clear receive status flag
	ret

readnum:
;reads a number
	lcall getchr			;reads MSB
	push 70h				;stores MSB
    mov 71h, 70h			;move MSB to send buffer
	lcall sndchr			;sends MSB
	lcall getchr			
	push 70h
	mov 71h, 70h			;move MSB to send buffer
	lcall sndchr			;sends MSB
    lcall getchr			;reads LSB
	push 70h				;stores LSB
    mov 71h, 70h			;move MSB to send buffer
	lcall sndchr			;sends MSB
    
;parses the number
	pop 50h					;pops LSB into 50h
	pop 51h
	pop 52h					;pops MSB into 52h
	
	mov a, 52h				;processes MSB
	add a, #0d0h		    ;convert from ascii to value
	mov b, #64h				;store 100 in B
	mul ab					;multiply A and B to get value for MSB
	mov 52h, a				;store value for MSB in 52h

	mov a, 51h				;processes second digit
	add a, #0d0h			;convert from ascii to value
	mov b, #0Ah
	mul ab					;multiplies ab
	mov 51h, a				;store valu in 51h

	
	mov a, 50h				;store LSB in A
	add a, #0d0h				;convert from ascii to value
	add a, 51h				;add up the digits
	add a, 52h
	mov r3, a				;store the number in the address specified earlier
	ret	
    
sndchr:
;sends a character to PC using serial. Sends the character in 71h. SCON.1 and TI are the same
	clr scon.1				;clear the ti complete flag
	mov sbuf, 71h			;move a character from acc to the sbuf
txloop:
	jnb scon.1, txloop		;if scon.1 is not set, jump to txloop
	ret    
    