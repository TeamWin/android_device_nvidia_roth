LOCAL_PATH := $(call my-dir)
LZMA := lzma

$(recovery_ramdisk): $(MKBOOTFS) \
	$(recovery_uncompressed_ramdisk)
	@echo -e ${PRT_IMG}"----- Making recovery ramdisk ------"${CL_RST}
	$(LZMA) < $(recovery_uncompressed_ramdisk) > $@

$(INSTALLED_RECOVERYIMAGE_TARGET): $(MKBOOTIMG) \
		$(recovery_ramdisk) \
		$(recovery_kernel)
	@echo -e ${PRT_IMG}"----- Making recovery image ------"${CL_RST}
	$(hide) $(MKBOOTIMG) $(INTERNAL_RECOVERYIMAGE_ARGS) $(BOARD_MKBOOTIMG_ARGS) --output $@
	$(hide) $(call assert-max-image-size,$@,$(BOARD_RECOVERYIMAGE_PARTITION_SIZE),raw)
	@echo -e ${PRT_IMG}"----- Made recovery image: $@ --------"${CL_RST}
