#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define RED_GPIO 13
#define BLUE_GPIO 12  // Representa o amarelo
#define GREEN_GPIO 11

volatile int estado = 0; // 0 - Vermelho, 1 - Amarelo (Azul), 2 - Verde

bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs
    gpio_put(RED_GPIO, 0);
    gpio_put(BLUE_GPIO, 0);
    gpio_put(GREEN_GPIO, 0);
    
    // Liga o LED correspondente ao estado atual
    switch (estado) {
        case 0:
            gpio_put(RED_GPIO, 1);
            break;
        case 1:
            gpio_put(BLUE_GPIO, 1);
            break;
        case 2:
            gpio_put(GREEN_GPIO, 1);
            break;
    }
    
    // Alterna o estado
    estado = (estado + 1) % 3;
    return true; // Mantém o timer ativo
}

int main() {
    stdio_init_all();
    
    // Configura os pinos como saída
    gpio_init(RED_GPIO);
    gpio_set_dir(RED_GPIO, GPIO_OUT);
    gpio_init(BLUE_GPIO);
    gpio_set_dir(BLUE_GPIO, GPIO_OUT);
    gpio_init(GREEN_GPIO);
    gpio_set_dir(GREEN_GPIO, GPIO_OUT);
    
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
    
    while (1) {
        printf("Semáforo operando: Estado %d\n", estado);
        sleep_ms(1000);
    }
}
