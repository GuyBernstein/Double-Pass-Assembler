; Example test file for .entry directive
; Valid uses of .entry
.entry &ENTRYLABEL1
    mov  #1, r0
    mov  #2, r1
    mov  #3, r2
    mov  #4, r3
ENTRYLABEL1: .data 1,2,3

.entry &ENTRYLABEL2
    mov #5, r4
    mov #6, r5
    mov #7, r6
    mov #8, r7
ENTRYLABEL2: .string "abcd"

.entry &LABEL4
LABEL4: cmp r0, #1

; Duplicate .entry directive for same symbol
.entry &ENTRYLABEL2
    mov r1, r2
    
LABEL: add r1, r2
; Use .entry directive with existing label
.entry &LABEL

; Define external symbol
.extern EXTERNLABEL
; Use .entry directive with external symbol
.entry &EXTERNLABEL

; Define a label as code symbol
LABEL2: add r1, #5
; Use .entry directive with existing label defined as code symbol
.entry &LABEL2

; Use .entry directive with undefined label
.entry &UNDEFINEDLABEL

; Use .entry directive with invalid label
.entry &2UNDEFINEDLABEL

; Define a label as data symbol
MYLABEL: .data 5
; Use .entry directive with existing label defined as data symbol
.entry &MYLABEL

; Use .entry directive without specifying a label
.entry

;invalid label
mov r1, r2 r2
cmp r1, r2 r2
