.ORIG x3000
AND R3, R3, #0 ;Holds String
AND R2, R2, #0 ;Temp Register
AND R4, R4, #0 ;Digit Counter

AND R6, R6, #0 ;Temp Register

LD R3, STRING

NEXT_DIGIT
AND R5, R5, #0 ;Clear R5, temp register
ADD R5, R5, #-4;Set R5 to -4
ADD R6, R4, R5 ;Check if digit counter is greater than or equal to 4
BRzp END

AND R1, R1, #0 ;Bit Counter
AND R0, R0, #0 ;Digit

NEXT_BIT

ADD R6, R1, R5 ;Check if bit counter is greater than or equal to 4
BRzp DIGIT

ADD R0, R0, R0 ;Left Shift Digit
ADD R2, R3, #0 ;Check if R3 is negative
BRn ADD_ONE
ADD R0, R0, #0 ;If R3 is not negative, add 0 to digit
BRnzp LEFT_SHIFT

ADD_ONE
ADD R0, R0, #1 ;If R3 is negative, add 1 to digit

LEFT_SHIFT
ADD R3, R3, R3 ;Left Shift R3
ADD R1, R1, #1 ;Increment Bit Counter
BRnzp NEXT_BIT

DIGIT
AND R5, R5, #0
ADD R5, R5, #-9

ADD R6, R0, R5
BRp DECIMAL ;Check if digit is greater than 9
ADD R0, R0, #15 ;If digit isn't, add ascii '0'
ADD R0, R0, #15
ADD R0, R0, #15
ADD R0, R0, #3
BRnzp OUTPUT

DECIMAL
ADD R0, R0, #15 ;If digit is than 9, add ascii 'A' - 10
ADD R0, R0, #15
ADD R0, R0, #15
ADD R0, R0, #10

OUTPUT
OUT ;Output character in R0 to console
ADD R4, R4, #1 ;Increment Digit Counter
BRnzp NEXT_DIGIT


END
HALT

STRING .FILL x57C3 


.END
; write your code here
