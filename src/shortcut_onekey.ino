/*
Adafruit NeoKey Trinkey（SAMD21/NeoPixel搭載 MX互換スイッチ対応USBキー）
https://www.switch-science.com/products/10049
  NeoPixel 0
  Switch   1
  Touch    2/A1


Adafruit NeoKey Trinkey  Overview
https://learn.adafruit.com/adafruit-neokey-trinkey
Adafruit NeoKey Trinkey  Factory Shipped Demo
https://learn.adafruit.com/adafruit-neokey-trinkey/factory-shipped-demo
Adafruit_Learning_System_Guides/Factory_Tests/NeoKey_Trinkey_FactoryTest
https://github.com/adafruit/Adafruit_Learning_System_Guides/blob/main/Factory_Tests/NeoKey_Trinkey_FactoryTest/NeoKey_Trinkey_FactoryTest.ino

Arduino HID Project
https://github.com/NicoHood/HID
Arduino HID-Projectを日本語キーボードに対応する
https://qiita.com/nak435/items/bbe04300c67c37febb7e
Arduino HID-Project.hライブラリとは？
https://speeddemon.jp/hid-project-h/
*/

#include <Adafruit_NeoPixel.h>
#include <HID-Project.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
//明るさ初期化(最大:255)
int16_t neo_brightness = 32;
//カラー切替タイミング
const int neo_interval = 600;
//うちOff時間
const int neo_interval_off = 100;
//カラー総数
const unsigned int neo_color_num = 6;
//現在のカラー番号(-1:消灯、0,1,2,…,neo_color_num-1:点灯)
int neo_color_no = -1;

//前回loop時のスイッチ状態（押:true、離:false）
bool last_switch = true;
//スイッチ押した際のmillis()
unsigned long tm_sw_pressed = 0;

//Mouse Zitter
//マウスを動かす間隔[[msec]
const unsigned long tm_mouse_interval = 300 * 1000;
//マウス用タイマ
unsigned long tm_mouse = 0;
//マウス移動量
const int mouse_move_px = 3;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_SWITCH, INPUT_PULLDOWN);
  Keyboard.begin();
  Mouse.begin();
  strip.begin();
  strip.setBrightness(neo_brightness);
  strip.show();  // Initialize all pixels to 'off'
  tm_mouse = millis() + tm_mouse_interval;
}

void loop() {
  //Mouse Zitter
  if (millis() > tm_mouse) {
    Mouse.move(0, mouse_move_px, 0);
    delay(5);
    strip.setPixelColor(0, strip.ColorHSV(128 * 256, 255, 16));
    strip.show();
    delay(30);
    Mouse.move(0, - mouse_move_px, 0);
    delay(5);
    strip.setPixelColor(0, 0);
    strip.show();
    tm_mouse = millis() + tm_mouse_interval;
  }
  //Shortcut Key
  bool curr_switch = digitalRead(PIN_SWITCH);
  if (curr_switch != last_switch) {
    //スイッチ状態に変化あり
    if (curr_switch) {
      //スイッチが押された
      Serial.println("Pressed");
    } else {
      //スイッチが離された
      Serial.println("Released");
      if (neo_color_no == 0) {
        //タスクマネージャ
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_ESC);
        delay(50);
        Keyboard.releaseAll();
      } else if (neo_color_no == 1) {
        //コマンドプロンプト        
        Keyboard.press(KEY_LEFT_WINDOWS);
        Keyboard.press('r');
        delay(50);
        Keyboard.releaseAll();
        delay(500);
        Keyboard.print("cmd\n");
      } else if (neo_color_no == 2) {
        //エクスプローラ
        Keyboard.press(KEY_LEFT_WINDOWS);
        Keyboard.press('r');
        delay(50);
        Keyboard.releaseAll();
        delay(500);
        Keyboard.print("explorer\n");
      } else if (neo_color_no == 3) {
        //「\n」:Enter
        Keyboard.print("Hello, World!\n");
      } else {
      }
    }
    last_switch = curr_switch;
  } else {
    if (curr_switch) {
      unsigned long t = millis() - tm_sw_pressed;
      if (t % neo_interval < neo_interval_off) {
        neo_color_no = -1;
      } else {
        neo_color_no = (t / neo_interval) % neo_color_num;
      }
      if (neo_color_no >= 0) {
        // 色相(strip.ColorHSV()の第１引数:0～65535)の上位1byte
        //   0：赤
        //  32：オレンジ
        //  64：黃
        //  96：緑
        // 128：水色
        // 160：青
        // 192：紫
        // 224：ピンク
        long hue = 256 * 256 * neo_color_no / neo_color_num;
        strip.setPixelColor(0, strip.ColorHSV(hue, 255, 255));
      } else {
        strip.setPixelColor(0, 0);
      }
      strip.show();

    } else {
      neo_color_no = -1;
      tm_sw_pressed = millis();
      strip.setPixelColor(0, 0);
      strip.show();
    }
  }
  delay(10);
}