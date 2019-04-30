

cwatch() {
    while [ 1 ]
    do
	output=$(/c/Users\/tokoharu//Anaconda3//envs//py36//python.exe $@ 2>&1)
	clear
	date
	echo  "$output"
	sleep 0.1
    done
}



observe(){
    cwatch atc_submit_latest.py $@
}


observe $@
