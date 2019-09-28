;
;
;
.ORIG x3000
	
;your code goes here
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	This program uses a stack data structure and subroutines to make a 
;simple calculator. There is a subroutine for each arithmetic operation 
;and a subroutine to print the result of the postfix expression in 
;hexadecimal. The user enters a character and the character entered is then 
;determined to invalid, an operator, or an operand.  If the character is an
;operand, it is pushed onto the stack and if it is an operator, it is applied
;to the previous two operands
;
;Table of Register Use
;R0 - Character input from keyboard
;R1 - Temporary Register
;R2 - Temporary Register
;R3 - Temporary Register
;R4 - Temporary Register
;R5 - Holds Result of Postfix Expression
;R6 - Counter for the number of elements currently in the stack
;
;
EVALUATE

;your code goes here

	AND R0, R0, #0		; Clear R0
	AND R1, R1, #0		; Clear R1
	AND R2, R2, #0		; Clear R2
	AND R6, R6, #0		; Clear R6


INPUT
	GETC			; Get character input
	OUT			; Echo character to screen
		
	LD R1, SPACE		; Set R1 to ascii value of ' '
	NOT R1, R1		; Invert R1
	ADD R1, R1, #1		
	ADD R4, R0, R1		; Subtract ascii value from input
	BRz INPUT		; If character input is space, branch to INPUT

	LD R1, ASCII_EQUAL	; Set R1 to ascii value of '='
	NOT R1, R1		; Invert R1
	ADD R1, R1, #1
	ADD R4, R0, R1		; Subtract ascii value from input
	BRz EQUAL		; If character input is space, branch to EQUAL

	LD R1, ASCII_PLUS	; Set R1 to ascii value of '+'
	NOT R1, R1		; Invert R1
	ADD R1, R1, #1
	ADD R4, R0, R1		; Subtract ascii value from input
	BRz PLUSJSR		; If character input is space, branch to PLUSJSR


	LD R1, ASCII_MIN	; Set R1 to ascii value of '-'
	NOT R1, R1		; Invert R1
	ADD R1, R1 , #1
	ADD R4, R0, R1		; Subtract ascii value from input
	BRz MINJSR		; If character input is space, branch to MINJSR


	LD R1, ASCII_MUL	; Set R1 to ascii value of '*'
	NOT R1, R1		; Invert R1
	ADD R1, R1 , #1
	ADD R4, R0, R1		; Subtract ascii value from input
	BRz MULJSR		; If character input is space, branch to MULJSR


	LD R1, ASCII_DIV	; Set R1 to ascii value of '/'
	NOT R1, R1		; Invert R1
	ADD R1, R1 , #1
	ADD R4, R0, R1		; Subtract ascii value from input
	BRz DIVJSR		; If character input is space, branch to DIVJSR

	LD R1, ASCII_EXP	; Set R1 to ascii value of '^'
	NOT R1, R1		; Invert R1
	ADD R1, R1 , #1
	ADD R4, R0, R1		; Subtract ascii value from input
	BRz EXPJSR		; If character input is space, branch to EXPJSR

	LD R1, ASCII_0		; Set R1 to ascii value of '0'
	NOT R1, R1		; Invert R1
	ADD R1, R1, #1
	ADD R4, R0, R1		; Subtract ascii value from input
	BRn INVALID_CHAR	; If character input less than ascii value of '0', branch to INVALID_CHAR

	LD R1, ASCII_9		; Set R1 to ascii value of '9'
	NOT R1, R1		; Invert R1
	ADD R1, R1, #1	
	ADD R4, R0, R1		; Subtract ascii value from input
	BRp INVALID_CHAR	; If character input greater than ascii value of '9', branch to INVALID_CHAR
	JSR PUSH		; If character input is an operand and is valid, push to stack
	ADD R6, R6, #1		; Increment Stack element counter
	BRnzp INPUT		; Unconditional branch back to INPUT

	PLUSJSR
	JSR PLUS		; Jump to PLUS subroutine
	BRnzp INPUT		; Unconditional branch back to INPUT

	MINJSR
	JSR MIN			; Jump to MIN subroutine
	BRnzp INPUT		; Unconditional branch back to INPUT

	MULJSR
	JSR MUL			; Jump to MUL subroutine
	BRnzp INPUT		; Unconditional branch back to INPUT

	DIVJSR
	JSR DIV			; Jump to DIV subroutine
	BRnzp INPUT		; Unconditional branch back to INPUT

	EXPJSR
	JSR EXP			; Jump to EXP subroutine
	BRnzp INPUT		; Unconditional branch back to INPUT

	EQUAL
	ADD R6, R6, #-1		; Decrement stack element counter
	BRnp INVALID_CHAR	; If stack element counter is not equal to 0, branch to INVALID_CHAR
	JSR POP			; Pop remaining value in stack 
	AND R5, R5, #0		; Clear R5
	ADD R5, R5, R0		; Set R5 to answer
	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	NOT R3, R3		; Invert R3
	ADD R3, R3, #1
	ADD R5, R5, R3		; Subtract ascii offset from R5 to convert to decimal
	JSR PRINT_HEX		; Jump to PRINT_HEX subroutine
	BRnzp END		; Unconditional branch to END
		
	INVALID_CHAR
	LEA R0, INVALID		; Load address of "Invalid Expression" string into R0
	PUTS			; Print "Invalid Expression" string

