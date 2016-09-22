#! /usr/bin/env bash

DEVICE_ID="83e740e6e0b40d51acdcccd4832bf8c6"
M2X_API_KEY="ec2e90fdf6f85173ad23574381b23b2d"

m2x_write() {
    local body=$(curl -s -H "X-M2X-KEY: ${M2X_API_KEY}" \
        -H "Content-Type: application/json" \
        -XPUT -d "$1" \
        http://api-m2x.att.com/v2/devices/${DEVICE_ID}/streams/level/value )

    [[ -z $body ]] || echo $body
}


while :
do

    m2x_write "{ \"value\": $(( ( RANDOM % 10 ) )) }"

    sleep 30
done
