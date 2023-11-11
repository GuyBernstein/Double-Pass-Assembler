;label errors
testLable1: .string "Valid"
testLable2:.string "no space"
testLable1LableNameIsTooLONGTESTtest: .string "lable name is too long"
test Lable: .string "lable name with space"
test#Lable:.string "Invalid label name "
$notAlable: .string "Invalid lable name"
testLable :.string "Space after label name "
testLable1: .string "This label was already used on first line"
.invalid1: .data 1,2,3
1invalid2: mov r1, r2
inv:alid3: add r1, #1
i_nvalid4: prn r3
i!nvalid5: jsr invalid
invalidLONGVERYLONGLABELSOITSINVALIDDDDDDDDDDDDDDDDDDD6: lea invalid, r1
]invalid7: cmp r2, #5
i]nvalid8: .entry invalid
VALID7: .entry invalid7
@invalid9: .extern invalid
i@nvalid10: .string "Invalid label: '!'"

; Invalid reserved words
jmp: .data 1,2,3
mov: mov r1, r2
add: add r1, #1
prn: prn r3
jsr: jsr valid
lea: lea valid, r1
cmp: cmp r2, #5
.entry: .entry valid7
.extern: .extern valid8

;comma errors
testData: .data 1,2,3,
testData1: .data 1,2, ,3
testData2: .data 1,2, ,3,,
testData3: .data 1,2,	 ,3,4 	,5
testData5: .data ,1,2,3
testData6: .data , ,1,2,3

mov, r1, r2
cmp r1, , r2
sub ,r1, r4
add , r1  ,#2
add , L3,  L3
inc , r1
inc, r1

;line length errors
LongData: .data 123, 123, 123,123, 123, 123,123, 123, 123,123, 123, 123,123, 123, 123,123, 123, 123,123, 123, 123,123, 123, 123
LongString: .string "I am a very long string that will surely exceed the maximum length of a line"

;data errors
    .data
    .data notNumber, 4, 8, 15, 16, 23, 42
    .data --1, 2, 3
    .data 1, 2, ++3, 4
    .data 1,2 3,4
    .data 1,2 +3,4
    .data 1,2 ,i,3
    .data a, b, c, d
    .data 3, 4, 6.5, 9
    .data 1,2,3,9000


;string errors
    .string
    .string notGood
    .string notGood"
    .string "not good
    .string not "good".
    .string not ."good"
    .string ",

;extraneous words
    .data 123 .data
    .string "sdf" .string
    .extern Hello World
    .entry Goodbye Earth

;Command errors
; Test for an invalid command name
invalid_command r7, r8
; Invalid directives
.entry .data 1,2,3
.extern mov r1, r2
.string add r1, #1
.extern Lable1: label2:

;FirstGroup
mov r1, r2, r2
mov r1, r2 r2
mov r1
mov r1,#1
mov r1 r2
mov r1,r2,
cmp #3, r2, r2
cmp A, r2 r2
cmp #3
cmp invalid#lable,r1
sub #3, r1,
sub #3
sub #3,#3
lea r1
lea test,test,test
lea test,,1

;SecondGroup
not r1,r2
not test,
not ,test
not r1,#3
clr r2, r6
clr r2 r6
clr test,#2
inc r1, r2
inc r1 r2
dec test1, test2, test3
dec test1 test2 test3
jmp %test1, %test2
jmp %test1 %test2
bne test1, test1
bne test1 test1
jsr test1, test1
jsr test1 test1
red r3, r5
red r3 r5
prn r1, r2
prn r1 r2

;labelTest
labelTest1:.data 123 .data
labelTest2:.string "sdf" .string
labelTest3:.extern Hello World
labelTest4:.entry Goodbye Earth
labelTest5:mov A, r1, r2
labelTest6:mov A, r1 r2
labelTest7:cmp A, r1, r2
labelTest8:cmp A, r1 r2
labelTest9:add A, r0, r1
labelTest10:add A, r0 r1
labelTest11:sub #3, r1, r5
labelTest12:sub #3, r1 r5
labelTest13:lea test, r3, r4
labelTest14:lea test, r3 r4
labelTest15:clr r2, r6
labelTest16:clr r2 r6
labelTest17:inc r1, r4
labelTest18:inc r1 r4
labelTest19:dec test1, test2, test3
labelTest20:dec test1 test2 test3
labelTest21:jmp test1, test2
labelTest22:jmp MISSING COMMA
labelTest23:bne , test
labelTest24:bne test test
labelTest25:jsr test, test
labelTest26:jsr test test
labelTest27:red test, r5
labelTest28:red r3 r5
labelTest29:prn r1, r2
labelTest30:prn r1 r2


;missing word
    .data
    .string
    .extern
    .entry
mov A
cmp A
add A
sub #3
lea A
clr
inc
dec
jmp
bne
jsr
red
prn
labelTest31:.data
labelTest32:.string
labelTest33:.extern
labelTest34:.entry
labelTest35:mov A
labelTest36:cmp A
labelTest37:add A
labelTest38:sub #3
labelTest39:lea HAHAHA
labelTest40:clr
labelTest41:inc
labelTest42:dec
labelTest43:jmp
labelTest44:bne
labelTest45:jsr
labelTest46:red
labelTest47:prn


;addressing errors
mov lable1, #1
mov #-1, #5
add #3, #1
add #-1, #5
add lable2, #-1
sub #-1, #5
sub lable2, #-1
lea #-1, #8
lea #-1, r4
lea lable1, #-1
lea r1, #-1
lea r1, r0
lea labelTest47, #-1
lea r1, label2
clr #-1
not #-1
inc #-1
dec #-1
jmp #-1
jmp r1,r2
bne #-1
jsr #-1
rts #-1
rts labelTest47
rts lable1
rts r1
stop #-1
stop labelTest47
stop lable1
stop r1