END
HALT


SPACE		.FILL x20	; Hex value for ' '
ASCII_0 	.FILL x30	; Hex value for '0'
ASCII_9 	.FILL x39	; Hex value for '9'
ASCII_PLUS 	.FILL x2B	; Hex value for '+'
ASCII_MIN 	.FILL x2D	; Hex value for '-'
ASCII_MUL 	.FILL x2A	; Hex value for '*'
ASCII_DIV 	.FILL x2F	; Hex value for '/'
ASCII_EQUAL	.FILL x3D	; Hex value for '='
ASCII_EXP	.FILL x5E	; Hex value for '^'
ASCII_OFFSET	.FILL x30	; Hex value for ascii offset to convert from ascii to decimal

INVALID .STRINGZ "Invalid Expression"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

	ST R7, SAVE_PRINT_HEX

	AND R3, R3, #0 		;Holds String
	AND R2, R2, #0 		;Temp Register
	AND R4, R4, #0 		;Digit Counter

	ADD R3, R3, R5

	NEXT_DIGIT
	AND R2, R2, #0 		;Clear R2, temp register
	ADD R2, R2, #-4		;Set R2 to -4
	ADD R2, R4, R2 		;Check if digit counter is greater than or equal to 4
	BRzp END_PRINT

	AND R1, R1, #0 		;Bit Counter
	AND R0, R0, #0 		;Digit

	NEXT_BIT

	AND R2, R2, #0 		;Clear R2, temp register
	ADD R2, R2, #-4		;Set R2 to -4
	ADD R2, R1, R2 		;Check if bit counter is greater than or equal to 4
	BRzp DIGIT

	ADD R0, R0, R0 		;Left Shift Digit
	ADD R3, R3, #0 		;Check if R3 is negative
	BRn ADD_ONE
	ADD R0, R0, #0 		;If R3 is not negative, add 0 to digit
	BRnzp LEFT_SHIFT

	ADD_ONE
	ADD R0, R0, #1 		;If R3 is negative, add 1 to digit

	LEFT_SHIFT
	ADD R3, R3, R3 		;Left Shift R3
	ADD R1, R1, #1 		;Increment Bit Counter
	BRnzp NEXT_BIT

	DIGIT
	AND R2, R2, #0
	ADD R2, R2, #-9

	ADD R2, R0, R2
	BRp DECIMAL 		;Check if digit is greater than 9
	ADD R0, R0, #15 	;If digit isn't, add ascii '0'
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #3
	BRnzp OUTPUT

	DECIMAL
	ADD R0, R0, #15 	;If digit is than 9, add ascii 'A' - 10
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #10

	OUTPUT
	OUT 			;Output character in R0 to console
	ADD R4, R4, #1 		;Increment Digit Counter
	BRnzp NEXT_DIGIT

	END_PRINT
	LD R7, SAVE_PRINT_HEX
	RET

SAVE_PRINT_HEX	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ST R7, SAVE_ADD		; Save R7
	JSR POP			; Pop Value out of Stack
	ADD R6, R6, #-1		; Decrement Stack element counter
	AND R1, R1, #0		; Clear R1
	ADD R1, R0, #0		; Store Popped value in R1
	JSR POP			; Pop next value out of Stack
	ADD R6, R6, #-1		; Decrement Stack element counter
	
	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	NOT R3, R3		; Invert R3
	ADD R3, R3, #1
	
	ADD R1, R1, R3		; Subtract ascii offset from popped values to convert them to decimal
	ADD R0, R0, R3
	
	ADD R0, R0, R1		; Add popped values together
	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	ADD R0, R0, R3		; Add ascii offset to convert the sum to ascii
	JSR PUSH		; Push the sum to the stack
	ADD R6, R6, #1		; Increment Stack element counter
	LD R7, SAVE_ADD		; Load saved R7 address
	RET			; Return

SAVE_ADD	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	ST R7, SAVE_MIN		; Save R7
	JSR POP			; Pop value out of stack
	ADD R6, R6, #-1		; Decrement Stack element counter
	AND R1, R1, #0		; Clear R1
	ADD R1, R0, #0		; Store popped value in R1
	JSR POP			; Pop next value out of stack
	ADD R6, R6, #-1		; Decrement Stack element counter

	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	NOT R3, R3		; Invert R3
	ADD R3, R3, #1
	
	ADD R1, R1, R3		; Subtract ascii offset from popped values to convert them to decimal
	ADD R0, R0, R3

	NOT R1, R1		; Invert R1 to subtract it from R0
	ADD R1, R1, #1
	ADD R0, R0, R1		; Subtract first popped value from second
	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	ADD R0, R0, R3		; Add ascii offset to new value to convert to ascii

	JSR PUSH		; Push new value onto stack
	ADD R6, R6, #1		; Increment Stack element counter
	LD R7, SAVE_MIN		; Load saved R7 address
	RET			; Return
	
