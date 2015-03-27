@REM PWM00.cをコンパイルするためのバッチファイルです。
@REM 本バッチはGDLから使用されるものではありません。
@REM GDLを使用しないで単体でコンパイルする際に利用してください。
@SET PATH=D:\Program Files\BestTech\GCC Developer Lite\GCC\SH\bin;d:\Program Files\BestTech\GCC Developer Lite\GCC\SH\libexec\gcc\sh-elf\4.4-GNUSH_v10.01;d:\Program Files\BestTech\GCC Developer Lite\GCC\SH\sh-elf\bin
sh-elf-gcc -I D:\Program Files\BestTech\GCC Developer Lite\TARGET\7125F -L D:\Program Files\BestTech\GCC Developer Lite\TARGET\7125F -m2 -nostartfiles -Wall -Wno-main -pipe -O0 -TD:\Program Files\BestTech\GCC Developer Lite\TARGET\7125F\shrom.x -Xlinker -Map -Xlinker PWM00.map D:\Program Files\BestTech\GCC Developer Lite\TARGET\7125F\shrom.s PWM00.c -ladd7125 -lm -o PWM00.exe 
