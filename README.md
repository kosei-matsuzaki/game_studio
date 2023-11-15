# GAME STUDIO
様々なゲームを遊ぶことができます

## HOW TO PLAY
ターミナルで以下のコマンドを実行してください
```shell
git clone https://github.com/kosei-matsuzaki/game_studio
```
```shell
gcc game.c */*.c */*/*.c -o play -lm -Wall && ./play
```
ターミナルの種類によって処理が追い付かず、画面が点滅してしまう可能性があります

## EXPLANATION
### TIC TAC TOE
- プレイ人数: 2名
- 始めに盤面のサイズ(3~20)と何目揃えたら勝ちかを設定してください
    - 例えば  `Size: 3 Victory Condition: 3` とすれば〇×ゲームになります
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

### RHYTHM
- プレイ人数: 1人
- 左の列からD, F, J, Kのキーが割り当てられています
- Qを押すといつでもプレイを中断できます
- スコアについて
    - SS: acc100%
    - S:  miss無しかつacc92%以上
    - A:  acc93%以上
    - B:  acc85%以上
    - C:  acc75%以上
    - D:  acc75%未満
- マップの追加方法
    1. ```ryhthm/maps```下にcファイルを作成
    2. 作成したcファイルに譜面情報を記入（以下例）
        ```c
            #include "maps.h"
            const map_info doremi = {
                .id = 2, // ID（かぶりがないように）
                .name = "Do-Re-Mi",// 曲のタイトル
                .difficulty = 2.0, // 難易度
                .bpm = 120, // bpm(1分間の拍数）
                .beat = 4, // 1小節の拍数
                .bar_count = 19, // 小節数
                .map = {...}, // 1の場所にノーツ・拍数^2の配列を1小節に用意する
            };
        ```
    3. 複数ノーツが短時間で連続すると入力検知が追いつかない可能性があります
    4. ```rhythm/maps/maps.h```でextern
    5. ```rhythm/map.c```のr_map_initializeとr_map_listに追記
- マップ一覧(2023/11/10)
    - 池の雨（ヤマハの音楽）
    - ドレミの歌
    - 夏祭り

