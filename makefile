BACKUP_PATH=/D
object=alert.o
DATE=`date +%d%m%y`
CFLAGS=

alert: $(object)
	gcc -o alert $(object)
	~/ALERT/alert | tee /C/Users/jd/Desktop/ALERT_PRINT.doc
	cp alert.h  $(BACKUP_PATH)/ALERT/alert.h_$(DATE)
	cp dress.h  $(BACKUP_PATH)/ALERT/dress.h_$(DATE)
	cp alert.c  $(BACKUP_PATH)/ALERT/alert.c_$(DATE)
	cp makefile $(BACKUP_PATH)/ALERT/makefile_$(DATE)

alert.o: alert.c alert.h 
	gcc -c  alert.c
		

config:
	cp -r ../TYPING			$(BACKUP_PATH)/TYPING/TYPING_$(DATE)
	cp /etc/fstab			$(BACKUP_PATH)/LINUX/fstab_$(DATE)
	cp /boot/grub2/grub.cfg	$(BACKUP_PATH)/LINUX/grub.cfg_$(DATE)
	cp ~/.bashrc			$(BACKUP_PATH)/LINUX/bashrc_$(DATE)
	cp ~/.bash_profile		$(BACKUP_PATH)/LINUX/bash_profile_$(DATE)
	cp ~/.gdbinit			$(BACKUP_PATH)/LINUX/gdbinit_$(DATE)
	cp ~/KERNEL/Kernel_Install.txt $(BACKUP_PATH)/KERNEL/Kernel_Install.txt_$(DATE)
	cp ~/RUN19/run.sh 		$(BACKUP_PATH)/RUN
	
clean:
	rm alert $(object)
