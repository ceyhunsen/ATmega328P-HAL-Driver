.. _timer-info:

How To Add To Project
=====================

If instructions in :ref:`getting-started` applied, this part can be skipped.

1. Copy ``atmega328p_hal_driver`` directory to target project's driver directory.
2. Add ``atmega328p_hal_driver/inc/`` directory to target project's include path.
3. Add ``atmega328p_hal_driver/src/atmega328p_hal_timer.c`` to target project's build toolchain as a source file.
4. Include ``atmega328p_hal_timer.h`` header to desired source file(s).
