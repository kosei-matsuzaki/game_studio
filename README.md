# GAME STUDIO

## HOW TO PLAY
ターミナルで以下のコマンドを実行してください。
```shell
gcc game.c */*.c -o play -lm -Wall && ./play
```

## EXPLANATION
### TIC TAC TOE
- プレイ人数: 2名
- 始めに盤面のサイズ(3~20)と何目揃えたら勝ちかを設定してください
    - 例えば  `Size: 3 Victory Condition: 3` とすれば〇×ゲーム（クソゲー）になります
- 入力は縦と横の数字を指定してください

### TEXAS HOLD'EM
- プレイ人数: 1名（コンピュータ: 4人）
- 初期チップ数は30000点、BBは200点で開始します
- 約5ラウンドでBBが上昇します
- テキサスホールデムのルールについては[こちら](https://www.bodoge-intl.com/list/insapo/texasholdem/)を参照ください

### TETRIS
- プレイ人数: 1人
- 操作方法は以下の通りです
    - A: 左に移動
    - D: 右に移動 
    - Q: 反時計回りに90°
    - E: 時計回りに90°
    - S: 下に移動 
- 1行消去すると10ポイントを取得します
- 1分30秒ごとにレベルが上昇し、落下速度が上がります
 

## TODO
- 