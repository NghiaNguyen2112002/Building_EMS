#include "lcd_i2c.h"

uint8_t *Lcd_buffer = NULL;

CLCD_I2C_Name LCD;

uint8_t currentCol, currentRow;


//===========CUSTOM FOR ICON========//
uint8_t icon_temp[8] = {
		0b00000,
		0b00000,
		0b10101,
		0b01110,
		0b11011,
		0b01110,
		0b10101,
		0b00000
};

uint8_t icon_humi[8] = {
		0b00100,
		0b00100,
		0b01010,
		0b01010,
		0b10001,
		0b10001,
		0b10001,
		0b01110
};

static void Delay(uint16_t time){
	delay(time);
}

void Write4bit(uint8_t address, uint8_t data){
	Wire.beginTransmission(address);
	Wire.write(data);
	Wire.endTransmission();
}

static void WriteI2C(uint8_t data, uint8_t mode){
	uint8_t dataH, dataL;
	uint8_t data_I2C[4];

	dataH = data & 0xF0;
	dataL = (data << 4) & 0xF0;

	if(LCD.BACKLIGHT){
		dataH |= LCD_BACKLIGHT;
		dataL |= LCD_BACKLIGHT;
	}

	if(mode == LCD_DATA){
		dataH |= LCD_RS;
		dataL |= LCD_RS;
	}

	data_I2C[0] = dataH | LCD_EN;
	data_I2C[1] = dataH;
	data_I2C[2] = dataL | LCD_EN;
	data_I2C[3] = dataL;

	for(uint8_t i = 0; i < 4; i++){
		Write4bit(LCD.ADDRESS, data_I2C[i]);
		Delay(1);
	}
}



//===========================HIGH LEVEL FUNCTION===========================//
void CLCD_Init(uint16_t pin_sda, uint16_t pin_scl, uint8_t address, uint8_t row, uint8_t col){
    uint8_t i;

    Wire.begin(pin_sda, pin_scl, 100000);

	LCD.ADDRESS = address;
	LCD.COL = col;
	LCD.ROW = row;

	LCD.FUNCTIONSET = LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
	LCD.ENTRYMODE = LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	LCD.DISPLAYCTRL = LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	LCD.CURSORSHIFT = LCD_CURSORSHIFT | LCD_CURSORMOVE | LCD_MOVERIGHT;
	LCD.BACKLIGHT = LCD_BACKLIGHT;


	Delay(50);

	if(Lcd_buffer != NULL) delete []Lcd_buffer;
	Lcd_buffer = new uint8_t[LCD.ROW * LCD.COL];

	for(i = 0; i < LCD.ROW * LCD.COL; i++) Lcd_buffer[i] = ' ';

	WriteI2C(0x33, LCD_COMMAND);
	Delay(5);
	WriteI2C(0x33, LCD_COMMAND);
	Delay(5);
	WriteI2C(0x32, LCD_COMMAND);
	Delay(5);
	WriteI2C(0x20, LCD_COMMAND);
	Delay(5);

//	config lcd
	WriteI2C(LCD.ENTRYMODE, LCD_COMMAND);
	Delay(1);
	WriteI2C(LCD.DISPLAYCTRL, LCD_COMMAND);
	Delay(1);
	WriteI2C(LCD.CURSORSHIFT, LCD_COMMAND);
	Delay(1);
	WriteI2C(LCD.FUNCTIONSET, LCD_COMMAND);
	Delay(1);

	WriteI2C(LCD_CLEARDISPLAY, LCD_COMMAND);
	Delay(1);

	WriteI2C(LCD_RETURNHOME, LCD_COMMAND);
}

void SetCursor(uint8_t row, uint8_t col){
	uint8_t address_dram = 0x00;

	row = row % LCD.ROW;
	col = col % LCD.COL;

	switch(row){
	case 0:
		address_dram = 0x00 + col;
		break;
	case 1:
		address_dram = 0x40 + col;
		break;
	case 2:
		address_dram = 0x14 + col;
		break;
	case 3:
		address_dram = 0x54 + col;
		break;
	}

	WriteI2C(LCD_SETDDRAMADDR | address_dram, LCD_COMMAND);
}

