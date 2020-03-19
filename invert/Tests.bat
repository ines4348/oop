echo off

REM Путь к тестируемой комманде передается через первый аргумент коммандной строки
SET MyProgram="%~1"

REM Защита от запуска без агрумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to programm
	exit /B 1
)

REM Запуск без параметра
%MyProgram% && goto err
echo Test 1 passed sucsessfully

REM На вход дан пустой файл
%MyProgram% empty.txt>"%TEMP%\output.txt" && goto err
echo Test 2 passed sucsessfully

REM Инвертировать матрицу
%MyProgram% input.txt>"%TEMP%\output.txt" || goto err
fc sucsessfullyTest.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed sucsessfully

REM Инвертировать эталонную матрицу
%MyProgram% etalon.txt>"%TEMP%\output.txt" || goto err
fc etalonTest.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed sucsessfully

REM Параметром передан несуществующий файл
%MyProgram% missing.txt "%TEMP%\output.txt" && goto err
echo Test 5 passed sucsessfully

REM Копирование с тремя аргументами в качестве параметра программы
%MyProgram% input.txt input1.txt input2.txt && goto err
echo Test 6 passed sucsessfully

REM Определитель равен 0
%MyProgram% det0.txt>"%TEMP%\output.txt" && goto err
echo Test 7 passed sucsessfully

REM На вход дан файл с текстовыми символами
%MyProgram% char.txt>"%TEMP%\output.txt" && goto err
echo Test 8 passed sucsessfully

REM На вход дан файл с неполной матрицей
%MyProgram% 3x2.txt>"%TEMP%\output.txt" && goto err
echo Test 9 passed sucsessfully

REM Добавить проверку на 0

REM Все тесты прошли успешно
echo All tests passed sucsessfully

REM Tests ok
exit /B 0

REM Tests failed
:err
echo Test failed
exit /B 1

