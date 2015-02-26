// Code provided by Smoke And Wires
// http://www.smokeandwires.co.nz
// This code has been taken from the Adafruit TFT Library and modified
//  by us for use with our TFT Shields / Modules
// For original code / licensing please refer to
// https://github.com/adafruit/TFTLCD-Library

#include "Adafruit_GFX.h"   // Core graphics library
#include "SWTFT.h" // Hardware-specific library
#include "TouchScreen.h"

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
// #define LCD_CS A3 // Chip Select goes to Analog 3
// #define LCD_CD A2 // Command/Data goes to Analog 2
// #define LCD_WR A1 // LCD Write goes to Analog 1
// #define LCD_RD A0 // LCD Read goes to Analog 0

// #define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

float temp = 0;

SWTFT tft;
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// SWTFT tft;

//TouchScreen part
#define YP A1 //tftloop-YU pcbundertft-13 arduinoshieldLCD_WR!!! arduinouno-A1
#define XM A2 //tftloop-XR pcbundertft-14 arduinoshieldLCD_RS!!! arduinouno-A2
#define YM 7  //tftloop-XR pcbundertft-15 arduinoshieldLCD_D7 arduinouno-7
#define XP 6  //tftloop-XR pcbundertft-12 arduinoshieldLCD_D6 arduinouno-6
#define TS_MINX 150//0
#define TS_MINY 120//0
#define TS_MAXX 920//900//320      //for calibrate analog resistans ~1500om/700om
#define TS_MAXY 940//800//900//240 //for calibrate analog resistans ~1500om/700om
#define MINPRESSURE 10    // analog calibrate
#define MAXPRESSURE 1000  // analog calibrate
#define bordur   5
#define pen      3
// For better pressure precision, we need to know the resistance// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(void) {
	Serial.begin(9600);
	Serial.println(F("TFT LCD test"));

	tft.reset();

	uint16_t identifier = tft.readID();


	Serial.print(F("LCD driver chip: "));
	Serial.println(identifier, HEX);


	tft.begin(identifier);
	tft.fillScreen(BLACK);

	//Serial.println(F("Benchmark                Time (microseconds)"));

	//Serial.print(F("Screen fill              "));
	//Serial.println(testFillScreen());
	//delay(500);

	//Serial.print(F("Text                     "));
	//Serial.println(testText());
	//delay(3000);

	//Serial.print(F("Lines                    "));
	//Serial.println(testLines(CYAN));
	//delay(500);

	//Serial.print(F("Horiz/Vert Lines         "));
	//Serial.println(testFastLines(RED, BLUE));
	//delay(500);

	//Serial.print(F("Rectangles (outline)     "));
	//Serial.println(testRects(GREEN));
	//delay(500);

	//Serial.print(F("Rectangles (filled)      "));
	//Serial.println(testFilledRects(YELLOW, MAGENTA));
	//delay(500);

	//Serial.print(F("Circles (filled)         "));
	//Serial.println(testFilledCircles(10, MAGENTA));

	//Serial.print(F("Circles (outline)        "));
	//Serial.println(testCircles(10, WHITE));
	//delay(500);

	//Serial.print(F("Triangles (outline)      "));
	//Serial.println(testTriangles());
	//delay(500);

	//Serial.print(F("Triangles (filled)       "));
	//Serial.println(testFilledTriangles());
	//delay(500);

	//Serial.print(F("Rounded rects (outline)  "));
	//Serial.println(testRoundRects());
	//delay(500);

	//Serial.print(F("Rounded rects (filled)   "));
	//Serial.println(testFilledRoundRects());
	//delay(500);

	//Serial.println(F("Done!"));
}

void loop(void) {
	//for (uint8_t rotation = 0; rotation<4; rotation++) {
	//      tft.setRotation(rotation);
	//      testText();
	//      delay(2000);
	//}

	//tft.setRotation(3);
	//tft.setCursor(90, 10);
	//tft.setTextSize(2);
	//tft.setTextColor(RED);
	//tft.println("Temperature");
	//tft.setTextSize(6);
	//tft.setCursor(70, 30);
	//tft.setTextColor(BLACK);
	//tft.println(temp);
	//temp = analogRead(5);
	//temp *= 0.48828125;
	//tft.setCursor(70, 30);
	//tft.setTextColor(GREEN);
	//tft.println(temp);

	Point p = ts.getPoint(); // get analog point
	pinMode(XM, OUTPUT); //2 chip on one pins
	pinMode(YP, OUTPUT); //2 chip on one pins
	if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { // analog calibrate
		p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width()); // aprocsimate variable
		p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height()); // aprocsimate variable

		//    if (300< p.x) { // erase only on bordur  //no need have reset button
		//      Serial.println("erase"); // test
		//      tft.fillRect(0, 0, tft.width(), tft.height(), RED);// BLACK); //fill black
		//    }

		// test
		Serial.print("getPoint x="); Serial.print(p.x); Serial.print(" y="); Serial.print(p.y); Serial.print(" PRESSURE="); Serial.println(p.z);

		// paint
		//if (((p.x)<tft.width()) && ((p.y)<tft.height())) { tft.fillRect(p.x, p.y, pen, pen, GREEN); }
	}
}

unsigned long testFillScreen() {
	unsigned long start = micros();
	tft.fillScreen(BLACK);
	tft.fillScreen(RED);
	tft.fillScreen(GREEN);
	tft.fillScreen(BLUE);
	tft.fillScreen(BLACK);
	return micros() - start;
}

