; Programming Studio 2 
; assignment: develop a code to print a value stored in a register 
;             as a hexadecimal number to the monitor
; algorithm: turnin each group of four bits into a digit
;            calculate the corresponding ASCII character;
;            print the character to the monitor

; R1 digits counter
; R2 bits counter
; R3 given info
; R5 stored vaule
; R6 temp
; R4 temp

.ORIG x3000				; program starts at x3000

		LD R3,INFO		; load given info to R3 for testing
		AND R1,R1,#0		; initialize R1 to be zero
	
START		AND R6,R6,#0		; initialize R6 to be zero 
		ADD R6,R1,#0		; add R1 into R6 for digits check
		ADD R6,R6,#-4		; add negative 4 to R6
		BRzp FINISH		; if digits counter is zero or positive, 						  it means the program printed all value 
		AND R2,R2,#0		; initialize R2 to be zero 
		AND R5,R5,#0		; initialize R5 to be zero

BITCHECK	AND R4,R4,#0		; initialize R4 to be zero
		ADD R4,R2,#0		; add R2 into R4 for testing
		ADD R4,R4,#-4		; add negative 4 to R4
		BRzp DIGITCHECK		; if it's zero or positive, go to 						  DIGITCHECK
		ADD R5,R5,R5		; shift R5
		ADD R3,R3,#0		; add zero to R3
		BRn ADDDIGIT		; if R3 is negative go to ADDDIGIT
		ADD R5,R5,#0		; add zero to R5
		BRnzp SHIFTINFO		; go to SHIFTINFO

ADDDIGIT	ADD R5,R5,#1		; add 1 to R5

SHIFTINFO	ADD R3,R3,R3		; shift R3

		ADD R2,R2,#1		; increment bits counter
		BRnzp BITCHECK		; go to BITCHECK

DIGITCHECK	ADD R5,R5,#-9		; add negative 9 to R5
		BRp ALPHABET		; if its positive, go to ALPHABET
		LD R0,ZERO		; load ASCII zero into R0 in hex
		ADD R5,R5,#9		; 
		ADD R0,R0,R5		; add R5 into R5
		BRnzp PRINTOUT		; go print the vaule

ALPHABET	LD R0,CHARA		; load ASCII A into R0 in hex
		ADD R5,R5,#9		; 
		ADD R0,R0,R5		; add R5 into R0
		ADD R0,R0,#-10		; add -10 to R0

PRINTOUT	OUT			; print the vaule in R0
		ADD R1,R1,#1		; increment digits counter
		BRnzp START		; back to start
					; stop the computer
FINISH		HALT

					; program data section starts here
INFO	.FILL xF9E0
ZERO	.FILL x0030
CHARA	.FILL x0041

.END

