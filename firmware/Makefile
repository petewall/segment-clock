.PHONY: build clean test

SRC_FILES := $(shell find . -path ./test -prune -false -o -name "*.cpp" -o -name "*.h")
TEST_FILES := $(shell find ./test -name "*.cpp" -o -name "*.h")

test: build ${TEST_FILES}
	pio test --environment segment-clock --verbose

.pio/build/segment-clock/firmware.bin: platformio.ini ${SRC_FILES}
	pio run

build: .pio/build/segment-clock/firmware.bin

clean:
	rm -rf .pio
