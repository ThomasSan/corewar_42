.name "Mutated champion"
.comment "Ha, Ha, Ha, bcvxlgjdfhgjskhd"

sti		r1, %:live2, %1
ld		%1, r3
ld		%33, r6

forks:
	add		r2, r3, r2
	xor		r2, %4, r4

live2:
	live	%4

zjmp	%:endwhile
fork	%:forks
ld		%0, r4
zjmp	%:forks

endwhile:
	ld		%0, r4

###############################################################################

entry:
	fork	%:coregeni
	st		r1, 6
	live	%42
	fork	%:torpgeni
	st		r1, 6
	live	%42
	fork	%:avdefgeni

ardeftgt:

ardefgeni:
	st		r1, 6

ardefgen:
	live	%213904
	fork	%:ardefgen

ardefinit:
	sti		r1, %:ardefl1, %1
	st		r1, 6
	live	%43123
	sti		r1, %:ardefchk, %1
	ld		%-6, r11
	ld		%-6, r12
	ld		%150994953, r13
	ld		%-186, r14

ardefwrite:

ardefl1:
	live	%295423
	sti		r13, %:ardeftgt, r11
	add		r11, r12, r11
	sti		r13, %:ardeftgt, r11
	add		r11, r12, r11

ardefchk:
	live	%3940641
	xor		r11, r14, r15
	zjmp	%:ardefinit
	
ardefloop:
	ld		%0, r16
	zjmp	%:ardefwrite

coregeni:
	st		r1, 6

coregen:
	live	%123012
	fork	%:coregen

coreinit:
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	st		r1, 58
	ld		%0, r16

corelive:
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	live	%985341
	zjmp	%:corelive

avdefgeni:
	st		r1, 6

avdefgen:
	live	%213904
	fork	%:avdefgen

avdefinit:
	sti		r1, %:avdefl1, %1
	st		r1, 6
	live	%43123
	sti		r1, %:avdefchk, %1
	ld		%0, r11
	ld		%6, r3
	ld		%150994953, r13
	ld		%180, r14

avdefwrite:

avdefl1:
	live	%295423
	sti		r13, %:avdeftgt, r11
	add		r11, r12, r11
	sti		r13, %:avdeftgt, r11
	add		r11, r12, r11

avdefchk:
	live	%3940641
	xor		r11, r14, r15
	zjmp	%:avdefinit

avdefloop:	
	ld		%0, r16
	zjmp	%:avdefwrite

torpgeni:
	st		r1, 6

torpgen:
	live	%96824
	fork	%:torpgen

torpinit:
	ld		%0, r11
	ld		%4, r12
	ld		%96, r14
	sti		r1, %:torpchk, %1
	st		r1, 6

torpwrite:

torpl1:
	live	%8008135
	ldi		%:torpinit, r11, r13
	sti		r13, %400, r11
	add		r11, r12, r11
	ldi		%:torpinit, r11, r13
	sti		r13, %383, r11
	add		r11, r12, r11

torpchk:
	live	%89523
	xor		r11, r14, r15
	zjmp	%362

torploop:
	ld		%0, r15
	zjmp	%:torpwrite

avdeftgt:

################################################################################
