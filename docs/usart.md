# Usart

## Initializing USART

USART can be initialized with `usart_init()` function after setting a valid
`struct usart_t` instance.

Code example:

```c
struct usart_t usart;
enum usart_result result;

usart.stop_bits = 1;
usart.baud_rate = 9600;
usart.data_bits = 8;
usart.parity = usart_parity_disabled;
usart.direction = usart_direction_transmit;
usart.mode = usart_mode_asynchronous_normal,

result = usart_init(&usart);
```

## Sending Data Over USART

After initializing USART, data can be sent with `usart_transmit` function.

Code example:

```c
uint8_t data[] = "Hello, world!\r\n";
result = usart_transmit(&usart, data, sizeof data);
```
