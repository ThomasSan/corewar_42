.name "ouineur"
.comment "Here for save the world - by pepito"

init:
	sti		r1, %:start, %1
	sti		r1, %:fork_a, %1
	sti		r1, %:while, %1
	sti		r1, %:wall_a, %1
	sti		r1, %:wall_a, %220
	sti		r1, %:wall_a, %225
	sti		r1, %:wall_a, %230
	sti		r1, %:wall_a, %235
	sti		r1, %:fork_b, %1

start:
	live	%10
	ld		%0, r2
	fork	%:fork_b

fork_a:
	live	%42
	ld		%0, r2
	fork	%:wall_a

while:
	live	%1
	zjmp	%:while

wall_a:
	live	%42
	ld		%6,		r10
	ld		%590174, r3
	st		r3, -370
	sub		r3, r10, r3
	st		r3, -374
	sub		r3, r10, r3
	st		r3, -378
	sub		r3, r10, r3
	st		r3, -382
	sub		r3, r10, r3
	st		r3, -386
	sub		r3, r10, r3
	st		r3, -390
	sub		r3, r10, r3
	st		r3, -394
	sub		r3, r10, r3
	st		r3, -398
	sub		r3, r10, r3
	st		r3, -402
	sub		r3, r10, r3
	st		r3, -406
	sub		r3, r10, r3
	st		r3, -410
	sub		r3, r10, r3
	st		r3, -414
	sub		r3, r10, r3
	st		r3, -418
	sub		r3, r10, r3
	st		r3, -422
	sub		r3, r10, r3
	st		r3, -426
	sub		r3, r10, r3
	st		r3, -430
	sub		r3, r10, r3
	st		r3, -434
	sub		r3, r10, r3
	st		r3, -438
	sub		r3, r10, r3
	st		r3, -442
	sub		r3, r10, r3
	st		r3, -446
	sub		r3, r10, r3
	live	%42
	live	%42
	live	%42
	live	%42
	ld		%0, r2
	zjmp	%:wall_a

fork_b:
	live	%42
	fork	%:infinite_fork
	ld		%0, r2
	zjmp	%:wall_a

infinite_fork:
	live	%42
	ld		%0, r2
	sti		r2, %:init, %0
	sti		r2, %:init, %4
	sti		r2, %:init, %8
	sti		r2, %:init, %12
	sti		r2, %:init, %16
	sti		r2, %:init, %20
	sti		r2, %:init, %24
	sti		r2, %:init, %28
	sti		r2, %:init, %32
	sti		r2, %:init, %36
	sti		r2, %:init, %40
	sti		r2, %:init, %44
	sti		r2, %:init, %48
	sti		r2, %:init, %52
	sti		r2, %:init, %56
	sti		r2, %:init, %60
	sti		r2, %:init, %64
	sti		r2, %:init, %66
	fork	%:start
	zjmp	%:infinite_fork

end_secu:
zjmp	%:wall_a
ld		%0, r2
zjmp	%:wall_a
