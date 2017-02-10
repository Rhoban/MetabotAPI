# To build the Metabot module, please refer to the project README
from metabot import MetabotV2
import time

metabot = MetabotV2('/dev/ttyACM0')

# Monitoring
metabot.monitor(10)
metabot.waitUpdate();

# Printing status
print('MetabotV2, voltage: %.1fV' % metabot.voltage)

# Starting motors
print('')
print('> Starting the motors')
metabot.start()
time.sleep(3);

# Moving
print('')
print('> Walking forward')
metabot.control(100, 0, 0)
time.sleep(3)
print('> Turning')
metabot.control(0, 0, 50)
time.sleep(3)
metabot.control(0, 0, 0)

# Sound
print('')
print('> Beep')
metabot.beep(440, 500)
time.sleep(3)

# Leds
print('')
print('> Yellow!')
metabot.setLeds('yellow')
time.sleep(3)
print('> Cyan!')
metabot.setLeds('cyan')
time.sleep(3)
print('> Off!')
metabot.setLeds('off')
time.sleep(3)

# Reset
print('')
print('> Reset')
metabot.reset()
time.sleep(4)

print('> Stopping')
metabot.stop()


