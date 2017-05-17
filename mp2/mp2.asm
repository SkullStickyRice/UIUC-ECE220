;Assuming user will only enter ' ' 0-9 *+/-
; In this MP will read the values from memory and use a stack to evaluate the expression. 
; If the read value is an operand, push it onto the stack. 
; If the read value is an operator, pop two values from the stack,
; apply the operator on the two values and push the result 
; back on the stack. Keep repeating this for every value read 
; from memory and stop when you reach the 2'complement of the
; ASCII value of the newline character. 
; If the last value is an operator, that means the expression was invalid.
; If there is a stack underflow during any point in this process,
; then the expression was invalid
;
;
.ORIG x3000
	LD R2, STR_ADDR		;store the decode string at x4000
	AND R0, R0, #0			; clear RO
	ADD R0, R0, #0			;	
	AND R4, R4, #0			; clear R4
GET_NEXT_CHAR
	GETC				;input from keyboard 
	OUT				;echo input
	ADD R3, R0, #0			;load input to R3
	NOT R3, R3			;negation of R3
	ADD R3, R3, #1			;
	LD R1, NEW_LINE			;load newline to R1
	ADD R5, R1, R3			;
	BRz DONE			;if '/n' branch to done
	LD R1, CHAR_RETURN		;load return to R1
	ADD R5, R1, R3			;
	BRz DONE			;if '/r' branch to done
	LD R1, SPACE			;load space to R1
	ADD R5, R1, R3			;
	BRz GET_NEXT_CHAR		;do the branch
	JSR DECODE			;decode subroutine
	ADD R4, R0, #0			;load input to R4
        STR R4, R2, #0			;
        ADD R2, R2, #1			;
        AND R4,R4,#0			;
	BRnzp GET_NEXT_CHAR		;do the branch

DONE
	LD R4, NEW_LINE			;load newline to R4
	NOT R4, R4			;negation of R4
	ADD R4, R4, #1			;
	STR R4, R2, #0			;
	BRnzp EVALUATE			;do the branch
	
STR_ADDR	.FILL x5000		
SPACE		.FILL x0020
NEW_LINE	.FILL x000A
CHAR_RETURN	.FILL x000D
	
;copy your code here
	



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;find the real value of operand, or keep the 2's complement ascii value if operator
;input - R0 holds the input
;output - R0
DECODE
	ST R1, DECODE_R1		;callee-saved reg
	ST R5, DECODE_R5		;callee-saved	reg
	ST R7, DECODE_R7		;
	LD R1, NINE			;load nine to R1
	NOT R1, R1			;negation of nine
	ADD R1, R1, #1			;
	ADD R5, R0, R1			;
	BRp EXPO			;do the branch
	LD R1, 	ZERO			;load zero to R1
	NOT R1, R1			;negation of zero
	ADD R1, R1, #1			;
	ADD R5, R0, R1			;
	BRn OPERATOR			;do the branch	
	ADD R0, R5, #0			; if number, move that number to R0
	BRnzp DECODE_DONE		;do the branch
OPERATOR
	NOT R0, R0			;negation of input
	ADD R0, R0, #1			;
	LD R1, OP_ADD			;check add
	ADD R5, R1, R0			;
	BRz DECODE_DONE			;do the branch
	LD R1, OP_MIN			;check minus
	ADD R5, R1, R0			;
	BRz DECODE_DONE			;do the branch
	LD R1, OP_MUL			;check multiplication
	ADD R5, R1, R0			;
	BRz DECODE_DONE			;do the branch
	LD R1, OP_DIV			;check division
	ADD R5, R1, R0			;
	BRz DECODE_DONE			;do the branch
	BRnzp DE_ERR			;do the branch
EXPO	
	NOT R0,R0			;negation of input
	ADD R0,R0,#1			;
	LD R1, OP_EXP			;check exponential
	ADD R5, R1, R0			;
	BRz DECODE_DONE			;do the branch
DE_ERR	LEA R0, ERR_MSG			;load error message to R0
	PUTS				;print out the error message
	AND R0, R0, #0			;initialize R0
DECODE_DONE
	LD R1, DECODE_R1		;
	LD R5, DECODE_R5		;
	LD R7, DECODE_R7
	RET


