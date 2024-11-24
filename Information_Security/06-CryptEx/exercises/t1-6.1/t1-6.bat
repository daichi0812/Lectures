@echo off

echo -----------------------------------------------------------------------
echo �Ɨ��s���@�l ��񏈗����i�@�\�u�Í��Z�p�Ɋւ���e-Learning�p���ށv
echo�@�@�@�@�@�@�@�@�@�@�@�@���K�p�v���O����
echo                �ut1-6.1�@RSA�f�W�^�������̎��K�v
echo -----------------------------------------------------------------------

setlocal
set path=..\..\common-programs;%path%

if "%3" == ""   goto USAGE
if "%2" == ""   goto USAGE
if "%1" == "-s" goto SIGN
if "%1" == "-v" goto VERIFY

rem -----------------------------------------------------------------------
rem �g����
:USAGE
echo �G���[�F����������Ă��邩�A�w�肳��Ă��܂���B
echo �g�����Ft1-6 -s �閧���t�@�C���� ��������t�@�C���̖��O (����)
echo �@�@�@  t1-6 -v ���J���t�@�C���� ��������t�@�C���̖��O (����)
goto QUIT
rem -----------------------------------------------------------------------
rem ����
:SIGN
set signfile=%3.sign
set hashfile=%3.sha1
echo �E�t�@�C�� %3 �̃f�W�^���������쐬���܂��B
echo �@�����ɗp���錮�i�閧���j�́A%2 �ł��B
echo �E�ŏ��ɁA�t�@�C�� %3 �̃n�b�V���l���ASHA-1�A���S���Y���Ōv�Z���܂��B
file2dmp.exe %3 | sha1.exe > %hashfile%
type %hashfile%
echo �@�n�b�V���l���A�t�@�C�� %hashfile% �Ɋi�[���܂����B
echo �@�ł́A�f�W�^���������A�t�@�C�� %signfile% �ɍ쐬���܂��B
type %hashfile% | rsa_cipher.exe -s sha1 -k %2 > %signfile%
echo �@�t�@�C�� %signfile% �ɁA�f�W�^�������̏�񂪕ۑ�����܂����B
echo �@�t�@�C�� %signfile% �̓��e�́A�ȉ��̒ʂ�ł��B
type %signfile%
goto QUIT
rem -----------------------------------------------------------------------
rem ����
:VERIFY
set signfile=%3.sign
echo �E�t�@�C�� %3 �̃f�W�^������ %signfile% �����؂��܂��B
echo �@�i�f�W�^�������𕜍����Č��̃t�@�C���̃n�b�V���l�ɂȂ邩���m�F���܂��B�j
echo �@���؂ɗp���錮�i���J���j�́A%2 �ł��B
echo �E�ŏ��ɁA�t�@�C�� %3 �̃n�b�V���l���ASHA-1�A���S���Y���Ōv�Z���܂��B
file2dmp.exe %3 | sha1.exe
echo �@�n�b�V���l�͂��̂悤�ɂȂ�܂����B
echo �E�ł́A�f�W�^�������𕜍����āA�����n�b�V���l�������邩�ǂ����m�F���܂��B
type %signfile% | rsa_cipher.exe -v sha1 -k %2
echo �����������ʁA�n�b�V���l�͏�̂悤�ɂȂ�܂����B
echo ��̌��ʂ͌��̃n�b�V���l�ƈ�v���Ă��܂����H
echo ��v���Ă��Ȃ���΁A�t�@�C�� %3 ����₂��ꂽ���A�f�W�^������ %signfile% ����₂���Ă��܂��B
goto QUIT
rem -----------------------------------------------------------------------
rem �v���O�����I��
:QUIT
endlocal
rem -----------------------------------------------------------------------
