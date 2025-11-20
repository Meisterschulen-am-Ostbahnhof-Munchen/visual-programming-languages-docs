### NVS\_UDINT

![NVS_UDINT](https://user-images.githubusercontent.com/116869307/214141938-76896e07-9f8c-482b-98be-9781ef2dc61d.png)

Typische Verwendung:

![image](https://user-images.githubusercontent.com/69573151/219948187-01299235-9e3e-4669-9171-a484f8b86fc1.png)

durch die Schaltung von INITO --> GET wird unmittelbar nach dem Init der Wert mit dem "Key" geladen, und steht an Ausgang VALUEO zur Verfügung. 

soll die Variable dann noch am Display angezeigt werden erweitert man das ganze so: 

![](https://user-images.githubusercontent.com/69573151/219948290-9e42dcfa-a3fb-4b06-a79d-66b7531be013.png)

dadurch ist sowohl die Eingabe als auch die Ausgabe; sowohl das Speichern wie auch das Laden der Variable abgedeckt. 

ACHTUNG !!

[https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html)

die Länge des Keys muss den Anforderungen der o.g. Library entsprechen. 

z.B. 

> the maximum key length is currently 15 characters
