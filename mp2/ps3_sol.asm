;Assuming user will only enter ' ' 0-9 *+/-
;
;
;
.ORIG x3000
	LD R2, STR_ADDR		;store the decode string at x4000
	AND R0, R0, #0			;
	ADD R0, R0, #0			;
	AND R4, R4, #0			;
GET_NEXT_CHAR
	GETC				;
	OUT
	ADD R3, R0, #0			;
	NOT R3, R3			;
	ADD R3, R3, #1
	LD R1, NEW_LINE			;
	ADD R5, R1, R3			;
	BRz DONE			;if '/n' branch to done
	LD R1, CHAR_RETURN		;
	ADD R5, R1, R3			;
	BRz DONE			;if '/r' branch to done
	LD R1, SPACE		;
	ADD R5, R1, R3			;
	BRz GET_NEXT_CHAR
	JSR DECODE			;
	ADD R4, R0, #0
        STR R4, R2, #0
        ADD R2, R2, #1
        AND R4,R4,#0			
	BRnzp GET_NEXT_CHAR		;

DONE
	LD R4, NEW_LINE			;
	NOT R4, R4
	ADD R4, R4, #1		
	STR R4, R2, #0
	HALT

STR_ADDR	.FILL x5000		
SPACE		.FILL x0020
NEW_LINE	.FILL x000A
CHAR_RETURN	.FILL x000D


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;find the real value of operand, or keep the ascii value if operator
;input - R0 holds the input
;output - R0
DECODE
	ST R1, DECODE_R1		;callee-saved reg
	ST R5, DECODE_R5		;callee-saved	reg
	ST R7, DECODE_R7
	LD R1, NINE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R5, R0, R1
	BRp EXPO
	LD R1, 	ZERO			;
	NOT R1, R1			;
	ADD R1, R1, #1			;
	ADD R5, R0, R1			;
	BRn OPERATOR			;	
	ADD R0, R5, #0			; if number, move that number to R0
	BRnzp DECODE_DONE
OPERATOR
	NOT R0, R0
	ADD R0, R0, #1
	LD R1, OP_ADD
	ADD R5, R1, R0
	BRz DECODE_DONE
	LD R1, OP_MIN
	ADD R5, R1, R0
	BRz DECODE_DONE
	LD R1, OP_MUL
	ADD R5, R1, R0
	BRz DECODE_DONE
	LD R1, OP_DIV
	ADD R5, R1, R0
	BRz DECODE_DONE
	BRnzp DE_ERR
EXPO	LD R1, OP_EXP
	ADD R5, R1, R0
	BRz DECODE_DONE
DE_ERR	LEA R0, ERR_MSG
	PUTS
	AND R0, R0, #0
DECODE_DONE
	LD R1, DECODE_R1		;
	LD R5, DECODE_R5		;
	LD R7, DECODE_R7
	RET


DECODE_R1	.BLKW #1	;
DECODE_R5	.BLKW #1	;
DECODE_R7	.BLKW #1
OP_ADD		.FILL x002B
OP_MIN		.FILL x002D
OP_DIV		.FILL x002F
OP_MUL		.FILL x002A
OP_EXP		.FILL x005E
ZERO	.FILL x0030
NINE	.FILL x003A
ERR_MSG	.STRINGZ "\nError invalid input"





.END

