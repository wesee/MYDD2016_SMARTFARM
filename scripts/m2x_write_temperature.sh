#! /usr/bin/env bash

DEVICE_ID="87b5f5569345d527f8a0cd5bab1b3871"
M2X_API_KEY="978e930b51c396e506fb6b78f7c38197"

m2x_write() {
    local body=$(curl -s -H "X-M2X-KEY: ${M2X_API_KEY}" \
        -H "Content-Type: application/json" \
        -XPUT -d "{ \"value\": 10}" \
        http://api-m2x.att.com/v2/devices/${DEVICE_ID}/streams/level/value )

    [[ -z $body ]] || echo $body
}


while :
do

    m2x_write "{ \"level\": 20}"

    sleep 1m
done
