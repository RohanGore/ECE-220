;number to print in decimal is in R3.
;it will be positive.
.ORIG x3000

	LD R3, SAVER3		; Loading testing value into R3
	AND R4, R4, #0		; Clearing Register R4
	ADD R4, R4, #10		; Set divisor to 10 
	JSR DIV			; Store quotient to R0, remainder to R1
MAINLOOP
	AND R3, R3, #0		; Clear R3
	ADD R3, R3, R0		; R3 = R0
	AND R0, R0, #0		; Clear R0
	ADD R0, R0, R1		; R0 = R1
	JSR PUSH		; 
	ADD R3, R3, #0		; R3 = R3 to properly set CC
	BRp MAINLOOP		; 
PRINTLOOP
	JSR POP
	ADD R5, R5, #0		; check R5 register value, BRp on R5 -> DONE
	BRp DONE
	; R0 currently the popped value
	ADD R0, R0, #15		; R0 = R0 + ascii value of '0' ; Simply load ASCII_0 in some register and do R0 = R0 + R1
	ADD R0, R0, #15	
	ADD R0, R0, #15
	ADD R0, R0, #3
	OUT
	BR PRINTLOOP
DONE
	HALT







SAVER3	.FILL x21

ASCII_0 .FILL x30
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0-quotient, R1-remainder
DIV	
	AND R0, R0, #0		; Clear R0
	AND R1, R1, #0		; Clear R1
	ADD R1, R1, R3		; R1 = R3
	;R4 = -R4
	NOT R4, R4
	ADD R4, R4, #1
DIVLOOP	
	ADD R0, R0, #1		; R0 = R0 + 1
	ADD R1, R1, R4		; R1 = R1 - R4
	BRzp DIVLOOP
	;ADD R0, R0, #1		; R0 = R0 - 1
	;NOT R4, R4		; R4 = -R4
	;ADD R4, R4, #1
	;ADD R1, R1, R4		; R1 = R1 + R4
	RET



;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

.END