DECODE_R1	.BLKW #1	
DECODE_R5	.BLKW #1	
DECODE_R7	.BLKW #1
OP_ADD		.FILL x002B
OP_MIN		.FILL x002D
OP_DIV		.FILL x002F
OP_MUL		.FILL x002A
OP_EXP		.FILL x005E
ZERO		.FILL x0030
NINE		.FILL x003A
ERR_MSG		.STRINGZ "\nError invalid input"


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; R1 - start address of the expression string
; R0 - value of string
; R3 - operator check use
; R5 - temp
; R6 - the numerical value of the end result, and temp
;
;
EVALUATE	 
	LD R1,STRADDR			; load string address into R1
EVA_START
	LDR R0,R1,#0			; load string value
	LD R5,NEWLINE			; load ascii of newline into R5
	ADD R5,R5,R0			; add R5 and current string value into R5
	BRz LAST_CHECK			; do the branch	
	LD R5,CHARRETURN		; load ascii of charreturn into R5
	ADD R5,R5,R0			; add R5 and current string value into R5
	BRz LAST_CHECK			; do the branche	
	ADD R0,R0,#0			
	BRn OPERATOR_CHECK		; do the branche
	JSR PUSH			; if it's not a operator, push the number into stack
	ADD R1,R1,#1			; increment the string address
	BRnzp EVA_START			; do the branche

OPERATOR_CHECK
	LD R3,OPADD		 	; check add first, load ascii add into R3
	ADD R5,R3,R0			; add current value and R3 into R5
	BRnp MIN_CHECK			; do the branche
	
	JSR POP				; if R5 is zero, pop the value from stack
	AND R6,R6,#0			; if R5 from the POP is negative, it's invalid
	ADD R6,R5,#-1
	BRz INVALID			; do the branche
	ADD R3,R0,#0			; load output R0 into R3
	JSR POP				; pop the value from stack again
	ADD R6,R5,#-1			; if R5 from the POP is negative, it's invalid
	BRz INVALID			; do the branche
	ADD R4,R0,#0			; load output R0 into R4

	JSR PLUS			; do add operation 
	JSR PUSH			; push the result back to stack
	ADD R1,R1,#1			; increment the string address
	BRnzp EVA_START			; do the branche

MIN_CHECK
	LD R3,OPMIN			; load ascii minus into R3
	ADD R5,R3,R0			; add current value and R3 into R5
	BRnp MUL_CHECK			; do the branche

	JSR POP				; if R5 is zero, pop the value from stack
	AND R6,R6,#0			; if R5 from the POP is negative, it's invalid
	ADD R6,R5,#-1			;
	BRz INVALID			; do the branche
	ADD R3,R0,#0			; load output R0 into R3
	JSR POP				; pop the value from stack again
	ADD R6,R5,#-1			; if R5 from the POP is negative, it's invalid
	BRz INVALID			; do the branche
	ADD R4,R0,#0			; load output R0 into R4

	JSR MIN				; do the minus operation
	JSR PUSH			; push the result back into the stack 
	ADD R1,R1,#1			; increment the string address
	BRnzp EVA_START			; do the branche


MUL_CHECK
	LD R3,OPMUL			; load ascii multiply into R3
	ADD R5,R3,R0			; add current value and R3 into R5
	BRnp DIV_CHECK			; do the branche

	JSR POP				; same as before
	AND R6,R6,#0
	ADD R6,R5,#-1
	BRz INVALID			; do the branche
	ADD R3,R0,#0
	JSR POP
	ADD R6,R5,#-1
	BRz INVALID			; do the branche
	ADD R4,R0,#0

	JSR MUL				; do the multiply operation
	JSR PUSH			; push the result back into the stack	
	ADD R1,R1,#1			; increment the string address
	BRnzp EVA_START			; do the branche

DIV_CHECK
	LD R3,OPDIV			; load ascii divison into R3
	ADD R5,R3,R0			; add current value and R3 into R5
	BRnp EXPO_CHECK			; do the branche
	
	JSR POP				; same as before
	AND R6,R6,#0
	ADD R6,R5,#-1
	BRz INVALID			; do the branche
	ADD R3,R0,#0
	JSR POP
	ADD R6,R5,#-1
	BRz INVALID			; do the branche
	ADD R4,R0,#0

	JSR DIV				; do the division operation
	JSR PUSH			; push the reslut back into the stack
	ADD R1,R1,#1			; increment the string address
	BRnzp EVA_START			; do the branche

EXPO_CHECK
	LD R3,OPEXP			; load ascii exponential into R3
	ADD R5,R3,R0			; if R5 is not zero, then it's a wrong operator
	BRnp INVALID			; do the branche

	JSR POP				; same as before
	AND R6,R6,#0			
	ADD R6,R5,#-1
	BRz ERROR_INPUT
	ADD R4,R0,#0
	JSR POP
	ADD R6,R5,#-1
	BRz INVALID
	ADD R3,R0,#0

	JSR EXP				; do the exponent operation
	JSR PUSH			; push the result back into the stack
	ADD R1,R1,#1			; increment the string address
	BRnzp EVA_START			; do the branche


