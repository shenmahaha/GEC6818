default:
	arm-linux-gcc  main.c lcd.c ts.c ./app/photo_app.c ./app/draw_app.c ./app/wzq_app.c ./app/AI.c  -o main  -L./ -lfont  -lm 
	sshpass -p '123456' scp -r  main root@192.168.45.149:/root