for i in {1..10}
do
	echo ">>>>>>>>>>NEW CLIENT STARTED<<<<<<<<<"
	konsole -e /home/tyom/workspace/clientserver/bin/client/client $1 &
done

