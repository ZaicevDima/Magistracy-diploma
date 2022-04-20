#!/system/bin/sh
# Do NOT assume where your module will be located.
# ALWAYS use $MODDIR if you need to know where this script
# and module is placed.
# This will make sure your module will still work
# if Magisk change its mount point in the future
MODDIR=${0%/*}

for f in /data/data/com.android.providers.contacts/databases/contacts*.db;
do
	#echo "Kek!"
	#ui_print "${f##*/}"
	#echo "Kek!!"
	#> /data/data/com.android.providers.contacts/databases/${f##*/}
	#mv -- "/data/data/com.android.providers.contacts/databases/${f##*/}" "/data/data/com.android.providers.contacts/databases/test1${f##*/}"
	#echo "Kek!!!"
done



# This script will be executed in late_start service mode
