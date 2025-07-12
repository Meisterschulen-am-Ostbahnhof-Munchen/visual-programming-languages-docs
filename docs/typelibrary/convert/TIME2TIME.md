# TIME2TIME

<img width="1174" height="182" alt="TIME2TIME" src="https://github.com/user-attachments/assets/6b1faea9-1bfb-41fc-988e-df69d382fbdb" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock TIME2TIME dient zur direkten Übertragung von TIME-Werten von einem Eingang zu einem Ausgang. Es handelt sich um einen einfachen Konverter, der keine Veränderung der Daten vornimmt, sondern lediglich den Wert weitergibt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Auslösendes Ereignis für die Ausführung des Funktionsblocks. Wird dieses Ereignis empfangen, wird der Algorithmus zur Übertragung des TIME-Wertes ausgeführt.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungsereignis, das nach erfolgreicher Ausführung des Algorithmus ausgelöst wird.

### **Daten-Eingänge**
- **IN** (TIME): Der Eingangswert vom Typ TIME, der an den Ausgang weitergegeben wird.

### **Daten-Ausgänge**
- **OUT** (TIME): Der Ausgangswert vom Typ TIME, der den Wert des Eingangs IN übernimmt.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock TIME2TIME überträgt den Wert des Eingangs IN unverändert an den Ausgang OUT, sobald das Ereignis REQ empfangen wird. Nach der Ausführung des Algorithmus wird das Ereignis CNF ausgelöst.

## Technische Besonderheiten
- Der Block führt keine Konvertierung oder Transformation der Daten durch.
- Die Ausführung erfolgt synchron mit dem Eingangsereignis REQ.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt direkt bei Empfang des REQ-Ereignisses.

## Anwendungsszenarien
- Weiterleitung von TIME-Werten ohne Modifikation.
- Einsatz in Systemen, wo eine explizite Übertragung von Zeitwerten erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konverter-Blöcken wie INT2TIME oder TIME2STRING übernimmt TIME2TIME keine Datentyp-Konvertierung, sondern dient lediglich der Weitergabe des Wertes.

## Fazit
Der TIME2TIME Funktionsblock ist ein einfaches und effizientes Mittel zur Weitergabe von TIME-Werten innerhalb eines 4diac-Systems. Seine Stärke liegt in der Einfachheit und direkten Ausführung ohne zusätzliche Verarbeitungsschritte.
