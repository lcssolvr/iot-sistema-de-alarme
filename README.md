Pode se executar o projeto no link abaixo:
[Wokwi - Projeto Alarme by Lucas Oliveira](https://wokwi.com/projects/424809797562574849)


# Enunciado

## Objetivo: Desenvolver um sistema de alarme

Desenvolver um sistema de alarme central utilizando uma placa Arduino, 2 sensores de movimento e 2 sensores de
portas/janelas, um display LCD I2C, LEDs e um buzzer. O sistema deve permitir
monitorar o status de um alarme, detectar movimento e violações, e fornecer sinais
sonoros e visuais em caso de eventos.


## Descrição da Atividade:

- Você deve criar um sistema de alarme central que possa ser armado e desarmado por meio de
botões. O sistema deve monitorar sensores de movimento e sensores de
portas/janelas para detectar quaisquer violações de segurança. As seguintes
funcionalidades devem ser implementadas:


- Armar e Desarmar o Alarme:
Um botão deve permitir
armar o sistema de alarme. Quando armado, o alarme estará ativo e o
sistema monitorará os sensores.
Outro botão deve permitir
desarmar o sistema de alarme. Quando desarmado, o sistema não monitorará
os sensores e os LEDs de alarme devem estar apagados.

- Detecção de Movimento e
Violação:
O sistema deve utilizar
dois sensores PIR (Passive Infrared) para detectar movimento em
diferentes áreas.
O sistema deve utilizar
dois sensores magnéticos para monitorar portas/janelas.
Se qualquer sensor detectar
movimento ou violação, um LED deve acender e o buzzer deve emitir um som
para indicar a situação.

- Display LCD I2C:
Um display LCD deve ser
usado para mostrar o status atual do sistema de alarme.
O display deve indicar se o
sistema está armado ou desarmado.
O display deve mostrar
mensagens sobre a detecção de movimento ou violação.

- Buzzer:
Um buzzer deve ser
adicionado ao sistema. Quando o alarme estiver ativado e um movimento ou
violação for detectado, o buzzer deve emitir um som contínuo.
O buzzer também deve tocar
um som de emergência quando o botão de emergência for pressionado.

- Botão de Emergência:
Um botão de emergência deve
ser incluído. Quando pressionado, o sistema deve acionar o buzzer e o LED
de violação, e exibir uma mensagem de emergência no display LCD por 5
segundos.

- O sistema deve permitir que o alarme seja armado ou desarmado usando uma senha numérica de 4 dígitos.
A senha deve ser inserida usando um conjunto de botões, onde cada botão representa um dígito (0 a 9).
Após a inserção da senha, o sistema deve verificar se a senha está correta antes de armar ou desarmar o alarme.
