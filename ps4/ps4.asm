; R0, input value of PUSH, output value of pop
; R1, string value
; R2, floor counter
; R3, string address
; R5, ouverflow and underflow check bit
; R4, temp register
; R6, temp register 

	.ORIG	x3000	;starting address is x3000

; YOUR CODE GOES HERE
	LDI R4,TOTAL_N
	BRz PRINT_NOT_PALIN
	LDI R4,TOTAL_N
	ADD R4,R4,#-1
	BRz PRINT_PALIN
	LD R3,STR_ADDR
	LDI R2,HALF_H

PUSH_START
	LDR R0,R3,#0
	JSR PUSH
	ADD R6,R5,#-1
	BRz O_U_FLOW_MSG
	ADD R2,R2,#-1
	BRp PUSH_COUNT
	LDI R2,HALF_H
	LDI R4,TOTAL_N
	NOT R4,R4
	ADD R4,R4,#1
	ADD R4,R4,R2
	ADD R4,R4,R2
	BRz POP_START 
	ADD R3,R3,#1
POP_START	
	ADD R3,R3,#1
	LDR R1,R3,#0
	JSR POP
	ADD R6,R5,#-1
	BRz O_U_FLOW_MSG
	ADD R4,R0,#0
	NOT R1,R1
	ADD R1,R1,#1
	ADD R1,R1,R4
	BRnp PRINT_NOT_PALIN
	ADD R2,R2,#-1
	BRnz PRINT_PALIN
	BRnzp POP_START
	
PUSH_COUNT
	ADD R3,R3,#1
	BRnzp PUSH_START
O_U_FLOW_MSG
	LEA R0, ERROR_MSG
	PUTS
	BRnzp DONE
PRINT_PALIN
	LEA R0, IS_PAN_MSG
	PUTS
	BRnzp DONE
PRINT_NOT_PALIN
	LEA R0, NOT_PAN_MSG
	PUTS
DONE
	HALT
	
	
	

TOTAL_N		.FILL x5000
HALF_H		.FILL x5001
STR_ADDR	.FILL x5002	;You string will be stored at x5002
NEG_LEFT	.FILL #-40	;negative "("
NEG_RIGHT	.FILL #-41	;negative ")"
IS_PAN_MSG	.STRINGZ "\nThe input is a palindrome\n"	;
NOT_PAN_MSG	.STRINGZ "\nThe input is not a palindrome!\n"	;
ERROR_MSG	.STRINGZ "\nYour stack has overflowed/underflowed!\n"	;


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

