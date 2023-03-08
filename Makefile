.PHONY: build upload 

clean:
	rm -rf .esphome

.esphome/build/segment-clock/.pioenvs/segment-clock/firmware.bin: device.yaml
	esphome compile device.yaml

build: .esphome/build/segment-clock/.pioenvs/segment-clock/firmware.bin

upload: .esphome/build/segment-clock/.pioenvs/segment-clock/firmware.bin
	esphome upload device.yaml

