;Assuming user will only enter ' ' 0-9 *+/-
;
;
;
.ORIG x3000
;Your code goes here  
	LD R5,STR_ADDR		
START	
	GETC			
	OUT			
	AND R1,R1,#0		
	ADD R1,R0,#0		

	LD R2,NEG_NL		
	ADD R3,R2,R1		
	BRz DONE		
	LD R2,NEG_CR		
	ADD R4,R2,R1		
	BRz DONE		
	
	JSR DECODE		

	STR R1,R5,#0		
	ADD R5,R5,#1		
	BRnzp START		
	
DONE
	STR R2,R5,#0 		
	HALT			
        
STR_ADDR        .FILL x5000  
SPACE   	.FILL x0020	
NEW_LINE        .FILL x000A	
NEG_NL		.FILL xFFF6	
CHAR_RETURN     .FILL x000D	
NEG_CR		.FILL xFFF3


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Subroutine: DECODE
;input - R0 holds the input
;output - R0 holds numerical value or negation of the ascii value
;find the numerical value of if input is an operand, 
;or find the negation of the ascii value if th input is an operator

DECODE
	ADD R0,R0,R1
	LD R2,NEG_SPACE
	ADD R3,R2,R0
	BRz DECODE
	LD R2,NEG_ZERO
	ADD R3,R2,R0
	BRzp NUMBER
	NOT R0,R0
	ADD R0,R0,#1
	RET
NUMBER	
	ADD R0,R0,R2
	RET

;Your code goes here


ZERO      .FILL x0030
NEG_ZERO  .FILL XFFD0
NEG_SPACE .FILL XFFE0





.END

