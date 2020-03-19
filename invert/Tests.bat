echo off

REM ���� � ����������� �������� ���������� ����� ������ �������� ���������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to programm
	exit /B 1
)

REM ������ ��� ���������
%MyProgram% && goto err
echo Test 1 passed sucsessfully

REM �� ���� ��� ������ ����
%MyProgram% empty.txt>"%TEMP%\output.txt" && goto err
echo Test 2 passed sucsessfully

REM ������������� �������
%MyProgram% input.txt>"%TEMP%\output.txt" || goto err
fc sucsessfullyTest.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed sucsessfully

REM ������������� ��������� �������
%MyProgram% etalon.txt>"%TEMP%\output.txt" || goto err
fc etalonTest.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed sucsessfully

REM ���������� ������� �������������� ����
%MyProgram% missing.txt "%TEMP%\output.txt" && goto err
echo Test 5 passed sucsessfully

REM ����������� � ����� ����������� � �������� ��������� ���������
%MyProgram% input.txt input1.txt input2.txt && goto err
echo Test 6 passed sucsessfully

REM ������������ ����� 0
%MyProgram% det0.txt>"%TEMP%\output.txt" && goto err
echo Test 7 passed sucsessfully

REM �� ���� ��� ���� � ���������� ���������
%MyProgram% char.txt>"%TEMP%\output.txt" && goto err
echo Test 8 passed sucsessfully

REM �� ���� ��� ���� � �������� ��������
%MyProgram% 3x2.txt>"%TEMP%\output.txt" && goto err
echo Test 9 passed sucsessfully

REM �������� �������� �� 0

REM ��� ����� ������ �������
echo All tests passed sucsessfully

REM Tests ok
exit /B 0

REM Tests failed
:err
echo Test failed
exit /B 1

