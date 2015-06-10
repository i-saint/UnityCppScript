UnityCppScript
==============

C++ から Unity の C# の API を呼べるようにするプラグイン兼ライブラリです。  
C++ スクリプト的に使いたい場合や、既存の C++ のライブラリと Unity のやりとりを簡単にできるようにすることを目的としています。

Mono の API を叩いて C# のアセンブリにアクセスすることで実現しています。  
詳細: http://i-saint.hatenablog.com/entry/2014/10/24/190807  
注意点として、Mono を経由する処理は非常に遅く、Unity の C# の API を呼ぶ処理は普通に C# で実行したのと同等の速度になります。
それ以外の純粋なスクリプトの処理内容が相応に重い場合でないと速度的にはあまり効果はありません。


<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
