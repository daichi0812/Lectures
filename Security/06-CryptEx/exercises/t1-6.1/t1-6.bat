@echo off

echo -----------------------------------------------------------------------
echo 独立行政法人 情報処理推進機構「暗号技術に関するe-Learning用教材」
echo　　　　　　　　　　　　実習用プログラム
echo                「t1-6.1　RSAデジタル署名の実習」
echo -----------------------------------------------------------------------

setlocal
set path=..\..\common-programs;%path%

if "%3" == ""   goto USAGE
if "%2" == ""   goto USAGE
if "%1" == "-s" goto SIGN
if "%1" == "-v" goto VERIFY

rem -----------------------------------------------------------------------
rem 使い方
:USAGE
echo エラー：引数が誤っているか、指定されていません。
echo 使い方：t1-6 -s 秘密鍵ファイル名 署名するファイルの名前 (署名)
echo 　　　  t1-6 -v 公開鍵ファイル名 署名するファイルの名前 (検証)
goto QUIT
rem -----------------------------------------------------------------------
rem 署名
:SIGN
set signfile=%3.sign
set hashfile=%3.sha1
echo ・ファイル %3 のデジタル署名を作成します。
echo 　署名に用いる鍵（秘密鍵）は、%2 です。
echo ・最初に、ファイル %3 のハッシュ値を、SHA-1アルゴリズムで計算します。
file2dmp.exe %3 | sha1.exe > %hashfile%
type %hashfile%
echo 　ハッシュ値を、ファイル %hashfile% に格納しました。
echo 　では、デジタル署名を、ファイル %signfile% に作成します。
type %hashfile% | rsa_cipher.exe -s sha1 -k %2 > %signfile%
echo 　ファイル %signfile% に、デジタル署名の情報が保存されました。
echo 　ファイル %signfile% の内容は、以下の通りです。
type %signfile%
goto QUIT
rem -----------------------------------------------------------------------
rem 検証
:VERIFY
set signfile=%3.sign
echo ・ファイル %3 のデジタル署名 %signfile% を検証します。
echo 　（デジタル署名を復号して元のファイルのハッシュ値になるかを確認します。）
echo 　検証に用いる鍵（公開鍵）は、%2 です。
echo ・最初に、ファイル %3 のハッシュ値を、SHA-1アルゴリズムで計算します。
file2dmp.exe %3 | sha1.exe
echo 　ハッシュ値はこのようになりました。
echo ・では、デジタル署名を復号して、同じハッシュ値が得られるかどうか確認します。
type %signfile% | rsa_cipher.exe -v sha1 -k %2
echo 復号した結果、ハッシュ値は上のようになりました。
echo 上の結果は元のハッシュ値と一致していますか？
echo 一致していなければ、ファイル %3 が改竄されたか、デジタル署名 %signfile% が改竄されています。
goto QUIT
rem -----------------------------------------------------------------------
rem プログラム終了
:QUIT
endlocal
rem -----------------------------------------------------------------------
