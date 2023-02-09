// declare function Sys.init 0
(Sys.init)
@0
D=A
@R10
M=D
@0
D=A
@R12
M=D
@Sys.init_NO_ARGS
D;JEQ
(Sys.init_LCL_INIT)
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
@Sys.init_LCL_INIT
D;JGT
@0
D=A
@SP
M=M+D
(Sys.init_NO_ARGS)
// push constant 4000
@4000
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 0
@3
D= A
@0
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 5000
@5000
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 1
@3
D= A
@1
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// call Sys.main 0
@Sys.main_1_return_address
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
@Sys.main
0;JMP
(Sys.main_1_return_address)
// pop temp 1
@5
D= A
@1
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// label LOOP 
(LOOP)
// goto LOOP 
@LOOP
0;JMP
// declare function Sys.main 5
(Sys.main)
@0
D=A
@R10
M=D
@5
D=A
@R12
M=D
@Sys.main_NO_ARGS
D;JEQ
(Sys.main_LCL_INIT)
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
@Sys.main_LCL_INIT
D;JGT
@5
D=A
@SP
M=M+D
(Sys.main_NO_ARGS)
// push constant 4001
@4001
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 0
@3
D= A
@0
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 5001
@5001
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 1
@3
D= A
@1
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 200
@200
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 1
@LCL
D= M
@1
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 40
@40
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 2
@LCL
D= M
@2
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 3
@LCL
D= M
@3
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 123
@123
D=A
@SP
A=M
M=D
@SP
M=M+1
// call Sys.add12 1
@Sys.add12_1_return_address
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
@1
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
@Sys.add12
0;JMP
(Sys.add12_1_return_address)
// pop temp 0
@5
D= A
@0
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
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
// push local 2
@LCL
D = M
@2
A = A + D
D=M
@SP
A=M
M=D
@SP
M=M+1
// push local 3
@LCL
D = M
@3
A = A + D
D=M
@SP
A=M
M=D
@SP
M=M+1
// push local 4
@LCL
D = M
@4
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
// declare function Sys.add12 0
(Sys.add12)
@0
D=A
@R10
M=D
@0
D=A
@R12
M=D
@Sys.add12_NO_ARGS
D;JEQ
(Sys.add12_LCL_INIT)
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
@Sys.add12_LCL_INIT
D;JGT
@0
D=A
@SP
M=M+D
(Sys.add12_NO_ARGS)
// push constant 4002
@4002
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 0
@3
D= A
@0
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 5002
@5002
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 1
@3
D= A
@1
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
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
// push constant 12
@12
D=A
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
