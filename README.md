## Clases en c++ para microcontrolador ESP32

Clases para manejar el Led RGB y el bluetooth en las placas ESP32 a través del entorno Arduino.

Estas clases son un "wrapper" de las que incluye el entorno Arduino: Neopixel y BLE respectivamente, por lo que no hacen falta más librerías externas.

**Material complementario a los videos de Youtube**:
- [Manejo del Led integrado RGB](https://youtu.be/IJEAADbAc6U)
- [Bluetooth: filtrado por MAC e intensidad de señal](https://youtu.be/yOpOOfQmYQc)
 
## Cómo usar:

Mira los ejemplos de los videos para saber cómo funcionan las clases y si se adaptan a tus necesitades.

- Para implementar el Led RGB necesitas los ficheros **include/onboardrgb7.hpp** y **src/onboardrgb7.cpp** en tu proyecto.

- Para el Bluetooth, **include/proximityble.hpp** y **src/proximityble.cpp**.

Si usas PlatformIO, esta estructura de directorios te vendrá bien, si usas Arduino IDE, seguramente sería mejor que copiaras todo en el directorio raíz de tu proyecto.

Por favor, si este código te ha sido de utilidad para realizar algún proyecto, comparte tu experiencia en los comentarios de los videos.