// call Sys.init 0
@Sys.init_1_return_address
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
D=M-D
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(Sys.init_1_return_address)
// declare function SimpleFunction.test 2
(SimpleFunction.test)
@0
D=A
@R10
M=D
@2
D=A
@R12
M=D
@SimpleFunction.test_NO_ARGS
D;JEQ
(SimpleFunction.test_LCL_INIT)
@R10
D=M
@SP
A=M+D
M=0
@R10
M=M+1
D=M
@R12
D=M-D
@SimpleFunction.test_LCL_INIT
D;JGT
@2
D=A
@SP
M=M+D
(SimpleFunction.test_NO_ARGS)
// push local 0
@LCL
D = M
@0
A = A + D
D=M
@SP
A=M
M=D
@SP
M=M+1
// push local 1
@LCL
D = M
@1
A = A + D
D=M
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=D+M
@SP
M=M+1
// not
@SP
AM=M-1
M=!M
@SP
M=M+1
// push argument 0
@ARG
D=M
@0
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
// add
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=D+M
@SP
M=M+1
// push argument 1
@ARG
D=M
@1
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
// sub
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
// return from function 
@LCL
D=M
@R11
M=D
@5
D=A
@R11
D=M-D
A=D
D=M
@R9
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D+1
@R11
D=M
@1
D=D-A
A=D
D=M
@THAT
M=D
@R11
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@R11
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@R11
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@R9
A=M
0;JMP