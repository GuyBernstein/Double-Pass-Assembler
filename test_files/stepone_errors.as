;; First pass errors - mostly syntax validation, but also double definitions!

; label errors
LABEL: .data -0,5,6,7,2,6
CODELABEL: mov r0,r1
LOCALCODE: add r0,r1
LOCALDATA: .string "Some local data"
LABEL: .string "Same label twice!"
CODELABEL: .data "Again!"
.extern LOCALCODE
.extern LOCALDATA
.extern WHATEVEREXT
.extern LONGLONGLONGLONGLONGLONGLABEL
.extern 1nvalidLabel
.extern Label@With4t
.extern
WHATEVEREXT: .string "Another definition!"
VERY_VERY_VERY_VERY_VERY_LONG_LABEL_DEFINITION_SO_ITS_ILLEGAL: .data 0
SOME*INVALID&CHARS%HERE: .data 5
2tartWithNumISILLEGAL: .data -6
ALLVALIDBUTLASTI$: .string "more invalid!"

; data and string errors
.string "No closing
.string No opening"
.string Not at all
.data ,5,6,-7
.data 5,,6,-7
.data 5,6,,-7
.data 5,6,-7,
.data 5 6 -7
.data 5 6 , -7
.data 5 , 6 -7,
.data 0.5
.data 5.9
.data -0.1
.data .5
; 2^23+1
.data 8388609
.data -8388609
.data -5,8388609,-8388609
