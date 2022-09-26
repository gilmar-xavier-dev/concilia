# concilia

Faz a conciliação entre arquivos texto, sem necessidade de carga ou de qualquer tratamento prévio nos arquivos.

Faz a conciliação baseada em chaves informadas por parâmetro na chamada do aplicativo.

Os arquivos podem ser com campos separados (CSV) por qualquer separador ou ainda arquivos de tamanho fixo.

Milhões de registros podem ser conciliados com uma excelente performance.

Desenvolvido para ser utilizado com três possíveis bancos de dados NoSql, bastando informar o BD desejado no momento da compilação, sendo:

`make bdb` - Utiliza *BERKELEYDB* para a indexação.

`make redis` - Utiliza *REDIS* para a indexação.

`make gbdm` - Utiliza *GBDM* para a indexação.

Use o formato:

`./concilia ARQUIVO|-stdin -k X.Y,Z [-k X.Y,Z] -in|-out [-debug] [-ign 999] [-sep S]`

Sendo:

   **ARQUIVO|-stdin** - Nome do arquivo de entrada, ou use -stdin para entrada manual ou via <
   
   **-k X.Y,Z** - informa a chave de conciliação (podem ser várias) X = Nro do campo (1 para registro fixo), Y = Posição inicial e Z = tamanho
   
   **-in|-out** - in para arquivo a indexar e out para arquivo a conciliar - Irá procurar os registros do arquivo out no arquivo in
   
   **-debug** - OPCIONAL - Mostra na tela as operações realizadas
   
   **-ign 000** - OPCIONAL - Ignora os primeiros 000 registros
   
   **-sep S** - OPCIONAL - Indica o caracter separador de campo, juntamente com o campo X do parâmetro -k
   
   
Exemplo:

   `./concilia arqent.txt -in  -k 1.11,18 -k 1.42,18 -k 1.76,6`
   
   `./concilia arqsai.txt -out -k 1.10,18 -k 1.41,18 -k 1.75,6`
   
   Os registros conciliados estarão em:

      *arqsai.txt-sim*
      
   Os registros **não** conciliados estarão em:
   
      *arqsai.txt-nao*
