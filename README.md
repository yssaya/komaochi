The text written in English is [here](README_en.md).
# Aoba駒落ち

「Aoba駒落ち」は、将棋の駒落ちを人間の知識なしでゼロから深層強化学習させるユーザ参加型の将棋人工知能プロジェクトです。  
香落、角落、飛落、2枚落、4枚落、6枚落、平手、の7種類を同時に学習します。勝率が5割になるように下手(先手)の強さを自動調節しています。  
AIは新定跡を発見、または二枚落ちの二歩突き切り、銀多伝などを再発見できるでしょうか？  

集めた棋譜や棋力のグラフ、棋譜のサンプルなどは[こちら](http://www.yss-aya.com/komaochi/)で公開しています。  
[AobaZero](http://www.yss-aya.com/aobazero/)との[違い](http://www.yss-aya.com/komaochi/diff.html)など。 

GPUがあれば、より高速に棋譜を生成できます。  
CPUだと10倍から100倍遅くなりますが、将棋をプレイして楽しむことは可能です。  

# 棋譜の生成に協力してみたい
[Windows用の実行ファイル(64bit版のみです)](https://github.com/yssaya/komaochi/releases)

CPUだけのマシンは
```
aobakomaochi-1.0-w64-cpu-only.zip
```
GPUがついたマシンは
```
aobakomaochi-1.0-w64-opencl.zip
```
をダウンロード、展開して、中のclick_me.batを実行してください。  
GPUの種類によっては autousi.cfg の  
```
Device        O-1:7:21W
```
を変更することでより高速で動作する場合があります。[autousi.cfg](autousi.cfg) の他のサンプルをご参考下さい。

Linuxの方は
```
komaochi-1.0.tar.gz
```
を展開してmakeしてから
```
./bin/autousi
```
を実行してください。

# 将棋所で遊んでみたい
CPU版をダウンロードして、click_me.batを実行します。しばらくすると最新のネットワークの重みファイルをダウンロードして「self-play started」が表示されて棋譜の生成を開始します。すかさずCtrl + Cで停止させます。(signal 1 caught)が表示されて、しばらく待つと止まります。  
weight_save/の下にw000000000066.txt という162MBほどのファイルが作られます。
(66、の数値は異なります)

aobakomaochi-1.0-w64-cpu-only.zipに同梱されているaobak.batを編集します。最後の1行が以下のようになっています。
```
bin\aobak -q -i -p 100 -w weight-save\w000000000066.txt
```
この66の部分を実際にダウンロードしてきたファイル名に合わせて書き直し、保存します。
将棋所にaobak.batをエンジンとして登録します。  
"-p 100"の100を増やすと強くなりますが、思考時間が長くなります。
CPU版は100で5秒ほどかかります。GPU版は4000で3秒ほどかかります(GPUの性能に依存します)。

将棋所はusiエンジンを動作させる将棋用のGUIです。こちらで入手できます。  
将棋所のページ
<http://shogidokoro.starfree.jp/>

# ShogiGUIで遊んでみたい
Aoba駒落ちはShogiGUIでも動作します。「ツール(T)」「オプション(O)」で「棋譜解析、検討モードで指し手をすべて送る」にチェックを入れて下さい。  
また2枚落ちを検討する場合、可能ならば2枚落ちの初期局面からの手順を含む棋譜で検討してください。  
これはAoba駒落ちは0手目の局面でこの棋譜が、香落ち、角落ち、飛落ち、2枚、4枚、6枚、平手かを判断しているためです。これ以外は平手として扱われます。  

チェックがない状態だと現在局面のみ(position sfen ... で move なし)なので、現在の手合い、過去5局面をNNの入力に必要とするAoba駒落ちの本来の実力が出せません。

ShogiGUIのページ
<http://shogigui.siganus.com/>

# コンパイルの仕方
[こちら](compile.txt)をご覧ください。

# Aoba駒落ちの紹介ページ
今までに作成した棋譜や重み、棋譜のサンプルなどを公開しています。  
<http://www.yss-aya.com/komaochi/>

# License
usiエンジンであるaobakはGPL v3です。それ以外はpublic domainです。  
[短めのライセンス](license.txt)  
詳しくは aobakomaochi-1.0.tar.gz 内の licenses をご覧ください。

# Link
 - [AobaZero](https://github.com/kobanium/aobazero)
 - [Leela Zero (Go)](https://github.com/leela-zero/leela-zero)
 - [LCZero (Chess)](https://github.com/LeelaChessZero/lczero)

