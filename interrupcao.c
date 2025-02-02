#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "interrupcao.pio.h"

// Definições dos pinos e número de pixels
#define NUM_PIXELS 25  // Número de LEDs na matriz
#define OUT_PIN 7      // Pino para controle dos LEDs WS2812
#define LED_VERDE 11   // Pino do LED verde (não utilizado no código, mas definido)
#define LED_AZUL 12    // Pino do LED azul (não utilizado no código, mas definido)
#define LED_VERMELHO 13 // Pino do LED vermelho
#define BOTAO_A 5      // Pino do Botão A (incrementa o número)
#define BOTAO_B 6      // Pino do Botão B (decrementa o número)

// Função que converte valores RGB para o formato adequado para o controle dos LEDs WS2812
uint32_t matrix_rgb(double r, double g, double b) {
    unsigned char R = r * 255;  // Convertendo o valor de 'r' para o intervalo de 0 a 255
    unsigned char G = g * 255;  // Convertendo o valor de 'g' para o intervalo de 0 a 255
    unsigned char B = b * 255;  // Convertendo o valor de 'b' para o intervalo de 0 a 255
    return (G << 24) | (R << 16) | (B << 8); // Retorna o valor no formato G, R, B (32 bits)
}

// Função para exibir um número na matriz de LEDs 5x5
void mostrar_numero(int num, PIO pio, uint sm) {
    // Matrizes representando os números de 0 a 9 em uma matriz 5x5
    static double numeros[10][25] = {
        // Definição dos números de 0 a 9 usando uma matriz de 5x5
        // Cada número é representado por 25 elementos (5 linhas e 5 colunas)
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1}, // 0
        {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}, // 1
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1}, // 2
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}, // 3
        {1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, // 4
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, // 5
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1}, // 8
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1}  // 9
    };
    // Loop para exibir o número na matriz de LEDs, passando os valores RGB de cada LED
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, matrix_rgb(numeros[num][24 - i], 0, 0));
    }
}

int main() {
    stdio_init_all();  // Inicializa o sistema de entrada/saída padrão (para depuração)
    
    // Inicializa o LED vermelho
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    
    // Inicializa o Botão A com resistor de pull-up
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    
    // Inicializa o Botão B com resistor de pull-up
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);
    
    // Inicializa o PIO para controlar os LEDs WS2812
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &interrupcao_program);
    uint sm = pio_claim_unused_sm(pio, true);
    interrupcao_program_init(pio, sm, offset, OUT_PIN);
    
    int contador = 0;  // Variável para controlar o número exibido na matriz
    bool estado_led = false;  // Estado do LED vermelho (alternando a cada ciclo)
    
    // Loop principal
    while (true) {
        // Alterna o estado do LED vermelho (para efeito de piscada)
        estado_led = !estado_led;
        gpio_put(LED_VERMELHO, estado_led);
        
        // Verifica se o Botão A foi pressionado (para incrementar o número)
        if (!gpio_get(BOTAO_A)) {
            if (contador < 9) contador++;  // Incrementa o contador (até 9)
            mostrar_numero(contador, pio, sm);  // Atualiza a matriz de LEDs com o número
            sleep_ms(200);  // Delay para evitar múltiplos incrementos rápidos (debouncing)
        }
        
        // Verifica se o Botão B foi pressionado (para decrementar o número)
        if (!gpio_get(BOTAO_B)) {
            if (contador > 0) contador--;  // Decrementa o contador (até 0)
            mostrar_numero(contador, pio, sm);  // Atualiza a matriz de LEDs com o número
            sleep_ms(200);  // Delay para evitar múltiplos decrementos rápidos (debouncing)
        }
        
        sleep_ms(50);  // Delay de estabilização para o loop principal.
    }

    return 0;
}