unsigned long testText() {
	tft.fillScreen(BLACK);
	unsigned long start = micros();
	tft.setCursor(0, 0);
	tft.setTextColor(WHITE);  tft.setTextSize(1);
	tft.println("Hello World!");
	tft.setTextColor(YELLOW); tft.setTextSize(2);
	tft.println(1234.56);
	tft.setTextColor(RED);    tft.setTextSize(3);
	tft.println(0xDEADBEEF, HEX);
	tft.println();
	tft.setTextColor(GREEN);
	tft.setTextSize(5);
	tft.println("Groop");
	tft.setTextSize(2);
	tft.println("I implore thee,");
	tft.setTextSize(1);
	tft.println("my foonting turlingdromes.");
	tft.println("And hooptiously drangle me");
	tft.println("with crinkly bindlewurdles,");
	tft.println("Or I will rend thee");
	tft.println("in the gobberwarts");
	tft.println("with my blurglecruncheon,");
	tft.println("see if I don't!");
	return micros() - start;
}

unsigned long testLines(uint16_t color) {
	unsigned long start, t;
	int           x1, y1, x2, y2,
		w = tft.width(),
		h = tft.height();

	tft.fillScreen(BLACK);

	x1 = y1 = 0;
	y2 = h - 1;
	start = micros();
	for (x2 = 0; x2<w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = w - 1;
	for (y2 = 0; y2<h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t = micros() - start; // fillScreen doesn't count against timing

	tft.fillScreen(BLACK);

	x1 = w - 1;
	y1 = 0;
	y2 = h - 1;
	start = micros();
	for (x2 = 0; x2<w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = 0;
	for (y2 = 0; y2<h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t += micros() - start;

	tft.fillScreen(BLACK);

	x1 = 0;
	y1 = h - 1;
	y2 = 0;
	start = micros();
	for (x2 = 0; x2<w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = w - 1;
	for (y2 = 0; y2<h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t += micros() - start;

	tft.fillScreen(BLACK);

	x1 = w - 1;
	y1 = h - 1;
	y2 = 0;
	start = micros();
	for (x2 = 0; x2<w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = 0;
	for (y2 = 0; y2<h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

	return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
	unsigned long start;
	int           x, y, w = tft.width(), h = tft.height();

	tft.fillScreen(BLACK);
	start = micros();
	for (y = 0; y<h; y += 5) tft.drawFastHLine(0, y, w, color1);
	for (x = 0; x<w; x += 5) tft.drawFastVLine(x, 0, h, color2);

	return micros() - start;
}

unsigned long testRects(uint16_t color) {
	unsigned long start;
	int           n, i, i2,
		cx = tft.width() / 2,
		cy = tft.height() / 2;

	tft.fillScreen(BLACK);
	n = min(tft.width(), tft.height());
	start = micros();
	for (i = 2; i<n; i += 6) {
		i2 = i / 2;
		tft.drawRect(cx - i2, cy - i2, i, i, color);
	}

	return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
	unsigned long start, t = 0;
	int           n, i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(BLACK);
	n = min(tft.width(), tft.height());
	for (i = n; i>0; i -= 6) {
		i2 = i / 2;
		start = micros();
		tft.fillRect(cx - i2, cy - i2, i, i, color1);
		t += micros() - start;
		// Outlines are not included in timing results
		tft.drawRect(cx - i2, cy - i2, i, i, color2);
	}

	return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
	unsigned long start;
	int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

	tft.fillScreen(BLACK);
	start = micros();
	for (x = radius; x<w; x += r2) {
		for (y = radius; y<h; y += r2) {
			tft.fillCircle(x, y, radius, color);
		}
	}

	return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
	unsigned long start;
	int           x, y, r2 = radius * 2,
		w = tft.width() + radius,
		h = tft.height() + radius;

	// Screen is not cleared for this one -- this is
	// intentional and does not affect the reported time.
	start = micros();
	for (x = 0; x<w; x += r2) {
		for (y = 0; y<h; y += r2) {
			tft.drawCircle(x, y, radius, color);
		}
	}

	return micros() - start;
}

unsigned long testTriangles() {
	unsigned long start;
	int           n, i, cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(BLACK);
	n = min(cx, cy);
	start = micros();
	for (i = 0; i<n; i += 5) {
		tft.drawTriangle(
			cx, cy - i, // peak
			cx - i, cy + i, // bottom left
			cx + i, cy + i, // bottom right
			tft.color565(0, 0, i));
	}

	return micros() - start;
}

unsigned long testFilledTriangles() {
	unsigned long start, t = 0;
	int           i, cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(BLACK);
	start = micros();
	for (i = min(cx, cy); i>10; i -= 5) {
		start = micros();
		tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
			tft.color565(0, i, i));
		t += micros() - start;
		tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
			tft.color565(i, i, 0));
	}

	return t;
}

unsigned long testRoundRects() {
	unsigned long start;
	int           w, i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(BLACK);
	w = min(tft.width(), tft.height());
	start = micros();
	for (i = 0; i<w; i += 6) {
		i2 = i / 2;
		tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
	}

	return micros() - start;
}

unsigned long testFilledRoundRects() {
	unsigned long start;
	int           i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(BLACK);
	start = micros();
	for (i = min(tft.width(), tft.height()); i>20; i -= 6) {
		i2 = i / 2;
		tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
	}

	return micros() - start;
}

