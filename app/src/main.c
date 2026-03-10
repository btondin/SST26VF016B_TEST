/*
 * SST26VF016B SPI NOR Flash - Test Application
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/flash.h>
#include <string.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app, CONFIG_LOG_DEFAULT_LEVEL);

#define FLASH_NODE DT_NODELABEL(sst26wf016ba)

#define TEST_OFFSET  0x0000
#define TEST_SIZE    256
#define SECTOR_SIZE  4096

int main(void)
{
	const struct device *flash_dev = DEVICE_DT_GET(FLASH_NODE);
	uint8_t wr_buf[TEST_SIZE];
	uint8_t rd_buf[TEST_SIZE];
	int rc;

	LOG_INF("=== SST26VF016B Flash Test ===");

	if (!device_is_ready(flash_dev)) {
		LOG_ERR("Flash device %s not ready", flash_dev->name);
		return -ENODEV;
	}
	LOG_INF("Flash device %s is ready", flash_dev->name);

	/* Step 1: Erase sector */
	LOG_INF("Erasing %d bytes at offset 0x%04X ...", SECTOR_SIZE, TEST_OFFSET);
	rc = flash_erase(flash_dev, TEST_OFFSET, SECTOR_SIZE);
	if (rc) {
		LOG_ERR("Erase failed: %d", rc);
		return rc;
	}
	LOG_INF("Erase OK");

	/* Step 2: Verify erased (all 0xFF) */
	rc = flash_read(flash_dev, TEST_OFFSET, rd_buf, TEST_SIZE);
	if (rc) {
		LOG_ERR("Read after erase failed: %d", rc);
		return rc;
	}

	bool erased = true;
	for (int i = 0; i < TEST_SIZE; i++) {
		if (rd_buf[i] != 0xFF) {
			LOG_ERR("Erase verify failed at byte %d: 0x%02X", i, rd_buf[i]);
			erased = false;
			break;
		}
	}
	if (erased) {
		LOG_INF("Erase verify OK (all 0xFF)");
	}

	/* Step 3: Write test pattern */
	for (int i = 0; i < TEST_SIZE; i++) {
		wr_buf[i] = (uint8_t)i;
	}

	LOG_INF("Writing %d bytes at offset 0x%04X ...", TEST_SIZE, TEST_OFFSET);
	rc = flash_write(flash_dev, TEST_OFFSET, wr_buf, TEST_SIZE);
	if (rc) {
		LOG_ERR("Write failed: %d", rc);
		return rc;
	}
	LOG_INF("Write OK");

	/* Step 4: Read back and verify */
	memset(rd_buf, 0, TEST_SIZE);
	rc = flash_read(flash_dev, TEST_OFFSET, rd_buf, TEST_SIZE);
	if (rc) {
		LOG_ERR("Read failed: %d", rc);
		return rc;
	}

	if (memcmp(wr_buf, rd_buf, TEST_SIZE) == 0) {
		LOG_INF("Read-back verify OK - all %d bytes match!", TEST_SIZE);
	} else {
		LOG_ERR("Read-back verify FAILED!");
		for (int i = 0; i < TEST_SIZE; i++) {
			if (wr_buf[i] != rd_buf[i]) {
				LOG_ERR("  Mismatch at [%d]: wrote 0x%02X, read 0x%02X",
					i, wr_buf[i], rd_buf[i]);
				break;
			}
		}
	}

	LOG_INF("=== Test complete ===");
	return 0;
}
