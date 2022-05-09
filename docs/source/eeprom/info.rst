.. _eeprom-info:

Reading And Writing To EEPROM
=============================

As specified in :ref:`eeprom-api-reference`, both read and write functions needs start address, data buffer and data buffer length. Data buffer will be filled with read data or written to EEPROM continuously beginning from start address. If read/write operation exceeds maximum memory address (which is 1024), operation will be cancelled and read/write length will be returned. If read/write operation is success, data buffer length will be returned. So, check returned value for success/fail read/write state.

Read and write operation is type independent. So, one can read or write any type of data (e.g. int, float, struct) to EEPROM. Also there is no file system, so one needs to track every address of written data.

Example code:

.. code-block:: c

	// Create variables.
	uint8_t eeprom_data_arr[4] = {1, 2, 3, 4};
	uint32_t eeprom_data = 0xDEADBEEF;

	// Write to EEPROM and check written data length.
	if (hal_eeprom_write(0, eeprom_data_arr, sizeof(eeprom_data_arr)) != sizeof(eeprom_data_arr)) {
		printf("EEPROM write unseccesfull!\n");
	}
	if (hal_eeprom_write(4, (uint8_t *)&eeprom_data, sizeof(eeprom_data)) != sizeof(eeprom_data)) {
		printf("EEPROM write unseccesfull!\n");
	}

	// Read EEPROM data.
	hal_eeprom_read(0, (uint8_t *)&eeprom_data, sizeof(eeprom_data));
	hal_eeprom_read(4, eeprom_data_arr, sizeof(eeprom_data_arr));

Changing EEPROM Programming Mode
================================

EEPROM write mode is changable. See :ref:`eeprom-api-reference` for more information. Defaults to ``atomic``.

Example code:

.. code-block:: c

	hal_eeprom_set_mode(atomic);
