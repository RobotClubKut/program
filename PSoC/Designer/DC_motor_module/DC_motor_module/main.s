	cpu LMM
	.module main.c
	.area text(rom, con, rel)
	.dbfile ./main.c
	.dbfile C:\Users\MATSUD~1\Dropbox\基盤班\プログ~1\PSoC\Designer\DC_MOT~1\DC_MOT~1\main.c
	.dbfunc e main _main fV
_main::
	.dbline 0 ; func end
	jmp .
	.dbend
	.area data(ram, con, rel)
	.dbfile C:\Users\MATSUD~1\Dropbox\基盤班\プログ~1\PSoC\Designer\DC_MOT~1\DC_MOT~1\main.c
_MyI2C_Motor::
	.byte 0,0,0,0,0,0
	.dbstruct 0 6 I2C_Motor
	.dbfield 0 x_1 c
	.dbfield 1 x_2 c
	.dbfield 2 y_1 c
	.dbfield 3 y_2 c
	.dbfield 4 z_1 c
	.dbfield 5 z_2 c
	.dbend
	.dbsym e MyI2C_Motor _MyI2C_Motor S[I2C_Motor]
