make

RINGMASTER_HOSTNAME=127.0.0.1
RINGMASTER_PORT=4001
NUM_PLAYERS=512
NUM_HOPS=512

./ringmaster $RINGMASTER_PORT $NUM_PLAYERS $NUM_HOPS &

sleep 2

for (( i=0; i<$NUM_PLAYERS; i++ ))
do
    ./player $RINGMASTER_HOSTNAME $RINGMASTER_PORT &
done

wait
