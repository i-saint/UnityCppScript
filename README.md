UnityCppScript
==============

C++ から Unity の C# の API を呼べるようにするプラグイン兼ライブラリです。  
C++ スクリプト的に使いたい場合や、既存の C++ のライブラリと Unity のやりとりを簡単にできるようにすることを目的としています。

Mono の API を叩いて C# のアセンブリにアクセスすることで実現しています。  
詳細: http://i-saint.hatenablog.com/entry/2014/10/24/190807  
注意点として、Mono を経由する処理は非常に遅く、Unity の C# の API を呼ぶ処理は普通に C# で実行したのと同等の速度になります。
それ以外の純粋なスクリプトの処理内容が相応に重い場合でないと速度的にはあまり効果はありません。


This plugin library enables calling Unity C# API from C++ code.
Use of C++ as a script, and the communication with existing C++ library can be done easily.

This library is implemented by calling Mono's API to access C# assembly directly.
Details: http://i-saint.hatenablog.com/entry/2014/10/24/190807  
Note that since processing through Mono is very slow, the speed of calling Unity C# API from C++ is about the same as simplly calling from C#.
Other than that, if it's not very heavy on pure script processing, it won't be very effective on performance.


<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.

