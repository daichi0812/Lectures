@echo off

echo -----------------------------------------------------------------------
echo �Ɨ��s���@�l ��񏈗����i�@�\�u�Í��Z�p�Ɋւ���e-Learning�p���ށv
echo�@�@�@�@�@�@�@�@�@�@�@�@���K�p�v���O����
echo                  �ut1-3.1�@���p���[�h�̎��K�v
echo -----------------------------------------------------------------------

setlocal
set path=..\..\common-programs;%path%

rem ���t�@�C���̎w��
set deskey=3des.key
set deskeypath=%cd%\%deskey%

if "%2" == "-m" (
	if "%3" == "e" (
		echo ���p���[�h�ɂ�ECB���w�肳��Ă��܂��B
		goto BEGIN
	)
	if "%3" == "c" (
		echo ���p���[�h�ɂ�CBC���w�肳��Ă��܂��B
		goto BEGIN
	)
	echo ���p���[�h���w�肳��Ă��Ȃ����A�����ȗ��p���[�h���w�肳��Ă��܂��B
	goto USAGE
) else (
	echo ���p���[�h���w�肳��Ă��Ȃ����A�����ȗ��p���[�h���w�肳��Ă��܂��B
	goto USAGE
)

:BEGIN
if "%1" == "-e" goto ENCRYPTO
if "%1" == "-d" goto DECRYPTO
rem -----------------------------------------------------------------------
rem �g����
:USAGE
echo �G���[�F����������Ă��邩�A�w�肳��Ă��܂���B
echo �g�����F
echo �@�Í����Ft1-3 -e -m mode �����t�@�C���̖��O
echo �@�����@�Ft1-3 -d -m mode �Í����t�@�C���̖��O
echo �@�@�@�@�F(mode��e�܂���c�Ae�̏ꍇECB�Ac�̏ꍇCBC)
goto QUIT
rem -----------------------------------------------------------------------
rem �Í���
:ENCRYPTO
echo �E3DES�Í��A���S���Y���ɂ��A����(�t�@�C��) %4 ���Í������܂��B
echo �@(���́A%deskey%���g���܂��B)
set desfile=%4.%3
file2dmp.exe %4 | 3des.exe -e -m %3 -k %deskeypath% > %desfile%
echo �E�Í����̌��ʂ̓t�@�C�� %desfile% �ɕۑ�����܂����B
echo �@�t�@�C�� %desfile% �̓��e�͈ȉ��̒ʂ�ł��B
type %desfile%
echo �@�Í����������I�����܂����B
goto QUIT
rem -----------------------------------------------------------------------
rem ����
:DECRYPTO
echo �E3DES�Í��A���S���Y���ɂ��Í������ꂽ�Í���(�t�@�C��) %4 �𕜍����܂��B
echo �@(���́A%deskey%���g���܂��B)
set orgfile=%4.org
type %4 | 3des.exe -d -m %3 -k %deskeypath% -b > %orgfile%
echo �@�����̌��ʂ́A�t�@�C�� %orgfile% �ɕۑ�����܂����B
echo �@���Ƃ̃t�@�C��(����)�Ɣ�ׂĂ݂܂��傤�B
goto QUIT
rem -----------------------------------------------------------------------
rem �v���O�����I��
:QUIT
endlocal
rem -----------------------------------------------------------------------
