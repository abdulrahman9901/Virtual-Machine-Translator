// push constant 10
@10
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 0
@LCL
D= M
@0
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 21
@21
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 22
@22
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop argument 2
@ARG
D= M
@2
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// pop argument 1
@ARG
D= M
@1
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 36
@36
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop this 6
@THIS
D= M
@6
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 42
@42
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 45
@45
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop that 5
@THAT
D= M
@5
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// pop that 2
@THAT
D= M
@2
A = A + D
D=A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 510
@510
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop temp 6
@5
D= A
@6
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
// push that 5
@THAT
D=M
@5
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
// push this 6
@THIS
D=M
@6
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
// push this 6
@THIS
D=M
@6
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
// push temp 6
@5
D=A
@6
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
(END)
@END
0;JMP
