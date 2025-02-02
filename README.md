README - Tarefa de Interrupções e Controle de LEDs com RP2040 e BitDogLab

Vídeo de Funcionamento

https://youtu.be/7ZebJRyOZps


Enunciado
Para consolidar a compreensão dos conceitos relacionados ao uso de interrupções no microcontrolador RP2040 e explorar as funcionalidades da placa de desenvolvimento BitDogLab, propõe-se a seguinte tarefa prática.

Objetivos
Compreender o funcionamento e a aplicação de interrupções em microcontroladores.
Identificar e corrigir o fenômeno do bouncing em botões por meio de debouncing via software.
Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.
Fixar o estudo do uso de resistores de pull-up internos em botões de acionamento.
Desenvolver um projeto funcional que combine hardware e software.
Descrição do Projeto
Neste projeto, você deverá utilizar os seguintes componentes conectados à placa BitDogLab:

Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.
LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).
Botão A conectado à GPIO 5.
Botão B conectado à GPIO 6.
Funcionalidades do Projeto
LED Vermelho Pisca 5 vezes por segundo: O LED vermelho do LED RGB deve piscar continuamente com uma frequência de 5 Hz (5 vezes por segundo).
Incremento com Botão A: O botão A deve incrementar o número exibido na matriz de LEDs cada vez que for pressionado.
Decremento com Botão B: O botão B deve decrementar o número exibido na matriz de LEDs cada vez que for pressionado.
Efeitos Visuais com LEDs WS2812: Os LEDs WS2812 devem ser usados para criar efeitos visuais representando números de 0 a 9.
Formatação fixa: Cada número deve ser exibido na matriz em um formato fixo, como caracteres em estilo digital (ex.: segmentos iluminados que formem o número).
Alternativamente, é permitido utilizar um estilo criativo, desde que o número seja claramente identificável.
Requisitos do Projeto
Para o desenvolvimento, devem ser seguidos os seguintes requisitos:

Uso de interrupções: Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando rotinas de interrupção (IRQ).
Debouncing: É obrigatório implementar o tratamento do bouncing dos botões via software.
Controle de LEDs: O projeto deve incluir o uso de LEDs comuns e LEDs WS2812, demonstrando o domínio de diferentes tipos de controle.
Organização do código: O código deve estar bem estruturado e comentado para facilitar o entendimento.
Como Executar a Tarefa
Pré-requisitos
Hardware:

Placa BitDogLab com o microcontrolador RP2040.
Matriz 5x5 de LEDs WS2812 conectada à GPIO 7.
LED RGB conectado às GPIOs 11 (Vermelho), 12 (Verde) e 13 (Azul).
Botões conectados às GPIOs 5 (Botão A) e 6 (Botão B).
Software:

SDK do Raspberry Pi Pico (RP2040) configurado.
Ferramentas de desenvolvimento como o Visual Studio Code com a extensão para RP2040.
PIO (Programmable I/O) do RP2040 configurado para controle dos LEDs WS2812.
Passo a Passo para Execução
Configuração do Ambiente de Desenvolvimento:

Instale o SDK do Raspberry Pi Pico.
Configure o Visual Studio Code com a extensão para o RP2040.
Conecte a placa BitDogLab ao computador via USB.
Compilação do Código:

Abra o código fornecido no Visual Studio Code.
Compile o código utilizando o compilador do RP2040 (arm-none-eabi-gcc).
Se não houver erros, o código será gerado no formato .uf2 para a placa.
Carregamento do Código na Placa:

Conecte a placa BitDogLab ao computador em modo de boot (pressione o botão BOOTSEL enquanto conecta a placa via USB).
Copie o arquivo .uf2 compilado para a unidade de armazenamento da placa (após o carregamento, a placa reiniciará automaticamente).
Execução e Testes:

Após a execução, o LED vermelho deve começar a piscar a uma taxa de 5 Hz.
Pressione o Botão A para incrementar o número exibido na matriz de LEDs.
Pressione o Botão B para decrementar o número exibido.
O número de 0 a 9 será exibido na matriz de LEDs WS2812, cada um representado de maneira visual clara.
Depuração e Ajustes:

Utilize a funcionalidade de debugging do Visual Studio Code para monitorar e ajustar qualquer comportamento inesperado.
Certifique-se de que as interrupções para os botões estejam funcionando corretamente e que o debouncing esteja implementado via software para evitar múltiplos registros de uma única pressão.
