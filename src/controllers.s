.zeropage
_ctrl1:			.res 3 ; first 2 bytes are controller button state and 3rd byte is connection status
_ctrl2:			.res 3

.exportzp _ctrl1
.exportzp _ctrl2

.export _ctrl_init ; prepend labels with _ so C can see them
.export _read_ctrl1
.export _read_ctrl2
.export _read_ctrls
.export _read_nes_ctrl1
.export _read_nes_ctrl2
.export _read_nes_ctrls
.export _read_controllers
.export _delay

;
.include "rp6502.inc" 

bit_latch = $08 ; PA3 (GPIO pin 9): LATCH (both controllers)  
bit_data1 = $10 ; PA4 (GPIO pin 11): DATA  (controller #1)  
bit_clock = $20 ; PA5 (GPIO pin 13): CLK   (both controllers)  
bit_data2 = $40 ; PA6 (GPIO pin 15): DATA  (controller #2)

.code
.proc _ctrl_init: near
	lda #$FF-bit_data1-bit_data2
	sta VIA_DDRA
	rts
.endproc

.proc _read_ctrl1: near
	lda #00
	sta VIA_PA1

	; pulse latch
	lda #bit_latch
	sta VIA_PA1
	lda #0
	sta VIA_PA1

	; read 2x 8 bits
	ldx #0
loop2:
	ldy #8
loop1:
	lda VIA_PA1
	and #bit_data1
	cmp #bit_data1
	rol _ctrl1,X
	lda #bit_clock
	sta VIA_PA1
	lda #0
	sta VIA_PA1
	dey
	bne loop1
	inx
	cpx #2
	bne loop2
	rts
.endproc

.proc _read_ctrl2: near
	lda #00
	sta VIA_PA1

	; pulse latch
	lda #bit_latch
	sta VIA_PA1
	lda #0
	sta VIA_PA1

	; read 2x 8 bits
	ldx #0
loop2:
	ldy #8
loop1:
	lda VIA_PA1
	cmp #bit_data2
	rol _ctrl2,X
	lda #bit_clock
	sta VIA_PA1
	lda #0
	sta VIA_PA1
	dey
	bne loop1
	inx
	cpx #2
	bne loop2
	rts
.endproc

.proc _read_ctrls: near
	lda #00
	sta VIA_PA1

	; pulse latch
	lda #bit_latch
	sta VIA_PA1
	lda #0
	sta VIA_PA1

	; read 2x 8 bits
	ldx #0
loop2:
	ldy #8
loop1:
	lda VIA_PA1
	cmp #bit_data2
	rol _ctrl2,X
	and #bit_data1
	cmp #bit_data1
	rol _ctrl1,X
	lda #bit_clock
	sta VIA_PA1
	lda #0
	sta VIA_PA1
	dey
	bne loop1
	inx
	cpx #2
	bne loop2
	rts
.endproc

.proc _read_nes_ctrl1: near
	lda #00
	sta VIA_PA1

	; pulse latch
	lda #bit_latch
	sta VIA_PA1
	lda #0
	sta VIA_PA1

	ldy #8
loop:
	lda VIA_PA1
	and #bit_data1
	cmp #bit_data1
	rol _ctrl1,X
	lda #bit_clock
	sta VIA_PA1
	lda #0
	sta VIA_PA1
	dey
	bne loop
	rts
.endproc

.proc _read_nes_ctrl2: near
	lda #00
	sta VIA_PA1

	; pulse latch
	lda #bit_latch
	sta VIA_PA1
	lda #0
	sta VIA_PA1

	ldy #8
loop:
	lda VIA_PA1
	cmp #bit_data2
	rol _ctrl2,X
	lda #bit_clock
	sta VIA_PA1
	lda #0
	sta VIA_PA1
	dey
	bne loop
	rts
.endproc

.proc _read_nes_ctrls: near
	lda #00
	sta VIA_PA1

	; pulse latch
	lda #bit_latch
	sta VIA_PA1  
	lda #0
	sta VIA_PA1

	ldy #8
loop:
	lda VIA_PA1
	cmp #bit_data2
	rol _ctrl2,X
	and #bit_data1
	cmp #bit_data1
	rol _ctrl1,X
	lda #bit_clock
	sta VIA_PA1
	lda #0
	sta VIA_PA1
	dey
	bne loop
	rts
.endproc

.proc _read_controllers: near
	lda #00
	sta VIA_PA1

	; pulse latch
	lda #bit_latch
	sta VIA_PA1
	lda #0
	sta VIA_PA1

	; read 3x 8 bits
	ldx #0
loop2:
	ldy #8
loop1:
	lda VIA_PA1
	cmp #bit_data2
	rol _ctrl2,X
	and #bit_data1
	cmp #bit_data1
	rol _ctrl1,X
	lda #bit_clock
	sta VIA_PA1
	lda #0
	sta VIA_PA1
	dey
	bne loop1
	inx
	cpx #3
	bne loop2
	rts
.endproc

.proc _delay: near
	ldx #$FF ;2
	ldy #$FF ;2: 4 total
loop:
	dey ;2
	bne loop ;3, 2
	dex ;2
	bne loop ;3, 2
	rts ;6
.endproc

