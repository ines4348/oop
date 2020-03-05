echo off

REM Путь к тестируемой комманде передается через первый аргумент коммандной строки
SET MyProgram="%~1"

REM Защита от запуска без агрумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to programm
	exit /B 1
)

REM Start without parameter
%MyProgram% && goto err
echo Test 1 passed sucsessfully

REM Flipbyte for 6 = 96
%MyProgram% "6">"%TEMP%\output.txt" || goto err
fc sucsessfullyTest.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed sucsessfully

REM Error for negative number 
%MyProgram% "-6">"%TEMP%\output.txt" && goto err
echo Test 3 passed sucsessfully

REM Error with a large number
%MyProgram% "256">"%TEMP%\output.txt" && goto err
echo Test 4 passed sucsessfully

REM Error with a large number
%MyProgram% "A256">"%TEMP%\output.txt" && goto err
echo Test 5 passed sucsessfully

REM Все тесты прошли успешно
echo All tests passed sucsessfully

REM Tests ok
exit /B 0

REM Tests failed
:err
echo Test failed
exit /B 1

