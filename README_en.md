# AobaKomaochi
AobaKomaochi is a distributed Deep reinforcement learning for Shogi handicap games without human knowledge.  
Handicaps are seven kinds. Lance(kyo ochi), Bishop(kaku ochi), Rook(hisha ochi), 2-Piece(ni-mai ochi), 4-Piece(yon-mai ochi), 6-Pieces(roku-mai ochi) and No handicap(hirate).  
Winrate are adjusted to keep 0.5 by weakening Black(shitate or sente) player strength.  
Can AI discover a new opening, or rediscover Two-Pawn Sacrifice Push, Silver Tandem, etc?  
If you are interested, please join us. Anyone can contribute using Google [Colab](http://www.yss-aya.com/komaochi/colab_e.html).

# I'd like to cooperate with the generation of the game records.
[Executable file for Windows(only 64-bit version)](https://github.com/yssaya/komaochi/releases)

For machine without GPU
```
aobakomaochi-1.0-w64-cpu-only.zip
```
For machine with GPU
```
aobakomaochi-1.0-w64-opencl.zip
```
Download it, unzip, and run click_me.bat.

For Linux,
```
komaochi-1.0.tar.gz
```
Unzip it, make, then run
```
./bin/autousi
```
Please see [compile.txt](compile.txt) for details.

# I'd like to play with ShogiDokoro.
Download CPU version and run click_me.bat.
After a while, it downloads the latest network weight file, and "self-play started" is displayed, and self-play starts. Input "Ctrl + C" immediately. (signal 1 caught) is displayed and it will stop after a while.

weight_save/w0000000000066.txt will be created. Its size is about 162MB.
(the numbers "66" will be different.)

Edit aobak.bat that is in aobakomaochi-1.0-w64-cpu-only.zip.
The last line is like this,
```
bin/aobak -q -i -p 100 -w weight-save\w000000000066.txt
```
Rewrite this "66" according to the file name actually downloaded, and save.
Register aobaz.bat as a engine in ShogiDokoro.
Increase by 100 of "-p 100", to get stronger. But it gets slower.
The CPU version takes about 5 seconds at 100. 
The GPU version takes about 3 seconds at 4000.(It depends on GPU.) 

ShogiDokoro is a GUI for USI engine.

ShogiDokoro 
<http://shogidokoro.starfree.jp/>

# I'd like to play with ShogiGUI
You have to change this option.  
[Tools(T)], [Options(O)], and Check [Send all moves].  
And if you concider 2-Piece game, please use entire game record from 2-Piece initial position.
AobaKomaohi recognizes current handicap from initial posiiton.  
AobaKomaohi needs handicaps(7 kinds) and past 5 moves for NN inputs. 

ShogiGUI 
<http://shogigui.siganus.com/>

# AobaKomaochi introduction page
There are game records, network weights, ELO progress and some self-play game samples.  
<http://www.yss-aya.com/komaochi/index_e.html>

# License
USI engine aobaz belongs to GPL v3. Others are in the public domain.
Detail is in the licenses in aobakomaochi-1.0.tar.gz.

# Link
 - [AobaZero](https://github.com/kobanium/aobazero)
 - [Leela Zero (Go)](https://github.com/leela-zero/leela-zero)
 - [LCZero (Chess)](https://github.com/LeelaChessZero/lczero)
