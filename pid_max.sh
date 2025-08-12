#!/bin/bash

if [[ -r /proc/sys/kernel/pid_max ]]; then
    # Linux
    cat /proc/sys/kernel/pid_max
elif command -v sysctl >/dev/null 2>&1; then
    # macOS ou BSD
    sysctl -n kern.pid_max
else
    echo "Impossible de déterminer pid_max sur ce système."
    exit 1
fi
