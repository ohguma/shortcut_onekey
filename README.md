# Shortcut 1key 2024年版

## 概要

+ Adafruit NeoKey Trinkey を使った人差し指デバイス
  + Adafruit NeoKey Trinkey（SAMD21/NeoPixel搭載 MX互換スイッチ対応USBキー）
    + フルカラー NeoPixel LEDを搭載。
    + 静電容量式タッチパッドを搭載。
    + Cherry社MXタイプのキースイッチを1個実装可能。
      + NeoPixcel LEDの光がキーキャップで拡散できるよう本体が透明なキースイッチがオススメ。
  + 購入先：https://www.switch-science.com/products/10049
  + 製造元の販売ページ：https://www.adafruit.com/product/5020
    + [Arduino IDE 初期設定](https://learn.adafruit.com/adafruit-neokey-trinkey/arduino-ide-setup)
      + ボードマネージャーでボードを追加するための設定が必要。
    + [工場出荷時デモ](https://learn.adafruit.com/adafruit-neokey-trinkey/factory-shipped-demo)



## ソース

+ [shortcut_onekey.ino](/src/shortcut_onekey.ino)
  + キースイッチ押下時は、NeoPixcelが一定間隔で色を変えて光る。
  + キースイッチを離したタイミングにより、複数のキー操作を切り替える。
    + 赤　タスクマネージャ起動（CTRL + SHIFT + ESC）
    + 黄　コマンドプロンプト起動（Win + R して「cmd」ENTER）
    + 緑　エクスプローラ起動（Win + R して「explorer」ENTER）
    + 水　「Hello, World!」と入力してENTER
    + 青　未実装
    + 紫　未実装
  + Mouse Zitter の機能を持つ。動作時は NeoPixel が一瞬光る。
  + キースイッチの実装前提。タッチパッドは未使用。

+ [keycap8mm.stl](/cad/keycap8mm.stl)
  + 適当に作成したキーキャップのSTLファイル。
  + 光の透過する白系のフィラメントがオススメ。
  + 市販のキーキャップでも良い。

## 動作例

+ 最終的にキースイッチこちらを使用した。
  + [KiiBoom リニア55gf クリスタルキーボードスイッチ PCハウジング付き 5ピンメカニカルスイッチ ナイロンステム DIYゲーミングキーボード用 35ピース](https://www.amazon.co.jp/dp/B0BJBF1FGN)
  + 購入時価格 ￥2,040

+ [発光状態](https://x.com/ohguma/status/1866858067738103999)
  + キーキャップは光の透過を期待して白色TPEで召喚した。
+ [キースイッチ操作](https://x.com/ohguma/status/1864302181354205467)
  + この時点では本体黒色のキースイッチを使っていた。


----

2024-12-13 ohguma 初版