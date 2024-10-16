# Pêndulo de Newton
Este projeto foi feito para fins acadêmicos. 

Consiste na modelagem e animação de um Pêndulo de Newton, utilizando a API OpenGL.

## Instalação
Certifique-se de ter o OpenGL e o OpenGL Utility Toolkit (GLUT) instalados.

Para sistemas UNIX, use o seguinte comando no terminal:

`sudo apt-get install freeglut3-dev mesa-utils libxmu-dev libxi-dev`

Em seguida, clone ou faça o download deste repositório. 

## Execução

O projeto conta com um arquivo Makefile para facilitar a compilação do arquivo alvo com as devidas dependências e sua execução.

No diretório onde o repositório foi salvo, abra o terminal e digite os seguintes comandos:

Para compilar o arquivo:
   
  `make`

Para executar o arquivo:

  `make out`

*Observação: caso não consiga compilar o arquivo, tente limpar o arquivo executável antes.*

Para limpar o arquivo executável:

  `make clean`

## Aplicação

Você pode interagir com a animação utilizando as setas direcionais no teclado para rotacionar o pêndulo.

Ainda, ao clicar com o botão direito do mouse, é possível selecionar a quantidade de esferas no pêndulo.

![Erro na imagem](https://i.imgur.com/wAF43Mi.png)