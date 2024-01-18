import board
import busio
import math
from adafruit_bno08x_rvc import BNO08x_RVC
import neopixel_spi

NUM_PIXELS = 68

uart = busio.UART(board.TX, board.RX, baudrate = 115200, receiver_buffer_size = 2048)
rvc = BNO08x_RVC(uart)

pixels = neopixel_spi.NeoPixel_SPI(board.SPI(), NUM_PIXELS, auto_write=False)

# Gravity reports appear to be more reliable than gyro rotation reports.
# Testing shows yaw affects roll and pitch, but will settle after some
# duration.  X, Y, Z components for gravity reports are not affected in this
# fashion and remain independently stable.

LEVEL_TOLERANCE_DEG = 2.5
MAX_TILT_DEG = 9.8

THRESHOLD = math.cos(LEVEL_TOLERANCE_DEG / 180.0 * math.pi)
MAX_TILT = math.cos(MAX_TILT_DEG / 180.0 * math.pi)

class Vec3:
    x: float
    y: float
    z: float

    def __init__(self, _x, _y, _z):
        self.x = _x
        self.y = _y
        self.z = _z

    def len(self):
        return math.sqrt(self.x ** 2 + self.y ** 2 + self.z ** 2)

    def unit(self):
        mag = self.len()
        return Vec3(self.x / mag, self.y / mag, self.z / mag)

    # Let A be a vector in 3d space.
    # Let B be a vector in 3d space.
    # Let A dot B = A.len * b.len * cos(theta)
    #   where theta is angle between A and B.
    def dot(self, other):
        return self.x * other.x \
            + self.y * other.y \
            + self.z * other.z

_, _, _, ax, ay, az = rvc.heading

a_vec = Vec3(ax, ay, az).unit()

while True:
    _, _, _, bx, by, bz = rvc.heading

    b_vec = Vec3(bx, by, bz).unit()

    dot_product = a_vec.dot(b_vec)

    # Calculate the percent # of lights to illuminate.
    percent = max(0.0, min(1.0, (dot_product - MAX_TILT) / (THRESHOLD - MAX_TILT)))

    # Dot Product (dp) is 1.0 when vectors align, and reduces to -1 as vectors
    # rotate away from alignment.
    # dp in range [THRESHOLD, 1.0] is level.
    # dp below THRESHOLD is not level.
    if dot_product < THRESHOLD:
        print("Tilt: % 8.2f degrees TILT   percent %6.2f" % (dot_product, percent))
    else:
        print("Tilt: % 8.2f degrees LEVEL  percent %6.2f" % (dot_product, percent))

    if percent == 1.0:
        pixels.fill(0x00_ff_00)
    else:
        pixels.fill(0x00_00_00)
        for i in range(int(NUM_PIXELS * percent)):
            pixels[i] = 0xff_00_00

    pixels.show()

