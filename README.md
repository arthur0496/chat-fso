## Informações

Até o presente momento foram implementadas todas as funcionalidades requisitadas para o ponto de controle 1.
  - Listar usuários online
  - Enviar mensagem para outros usuários
  - Receber mensagens
  - Formatar as mensagens conforme o protocolo
  - Broadcast para todos usuários disponíveis
  - Bloqueio da saída com ^c(control+c)
  - Validações sobre tamanho do nome de usuário e tamanho das mensagens
  - O envio e recebimento das mensagens foram separados em threads
  - Mensagens de erro para envio de mensagens a usuários não existentes, e caso de falha no envio da mensagem

## Problemas conhecidos
- Caso o usuário insira como entrada comandos não implementados ou mensagens, o programa retorna a mensagem de erro destinada a usuário não encontrado
- Caso o usuário receba mensagens fora do formato definido (SENDER:RECEIVER:MESSAGE), ocorre falha de segmentação.

## Dificuldades
Houve uma certa dificuldade na implementação de threads, especialmente ao enviar múltiplos parâmetros e por tratar de strings, que se tratam de endereços de memória, tornando-se uma região crítica.

## Instruções para execução
Na pasta raiz do chat, basta executar os seguintes comandos
~~~~
make clean
make all
make run
~~~~