SAVE_MIN	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ST R7, SAVE_MULT	; Save R7
	JSR POP			; Pop value out of stack
	ADD R6, R6, #-1		; Decrement Stack element counter
	AND R1, R1, #0		; Clear R1
	ADD R1, R0, #0		; Store popped value in R1
	JSR POP			; Pop next value out of stack
	ADD R6, R6, #-1		; Decrement stack element counter

	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	NOT R3, R3		; Invert R3
	ADD R3, R3, #1
	
	ADD R1, R1, R3		; Subtract ascii offset from popped values to convert them to decimal
	ADD R0, R0, R3

	AND R2, R2, #0		; Clear R2
REPEAT
	ADD R2, R2, R1		; Add First popped value to R2
	ADD R0, R0, #-1		; Decrement Second popped value
	BRp REPEAT		; When second popped value > 0, repeat the addition
	AND R0, R0, #0		; Clear R0
	ADD R0, R0, R2		; Set R0 to result of multiplication
	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	ADD R0, R0, R3		; Add ascii offset to new value to convert to ascii
	JSR PUSH		; Push new value onto stack
	ADD R6, R6, #1		; Increment Stack element counter
	LD R7, SAVE_MULT	; Load saved R7 address
	RET			; Return

SAVE_MULT	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	ST R7, SAVE_DIV		; Save R7
	JSR POP			; Pop value out of stack
	ADD R6, R6, #-1		; Decrement Stack element counter
	AND R1, R1, #0		; Clear R1
	ADD R1, R0, #0		; Store popped value in R1
	JSR POP			; Pop next value out of stack
	ADD R6, R6, #-1		; Decrement Stack element counter

	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	NOT R3, R3		; Invert R3
	ADD R3, R3, #1
	
	ADD R1, R1, R3		; Subtract ascii offset from popped values to convert them to decimal
	ADD R0, R0, R3

	AND R2, R2, #0		; Clear R2, subtraction counter
	NOT R4, R1		; Set R4 to -R1
	ADD R4, R4, #1
	
REPEAT_MIN
	ADD R0, R0, R4		; Subtract R4 from R0
	BRn END_MIN		; If R0 is negative, stop subtracting
	ADD R2, R2, #1		; If R0 is zero or positive, increment R2
	BRnzp REPEAT_MIN	; Unconditional branch to REPEAT_MIN

END_MIN
	AND R0, R0, #0		; Clear R0
	ADD R0, R0, R2		; Set R0 to result of division
	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	ADD R0, R0, R3		; Add ascii offset to new value to convert to ascii
	JSR PUSH		; Push result of division onto stack
	ADD R6, R6, #1		; Increment Stack element counter
	LD R7, SAVE_DIV		; Load R7 saved address
	RET
	
SAVE_DIV	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ST R7, SAVE_EXP		; Save R7
	JSR POP			; Pop value out of stack
	ADD R6, R6, #-1		; Decrement Stack element counter
	AND R1, R1, #0		; Clear R1
	ADD R1, R0, #0		; Store popped value in R1
	JSR POP			; Pop next value out of stack
	ADD R6, R6, #-1		; Decrement stack element counter

	LD R3, ASCII_OFFSET	; Set R3 to ascii offset
	NOT R3, R3		; Invert R3
	ADD R3, R3, #1
	
	ADD R1, R1, R3		; Subtract ascii offset from popped values to convert them to decimal 
	ADD R0, R0, R3
	
	AND R2, R2, #0		; Clear R2
	AND R3, R3, #0		; Clear R3
	AND R4, R4, #0		; Clear R4
	AND R5, R5, #0		; Clear R5

	ADD R5, R5, R1		; Set R5 to second popped value

	ADD R4, R4, R1		; Set R4 to second popped value
	ADD R3, R3, R0		; Set R3 to second popped value

	ADD R4, R4, #-1


REPEAT_MUL
REPEAT_ADD
	ADD R2, R2, R3		; ADdd R3 to R2
	ADD R0, R0, #-1		; Decrement inner loop counter
	BRp REPEAT_ADD		; If inner loop counter is positive, branch to REPEAT_ADD
	AND R3, R3, #0		; Clear R3
	ADD R3, R3, R2		; Set R3 to R2
	ADD R4, R4, #-1		; Decrement outer loop counter
	BRp REPEAT_MUL		; If outer loop counter is positive, branch to REPEAT_MUL
	
	AND R0, R0, #0		; Clear R0
	LD R3, ASCII_OFFSET	; Set R3 to Ascii Offset
	ADD R2, R2, R3		; Add ascii offset to new value to convert to ascii
	ADD R0, R0, R2		; Set R0 to exponent result
	JSR PUSH		; Push result to stack
	ADD R6, R6, #1		; Increment Stack element counter
	LD R7, SAVE_EXP		; Load saved R7 address
	RET			; Return

SAVE_EXP	.BLKW #1
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
