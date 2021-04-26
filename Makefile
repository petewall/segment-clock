.PHONY: build clean test

clean:
	rm -rf .pio data

~/.ssh/id_github:
	setup-github-ssh-key.sh

.pio/libdeps/testing/PeriodicAction/library.json: ~/.ssh/id_github
	pio lib install

deps: .pio/libdeps/testing/PeriodicAction/library.json

SRC_FILES := $(shell find . -path ./test -prune -false -o -name "*.cpp" -o -name "*.h")
TEST_FILES := $(shell find ./test -name "*.cpp" -o -name "*.h")

define invoke-pio
	FIRMWARE_TYPE="${FIRMWARE_TYPE}" \
	FIRMWARE_VERSION="${FIRMWARE_VERSION}" \
	OTA_HOST="http://wallserver.local:8266" \
	WIFI_SSID="${WIFI_SSID}" \
	WIFI_PASSWORD="${WIFI_PASSWORD}" \
		pio $1 --environment segment-clock $2 $3
endef

test: ${SRC_FILES} ${TEST_FILES}
	pio test --environment testing --verbose

.pio/build/segment-clock/firmware.bin: platformio.ini ${SRC_FILES}
	$(call invoke-pio,run,--verbose)

build: .pio/build/segment-clock/firmware.bin

check: ${SRC_FILES}
	$(call invoke-pio,check,--verbose,--skip-packages)

upload:
	$(call invoke-pio,run,--target,upload)

upload-fs: build-client
	$(call invoke-pio,run,--target,uploadfs)

# Client targets

client-deps: client/node_modules/.deps-pulled
client/node_modules/.deps-pulled:
	cd client && yarn install
	touch client/node_modules/.deps-pulled

# test-client: client-deps
# 	yarn

build-client: data/index.htm
data/index.htm: client-deps
	mkdir -p data
	cp client/actions.js client/index.htm client/style.css client/node_modules/jquery/dist/jquery.min.js data/


# CI targets
set-pipeline:
	fly -t wallhouse set-pipeline \
		--load-vars-from ../secrets/pipeline-creds.json \
		--pipeline segment-clock \
		--config ci/pipeline.yaml
