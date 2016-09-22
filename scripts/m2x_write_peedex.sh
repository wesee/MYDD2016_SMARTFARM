#! /usr/bin/env bash

case $1 in
1)
DEVICE_ID="02148334c5487d65cc0a0d10fff3a144"
M2X_API_KEY="d3f4abbcfcd6c3e56765dbd0f4af65b9"
;;
2)
DEVICE_ID="7746fe57137f3e0b80e46a1c23bba971"
M2X_API_KEY="017cbd5dc7393bfb127e7f39062609dc"
;;
3)
DEVICE_ID="aa8add37a661a1faf76365ab46755a6b"
M2X_API_KEY="0c0e2497b36c5e18b10537719578ea4e"
;;
4)
DEVICE_ID="e81704232ff64106b59c8c9566a37efc"
M2X_API_KEY="9d4025ad582439cc24f21009aa01beb5"
;;
*)
echo "error..."
exit 0
;;
esac


m2x_write() {
    local body=$(curl -s -H "X-M2X-KEY: ${M2X_API_KEY}" \
        -H "Content-Type: application/json" \
        -XPUT -d "$1" \
        http://api-m2x.att.com/v2/devices/${DEVICE_ID}/streams/level/value )

    [[ -z $body ]] || echo $body
}


m2x_write "{ \"value\": $(( ( RANDOM % 10 )  + 40 )) }"