LAST_CHECK	
	JSR POP				; pop out the reslut
	ADD R5,R5,#-1			; if the output R5 is 1 from pop, then it's an 						; invalid result
	BRz INVALID	
	ADD R6,R0,#0			; add the reslut into R6
	JSR POP				; pop again
	ADD R5,R5,#0			; if R5 is zero, then there are addtion value in the 						; stack. it's an invalid result
	BRnz INVALID			; do the branche
FINISH	
	HALT				; stop the program 

INVALID
	LEA R0,INVALID_EX		; print out the invalid expression text
	PUTS
	BRnzp FINISH			; do the branche

ERROR_INPUT
	LEA R0, ERROR_EX		; print out the invalid input text
	PUTS
	BRnzp FINISH			; do the branche

STRADDR		.FILL x5000		; beginning of the string address
NEWLINE		.FILL x000A		; ascii of newline
CHARRETURN	.FILL x000D		; ascii of charactor return 
OPADD		.FILL x002B		; ascii of add operator
OPMIN		.FILL x002D		; ascii of minus operator
OPDIV		.FILL x002F		; ascii of division operator
OPMUL		.FILL x002A		; ascii of multiplcation operator
OPEXP		.FILL x005E		; ascii of exponent operator
INVALID_EX	.STRINGZ "\nInvalid Expression"		; invalid text
ERROR_EX	.STRINGZ "\nError Invalid Input"	; invalid input text	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	

	ADD R0,R3,R4			; add R3 and R4 into R0	
	RET				; return 


	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN		
	ST R3, MIN_SAVE_R3		; save R3
	NOT R3,R3			; 2's complement of R3
	ADD R3,R3,#1			
	ADD R0,R4,R3			; add R3 and R4 into R0
	LD R3, MIN_SAVE_R3		; restore R3
	RET				; return 

MIN_SAVE_R3	.BLKW #1

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
	ST R3, MUL_SAVE_R3		; save R3
	AND R0,R0,#0			; clear R0
LOOPADD	
	ADD R0,R0,R4			; add R4 into R0
	ADD R3,R3,#-1			; decrement R3 as a counter
	BRp LOOPADD			; if the counter is positive, add R4 into R0 again
	LD R3, MUL_SAVE_R3		; restore R3
	RET				; return 

MUL_SAVE_R3	.BLKW 1
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
	ST R3, DIV_SAVE_R3		; save R3
	AND R0,R0,#0			; clear R0
	NOT R3,R3			; 2's complement of R3
	ADD R3,R3,#1			
LOOPMIN
	ADD R4,R4,R3			; add R3 and R4 into R4
	BRn DIV_BACK			; do the branche
	ADD R0,R0,#1			; increment R0 as counter and reslut
	BRnzp LOOPMIN			; do the branche
	
DIV_BACK	
	LD R3,DIV_SAVE_R3		; restore R3
	RET				; return 
DIV_SAVE_R3	.BLKW #1
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;temp R5, R6
;out R0
EXP
	ST R3, EXP_SAVE_R3		; save R3
	ST R4, EXP_SAVE_R4		; save R4
	AND R0,R0,#0			; clear R0
	ADD R6,R3,#0			; load R3 into R6
	ADD R4,R4,#-1			; decrement counter
	ADD R6,R6,#-1			; decrement counter
	ADD R0,R3,#0			; load R3 into R0
LOOPEXP
	ADD R4,R4,#0			; check the end 
	BRz EXP_BACK			; do branch
	ADD R5,R6,#0			; initial counter
LOOPMUL
	ADD R5,R5,#0			; clear R5
	BRz DECREMENT			; do branch
	ADD R0,R0,R3			; do multiply calculation 
	ADD R5,R5,#-1			; decrement counter
	BRnzp LOOPMUL			; do the branche
DECREMENT
	ADD R4,R4,#-1			; devrement counter
	ADD R3,R0,#0			; load R0 into R3
	BRnzp LOOPEXP			; do the branche
EXP_BACK
	LD R3,EXP_SAVE_R3		; restore R3
	LD R4,EXP_SAVE_R4		; restore R4
	RET				; return 



EXP_SAVE_R3	.BLKW #1
EXP_SAVE_R4	.BLKW #1
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
	ADD R3, R3, R4		;2
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
