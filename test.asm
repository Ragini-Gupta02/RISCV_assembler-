
.data

abc: .word 1,2,33,678,234
hello world

.text

and x31,x14,x21
sub x12,x22,x23
addi x11,x21,100
jal x21,label
l3:
lw x13,98(x21)
sb x25,0(x17)
and x5,x14,x21
label:
sub x12,x22,x23 
addi x4, x0, 569
lw x13,98(x5)
sb x1,0(x17)
jal x2,l2
lui x3,1234

sub x1,x2,x4
jal x1,l2
l2:
