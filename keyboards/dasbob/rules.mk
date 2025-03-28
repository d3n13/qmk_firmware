

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
UNICODE_ENABLE = no         # Unicode
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes        # Use shared split_common code
COMBO_ENABLE = yes          # Enable combos, believe it or not
OLED_ENABLE = no
OLED_DRIVER = ssd1306
WPM_ENABLE = no
LTO_ENABLE = yes
SERIAL_DRIVER = vendor
AUDIO_DRIVER = pwm_hardware
