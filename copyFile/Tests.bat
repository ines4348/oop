echo off

REM ���� � ����������� �������� ���������� ����� ������ �������� ���������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to programm
	exit /B 1
)

REM Copy empty file
%MyProgram% empty.txt "%TEMP%\output.txt" || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed sucsessfully

REM Copy non empty file
%MyProgram% nonempty.txt "%TEMP%\output.txt" || goto err
fc nonempty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed sucsessfully

REM ����������� ������������� ������
%MyProgram% missing.txt "%TEMP%\output.txt" && goto err
echo Test 3 passed sucsessfully

REM ����������� ��� ���������� � �������� ��������� ���������
%MyProgram% && goto err
echo Test 4 passed sucsessfully

REM ����������� � ����� ���������� � �������� ��������� ���������
%MyProgram% input.txt && goto err
echo Test 5 passed sucsessfully

REM ��� ����� ������ �������
echo All tests passed sucsessfully

REM Tests ok
exit /B 0

REM Tests failed
:err
echo Test failed
exit /B 1

