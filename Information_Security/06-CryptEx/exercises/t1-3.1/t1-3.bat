@echo off

echo -----------------------------------------------------------------------
echo 独立行政法人 情報処理推進機構「暗号技術に関するe-Learning用教材」
echo　　　　　　　　　　　　実習用プログラム
echo                  「t1-3.1　利用モードの実習」
echo -----------------------------------------------------------------------

setlocal
set path=..\..\common-programs;%path%

rem 鍵ファイルの指定
set deskey=3des.key
set deskeypath=%cd%\%deskey%

if "%2" == "-m" (
	if "%3" == "e" (
		echo 利用モードにはECBが指定されています。
		goto BEGIN
	)
	if "%3" == "c" (
		echo 利用モードにはCBCが指定されています。
		goto BEGIN
	)
	echo 利用モードが指定されていないか、無効な利用モードが指定されています。
	goto USAGE
) else (
	echo 利用モードが指定されていないか、無効な利用モードが指定されています。
	goto USAGE
)

:BEGIN
if "%1" == "-e" goto ENCRYPTO
if "%1" == "-d" goto DECRYPTO
rem -----------------------------------------------------------------------
rem 使い方
:USAGE
echo エラー：引数が誤っているか、指定されていません。
echo 使い方：
echo 　暗号化：t1-3 -e -m mode 平文ファイルの名前
echo 　復号　：t1-3 -d -m mode 暗号文ファイルの名前
echo 　　　　：(mode＝eまたはc、eの場合ECB、cの場合CBC)
goto QUIT
rem -----------------------------------------------------------------------
rem 暗号化
:ENCRYPTO
echo ・3DES暗号アルゴリズムにより、平文(ファイル) %4 を暗号化します。
echo 　(鍵は、%deskey%を使います。)
set desfile=%4.%3
file2dmp.exe %4 | 3des.exe -e -m %3 -k %deskeypath% > %desfile%
echo ・暗号化の結果はファイル %desfile% に保存されました。
echo 　ファイル %desfile% の内容は以下の通りです。
type %desfile%
echo 　暗号化処理が終了しました。
goto QUIT
rem -----------------------------------------------------------------------
rem 復号
:DECRYPTO
echo ・3DES暗号アルゴリズムにより暗号化された暗号文(ファイル) %4 を復号します。
echo 　(鍵は、%deskey%を使います。)
set orgfile=%4.org
type %4 | 3des.exe -d -m %3 -k %deskeypath% -b > %orgfile%
echo 　復号の結果は、ファイル %orgfile% に保存されました。
echo 　もとのファイル(平文)と比べてみましょう。
goto QUIT
rem -----------------------------------------------------------------------
rem プログラム終了
:QUIT
endlocal
rem -----------------------------------------------------------------------
