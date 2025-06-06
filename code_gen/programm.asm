include \masm32\include\masm32rt.inc

.365

.data?
x8 dd ?
x12 dd ?
x13 dd ?
x15 dd ?
x17 dd ?
x19 dd ?
x23 dd ?
x34 dd ?
x41 dd ?
x60 dd ?
x67 dd ?
x700	dd	?
x701	dd	?

.data
x0 dd 1
x287 dd 0
x288 dd 7
x289 dd 31
x290 dd 1
x291 dd 2
x292 dd 3
x293 dd 0
x294 dd 0
x295 dd 0
x296 dd 0
x297 dd 0
x298 dd 0
x299 dd 0
x300 dd 0
x301 dd 0

.code
label_10:
mov eax, x287
mov x23, eax
label_30:
mov eax, x288
mov x13, eax
label_50:
mov eax, x289
mov x12, eax
label_55:
mov eax, x287
mov x17, eax
label_60:
mov eax, x13
mov x23, eax
label_70:
call label_2000
label_80:
je label_90
jl label_90
jg label_90
jle label_90
jge label_90
jne label_90
label_81:
jmp label_1000
label_90:
mov eax, x12
mov x23, eax
label_100:
call label_2000
label_120:
jmp label_1000
label_1000:
mov eax, x290
add eax, x23
mov x293, eax
mov eax, x293
mov x19, eax
label_1010:
mov eax, x287
mov x15, eax
label_1020:
mov eax, x290
mov x41, eax
label_1030:
jge label_1070
jne label_1070
label_1040:
mov eax, x67
imul x291
mov x294, eax
mov eax, x294
mov x41, eax
label_1050:
mov eax, x290
add eax, x15
mov x295, eax
mov eax, x295
mov x15, eax
label_1060:
jmp label_1030
label_1070:
je label_1073
jl label_1073
jg label_1073
jle label_1073
jge label_1073
jne label_1073
label_1071:
mov eax, x287
mov x17, eax
label_1072:
ret
label_1073:
call label_3000
label_1074:
je label_1077
jl label_1077
jg label_1077
jle label_1077
jge label_1077
jne label_1077
label_1075:
mov eax, x287
mov x17, eax
label_1076:
ret
label_1077:
mov eax, x290
mov x17, eax
label_1078:
ret
label_3000:
mov eax, x290
mov x34, eax
label_2001:
jle label_2007
jge label_2007
jne label_2007
label_2002:
mov eax, x15
cdq
idiv 291
mov x296, eax
mov eax, x296
imul x291
mov x297, eax
je label_2007
jl label_2007
jg label_2007
jle label_2007
jge label_2007
jne label_2007
label_2003:
mov eax, x292
mov x8, eax
mov eax, x15
cdq
idiv 291
mov x298, eax
mov eax, x290
add eax, x298
mov x299, eax
mov eax, x299
mov x700 , eax
mov eax, x290
mov x701 , eax
label_256:
mov eax, x8
cmp eax, x700
jg label_257
label_2004:
mov eax, x15
cdq
idiv 8
mov x300, eax
mov eax, x300
imul x8
mov x301, eax
je label_2007
jl label_2007
jg label_2007
jle label_2007
jge label_2007
jne label_2007
label_2005:
mov eax, x8
add eax, x701
mov x8, eax
jmp label_-1
label_257:
label_2006:
ret
label_2007:
mov eax, x287
mov x34, eax
label_2008:
ret
label_3000:
print str$(x16),10,13
end start