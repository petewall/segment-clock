#!/bin/bash

export FIRMWARE_TYPE="segment-clock-dev"
export FIRMWARE_VERSION=$(cat version)
export WIFI_SSID=$(cat ../secrets/pipeline-creds.json | jq -r '.["wifi-ssid"]')
export WIFI_PASSWORD=$(cat ../secrets/pipeline-creds.json | jq -r '.["wifi-password"]')
