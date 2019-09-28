;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; 	Prints Histogram using data calculated earlier in the program by using a 
; bin counter to determine which bin of the histogram is currently being used 
; and which character and its respective count to print.  
; It then prints the character and prints its respective count as a hexadecimal value
;
;
; Table of register use in this part of the code
;    R0 holds either the current ascii character to be printed or the count of the current ascii character
;    R1 holds a pointer to the current bin of the histogram
;    R2 is used as a bit counter
;    R3 holds the count of the current character
;    R4 is used as a digit counter
;    R5 holds the current ascii character to be printed
;    R6 is used as a temporary register
;

	LD R1, NUM_BINS		; Initialize Bin Counter
	LD R5, AT		; Load Hex Value for '@' into R5
	LD R6, HIST_ADDR	; Load histogram starting address into R6


PRINT_LOOP
	AND R0, R0, #0		; Clear R0
	ADD R0, R0, R5		; Add Current Character to be printed to R0
	OUT			; Print Character in R0
	ADD R5, R5, #1		; Set R5 to the next ascii character to be counted
	LD R0, SPACE		; Load Hex Value for ' ' into R0
	OUT			; Print ' '
	LDR R3, R6, #0		; Load Data stored at histogram starting address into R3

	STI R6, HIST_CUR_ADDR	; Store current histogram address at memory location x5000
	AND R4, R4, #0		; Clear R4, digit counter
	
NEXT_DIGIT
	ADD R6, R4, #-4		; Check if digit counter is greater than or equal to 4
	BRzp END_PRINT_HEX	; If digit counter is greater than or equal to 4, branch to END_PRINT_HEX

	AND R2, R2, #0 		; Initialize Bit Counter
	AND R0, R0, #0 		; Clear R0, Holds Digit

NEXT_BIT

	ADD R6, R2, #-4		; Check if bit counter is greater than or equal to 4
	BRzp DIGIT		; If bit counter is greater than or equal to 4, branch to DIGIT

	ADD R0, R0, R0 		; Left Shift Digit
	ADD R3, R3, #0 		; Check if R3 is negative
	BRn ADD_ONE		; If R3 is negative, branch to ADD_ONE
	ADD R0, R0, #0 		; If R3 is not negative, add 0 to digit
	BRnzp LEFT_SHIFT	; Unconditional Branch to LEFT_SHIFT

ADD_ONE
	ADD R0, R0, #1 		; If R3 is negative, add 1 to digit

LEFT_SHIFT
	ADD R3, R3, R3 		; Left Shift R3
	ADD R2, R2, #1 		; Increment Bit Counter
	BRnzp NEXT_BIT		; Unconditional Branch to NEXT_BIT

DIGIT

	ADD R6, R0, #-9		; Add R0 with R5 to check if R0 is greater that 9
	BRp DECIMAL 		; Check if digit is greater than 9
	ADD R0, R0, #15 	; If digit isn't greater than 9, add ascii '0' or #48
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #3
	BRnzp OUTPUT

DECIMAL
	ADD R0, R0, #15 	; If digit is greater than 9, add ascii 'A' - 10 or #55
	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #10

OUTPUT
	OUT 			; Output character in R0 to console
	ADD R4, R4, #1 		; Increment Digit Counter
	BRnzp NEXT_DIGIT	; Unconditional Branch to NEXT_DIGIT

END_PRINT_HEX
	LD R0, NEW_LINE		; Load Hex Value for New Line into R0
	OUT
	LDI R6, HIST_CUR_ADDR	; Load Current Histogram Address into R6
	ADD R6, R6, #1		; Increment Current Histogram Address
	ADD R1, R1, #-1		; Decrement Bin Counter
	BRp PRINT_LOOP		; Check if bin counter is greater than 0, if it is branch to PRINT_LOOP
	

DONE	HALT			; done

AT		.FILL x0040	; Hex for @
SPACE		.FILL x0020	; Hex for ' '
NEW_LINE	.FILL x000A	; Hex for NewLine
HIST_CUR_ADDR 	.FILL x5000	; Memory Location to store Current Histogram Address

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address

STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