void UpdateCharBuffer(uint8_t c){
	Lcd_buffer[currentRow * LCD.COL + currentCol] = c;
	currentCol++;
}

void CLCD_PrintCharBuffer(uint8_t row, uint8_t col, char c){
	currentRow = row % LCD.ROW;
	currentCol = col % LCD.COL;
	Lcd_buffer[currentRow * LCD.COL + currentCol] = c;
}

void CLCD_PrintStringBuffer(uint8_t row, uint8_t col, char* str){
	currentRow = row % LCD.ROW;
	currentCol = col % LCD.COL;
	while(*str){
		UpdateCharBuffer(*str++);
	}
}

void CLCD_PrintNumBuffer(uint8_t row, uint8_t col, int16_t num){
    char flag_num = 0;
    unsigned char i;
    unsigned long power_of_10 = 1000000000;
    currentRow = row % 2;
    currentCol = col % 16;

    if(num < 0) {
        num *= -1;
        UpdateCharBuffer('-');
    }
    else if(num == 0){
    	UpdateCharBuffer('0');
    	UpdateCharBuffer('0');
//        UpdateCharBuffer(' ');
//        UpdateCharBuffer(' ');
        return;
    }

    else if(num < 10){
        UpdateCharBuffer('0');
//        UpdateCharBuffer(num + '0');
    }

    for(i = 10; i > 0; i--){
        if( (num / power_of_10) != 0){
            flag_num = 1;
            UpdateCharBuffer(num / power_of_10 + '0');
        }
        else{
            if(flag_num != 0) UpdateCharBuffer('0');
        }
        num %= power_of_10;
        power_of_10 /= 10;
    }

//    UpdateCharBuffer(' ');
//    UpdateCharBuffer(' ');
}

void CLCD_PrintFloatBuffer(uint8_t row, uint8_t col, float f){
	uint8_t integer_part, decimal_part;
    char flag_num = 0;
    unsigned char i;
    unsigned long power_of_10 = 10000;

    currentRow = row % 2;
    currentCol = col % 16;

    integer_part = (uint8_t) f;
    decimal_part = (uint8_t) ((f - integer_part)*10);

	if(integer_part == 0) UpdateCharBuffer('0');

	for(i = 5; i > 0; i--){
        if( (integer_part / power_of_10) != 0){
            flag_num = 1;
            UpdateCharBuffer(integer_part / power_of_10 + '0');
        }
        else{
            if(flag_num != 0) UpdateCharBuffer('0');
        }
        integer_part %= power_of_10;
        power_of_10 /= 10;
    }
    UpdateCharBuffer('.');
    UpdateCharBuffer(decimal_part % 10 + '0');
}


void CLCD_ClearBuffer(void){
	uint8_t i;

	for(i = 0; i < LCD.ROW * LCD.COL; i++) Lcd_buffer[i] = ' ';
}

void CLCD_DisplayScreen(void){
	uint8_t i, j;

	for(i = 0; i < 2; i++){
		SetCursor(i, 0);
		for(j = 0; j < 16; j++){
			WriteI2C(Lcd_buffer[i * LCD.COL + j], LCD_DATA);
		}
	}
}


void CLCD_TurnBackLight(uint8_t isOn){
	if(isOn == 0){
		LCD.BACKLIGHT = LCD_NOBACKLIGHT;
	}
	else LCD.BACKLIGHT = LCD_BACKLIGHT;
	
}

//=============CUSTOM CHAR=============//
void CLCD_CreateChar(uint8_t addr, uint8_t* custom_arr){
	uint8_t i;

	WriteI2C(LCD_SETCGRAMADDR + 8*addr, LCD_COMMAND);

	for(i = 0; i < 8; i++){
		WriteI2C(custom_arr[i], LCD_DATA);
	}
}