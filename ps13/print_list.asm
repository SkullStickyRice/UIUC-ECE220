; print_list.asm

    .ORIG x3000

MAIN
    ; Set up stack
    LD R5, RSTACK
    LD R6, RSTACK

    ; Push argument to print_list
    LD R0, HEAD
    STR R0, R6, #0

    ; print_list(head)
    JSR PRINT_LIST

    HALT

HEAD
    .FILL x2004
RSTACK
    .FILL x7000

; int print_list(node *head)
; {
;     if (!head)
;         return 0;
;
;     printf("%c", head->data);
;     return print_list(head->next);
; }
PRINT_LIST
    ; TODO: Setup activation record
	ADD R6,R6,#-1;
	ADD R6,R6,#-1;
	STR R7,R6,#0;
	ADD R6,R6,#-1;
	STR R5,R6,#0;
	ADD R5,R6,#-1
    ; TODO: Check if head is NULL, if it is, branch to DONE
    ; if (!head)
	LDR R0,R5,#4;
	BRz DONE

    ; TODO: Use OUT trap to output the value of head->data
    ; printf("%c", head->data);
	ADD R2,R0,#0
	LDR R0,R0,#0
	OUT;

    ; TODO: Implement call to print_list(head->next) and place the
    ; return value in the correct location in the activation record
		
	LDR R1,R2,#1;
	ADD R6,R6,#-1;
	STR R1,R6,#0;
	JSR PRINT_LIST
	ADD R6,R6,#2
    BR TEARDOWN

DONE
    ; TODO: return 0: place the return value in the correct location
    ; in the activation record
	ADD R0,R5,#3

TEARDOWN

    ; TODO: teardown activation record prior to RET
	LDR R5,R6,#0;
	ADD R6,R6,#1;
	LDR R7,R6,#0;
	ADD R6,R6,#1
    RET

    .END
