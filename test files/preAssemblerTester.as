mcr  m0
.data 1,2,3
.string "this is macro test 0 tab after mcr"
endmcr

;test0
m0
;end test0


     mcr m1
.data 1,2,3
.string "this is macro test 1 tab and space befor mcr"
endmcr

;test1
m1
;end test1

.string "text befor 2" mcr m2
.data 1,2,3
.string "this is macro test 2"
endmcr

;test2
m2
;end test2

mcr m3 .stinrg "text after mcr 3"
.data 1,2,3
.string "this is macro test 3"
endmcr

;test3
m3
;end test3

mcr m4
.data 1,2,3
.string "this is macro test 4"
.string "text befor endmcr 4 " endmcr

;test4
m4
;end test4

mcr m5
.data 1,2,3
.string "this is macro test 5"
endmcr .string "text after endmcr 5"

;test5
m5
;end test5


mcr m6
.string "this is macro test 6 this macro is ververyververyververyververyververyververyververyververyververyververyververyververylong"
.string "this is macro test 6 this macro is ververyververyververyververyververyververyververyververyververyververyververyververylong"
endmcr

;test6
m6
;end test6

mcr r1
.string "this macro name is reserved word"
endmcr

;test7 reserved word
r1
;end test7

mcr m8
.string "this is macro with no end"

