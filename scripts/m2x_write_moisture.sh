#! /usr/bin/env bash

DEVICE_ID="b44c972a5d146202c60a72741e0ddebd"
M2X_API_KEY="5b4eee9d0cfcc0adad9e7d9d978d1db8"

m2x_write() {
    local body=$(curl -s -H "X-M2X-KEY: ${M2X_API_KEY}" \
        -H "Content-Type: application/json" \
        -XPUT -d "$1" \
        http://api-m2x.att.com/v2/devices/${DEVICE_ID}/streams/content/value )

    [[ -z $body ]] || echo $body
}


while :
do

    m2x_write "{ \"value\": $(( ( RANDOM % 10 )  + 40 )) }"

    sleep 30
done
